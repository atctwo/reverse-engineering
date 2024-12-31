# 433MHz Module Tests
These Arduino scripts were used for parsing transmissions from 433MHz devices, as well as spoofing those transmissions (replay attacks).

## RadioHead scripts
- [`rh_send`](./rh_send/): script for sending a string using Radiohead's ASK modulation
- [`rh_receive`](./rc_receive/) script for receiving and parsing RH ASK transmissions

## rc-switch scripts
- [`rc_receive`](./rc_receive/): script for receiving and parsing 433MHz transmissions.  based on rc-switch's [advanced receive example](https://github.com/sui77/rc-switch/tree/master/examples/ReceiveDemo_Advanced) so it should be able to parse any protocol 
- [`rc_send`](./rc_send/): script for transmitting 433MHz codes when a button is pressed
  - please note that I could only get this working by [modifying the rc-switch library](../rc-switch-modified/) to send the sync pulse before the data sections