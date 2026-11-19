# VSCP over Bluetooth Low Energy (BLE)

> **Status: proposed revision for review.** The legacy version 0 encoding is documented for compatibility. The version 1 encoding, UUID allocation, and security profile in this document are proposals, not registered or deployed interoperability standards. Do not claim conformance to version 1 until these parameters are ratified.

## 1. Scope

VSCP over BLE transports VSCP events using (a) legacy advertising, (b) Bluetooth 5 extended advertising, and (c) connected GATT communication. Advertising is connectionless and provides **no delivery guarantee**. GATT offers bidirectional transfer but does not by itself guarantee application processing. Implementations MUST distinguish the VSCP application event from the BLE advertising data (AD) structure and the link-layer PDU.

Bluetooth LE 5.0 extended advertising is an **optional controller/host capability**: a Bluetooth 5 version number alone does not establish support. LE 2M and LE Coded PHY are separate optional features. Legacy advertising data is limited to 31 octets; extended advertising can use a chain of PDUs, with an advertising data set of up to 1650 octets where supported. A 255-octet extended advertising PDU payload is **not** equivalent to 255 octets of VSCP data.

![Bluetooth advertising illustration](./images/ble-advertising-pdu.png)

## 2. Transport profiles

| Profile | BLE mechanism | Intended use | Security |
| --- | --- | --- | --- |
| L0 (legacy) | Legacy advertising, optionally scan response | Compatibility with deployed nodes | Legacy limitations apply |
| E1 (proposed) | Extended advertising, optionally periodic advertising in a future extension | Connectionless measurements, alarms, discovery | Open or authenticated/encrypted |
| G1 (proposed) | Connected GATT service | Configuration, event exchange, register access | Authenticated provisioning and protected writes |

An implementation MAY support several profiles. A receiver MUST NOT interpret an unknown frame version as version 0. Security policy MUST be enforced independently of which profiles a device advertises.

## 3. Bluetooth advertising fundamentals

Advertising data is a series of AD structures: **Length (1 octet), AD Type (1 octet), AD Data (Length - 1 octets)**. Manufacturer Specific Data uses AD Type `0xFF` and begins with a **Bluetooth SIG-assigned Company Identifier**, encoded little-endian. `0xFFFF` is reserved for testing and MUST NOT be used as a production company identifier.

Legacy advertising supports at most 31 octets of advertising data and, separately, up to 31 octets of scan-response data. The legacy `ADV_IND` advertising event is connectable and scannable. A scan request is a BLE link-layer operation; it does **not** contain arbitrary VSCP request payload or a VSCP timestamp. A scan response is not guaranteed to arrive, is not bound transactionally to an individual VSCP event, and MUST NOT be treated as reliable delivery.

### 3.1 Bluetooth 5 extended advertising: PDU size versus advertising data set

Bluetooth 5.0 introduced **LE Advertising Extensions**. This is a feature of the controller and host stack, not a guarantee implied merely by a Bluetooth version label. Extended advertising uses a primary-channel `ADV_EXT_IND` PDU (on advertising channels 37–39) that can point via `AuxPtr` to a secondary-channel `AUX_ADV_IND` PDU (on channels 0–36). Further `AUX_CHAIN_IND` PDUs can carry additional advertising data. The Link Layer/controller handles this PDU chaining; it is **not** VSCP application-level fragmentation.

```text
Primary advertising channel (37, 38, 39)
    ADV_EXT_IND
       |
       | AuxPtr
       v
Secondary advertising channel (0–36)
    AUX_ADV_IND  -->  AUX_CHAIN_IND  -->  AUX_CHAIN_IND ...
         advertising data set, split by controller as needed
```

**Three different limits MUST NOT be confused:**

| Quantity | Limit | What it actually limits |
| --- | ---: | --- |
| Legacy advertising data | 31 octets | Total host AD data in a legacy advertisement |
| Extended advertising physical-channel PDU payload | Up to 255 octets | Includes the extended advertising header and optional fields; **not** 255 octets of application data |
| Extended advertising data set | Up to 1,650 octets | Total host advertising data across controller-managed auxiliary PDU chains, **if supported by the controller and configuration** |

The amount of advertising data in any one auxiliary PDU is less than the maximum PDU payload when extended-header fields are present. The exact available amount varies with the PDU type and included fields. An AD structure may cross a PDU boundary; the receiver processes the reconstructed advertising data set rather than assuming one AD structure per PDU.

### 3.2 Actual controller and host limits

**1,650 octets is a specification ceiling, not a guaranteed minimum.** A compliant implementation may support a shorter advertising data set. On controllers exposing the standard HCI interface, the host SHOULD check:

- `LE Read Local Supported Features` for LE Advertising Extensions.
- `LE Read Maximum Advertising Data Length` (HCI OCF `0x003A`): reports `Max_Advertising_Data_Length`, in the defined range **31–1,650 octets**.
- `LE Read Number of Supported Advertising Sets` (HCI OCF `0x003B`): reports available advertising sets; available capacity can change as controller resources are allocated.

The host MUST also check whether the operating-system BLE API and controller firmware expose extended advertising, and whether the receiver can obtain complete extended advertising reports. A controller's advertised maximum is **not** a promise that every combination of advertising interval, PHY, event duration, advertising mode, and concurrent sets can transmit that much data. A controller may reject parameters or data with an error such as `Packet Too Long (0x45)`. Applications SHOULD handle these errors and fall back to a shorter data set or a different VSCP transport.

The HCI `LE Set Extended Advertising Data` command accepts **at most 251 advertising-data octets per HCI command**, with first/intermediate/last/complete operation values for assembling a larger data set in the controller. This **251-octet HCI transfer limit** is distinct from the 255-octet on-air PDU payload limit and the 1,650-octet advertising data-set limit.

Extended scanning implementations may also have smaller receive/report buffers or may deliver incomplete/truncated reports. A VSCP receiver MUST reject truncated AD structures or incomplete VSCP frames rather than treating them as valid events.

### 3.3 Advertising modes and PHYs

Extended advertising supports distinct **non-connectable**, **scannable**, and **connectable** configurations, subject to Bluetooth Link Layer restrictions. Unlike legacy `ADV_IND`, extended advertising does **not** generally combine connectable and scannable properties in one advertising set. In particular, a scannable extended advertising set carries its host data in the extended scan response, not ordinary advertising data; VSCP E1 senders SHOULD use a **non-connectable, non-scannable extended advertising set** for standalone broadcast events unless a separately specified profile requires otherwise.

The primary `ADV_EXT_IND` may use LE 1M or LE Coded PHY where supported; secondary advertising may use LE 1M, LE 2M, or LE Coded PHY where supported. LE 2M, LE Coded (S=2/S=8), and periodic advertising are **separate optional capabilities** and MUST NOT be inferred from the presence of Bluetooth 5 or extended advertising alone.

### 3.4 Implications for VSCP

VSCP E1 events SHOULD be self-contained within a complete, correctly reconstructed advertising data set. The current proposed E1 format uses **one Manufacturer Specific Data AD structure**, which is constrained by the **one-octet AD Length field** even if the controller supports a 1,650-octet data set. In that format, the manufacturer AD structure can hold at most 254 octets of AD Data, of which 32 are the proposed E1 header, leaving **222 octets of VSCP event data** in an unencrypted E1 frame. This is a **format limit**, not a Bluetooth 5 PDU limit.

