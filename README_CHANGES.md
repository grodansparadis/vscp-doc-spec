# Changes in vscp-doc-spec

Every change that goes into a release is listed here, newest release first.
Add each change under **Unreleased** when it is made. When a release is
tagged, rename **Unreleased** to the version and date, and start a new
**Unreleased** section above it.

## Unreleased

- Register abstraction model: the time remote variable is three bytes (hh mm ss); the text said four. Date is four bytes with a 16-bit year (grodansparadis/vscp#331)
- HMAC use in binary frames clearified (bc49ecf)
- Prefix and HMAC-SHA256 added to VSCP binary protocol. (1939aa2)
- Measurement command added to VSCP link protocol. (8dd341b)
- Added illustrations (cee97f4)
- Edit (fc50c5d)
- tcplink protocol challenge doc updated (71cada8)

## v1.22.0 - 2026-09-07

- Updated GUID shorthand to confirm with Ipv6 (2ab0cb4)
- Fixed typo (eff671c)
- Fixed typo (cec9847)
