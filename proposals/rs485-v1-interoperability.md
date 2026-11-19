# VSCP Level I RS-485/RS-422 V1 interoperability clarification (proposal)

**Status: draft, non-normative.** This document proposes clarifications to [the existing specification](../vscp_level_i_over_rs-485_rs-422.md). It does not supersede the legacy wire format.

## Existing behavior to preserve
- Coordinator-based polling, nominal 115200 baud, other rates possible.
- Address 0 reserved for coordinator; specification mentions 127 client addresses.
- Nine-bit destination address followed by eight-bit characters.
- Operation 1 EVENT, 2 POLL, 3 NO_EVENTS; operation 0 reserved/no operation.
- Event fields: destination, source, operation, flags, class low, type, 0–8 data bytes, DOW checksum.
- Flags bits 0–3 payload length, bit 4 class bit 8, bits 5–7 zero.

## Clarifications required before normative release
1. Define exactly whether the UART ninth bit is an address *marker* or numeric address bit, and specify transmitter/receiver address filtering.
2. Define exact short-frame fields for POLL and NO_EVENTS, and whether flags/class/type are omitted.
3. Specify DOW CRC parameters (polynomial, reflection, init, xorout), byte coverage, and independent golden vectors.
4. State legal numeric addresses, reserved/broadcast addresses, and the procedure for duplicate-address detection.
5. Define UART character timing correctly (8N1 = 10 bits; 9N1 = 11 bits), DE assertion/release, turn-around, poll deadline, and retry behavior.
6. Specify how receivers detect frame boundaries, reset after errors, and reject inconsistent length, reserved flags, or CRC.
7. Define full GUID/nickname mapping, event priority treatment, and gateway forwarding semantics.
8. Separate physical wiring and duplex profiles for 2-wire half-duplex RS-485 and 4-wire RS-422; document termination, fail-safe biasing, grounding, isolation and line-fault handling.

## Provisional implementation interpretation — NOT a standard
- Address word is a nine-bit UART character with bit 8 set as a marker; lower eight bits contain the destination.
- POLL/NO_EVENTS are four UART characters: destination, source, operation, CRC.
- EVENT is 7 + N UART characters (N = 0–8).
- CRC is CRC-8/MAXIM-DOW over the lower eight bits of the destination followed by each non-CRC byte; standard algorithm check string `123456789` yields `A1`.
- Class range 0–511 and type range 0–255.
These assumptions are suitable for experiments but **must be checked against an existing VSCP implementation or independently captured legacy traffic**.

## Compatibility rules
Do not change V1 framing in place. New sequence numbers, capability discovery, fragmentation and authenticated encryption belong in a separately versioned V2 profile. V2 must not transmit incompatible frames on a V1-only segment without explicit negotiation or separate configuration.

## Acceptance gates
- Confirm V1 behavior against upstream firmware and at least one independent implementation.
- Add byte-exact golden vectors for POLL, NO_EVENTS, EVENT with 0/1/8 data bytes and CRC corruption.
- Test 9-bit UART address mark and RS-485 direction control on physical hardware.
- Measure response latency and full-network poll cycle.
- Test missing nodes, duplicates, CRC faults, truncated frames and coordinator restarts.
- Only then promote verified statements into the normative V1 chapter.
