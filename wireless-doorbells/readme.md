# 433.92 MHz Wireless Doorbell Hacking
Hi!  I hacked a wireless doorbell :p

This work was performed as part of a series of tutorial events done for the Queen's University Belfast Amateur Radio and Electronics Society (QUB_ARES).

## Reverse Engineering Artifacts
- [URH Captures](./URH%20Captures/) contains a Universal Radio Hacker project with captures for all the devices I've tested
- [433MHz Module Tests](./433MHz%20Module%20Tests/) contains a few Arduino sketches for testing and parsing protocols used by EV1527 devices, using the [rc-switch](https://github.com/sui77/rc-switch) library, as well as experiments with the [Radiohead](https://www.airspayce.com/mikem/arduino/RadioHead/) library
- [rc-switch-modified](./rc-switch-modified/) a modified version of rc-switch which transmits the sync pulse before the data sections

## Transmitter Codes
These are codes derived from transmitters I've analysed.  The Code column is the decimal representation of the unique key part and the data part together.  Remember that the unique key parts mean that these codes are almost completely unique to the specific devices I used; the likely won't do anything for other devices.  They are included just for reference.

The codes were parsed using the [`rc_receive`](./433MHz%20Module%20Tests/rc_receive/) script, although they could also be manually parsed using a tool like URH.

| Device | Button | Code (key+btn) | Bits | Pulse length (µs) | Protocol |
|--------|--------|----------------|------|-------------------|----------|
| Jisusu Doorbell       | Doorbell | 139187    | 24 | 200 | 1 |
| Dewenwils Switch      | 1 On     | 7836460   | 24 | 175 | 1 |
|                       | 1 Off    | 7836452   | 24 | 175 | 1 |
|                       | 2 On     | 7836458   | 24 | 175 | 1 |
|                       | 2 Off    | 7836450   | 24 | 175 | 1 |
|                       | 3 On     | 7836457   | 24 | 175 | 1 |
|                       | 3 Off    | 7836449   | 24 | 175 | 1 |