#!/usr/bin/env python3
"""Observe VSCP E1 S0 manufacturer data via BlueZ D-Bus.

BlueZ ManufacturerData values exclude the 2-byte Company Identifier and
the AD Length/Type bytes. BlueZ does not expose all extended report metadata
on every version; this is an observer, not a conformance receiver.
"""
import dbus
from dbus.mainloop.glib import DBusGMainLoop
from gi.repository import GLib

COMPANY = 0xFFFF  # test only
seen = set()

def parse_e1(value):
    # Rebuild complete AD structure for the shared byte layout.
    payload = bytes(value)
    if len(payload) < 30 or len(payload) > 252:
        return None
    ad = bytes([len(payload)+3, 0xFF, COMPANY & 255, COMPANY >> 8]) + payload
    if len(ad) < 34 or ad[4] != 1 or ad[5] != 0:
        return None
    n = int.from_bytes(ad[32:34], "big")
    if n > 222 or len(ad) != 34+n or not any(ad[10:26]):
        return None
    return (ad[10:26].hex(), int.from_bytes(ad[6:10], "big"),
            int.from_bytes(ad[28:30], "big"),
            int.from_bytes(ad[30:32], "big"), ad[34:])

def observe(path, props):
    md = props.get("ManufacturerData", {})
    if COMPANY not in md:
        return
    event = parse_e1(md[COMPANY])
    if event is None:
        return
    key = (path, event[0], event[1])
    if key not in seen:
        seen.add(key)
        print("GUID=%s seq=%d class=%d type=%d data=%s" %
              (event[0], event[1], event[2], event[3], event[4].hex()))

def interfaces_added(path, interfaces):
    props = interfaces.get("org.bluez.Device1")
    if props:
        observe(path, props)

def changed(interface, changed_props, invalidated, path=None):
    if interface == "org.bluez.Device1" and path:
        observe(path, changed_props)

def main():
    DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()
    manager = dbus.Interface(bus.get_object("org.bluez", "/"),
                             "org.freedesktop.DBus.ObjectManager")
    objects = manager.GetManagedObjects()
    adapter = next((path for path, interfaces in objects.items()
                    if "org.bluez.Adapter1" in interfaces), None)
    if adapter is None:
        raise SystemExit("No BlueZ adapter found")
    for path, interfaces in objects.items():
        if "org.bluez.Device1" in interfaces:
            observe(path, interfaces["org.bluez.Device1"])
    bus.add_signal_receiver(interfaces_added,
                            dbus_interface="org.freedesktop.DBus.ObjectManager",
                            signal_name="InterfacesAdded")
    bus.add_signal_receiver(changed,
                            dbus_interface="org.freedesktop.DBus.Properties",
                            signal_name="PropertiesChanged",
                            path_keyword="path")
    iface = dbus.Interface(bus.get_object("org.bluez", adapter),
                           "org.bluez.Adapter1")
    iface.SetDiscoveryFilter({"Transport": dbus.String("le")})
    iface.StartDiscovery()
    print("Scanning; Ctrl-C to stop")
    try:
        GLib.MainLoop().run()
    except KeyboardInterrupt:
        iface.StopDiscovery()

if __name__ == "__main__":
    main()
