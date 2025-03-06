# Arduino-LoRa-power-test
Measure frequency and power of a Lora module connected on an Arduino pro-mini

Use VS + platformIO to modify the parameters in the main.cpp file </br>
TXdelay  = in seconds, transmit time before stopping transmisson</br>
TXfreq   = in MHz, transmit frequency</br>
FREQ_ERR = in MHZ, the frequency offset from programmed frequency</br>
Txpower  = in dBm, Lora module output power</br></br>
Compile and load the SW into your Arduino pro-mini.</br>
The SW will transmit
