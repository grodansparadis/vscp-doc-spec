# Linux 9-bit UART support for VSCP RS-485 (proposal)

Linux does **not** offer a universal portable 9-bit serial mode through POSIX termios. Support depends on the UART controller and driver.

## Recommended backend order
1. **Native RS-485 multipoint address support:** inspect `linux/serial.h` and `TIOCGRS485` for `SER_RS485_ADDRB`, `SER_RS485_ADDR_RECV`, and `SER_RS485_ADDR_DEST`. These are optional driver features, not a promise that arbitrary 9-bit words are exposed to user space.
2. **Mark/space parity:** `CMSPAR` plus `PARODD` can emit mark parity for address characters and space parity for data characters on compatible drivers. Changing parity with `tcsetattr` between bytes is **not guaranteed** to provide glitch-free, atomic frame transmission, particularly through USB adapters. Receive-side ninth-bit visibility must be tested separately.
3. **External USB-to-9-bit bridge:** a microcontroller with genuine 9-bit UART support accepts explicit 9-bit words from the host and controls RS-485 driver enable. Define bridge framing, error reporting and transmit-complete acknowledgments.

## Hardware validation
Run `tools/rs485-capability-probe.c` on the intended serial device. It queries the Linux RS-485 configuration but **does not certify** the port as VSCP-compatible. The probe is read-only. A positive result requires loopback/logic-analyzer testing of address-mark transmission, address recognition, DE turnaround and receiving 9-bit traffic.

## Linux coordinator implementation
- Prefer native support only after confirming driver-specific behavior.
- Use explicit timeouts, CRC validation, and bounded frame buffers.
- Distinguish kernel RS-485 DE control from multipoint address support.
- Do not claim that ordinary USB-RS485 converters support 9-bit addressing.
- Never use unverified parity switching for production-critical addressing.

## Outstanding decisions
Confirm whether the V1 destination ninth bit is a marker or an address bit; establish legacy CRC coverage and short-frame encoding before publishing normative test vectors.
