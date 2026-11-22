# HYWS-SGT0204S

| Field | Value |
|---|---|
| Model | HYWS-SGT0204S |
| PCB | 2G5F4_10G2_V1.04 |
| PCB date | 2024-09-19 |
| Manufacturer | Hongyavision (Shenzhen Hongyavision Electronic Technology) |
| SoC | RTL8372 |
| Copper | 4 x 2.5G RJ45 |
| Uplink | 2 x SFP+ |
| Flash | 4 Mbit / 512 KB, single-IO |
| Stock firmware | not available |
| Tested firmware | V0.2.10_LEDBROKE |

## Differences from V1.01

The upstream profile `2G5F4_10G2_V1_01` uses GPIO30 / GPIO50 for SFP detect.
On this V1.04 board the detect pins are:

```text
SFP1 (left,  physical 5) = GPIO38
SFP2 (right, physical 6) = GPIO37
```

Reading `gpio` before and after inserting a module shows exactly these two
lines changing. With the upstream pins the console command `sfp` reported
both slots as empty and neither cage passed traffic.

## Ports

```text
physical 1-4 -> logical 4-7
SFP1         -> logical 8, SDS1
SFP2         -> logical 3, SDS0
```

## SFP

```text
SFP1 I2C = GPIO39 (SDA4) / GPIO40 (SCL3)
SFP2 I2C = GPIO41 (SDA3) / GPIO40 (SCL3)
LOS pins kept from upstream (GPIO37 / GPIO10), not verified individually
TX disable: not connected
```

Verified with a 10G multimode module and a 10G copper module: both cages link
and pass traffic to 2.5G peers.

Note: a 10G copper module appears to the switch as a 10G port regardless of the
speed negotiated by the module (2.5G in our tests), so the cage's "10G" state is
what the ASIC reports.

## LEDs

13 lamps on the chassis. See [../led/open-question.md](../led/open-question.md)
for the three that cannot be driven and the full list of experiments.

## Flash

- 512 KB image
- `flash_sio = 1`, single-IO read; DIO does not work with this chip
- Web firmware update is rejected (HTTP 400), use a programmer
- No reset pin (`GPIO_NA`); the 3-hole reset footprint is unpopulated and the
  case has no opening for it

## Power

12 V DC, 2 A (per the label on the unit).