Supporting larger VSCP events would require a new, explicitly specified encoding (for example multiple AD structures or application-level fragmentation), with length validation, identity, reassembly limits, and security rules. Controller-managed PDU chaining alone does not remove the AD-structure length limit or guarantee delivery. A connected VSCP transport SHOULD be preferred when larger payloads, bidirectional transfer, or reliable application-level handling are needed.

### 3.5 References

- [Bluetooth SIG: Bluetooth LE primer, legacy versus extended advertising](https://www.bluetooth.com/bluetooth-le-primer/)
- [Bluetooth Core Specification: HCI LE Read Maximum Advertising Data Length and LE Set Extended Advertising Data](https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Core-62/out/en/host-controller-interface/host-controller-interface-functional-specification.html)
- [Bluetooth Core Specification: Link Layer advertising PDU payloads and auxiliary chaining](https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Core-60/out/en/low-energy-controller/link-layer-specification.html)

## 4. Legacy advertising (L0, version 0)

### 4.1 Explicit proposed legacy AD layout

**Compatibility status:** The previous specification described a 16-octet VSCP block, a Company Identifier and flags but did not unambiguously place all fields in the on-air AD structure. The following is a **proposed canonical layout for new L0 implementations**, not a verified claim about every deployed legacy device. Existing firmware and captured advertisements MUST be checked before this layout is declared historically interoperable.

The VSCP data is carried in a Manufacturer Specific Data AD structure (AD Type `0xFF`). Offsets below are measured from the **first byte of this AD structure**, not from the link-layer PDU:

| Offset | Field | Octets | Encoding / value |
| ---: | --- | ---: | --- |
| 0 | AD Length | 1 | `0x14` (20 following octets, including AD Type) |
| 1 | AD Type | 1 | `0xFF` (Manufacturer Specific Data) |
| 2–3 | Company Identifier | 2 | Bluetooth SIG assigned identifier, little-endian |
| 4 | VSCP flags | 1 | Version/encryption bit field, see §4.2 |
| 5–6 | Node ID | 2 | Proposed network byte order (big-endian) |
| 7 | VSCP head | 1 | Low eight bits of VSCP header |
| 8–9 | VSCP class | 2 | Proposed network byte order (big-endian) |
| 10–11 | VSCP type | 2 | Proposed network byte order (big-endian) |
| 12 | Data length | 1 | 0–8 for self-contained advertisement |
| 13–20 | VSCP data | 8 | Event bytes followed by zero padding |

Total: **21 octets** for this AD structure; the VSCP block at offsets 5–20 is exactly **16 octets**. The Company Identifier and flags are **not** part of the encrypted block. When encryption flag bit 7 is set, bytes 5–20 are a single encrypted 16-octet block, and their subfields are interpreted **only after decryption**. This preserves the historical 16-octet encryption-block concept without claiming AES-ECB is secure.

The proposed byte order for the Node ID, class and type is big-endian. The historical text did not specify this byte order explicitly; interoperability with existing firmware MUST be verified before treating it as an established legacy rule.

### 4.2 Flags

| Bit(s) | Meaning |
| --- | --- |
| 0–3 | Frame version; **0** for L0 |
| 4–6 | Reserved; sender MUST set to zero, receiver MUST reject nonzero values under this proposed canonical layout |
| 7 | Encrypted block if 1; plaintext block if 0 |

The frame flags occupy offset 4 in the proposed layout. An L0 receiver MUST NOT mistake this byte for a VSCP header.

### 4.3 AD structure sizing and optional device name

A legacy advertising data set has a maximum of **31 octets**. The manufacturer-specific AD structure above uses 21, leaving **10 octets** for other AD structures. For example, the standard Flags AD structure `02 01 06` uses 3 octets, leaving 7 octets; a Complete Local Name AD structure then has at most 5 name bytes (`Length + Type + 5 bytes`). A longer name MAY instead be placed in scan-response data if supported, or omitted.

**Do not confuse** the standard Bluetooth Flags AD Type `0x01` with the **VSCP flags byte** at offset 4. The old draft's statement that the advertising format was “max 32 bytes” is corrected to **31 advertising data octets**. The name AD Type is `0x09` for Complete Local Name or `0x08` for Shortened Local Name, not the old draft's value 6.

### 4.4 Byte-exact illustrative example (plaintext)

Test-only Company Identifier `0xFFFF`; version 0; no encryption; node ID `0x1234`; head `0x10`; class `0x000A`; type `0x0006`; two data octets `AA BB`:

```text
02 01 06                                  # Standard Bluetooth Flags AD structure
14 FF FF FF 00 12 34 10 00 0A 00 06 02 AA BB 00 00 00 00 00 00
|  |  |     |  |     |  |     |     |  |-----------------------|
|  |  |     |  |     |  |     |     |        8 data octets
|  |  |     |  |     |  |     |     data length = 2
|  |  |     |  |     |  |     type = 0x0006
|  |  |     |  |     |  class = 0x000A
|  |  |     |  |     head = 0x10
|  |  |     |  node ID = 0x1234
|  |  |     VSCP flags = 0x00
|  |  Company ID = 0xFFFF (test only, little-endian)
|  AD Type = 0xFF
AD Length = 0x14
```

The manufacturer AD structure is 21 octets, plus 3 octets for the standard Flags AD structure: **24 of the permitted 31 advertising data octets**. The VSCP block is 16 octets. This is a framing test, not a validated VSCP application-event example. `0xFFFF` MUST NOT be used as a production Company Identifier.

### 4.5 GUID construction

The original legacy GUID derivation is `FF:FF:FF:FF:FF:FF:FF:F8:YY:YY:YY:YY:YY:YY:XX:XX`, where `YY` is the BLE address and `XX` is the node ID. The receiver sets `obid` and timestamps as appropriate. This derived GUID is not stable with BLE private-address rotation.

### 4.6 Legacy scan request and scan response

#### 4.6.1 Standard BLE operation

For a legacy **scannable** advertiser, a scanner performing **active scanning** may initiate the following Link Layer exchange:

```text
Advertiser                                 Active scanner
    |                                             |
    | -------- ADV_IND (advertising data) ------> |
    | <------- SCAN_REQ (scanner, advertiser) --- |
    | -------- SCAN_RSP (scan-response data) ---> |
    |                                             |
```

The diagram illustrates the normal legacy active-scan exchange, not a guaranteed application transaction. A scanner performing **passive scanning** does not transmit `SCAN_REQ` and therefore does not solicit `SCAN_RSP`. Whether active scanning is supported or permitted can depend on the host, controller, advertising mode, scanning configuration, filtering, and platform APIs.

A legacy `SCAN_REQ` is a Bluetooth Link Layer control PDU containing scanner and advertiser address information. It is **not** a VSCP request, and it has no application-defined timestamp, VSCP class, VSCP type, or arbitrary data field. An application cannot place VSCP commands or additional event bytes inside a standard `SCAN_REQ`.

The advertiser's `SCAN_RSP` carries a separately configured **scan-response advertising data set**, consisting of standard AD structures. For legacy advertising its maximum size is **31 octets**, independent of the maximum 31-octet advertising data set. It is not a response payload dynamically assembled from fields in the scan request. Implementations MUST distinguish these AD data sets from the Bluetooth Link Layer packet headers.

#### 4.6.2 Limitations for extending VSCP events

The earlier VSCP draft suggested carrying a 4-octet timestamp and 16 additional VSCP data octets in the scan response when the advertised event's data length is 9–24. That text did not specify the required AD Length, AD Type, Company Identifier, byte ordering, timestamp reference, encryption handling, or binding of the continuation to a particular event. **Those 20 bytes are not a complete BLE scan-response wire format.**

Even when a `SCAN_RSP` is received, the scanner may have missed the associated advertisement, or the advertiser may have changed its event data between advertising and scanning. A scanner may also receive an advertisement without its scan response. Bluetooth does not provide a VSCP event identifier, transaction ID, or atomic snapshot across the two AD data sets.

Therefore:

1. New L0 senders **SHOULD** transmit self-contained events with data lengths **0–8**.
2. New receivers **MUST NOT** reconstruct a 9–24-byte VSCP event merely by concatenating an arbitrary scan response with an advertisement.
3. A receiver **MUST NOT** report a partial extended event as a valid complete VSCP event.
4. A receiver **MUST NOT** treat a scan response as an acknowledgment of receipt or processing.
5. A receiver **MUST NOT** assume a scan response is available through passive scanning or every platform's scanning API.
6. Any deployed legacy continuation scheme **MAY** be supported in an explicitly documented compatibility mode, with verified AD framing, matching rules, and timeouts. It MUST NOT be claimed as interoperable solely from the original draft.
7. New transports needing more than eight VSCP data octets **SHOULD** use the E1 extended-advertising profile (within its limits) or a connected transport once standardized.

#### 4.6.3 Compatibility-mode requirements for a historical 9–24-byte extension

If an implementation must receive an existing continuation format, its documentation MUST identify the actual on-air AD structures and offsets, timestamp encoding and units, encryption scheme, and how the 16-octet continuation relates to the primary event. The receiver SHOULD impose a short, bounded association window and reject mismatched, missing, duplicated, stale, or ambiguous continuations. A matching Bluetooth advertiser address alone is insufficient to prove that two data sets belong to the same VSCP event.

A newly standardized continuation format would require a common event identifier or sequence counter in **both** AD data sets, authenticated binding where security is required, and a complete byte-level definition. Such a format is **not defined in L0** by this revision.

#### 4.6.4 Practical receiver behavior

A passive scanner can decode complete 0–8-byte L0 events without waiting for scan responses. An active scanner MAY receive scan-response AD structures for discovery information such as a shortened/complete local name, but that information MUST NOT be interpreted as VSCP event continuation unless a separately verified compatibility format is enabled. Incomplete, malformed, or unsupported legacy extended events SHOULD be counted or logged for diagnostics without delivering them to the VSCP application layer.

### 4.7 Legacy security

AES-128 ECB, when used by historical devices, provides neither event authentication nor replay protection. L0 encrypted frames MUST NOT authorize access control or other privileged operations solely on that basis. Do not infer authentication from the encryption flag.

### Legacy connected devices

The former document lists Name (11 bytes), Key (16 bytes), and Period (1 byte) characteristics without UUIDs, properties, access permissions, or framing. These are **historical descriptions only**, not a complete GATT profile. A generic writable plaintext Key characteristic MUST NOT be introduced in new implementations.

## 5. Proposed extended advertising profile E1 — frame version 1

> **Status:** This section defines a complete **cleartext E1 version 1 wire format** for technical review and interoperability testing. It is a proposed format, not a deployed standard. Authenticated/encrypted E1 frames are **not defined** here and MUST NOT be transmitted under version 1 until a separate extension is ratified.

### 5.1 Encapsulation and byte order

E1 version 1 carries **exactly one complete VSCP event** in **one Manufacturer Specific Data AD structure** (AD Type `0xFF`). The structure can be transmitted using a controller-supported extended advertising data set; controller-managed `AUX_CHAIN_IND` PDU chaining does not change the E1 bytes. No E1 application-level fragmentation, multiple-event packing, or continuation via scan response is defined.

All offsets in §5.2 are measured from the **first octet of the AD structure** (the AD Length octet). All multi-octet VSCP and sequence fields are **unsigned big-endian** (most-significant octet first). The Bluetooth Company Identifier is **little-endian**, as required by the Bluetooth AD format. A GUID is exactly 16 octets in canonical VSCP byte order; it is not a character string or a BLE address.

The Company Identifier is a Bluetooth SIG-assigned identifier selected for this transport deployment. **No globally assigned VSCP Company Identifier is specified by this proposal.** `0xFFFF` MAY be used only in isolated test fixtures and MUST NOT be transmitted in production. A production deployment MUST document the actual assigned identifier used and receivers MUST filter by that identifier before interpreting E1 fields.

### 5.2 Byte-exact AD structure

| Offset | Field | Octets | Encoding / validation |
| ---: | --- | ---: | --- |
| 0 | AD Length | 1 | `0x21 + N` (33 + N); counts all following octets, including AD Type |
| 1 | AD Type | 1 | `0xFF` (Manufacturer Specific Data) |
| 2–3 | Company Identifier | 2 | Bluetooth SIG assigned identifier, **little-endian** |
| 4 | Frame version | 1 | Exactly `0x01` |
| 5 | Flags | 1 | Exactly `0x00` for this cleartext version; see §5.3 |
| 6–9 | Sequence number | 4 | Unsigned 32-bit integer, **big-endian** |
| 10–25 | Sender GUID | 16 | Stable canonical VSCP GUID |
| 26–27 | VSCP head | 2 | Unsigned 16-bit header, **big-endian** |
| 28–29 | VSCP class | 2 | Unsigned 16-bit class, **big-endian** |
| 30–31 | VSCP type | 2 | Unsigned 16-bit type, **big-endian** |
| 32–33 | VSCP data length | 2 | Unsigned 16-bit `N`, **big-endian** |
| 34–(33+N) | VSCP event data | N | Exactly `N` octets, unpadded |

The complete AD structure occupies **34 + N octets**. The AD Length field is **33 + N**, and the Manufacturer Specific AD Data occupies **32 + N octets**. Since the one-octet AD Length field cannot exceed 255, **0 ≤ N ≤ 222**. Other AD structures, if present, consume additional advertising data-set capacity. Senders MUST also respect the controller's actual supported advertising data-set length. No implicit null terminator, checksum, padding, or trailing bytes are permitted **inside this AD structure**.

### 5.3 Flags and reserved bits

| Flag bit | Definition for version 1 |
| --- | --- |
| 0 | Reserved for a future authenticated-encryption envelope; MUST be zero |
| 1–7 | Reserved; MUST be zero |

Thus, the only valid flags octet for this proposal is `0x00`. A receiver MUST reject a version 1 AD structure with any flags bit set. A receiver MUST NOT assume that bit 0 identifies a supported cipher or attempt to interpret encrypted bytes as a cleartext event. Future formats MUST define their envelope and compatibility rules explicitly; reserved bits are not available for vendor-specific meanings.

The VSCP head is **not** the E1 flags octet. Its bit definitions and valid combinations remain those of the applicable VSCP event specification. A receiver MUST validate VSCP head/class/type/data semantics at the VSCP application layer, after structural decoding.

### 5.4 Sender identity

The Sender GUID identifies the VSCP node that originated the event, not the BLE scanner or gateway. It MUST remain stable across ordinary reboots and BLE private-address rotation. A sender MUST NOT derive the E1 GUID solely from its current BLE MAC address. A gateway MUST preserve the sender GUID when forwarding the event; it MAY separately record the observed BLE address as transport metadata. A receiver MUST NOT replace the on-wire GUID with a reconstructed MAC-derived GUID.

An all-zero GUID is **invalid in this proposed E1 profile** and MUST be rejected. Provisioning MUST ensure GUID uniqueness within the intended VSCP network. Since E1 cleartext is unauthenticated, a GUID is an **asserted identity**, not cryptographic proof of origin; receivers MUST NOT use it alone to authorize privileged actions.

### 5.5 Sequence numbering and duplicate handling

The sequence number is a 32-bit **unsigned** counter, scoped to one stable Sender GUID and E1 version 1 frame stream, across all event classes and types. The sender MUST assign a new value to each newly constructed event and MUST NOT reuse a value for a different event under the same GUID. Repeated transmissions of the **same unchanged event frame** MAY retain the same sequence number. The counter MUST increase by one modulo no wrap: valid transmitted values are `0x00000000` through `0xFFFFFFFF`; **wrap to zero is forbidden** under the same GUID. A sender MUST stop transmitting E1 version 1 events when the counter space is exhausted until a new unique GUID is provisioned or a future epoch-bearing format is used.

A sender MUST maintain the next sequence number across reboot, power loss, and firmware update, or MUST stop E1 transmission until a safe new identity is provisioned. Implementations SHOULD use nonvolatile counter-range reservation to avoid a flash write for every event. Skipped counter values are allowed (for example after a crash or reservation); receivers MUST NOT assume gap-free delivery. **A new device GUID starts a new sequence space.**

Receivers MAY deduplicate by the pair `(Sender GUID, sequence number)` within a bounded retention window. Identical repeats MAY be ignored. If the same pair appears with different event bytes, the receiver SHOULD report a conflict and MUST NOT merge their data. A receiver MUST NOT require contiguous sequences or reject a valid event solely because a previous advertisement was lost or arrived out of order. Sequence numbers do **not** provide authenticity or cryptographic anti-replay for cleartext E1.

### 5.6 Validation algorithm

For each **complete** advertising data set, the receiver MUST:

1. Parse its AD structures using their Length octets, checking bounds before every read. A zero AD Length terminates parsing; any remaining bytes are not part of an AD structure.
2. Select Manufacturer Specific Data AD structures (`0xFF`) with the configured Company Identifier. Ignore unrelated manufacturers and AD types.
3. Require at least **34 octets** in a candidate E1 AD structure (including AD Length and AD Type).
4. Require frame version exactly `0x01`. Unknown versions MUST NOT be interpreted as legacy version 0.
5. Require flags exactly `0x00`; reject all reserved-bit combinations.
6. Decode `N` at offsets 32–33 as big-endian and require `0 ≤ N ≤ 222`.
7. Require the AD Length value to equal **33 + N**, and the AD structure size to equal **34 + N**. Reject missing, excess, or padded event octets within the structure.
8. Require a nonzero Sender GUID. Preserve the full VSCP head, class, type, and exact `N` event data octets.
9. Reject ambiguous data sets containing more than one candidate E1 event under the same configured Company Identifier; multi-event packing is not defined.
10. Apply VSCP application validation, local resource limits, and security policy **before** delivering the event. Unauthenticated E1 MUST NOT authorize privileged operations.

The receiver MUST reject truncated extended advertising reports or incomplete controller-reassembled data sets. Malformed packets MUST NOT cause out-of-bounds reads, unbounded allocations, or implicit fallback to another frame version.

### 5.7 Hexadecimal interoperability vectors

**Vector A — empty event payload.** Test-only Company Identifier `0xFFFF`; sequence 0; GUID `00:01:02:03:04:05:06:07:08:09:0A:0B:0C:0D:0E:0F`; head/class/type all zero; `N = 0`.

```text
21 FF FF FF 01 00 00 00 00 00
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00 00 00 00 00 00 00 00
```

**Vector B — two event-data octets.** Same test identifier and GUID; sequence 1; head `0x0000`; class `0x000A`; type `0x0006`; event data `11 22`; `N = 2`.

```text
23 FF FF FF 01 00 00 00 00 01
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00 00 00 0A 00 06 00 02 11 22
```

Both vectors are **framing tests**, not claims that the selected VSCP class/type combinations constitute meaningful application events. Both use `0xFFFF` strictly as a test identifier.

**Negative tests:** reject version `0x02`, flags `0x01` or `0x80`, zero GUID, `N=223`, AD Length not equal to `33+N`, truncated data, extra bytes inside the candidate AD structure, multiple candidate E1 frames, and incomplete extended advertising reports.

### 5.8 Security boundary

E1 version 1 as defined here is **cleartext and unauthenticated**. It MUST be restricted to data permitted by policy to be public and untrusted. AES-ECB is not permitted for E1. Authenticated/encrypted E1 requires a separately specified and tested envelope with key identifiers, nonce uniqueness, authenticated metadata, replay protection, key lifecycle, and known-answer vectors. Until then, flag bit 0 remains reserved and unusable.

## 6. Connected GATT profile G1 — proposed version 1

> **Allocation status:** The 128-bit UUIDs below are allocated **by this VSCP draft specification**, not registered with or assigned by the Bluetooth SIG. They MUST be reviewed for conflicts with existing VSCP deployments before ratification. They are not Bluetooth SIG 16-bit UUIDs.

### 6.1 Roles, UUIDs and characteristic definitions

The VSCP node is normally the GATT **server** (BLE peripheral), and the gateway or controller is the GATT **client** (BLE central). The event transport is bidirectional: Event TX sends server-to-client notifications; Event RX accepts client-to-server writes. A central may host another VSCP service only as a separate instance, not by reversing the semantics of these characteristics.

The following UUID block is **provisionally reserved for this G1 draft**:

| Attribute | UUID (128-bit) | Properties | Access policy |
| --- | --- | --- | --- |
| VSCP G1 primary service | `9b7a0000-6e44-4b8a-9d64-565343502001` | Primary service | Discoverable |
| Capabilities | `9b7a0001-6e44-4b8a-9d64-565343502001` | Read | Public; no secrets |
| Device GUID | `9b7a0002-6e44-4b8a-9d64-565343502001` | Read | Public asserted identity |
| Event TX | `9b7a0003-6e44-4b8a-9d64-565343502001` | Notify | Authenticated, encrypted, authorized subscription |
| Event RX | `9b7a0004-6e44-4b8a-9d64-565343502001` | Write (with response) | Authenticated, encrypted, authorized write |
| Control | `9b7a0005-6e44-4b8a-9d64-565343502001` | Write (with response), Indicate | Authenticated, encrypted, authorized |
| Configuration | `9b7a0006-6e44-4b8a-9d64-565343502001` | Read, Write (with response) | Authenticated, encrypted, admin authorization |
| Security Status | `9b7a0007-6e44-4b8a-9d64-565343502001` | Read | Authenticated, encrypted; no key material |

Each Notify/Indicate characteristic MUST have a Client Characteristic Configuration Descriptor (CCCD, standard UUID `0x2902`). The GATT server MUST enforce link encryption and authenticated pairing (MITM protection) for protected attributes, plus an application trust/authorization policy. **LE Secure Connections with authenticated association is RECOMMENDED**; if a platform cannot provide authenticated pairing, it MUST NOT expose privileged operations through G1. A bonded device is not automatically an authorized VSCP administrator. Just Works pairing alone MUST NOT authorize sensitive writes. There is **no** writable plaintext Key characteristic.

### 6.2 Byte order and common record framing

G1 uses the same canonical VSCP GUID byte order as E1. All G1 multioctet integers are unsigned **big-endian**. Each Event TX or Event RX message is a complete **G1 record**, split across ATT value transfers when necessary. A record header is:

| Offset | Field | Size | Value |
| ---: | --- | ---: | --- |
| 0 | Protocol version | 1 | `0x01` |
| 1 | Record kind | 1 | `0x01` = VSCP event |
| 2 | Record flags | 1 | `0x00` (all bits reserved) |
| 3 | Reserved | 1 | `0x00` |
| 4–7 | Transaction ID | 4 | Sender-selected, nonzero; unique among in-flight records on that connection |
| 8–9 | VSCP event length | 2 | `L = 22 + N` |
| 10–25 | Sender GUID | 16 | Canonical 16-octet GUID |
| 26–27 | VSCP head | 2 | Full 16-bit VSCP head |
| 28–29 | VSCP class | 2 | 16-bit VSCP class |
| 30–31 | VSCP type | 2 | 16-bit VSCP type |
| 32–33 | VSCP data length | 2 | `N` |
| 34–(33+N) | VSCP event data | N | Exactly N octets |

The record is **34 + N** octets, with `L=22+N` denoting the 16-byte GUID, 2-byte head, 2-byte class, 2-byte type, 2-byte data length, and `N` data octets. The record carries no implicit timestamp or obid; gateways may supply these as local metadata. `N` MUST be between 0 and the negotiated `max_event_data`, never greater than 487 octets for this G1 revision. The maximum record size is therefore 521 octets. Zero GUID, unsupported record kind/version/flags, or inconsistent lengths MUST be rejected.

### 6.3 ATT fragmentation

ATT notifications and writes can carry at most **ATT_MTU - 3** octets of characteristic value. G1 does not require a particular ATT MTU; the minimum ATT MTU of 23 is supported. Every Event TX notification and Event RX Write Request carries **one fragment** of exactly one G1 record. Each fragment has this 8-octet header:

| Offset | Field | Size | Value |
| ---: | --- | ---: | --- |
| 0 | Fragment version | 1 | `0x01` |
| 1 | Flags | 1 | Bit 0 FIRST, bit 1 LAST; bits 2–7 zero |
| 2–5 | Transaction ID | 4 | Matches the G1 record |
| 6–7 | Offset | 2 | Zero-based byte offset into complete G1 record |
| 8… | Fragment bytes | Variable | Contiguous bytes from the record |

A fragment MUST fit `ATT_MTU - 3`; therefore fragment payload capacity is `ATT_MTU - 11` (12 octets at MTU 23). The FIRST fragment MUST have offset zero and include at least the first 10 record-header octets; its record Transaction ID MUST match the fragment Transaction ID. Fragments MUST arrive in strictly increasing contiguous offset order for a transaction; gaps, overlaps, duplicates, and unexpected offsets are rejected. The LAST fragment MUST end exactly at the record's computed total length. Zero-length fragment payloads are invalid. A single-fragment record sets both FIRST and LAST.

At most **one reassembly transaction per direction per connection** is permitted in G1 version 1. This avoids interleaving and makes memory limits explicit. The receiver MUST bound buffers to the negotiated maximum record length and discard incomplete reassembly after **5 seconds** without a new fragment. A disconnect immediately discards all incomplete records. No partially reassembled event may reach the VSCP application.

### 6.4 Control characteristic and flow control

Control uses Write Request for client-to-server commands and **Indications** for server-to-client results. The client MUST enable Control indications before sending Event RX records. Every Control value has:

```text
byte 0    version = 0x01
byte 1    opcode
bytes 2–5 transaction ID (uint32 BE; zero for connection-level commands)
byte 6    status
byte 7    payload length P
bytes 8…  payload (P octets)
```

The total value length MUST be exactly `8 + P` and fit the negotiated ATT MTU. Unknown opcodes, invalid lengths, and reserved status values MUST be rejected. Opcodes:

| Opcode | Direction | Semantics |
| --- | --- | --- |
| `0x01` HELLO | Client → server | Negotiate version and limits |
| `0x81` HELLO_RESULT | Server → client | Negotiated limits or error |
| `0x02` RESET | Client → server | Cancel incomplete inbound record |
| `0x82` EVENT_RESULT | Server → client | Application acceptance/rejection for Event RX transaction |
| `0x83` TX_RESULT | Server → client | Status for server-side Event TX delivery attempt; not client acknowledgment |

HELLO request payload is exactly six octets: `max_event_data` (uint16 BE, 0–487), `max_record_size` (uint16 BE, 34–521), `features` (uint16 BE; all bits zero in version 1). HELLO_RESULT success uses the same six-octet payload with negotiated minima. The client MUST complete HELLO successfully before sending Event RX or subscribing to Event TX event traffic. The server MUST reject events that exceed negotiated limits. Both peers MUST enforce the maximum of one outstanding event per direction; the sender waits for an Event RX `EVENT_RESULT` before starting another Event RX record.

An ATT Write Response confirms only that a fragment was accepted by the GATT server; it does **not** mean the complete VSCP event was accepted or executed. `EVENT_RESULT` indicates that a complete event passed framing and admission checks, **not** that its physical side effects completed. Any application requiring execution acknowledgment MUST define a separate VSCP-level response. Server-to-client Event TX uses notifications and has no G1 application acknowledgment in this revision; a server MUST NOT claim reliable client processing based on a successful notification API call.

### 6.5 Status and error handling

Control status codes:

| Code | Name | Meaning |
| --- | --- | --- |
| `0x00` | OK | Command or event accepted |
| `0x01` | UNSUPPORTED_VERSION | Unknown protocol version |
| `0x02` | BAD_LENGTH | Invalid or inconsistent length |
| `0x03` | BAD_FLAGS | Reserved or invalid flag bits |
| `0x04` | BAD_SEQUENCE | Fragment offset/order mismatch |
| `0x05` | BUSY | Another record is in progress |
| `0x06` | NOT_AUTHORIZED | Insufficient application permission |
| `0x07` | TOO_LARGE | Exceeds negotiated limits |
| `0x08` | TIMEOUT | Reassembly expired |
| `0x09` | INVALID_EVENT | VSCP semantic validation failed |
| `0x0A` | NOT_READY | HELLO or CCCD setup incomplete |
| `0x0B` | INTERNAL_ERROR | Server unable to process request |

A failed ATT access permission MUST use standard ATT errors (such as Insufficient Authentication, Insufficient Encryption, or Insufficient Authorization), not silently downgrade. A structurally valid Event RX transaction that fails VSCP admission MUST receive `EVENT_RESULT` with an appropriate status, if the connection remains active. On fragmentation errors, the receiver MUST discard the current record, return a status where the protocol allows, and require a fresh FIRST fragment. Clients MUST NOT retry a privileged command with weaker permissions or a different security profile.

### 6.6 Capabilities, configuration and security status

Capabilities Read returns a fixed 12-octet structure:

```text
0       G1 version (0x01)
1       flags (0x00, reserved)
2–3     max_event_data (uint16 BE; <= 487)
4–5     max_record_size (uint16 BE; <= 521)
6–7     max_fragment_payload (uint16 BE; ATT_MTU-dependent, 0 if not negotiated)
8–9     supported_features (uint16 BE; 0x0000 in v1)
10–11   reserved (0x0000)
```

Device GUID Read returns exactly 16 octets in VSCP canonical order. Configuration Read/Write uses a versioned TLV envelope: `version (1)=0x01, count (1), repeated [type (1), length (1), value (length)]`. Version 1 defines **no writable TLV types**; a write MUST be rejected as unsupported unless a separately published authorized extension defines it. This prevents unspecified configuration writes from becoming de facto interoperability requirements.

Security Status Read returns exactly four octets: `version=0x01, pairing_state, authorization_state, reserved=0x00`. Pairing state is `0` unauthenticated or `1` authenticated/encrypted; authorization state is `0` none, `1` event access, `2` administrator. These are advisory status indicators, not proof of authorization. No keys, key identifiers, or nonce prefixes are exposed.

### 6.7 Connection lifecycle and interoperability

On connection, the client discovers the service and characteristics, establishes required BLE link security, subscribes to Control indications, reads Capabilities and Device GUID, and sends HELLO. On successful HELLO it may subscribe to Event TX and use Event RX subject to authorization. Notifications/indications MUST NOT carry unnegotiated event records. On reconnect, negotiation and transaction IDs start a new connection scope; stale fragments and outstanding transactions MUST be discarded.

Implementations MUST validate every byte length before allocating memory or decoding a VSCP event, rate-limit malformed traffic, and never execute an event from a partial record. Implementers SHOULD provide conformance tests at ATT MTU 23 and larger MTUs, including single/multi-fragment records, maximum payload, missing LAST, overlapping fragments, duplicate transaction IDs, timeout, disconnect, permission failures, HELLO failure, and invalid VSCP data.

## 7. Authenticated security profile A2 (proposed)

> **Status:** A2 is a **new, proposed frame version 2**. It does not redefine E1 version 1, whose flags MUST remain zero. A2 uses authenticated encryption; interoperability requires provisioning the same key records and implementing the rules below. Cryptographic test vectors and independent implementation review are required before ratification or production deployment.

### 7.1 Security policy and threat model

| Policy | Requirement | Allowed format |
| --- | --- | --- |
| S0 | Public, untrusted telemetry; no origin authentication | E1 version 1 |
| S1 | Origin authentication, integrity, anti-replay | A2 version 2 (AEAD, even if data is not sensitive) |
| S2 | Origin authentication, confidentiality, integrity, anti-replay | A2 version 2 |

A2 always encrypts the event data and authenticates the complete event metadata; it therefore satisfies the **cryptographic transport** requirements for S1 and S2. Policy authorization remains separate. A2 does not protect against radio jamming, intentional packet loss, traffic analysis, compromised endpoints, or denial of service. BLE link-layer encryption is not a substitute for A2 authentication of broadcast data. Never authorize a privileged VSCP action from S0 or legacy AES-ECB alone.

### 7.2 A2 cryptographic suite

The mandatory suite is **AES-128-CCM**, with a **13-octet nonce** and **16-octet authentication tag** (CCM parameter `L=2`, `M=16`). The secret is a uniformly random **16-octet AES key**. A2 MUST NOT use AES-ECB, unauthenticated AES-CTR, truncated tags, or ad hoc MAC constructions. An implementation MUST use a vetted constant-time cryptographic library where available, verify the tag before exposing plaintext, and clear sensitive temporary buffers.

The AES-CCM plaintext is the `N` VSCP event data octets; the entire fixed A2 header, including the VSCP head/class/type, is authenticated as associated data (AAD). The **AAD** is the ASCII domain separator `VSCP-BLE-A2` (11 octets) followed by the **38-octet A2 AD Data header**, from Company Identifier through Data Length (offsets 2–39 of the AD structure). The outer AD Length and AD Type are validated as framing but are not part of AAD.

### 7.3 A2 frame version 2: exact on-air layout

Offsets are relative to the first octet of the complete Manufacturer Specific Data AD structure, including AD Length and AD Type. The Company Identifier is little-endian; all other multioctet integers are unsigned **big-endian**.

| Offset | Field | Octets | Encoding / validation |
| ---: | --- | ---: | --- |
| 0 | AD Length | 1 | `0x37 + N` (55 + N) |
| 1 | AD Type | 1 | `0xFF` |
| 2–3 | Company Identifier | 2 | Assigned Bluetooth SIG identifier, little-endian |
| 4 | Version | 1 | Exactly `0x02` |
| 5 | Flags | 1 | Exactly `0x01`: authenticated encryption enabled; all other bits reserved/zero |
| 6–7 | Key ID | 2 | Nonzero key-record identifier, big-endian |
| 8–11 | Key epoch | 4 | Unsigned 32-bit persistent epoch, big-endian |
| 12–15 | Sequence | 4 | Unsigned 32-bit counter, big-endian |
| 16–31 | Sender GUID | 16 | Stable, nonzero VSCP GUID |
| 32–33 | VSCP head | 2 | Big-endian |
| 34–35 | VSCP class | 2 | Big-endian |
| 36–37 | VSCP type | 2 | Big-endian |
| 38–39 | VSCP data length | 2 | Unsigned `N`, big-endian |
| 40–(39+N) | Ciphertext | N | AES-CCM encryption of exactly `N` VSCP event-data octets |
| (40+N)–(55+N) | Authentication tag | 16 | AES-CCM tag, untruncated |

The A2 AD Data header is **38 octets**. The complete AD structure is **56 + N octets**, and AD Length is **55 + N**. Therefore **0 ≤ N ≤ 200** for a single AD structure. No padding, trailing fields, fragmentation, or multiple events per AD structure are defined. The Company Identifier MUST be assigned and configured for production; `0xFFFF` is for isolated tests only.

**A2 flags:** bit 0 MUST be one (AES-128-CCM); bits 1–7 MUST be zero. Unknown versions, suites, flags, or key IDs MUST be rejected without fallback to cleartext. The E1 version 1 flag byte remains strictly `0x00`.

### 7.4 Nonce construction and uniqueness

The AES-CCM nonce is exactly 13 octets:

```text
nonce[0..4]   = sender-specific 5-octet nonce prefix (provisioned)
nonce[5..8]   = key epoch (4 octets, big-endian)
nonce[9..12]  = sequence (4 octets, big-endian)
```

The 5-octet prefix is stored in the receiver's authenticated key record and is **not transmitted**. Each sender/key combination MUST have a unique prefix; if the same AES key is shared by multiple senders, prefixes MUST be unique across all those senders, and epochs/counters MUST never repeat for a given prefix and key. **Per-sender keys are strongly recommended**; group/shared keys weaken attribution and require coordinated prefix allocation.

For any given AES key, a nonce MUST NEVER be reused to encrypt two distinct plaintext/AAD combinations. Retransmission of the **identical precomputed frame** is allowed; retransmission MUST NOT re-encrypt changed data using the same nonce. A sender MUST reserve or persist sequence ranges safely **before use**, including across power loss, rollback, restore, or firmware update. Counter `0xFFFFFFFF` is the final allowed value in an epoch; wraparound is forbidden. On exhaustion, the sender MUST advance to a previously unused, durably recorded epoch before encrypting more frames, or stop transmission. Epoch values MUST NOT repeat with the same key/prefix; if epoch exhaustion or persistence failure occurs, rekey and provision a fresh nonce prefix before resuming.

### 7.5 Key provisioning, lifecycle and authorization

Each receiver's protected key store MUST associate `(Company Identifier, Sender GUID, Key ID)` with an AES key, unique 5-octet nonce prefix, authorized event policy, permitted epoch range, and revocation state. The Key ID is a lookup identifier, **not a secret**. The receiver MUST verify that the authenticated sender GUID matches the provisioned record; it MUST NOT trust a claimed GUID merely because the frame names a known Key ID.

Keys MUST be generated with a cryptographically secure random generator, provisioned using an authenticated and confidential out-of-band channel or authenticated protected GATT procedure, and stored using platform-supported protected storage where available. Factory-default universal keys, keys embedded in publicly distributed firmware, plaintext advertising of keys, and unprotected writable GATT Key characteristics MUST NOT be used. Where protected storage is unavailable, deployments MUST document physical extraction risks and restrict security-sensitive applications accordingly.

Key rotation MUST provision a **new AES key**, a new nonzero Key ID (or a carefully versioned non-ambiguous identifier), and a fresh nonce prefix; receiver acceptance of old and new keys MAY overlap for a bounded migration period. Revocation MUST disable the old key record, including its replay state, and MUST NOT allow automatic fallback to an older key. A compromised sender or leaked shared key requires revocation and re-provisioning; a new Key ID alone is not rekeying.

The receiver MUST check authorization **after tag verification** and **before event delivery**. Permissions SHOULD be scoped by GUID, VSCP class/type, intended target, and allowed actions. Successful authentication MUST NOT imply blanket permission for control, firmware updates, access control, or configuration.

### 7.6 Replay protection and receiver processing

The receiver MUST maintain replay state for each `(Company Identifier, Sender GUID, Key ID, epoch)` and enforce a **strictly increasing sequence** within the accepted epoch. To avoid ambiguity, the baseline profile **does not support out-of-order acceptance**: a correctly authenticated frame with a sequence number not greater than the highest accepted value for that epoch is rejected as replay/duplicate. Gaps are allowed. A higher epoch is accepted only when authorized by the provisioned key record and monotonic epoch policy; lower epochs are rejected after advancing. Replay state (highest epoch and sequence) MUST survive receiver restart and rollback, or the receiver MUST fail closed until re-provisioned or securely resynchronized.

A2 is intended for event reporting, not guaranteed delivery. A sender MAY retransmit the same authenticated frame; the receiver then discards duplicates. Where reliable command execution is required, use an authenticated connected transport with application-level acknowledgment and idempotency controls.

Receiver order of operations:

1. Check the complete AD structure, AD Type, configured Company Identifier, exact version `0x02`, flags `0x01`, and exact length `56+N` with `0 ≤ N ≤ 200`; reject truncated reports and duplicate candidate frames.
2. Reject all-zero GUID, unknown/revoked Key ID, unsupported key epoch, and key-record/GUID mismatch. Apply bounded parsing and resource limits.
3. Construct the 13-octet nonce from the provisioned prefix, transmitted epoch, and sequence. Construct AAD exactly as in §7.2.
4. Verify the **full 16-octet CCM tag** and decrypt into a private buffer; on failure, discard without event delivery and without updating replay state. Never release unauthenticated plaintext.
5. Under an atomic per-sender replay-state update, reject stale/duplicate sequence or epoch; persist the new replay state before accepting security-sensitive events. Implementations MUST avoid races between parallel receive paths.
6. Validate VSCP head/class/type/data semantics and authorization policy, then deliver the event. Authentication failures MUST NOT trigger plaintext fallback.

A replay database that cannot be safely persisted MUST NOT be used for security-sensitive event acceptance. Logging SHOULD rate-limit repeated failures and MUST NOT expose secret keys, nonce prefixes, or decrypted sensitive event contents.

### 7.7 Implementation and interoperability tests

Conformance testing MUST include AES-128-CCM known-answer tests for the **exact AAD and nonce construction**, empty payload (`N=0`), maximum payload (`N=200`), modified ciphertext, modified authenticated header, modified tag, unknown/revoked Key ID, zero GUID, reserved flags, malformed lengths, replayed sequence, out-of-order frames, counter exhaustion, epoch advancement, reboot/power-loss recovery, concurrent receiver updates, and sender/receiver rollback. Independent interoperable implementations SHOULD verify byte-identical ciphertext and tags before the profile is ratified.

**Open deployment dependencies:** a production Bluetooth SIG Company Identifier, secure provisioning protocol, device trust anchors, persistent counter implementation, receiver storage model, and published executable known-answer vectors. These are mandatory deployment decisions; a wire format alone cannot supply them.

## 8. Discovery, capabilities and compatibility

### 8.1 Discovery principles

A BLE device address identifies a radio endpoint for a particular observation; it is **not** a durable VSCP node identity. A scanner MUST NOT infer E1, A2, or G1 support merely from the Bluetooth Core version, PHY, appearance, local name, or presence of a manufacturer-specific AD structure. A receiver MUST verify the actual AD Type, configured Company Identifier, frame version, exact framing, and security policy before accepting a VSCP event.

Discovery is a best-effort process. Passive scanning can observe legacy or extended advertisements supported by the scanner; active scanning can additionally solicit scan responses from scannable advertisers. Extended advertising reports may be fragmented or truncated by the host API. A receiver MUST ignore incomplete frames and MUST NOT interpret missing observations as proof that a capability is absent.

### 8.2 Profile support detection

| Profile | Positive support evidence | What is **not** sufficient |
| --- | --- | --- |
| L0 | Successfully parsed, implementation-verified legacy version 0 manufacturer AD structure | BLE local name, arbitrary manufacturer data, or a scan response alone |
| E1 | Complete manufacturer AD structure with configured Company Identifier, version `0x01`, valid flags and length | Bluetooth 5 version or extended advertising presence alone |
| A2 | Complete authenticated version `0x02` frame, provisioned key record, valid CCM tag and replay checks | Version byte alone, Key ID alone, or unverified GUID |
| G1 | Discovery of the exact G1 primary service UUID and required characteristics, successful secure HELLO negotiation | Device name, advertisement of an unverified service UUID, or an encrypted link alone |

For G1, service UUIDs MAY be advertised in standard Service UUID AD structures to accelerate discovery. Such advertising is a **hint**, not proof: the client MUST connect and discover the actual GATT service, verify characteristic properties, establish required security, and negotiate HELLO. Devices MAY omit the service UUID from advertising because of space constraints; clients MAY discover G1 after connecting to a device selected by other authorized means.

A G1 server MUST expose the Capabilities and Device GUID characteristics defined in §6. A client MUST verify that the Device GUID read is 16 octets and nonzero. An application MUST NOT treat a public Device GUID read as cryptographic proof of identity.

### 8.3 Stable GUID mapping and multiple transports

The canonical VSCP identity is the **16-octet Sender GUID**, not the Bluetooth MAC address. For a single VSCP node, the E1/A2 sender GUID and G1 Device GUID MUST match when the same node originates the event. Gateways that forward events from other VSCP nodes MUST preserve each event's original Sender GUID and MUST NOT replace it with the gateway's GATT Device GUID.

A receiver MAY maintain a temporary association between observed BLE address, advertising set, GATT connection, and canonical GUID for discovery and diagnostics. Such associations MUST tolerate BLE private-address rotation, reconnection, and address reuse. They MUST NOT be used as authentication or as the sole key for long-lived VSCP identity records.

Legacy L0 may derive its GUID from a BLE address and Node ID as described in §4.5. This derived identity MUST NOT be automatically merged with a stable E1/A2/G1 GUID without an explicit trusted provisioning record. If multiple devices claim the same stable GUID, receivers SHOULD flag an identity conflict; privileged communication MUST fail closed until the conflict is resolved.

### 8.4 Capability sources and negotiation

G1 Capabilities Read (§6.6) reports G1 protocol version, maximum event data, maximum record size, fragment capacity, and G1 feature bits. Its `supported_features` field is **G1-scoped** and is zero in version 1; it MUST NOT be interpreted as a bitmap advertising L0/E1/A2 support. The actual negotiated G1 limits are established by HELLO (§6.4). The effective transfer limit is the minimum of both peers' limits and current ATT MTU constraints.

E1 and A2 have **no separate discovery-capability advertisement** in this revision. Support is observed by receiving and validating a frame of that version. Observing an E1 frame does not prove A2 support, and observing an A2 frame does not authorize E1 fallback. Implementations MUST NOT invent meanings for reserved flags or infer support for unadvertised versions.

If a future capability AD structure or G1 capability extension is introduced, it MUST receive its own explicit versioned wire definition and must not reinterpret reserved bytes of existing E1/A2 frames. Capability claims from unauthenticated advertising are advisory; security-critical capabilities and policy MUST be verified through authenticated configuration or a trusted provisioning record.

### 8.5 Version compatibility matrix

| Sender format | Receiver support | Result |
| --- | --- | --- |
| L0 v0 | Verified L0 decoder | Accept only under configured legacy security policy |
| E1 v1 | E1 v1 decoder | Accept only as S0 untrusted data |
| A2 v2 | A2 v2 decoder with valid key and replay state | Accept subject to authorization policy |
| G1 v1 | G1 v1 service and successful HELLO | Exchange events within negotiated limits |
| Any newer/unknown version | No explicit decoder | Reject or ignore; MUST NOT reinterpret as an older version |

A G1 HELLO request with an unsupported protocol version MUST fail with `UNSUPPORTED_VERSION`; the client MAY negotiate a separately supported older G1 version only when local policy permits it. Unknown E1/A2 frame versions MUST be ignored or rejected without guessing their layouts. A receiver MUST NOT treat the lower four bits of an E1/A2 version byte as an L0 version field.

### 8.6 Fallback and downgrade prevention

A transport selection policy MUST be configured independently of discovery. For each class of operation, the application SHOULD define the minimum acceptable security level (S0, S1, or S2) and required directionality, payload size, and delivery semantics. The following is a recommended preference order **only among profiles that satisfy the policy**:

1. **G1** for authorized bidirectional event exchange and configuration, after secure HELLO.
2. **A2** for authenticated, connectionless event reporting with valid keys and replay state.
3. **E1** for public, untrusted connectionless telemetry.
4. **L0** only for explicitly enabled, verified legacy interoperability.

This order is not a universal ranking: an application needing broadcast reception may prefer A2 over G1; a deployment with no credentials cannot claim A2 support. **Security policy overrides convenience and transport availability.** If an authenticated profile fails due to invalid tags, missing credentials, replay, revocation, or incompatible security, the implementation MUST NOT retry the same privileged operation over E1, L0, or an unauthenticated G1 link. A2 failure MUST NOT trigger plaintext fallback. Fallback from G1 to E1/L0 MAY occur only for operations independently authorized as public S0 data.

A scanner or GATT client SHOULD cache supported capabilities per **trusted stable GUID**, with an expiration or explicit invalidation rule. Cached capabilities MUST be refreshed after firmware upgrade, re-provisioning, key rotation, or incompatible protocol responses. A BLE address alone MUST NOT be a persistent capability-cache key. Negative discovery results SHOULD be treated as temporary because advertisements and scan responses may be missed.

### 8.7 Discovery and fallback test cases

Conformance tests SHOULD cover: L0-only devices; E1-only devices; A2 with correct and incorrect credentials; G1 UUID advertised but service absent; G1 service present but HELLO incompatible; GUID match across E1/A2/G1; rotating BLE private addresses; conflicting GUIDs; truncated extended reports; unsupported frame versions; stale cached capabilities; failed authenticated transport with attempted downgrade; and G1 operation on a controller without extended advertising support.

## 8. Interoperability and error handling

An E1 receiver MUST:
1. Parse the outer AD Length and AD Type and verify the manufacturer AD structure is complete.
2. Match the expected Company ID and frame version.
3. Reject any reserved flag bits, encrypted frames without a ratified envelope, or unsupported versions.
4. Verify that the data length equals the exact remaining number of octets.
5. Preserve the 16-octet GUID, full head, class, type and data without reinterpretation.
6. Bound allocations and parsing work to configured resource limits.
7. Never interpret an incomplete or unauthenticated event as an authenticated control command.

A test suite SHOULD include zero-length data, the largest permitted single-AD event, truncated AD structures, off-by-one lengths, invalid version, reserved bits, duplicate sequences, controller feature absence, and legacy-version separation.

## 9. Implementation and compatibility guidance

- Keep existing L0 implementations unchanged unless tested against real deployed traffic.
- Prefer E1 for short, connectionless public events on controllers supporting extended advertising.
- Prefer G1 (once ratified) or another established secure VSCP transport for bidirectional or privileged operations.
- Do not assume every BLE 5 controller supports extended advertising, LE 2M, LE Coded PHY, or periodic advertising.
- Keep the legacy format and new version 1 on separately recognizable frame encodings; do not infer the version from a Bluetooth PHY.
- For large VSCP Level II events, use GATT or another transport until a fully specified fragmentation/large-event encoding is standardized.

## 10. Open standardization decisions

The following MUST be resolved before declaring E1/G1 a final VSCP transport standard:

1. Which assigned Company Identifier or Service Data UUID identifies VSCP on the wire?
2. Is the full GUID required in every E1 advertisement, or is a separately provisioned compact identity mode needed?
3. Which authenticated-encryption envelope and provisioning method will be reused from the broader VSCP security model?
4. Which GATT UUIDs, exact event wire encoding, flow control, and application error model will be standardized?
5. Should large events use multiple AD structures, an application fragment format, or connected transfer only?
6. Which hardware/host combinations form the interoperability reference test matrix?

## 11. References

- [Bluetooth SIG specifications and assigned numbers](https://www.bluetooth.com/specifications/specs/)
- [Bluetooth Core Specification](https://www.bluetooth.com/specifications/specs/core-specification/)
- [VSCP specification repository](https://github.com/grodansparadis/vscp-doc-spec)
- [VSCP Bluetooth mesh transport](./vscp_over_bt_mesh.md)

[filename](./bottom_copyright.md ':include')
