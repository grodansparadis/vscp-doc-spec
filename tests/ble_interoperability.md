# VSCP BLE interoperability and conformance tests

This document is a companion to [VSCP over BLE](../vscp_over_bt_ble.md). **All E1/A2/G1 encodings are draft proposals**; the vectors here freeze their current byte layouts for review, not production ratification.

## 1. Test-only values and prerequisites

All examples use the **test-only** Bluetooth Company Identifier `0xFFFF` (encoded `FF FF`); it MUST NOT be used in production. The canonical GUID is `00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F`. Multioctet VSCP fields are big-endian. A test harness MUST distinguish complete advertising data sets from Link Layer PDUs and MUST reject truncated host reports.

## 2. Byte-exact E1 examples

**E1, no data, sequence 0:** 34-byte AD structure, Length `0x21`.

```text
21 FF FF FF 01 00 00 00 00 00
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00 00 00 00 00 00 00 00
```

**E1, 2 data octets, sequence 1:** 36-byte AD structure, Length `0x23`.

```text
23 FF FF FF 01 00 00 00 00 01
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00 00 00 0A 00 06 00 02 11 22
```

**E1 maximum:** `N=222`, AD Length `0xFF`, total AD structure 256 octets. Test with `data[i]=i mod 256`, `0≤i<222`; verify the controller supports at least 256 advertising data octets. An E1 event with `N=223` MUST be rejected.

## 3. Byte-exact AES-128-CCM A2 vector

This is a **reproducible deterministic test vector** for the draft A2 algorithm, not a claim of external certification. Independently verify against a second CCM implementation before ratification.

| Parameter | Hex / value |
| --- | --- |
| AES key | `000102030405060708090a0b0c0d0e0f` |
| Nonce prefix (provisioned) | `a0a1a2a3a4` |
| Epoch | `00000001` |
| Sequence | `00000002` |
| Nonce (13 octets) | `a0a1a2a3a40000000100000002` |
| Company ID | `ffff` (test only) |
| Version / flags | `02 01` |
| Key ID | `0001` |
| GUID | `000102030405060708090a0b0c0d0e0f` |
| Head / class / type / N | `0000 000a 0006 0003` |
| Plaintext | `112233` |
| Ciphertext | `3c4532` |
| Authentication tag (16 octets) | `039788b44a4ad321c6493748c0f6c4d1` |

AAD is the 11 ASCII octets `VSCP-BLE-A2` followed by the 38-octet AD Data header (Company Identifier through N):

```text
565343502d424c452d4132
ffff020100010000000100000002
000102030405060708090a0b0c0d0e0f
0000000a00060003
```

**Complete 59-octet A2 AD structure** (AD Length `0x3A`):

```text
3a ff ffff020100010000000100000002
000102030405060708090a0b0c0d0e0f
0000000a00060003
3c4532 039788b44a4ad321c6493748c0f6c4d1
```

Changing any AAD byte, ciphertext byte, tag byte, nonce component or key MUST cause authentication failure. Test `N=0` and `N=200` separately with the same algorithm and fresh nonces; never reuse a nonce for different messages in a deployed sender.

## 4. Negative parsing and security cases

| Test | Input mutation | Required outcome |
| --- | --- | --- |
| E1 wrong AD Length | `0x23 → 0x22` | Reject |
| E1 unknown version | `0x01 → 0x03` | Reject, no L0 fallback |
| E1 reserved flags | `0x00 → 0x80` | Reject |
| E1 zero GUID | Replace 16 GUID octets with zeros | Reject |
| E1 inconsistent N | Declared `N=3`, two data bytes | Reject |
| E1 duplicated candidate | Two E1 structures for same configured Company ID | Reject as ambiguous |
| E1 truncated host report | Report data status incomplete | Do not deliver |
| A2 invalid tag | Flip last tag bit | Reject; replay state unchanged |
| A2 tampered header | Flip class/type/GUID byte | Reject authentication |
| A2 unknown/revoked key | Key ID not provisioned | Reject |
| A2 repeated sequence | Resubmit identical authenticated frame | Reject as replay |
| A2 stale epoch | Previously accepted newer epoch | Reject |
| A2 reserved flags | `0x01 → 0x03` | Reject |
| A2 malformed length | Wrong `0x3A` or `N` | Reject |
| Downgrade | A2 auth fails, try E1 for privileged event | Reject |
| G1 fragment overlap | Reuse prior offset | Reject and clear reassembly |
| G1 missing LAST | Timeout after partial record | Discard |
| G1 unpaired write | Event RX Write Request without required security | ATT access error |
| G1 unsupported HELLO | Unsupported G1 version | `UNSUPPORTED_VERSION` |
| G1 disconnect | Disconnect during reassembly | Discard partial record |

Fuzz the AD parser with zero lengths, boundary lengths (31/32/254/255), random truncations, nested-looking bytes, duplicate structures and arbitrary byte strings. Use address/memory sanitizers where supported. No malformed input may cause an out-of-bounds access, unbounded allocation or event delivery.

## 5. Cross-platform interoperability matrix

| Environment | Transmit / receive scenarios | Expected checks |
| --- | --- | --- |
| Linux BlueZ with supported controller | L0/E1/A2 active/passive extended scan; G1 client/server | Complete report status, controller limits, ATT MTU 23 and larger, CCCD/HELLO, security |
| Windows with compatible BLE adapter/API | Receive L0/E1/A2 where extended advertisement reports are exposed; G1 | API support detection, truncated reports, pairing and service discovery |
| macOS CoreBluetooth | G1 discovery, notifications, writes; legacy discovery | Platform restrictions on raw manufacturer/extended advertising, address privacy, GATT security |
| Android with BLE 5 extended-advertising support | E1/A2 advertising and scanning; G1 | `isLeExtendedAdvertisingSupported`, max data length, PHY support, scan result data status |
| iOS CoreBluetooth | G1 and platform-exposed advertising discovery | No assumption of raw HCI access, arbitrary extended advertising transmission or complete manufacturer reports |
| Embedded Zephyr / Nordic / ESP-IDF (supported SoCs) | E1/A2 transmit/receive; G1 peripheral | Feature checks, set allocation, data length, PHY, reboot/replay persistence |
| Independent implementation pair | Cross-vendor E1/A2/G1 exchange | Byte-for-byte vectors, endianness, permissions, replay, reconnect |

**Capability-dependent tests must be marked SKIP with the specific unsupported feature**, not PASS. Record OS/stack version, controller model/firmware, primary/secondary PHY, maximum advertising data length, maximum advertising sets, ATT MTU, and observed complete/truncated status. No platform is presumed to support extended advertising merely because it reports Bluetooth 5.

## 6. Suggested acceptance criteria

Two independent implementations MUST agree on E1 and A2 byte layout, AES-CCM ciphertext/tag, identity handling and validation. A2 MUST fail closed on replay and failed authentication. G1 MUST pass fragmentation, authorization and error-handling tests at ATT MTU 23 and at least one larger MTU. Optional PHY/platform cases MAY be skipped with documented evidence; baseline profile claims require actual end-to-end tests.

