# VSCP BLE reference examples (draft)

These examples implement the **E1 version 1, S0-only** manufacturer-data encoding from [the draft transport specification](../../vscp_over_bt_ble.md). They do **not** implement A2 authenticated encryption, F1 fragmentation or G1 application authorization. **Do not use for control, access, firmware update, or confidential data.**

The sample company identifier `0xFFFF` is for isolated tests only. Replace it with an actually assigned Bluetooth SIG Company Identifier for deployed systems. The sender GUID must be a provisioned stable, nonzero GUID.

| Available artifact | Purpose |
| --- | --- |
| [common/vscp_ble_e1.h](common/vscp_ble_e1.h) | Dependency-free E1 encoder and decoder |
| [tests/test_e1.c](tests/test_e1.c) | Codec vectors and validation checks |

The shared [codec](common/vscp_ble_e1.h) builds the complete E1 AD structure. When integrating it with a Bluetooth API, check which bytes that API expects: a manufacturer value includes the Company Identifier but excludes AD Length and AD Type, while BlueZ D-Bus ManufacturerData provides the Company Identifier separately.

## Test

    cc -std=c11 -Wall -Wextra -Werror -Iexamples/ble/common examples/ble/tests/test_e1.c -o /tmp/test_vscp_ble_e1
    /tmp/test_vscp_ble_e1

Platform-specific ESP32, Nordic, Zephyr and BlueZ examples are not included in this tree.

**Status:** illustrative source; hardware, OS-version, compiler, and radio interoperability validation remains outstanding. Unsupported BLE features must be reported as unsupported, never silently converted to legacy advertisements.

## A2 authenticated frame and G1 transport-core tests

The new portable [A2 AES-128-CCM OpenSSL reference](common/vscp_ble_a2_openssl.c) implements the draft authenticated frame encoding, tag verification and in-memory replay rejection. It uses the [A2 interface](common/vscp_ble_a2.h). **Before accepting an A2 event**, the application MUST durably persist the updated replay state and enforce VSCP authorization. Before sending, the application MUST reserve and persist a unique epoch/sequence; the example deliberately does not manage persistent keys or counters.

The [G1 framing core](common/vscp_ble_g1.c) and [interface](common/vscp_ble_g1.h) implement VSCP event serialization, ATT-MTU-aware fragmentation and bounded, ordered reassembly. They are transport-neutral building blocks for GATT clients and servers, **not complete Bluetooth GATT applications**. GATT UUID registration, characteristic permissions, HELLO/Control indications, transaction scheduling, pairing and platform-specific server/client integration remain to be implemented.

Build and run portable tests on a Linux development host with OpenSSL headers and libraries:

```sh
cc -std=c11 -Wall -Wextra -Werror -Iexamples/ble/common \
  examples/ble/tests/test_e1.c -o /tmp/test_vscp_e1
/tmp/test_vscp_e1

cc -std=c11 -Wall -Wextra -Werror -Iexamples/ble/common \
  examples/ble/tests/test_a2_g1.c \
  examples/ble/common/vscp_ble_a2_openssl.c \
  examples/ble/common/vscp_ble_g1.c -lcrypto -o /tmp/test_vscp_a2_g1
/tmp/test_vscp_a2_g1
```

The A2 known-answer vector is independently reproduced using Python `cryptography` AESCCM: nonce `a0a1a2a3a40000000100000002`, ciphertext plus tag `3c4532039788b44a4ad321c6493748c0f6c4d1`. This does not substitute for a security audit.

## Hardware interoperability acceptance procedure (not yet executed)

1. Record **exact** board/SoC, controller firmware, SDK, OS/BlueZ version, adapter, PHY and controller-reported advertising limits.
2. Build the ESP32, Nordic and Zephyr transmitters with an assigned test GUID and the test-only Company ID in an isolated lab. Capture **raw complete advertising data**, not only the decoded BLE name, on an independent BLE sniffer.
3. Confirm E1 sequence, GUID, class, type and data bytes match the shared C vector on **two different vendor controllers**. Exercise minimum and maximum E1 payloads, truncated reports, reserved flags and unsupported controllers.
4. Verify the Linux BlueZ observer receives the supported frames; if BlueZ hides truncation/report status, use a raw HCI or dedicated sniffer capture for the conformance verdict.
5. Integrate the A2 codec into the advertising sender/receiver with provisioned unique keys and **durable** counters/replay state. Verify CCM vectors, tamper rejection, replay rejection and power-loss behavior on physical devices.
6. Implement G1 UUID service, secure ATT permissions, HELLO/Control and notifications/writes in at least two platform stacks. Validate 23-byte and larger MTUs, disconnect/reconnect, authorization and failure codes.
7. Attach capture files, console logs and firmware revisions to the draft PR. Mark unsupported features **SKIP** with evidence, and unexecuted hardware cases **NOT RUN**, never PASS.

**Current result:** source and test cases are committed; the independent Python AES-CCM known-answer calculation was executed successfully. Platform builds, live radio captures, hardware replay persistence, and complete GATT client/server interoperability are **NOT RUN**.
