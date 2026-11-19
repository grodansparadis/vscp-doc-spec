# VSCP BLE reference examples (draft)

These examples implement the **E1 version 1, S0-only** manufacturer-data encoding from [the draft transport specification](../../vscp_over_bt_ble.md). They do **not** implement A2 authenticated encryption, F1 fragmentation or G1 application authorization. **Do not use for control, access, firmware update, or confidential data.**

The sample company identifier `0xFFFF` is for isolated tests only. Replace it with an actually assigned Bluetooth SIG Company Identifier for deployed systems. The sender GUID must be a provisioned stable, nonzero GUID.

| Target | Example | Stack | Role |
| --- | --- | --- | --- |
| ESP32 | [esp32/main/main.c](esp32/main/main.c) | ESP-IDF NimBLE | Extended advertiser |
| Nordic | [nordic/main.c](nordic/main.c) | nRF5 SDK SoftDevice advertising API | Extended advertiser |
| Zephyr | [zephyr/src/main.c](zephyr/src/main.c) | Zephyr Bluetooth | Extended advertiser |
| Linux | [bluez/scan.py](bluez/scan.py) | BlueZ D-Bus / python-dbus | Manufacturer-data observer |

The shared, dependency-free [codec](common/vscp_ble_e1.h) builds the complete E1 AD structure. Some Bluetooth APIs require only the **manufacturer value** (Company Identifier + frame), not the AD Length/AD Type; those examples explicitly strip the two AD-structure prefix bytes. Linux D-Bus ManufacturerData similarly provides the Company Identifier separately.

## Test

```sh
cc -std=c11 -Wall -Wextra -Werror -Iexamples/ble/common examples/ble/tests/test_e1.c -o /tmp/test_vscp_ble_e1
/tmp/test_vscp_ble_e1
```

ESP32: create an ESP-IDF project with the supplied `main` directory and `idf_component_register`, enable NimBLE and BLE extended advertising in menuconfig; build for an ESP32 controller/firmware supporting extended advertising. Not all ESP32 chips support it.

Nordic: this example targets the **nRF5 SDK SoftDevice API** (not nRF Connect SDK); enable extended advertising on a compatible SoftDevice and adjust SDK startup, RAM and linker settings for the selected chip. For nRF Connect SDK use the Zephyr example instead.

Zephyr: place the supplied `src/main.c` and `prj.conf` in a Zephyr application; build with a board whose controller and host support extended advertising.

Linux: install BlueZ and Python D-Bus bindings; use `python3 examples/ble/bluez/scan.py`. BlueZ D-Bus scanning exposes manufacturer data but **does not guarantee complete extended-advertising reports or data-status visibility** on every version/adapter. This sample therefore only observes and validates E1-like manufacturer values; it is not a conformance-grade extended advertising receiver.

**Status:** illustrative source; hardware, OS-version, compiler, and radio interoperability validation remains outstanding. Unsupported BLE features must be reported as unsupported, never silently converted to legacy advertisements.
