# VSCP RS-485 V1 conformance and hardware test plan

**Status: draft.** No hardware interoperability claim is made.

## Required test equipment
- One coordinator using a real nine-bit UART bridge (a standard 8-bit USB–RS-485 adapter is insufficient for the proposed interpretation).
- One embedded node with 9-bit UART and RS-485 driver-enable control.
- Logic analyzer able to decode ninth-bit address signaling; suitable differential probes and termination.

## Verification matrix
| ID | Test | Expected outcome |
| --- | --- | --- |
| F01 | POLL known address | Exactly one permitted reply, or documented silence |
| F02 | NO_EVENTS | Correct operation, destination, checksum |
| F03 | EVENT with 0, 1 and 8 data bytes | Correct frame length and payload |
| F04 | Class 0, 255, 256, 511; type 0 and 255 | Correct flags/class encoding |
| F05 | Reserved flag bits nonzero | Rejected |
| F06 | CRC altered | Rejected without event delivery |
| F07 | Truncated frame | Receiver times out and recovers |
| F08 | Ninth-bit marker missing | Rejected or ignored per verified specification |
| F09 | Two nodes with same address | Conflict detected/documented, no unbounded collision |
| F10 | Silent node | Coordinator timeout and continued polling |
| F11 | Node reset during poll | Bus returns to idle, no stuck driver-enable |
| F12 | 127-address scan | Measured poll cycle and latency |
| F13 | Repeated traffic | No duplicate delivery outside specified semantics |
| F14 | Bus wiring/termination faults | Documented recovery and diagnostics |

## CRC verification
A CRC-8/MAXIM-DOW implementation passes the *algorithm* check `123456789 -> A1`. This alone does not verify that legacy VSCP uses the same parameters, byte coverage, or short-frame encoding. Golden vectors must be captured from an independent implementation before publishing normative hex frames.

## Linux and embedded implementation requirements
- Linux coordinator must explicitly depend on a nine-bit bridge contract, include bounded timeouts, validate all received words, and not treat host `tcdrain()` as proof that bus transmission completed.
- Embedded responder must queue transmission outside interrupt context, assert DE before the first start bit, and release DE only after the final stop bit.
- Implement recovery after corrupt/truncated bridge frames and buffer overflow.
- Record UART framing, CRC, timeout, collision and retry counters.

## Release criteria
Mark conformance as passed only after automated codec tests, independent golden-vector comparison, and physical interoperability measurements. Record firmware revision, baud rate, UART mode, transceiver type, wiring length, termination and test captures.
