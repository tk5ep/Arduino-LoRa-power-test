# Arduino-LoRa-power-test
Purpose : Measure frequency and power of a Lora module connected on an Arduino pro-mini

Use VS + platformIO to modify the parameters in the main.cpp file </br>
TXdelay  = in seconds, transmit time before stopping transmisson</br>
TXfreq   = in MHz, transmit frequency</br>
FREQ_ERR = in MHZ, the frequency offset from programmed frequency</br>
Txpower  = in dBm, Lora module output power</br></br>
Compile and load the SW into your Arduino pro-mini.</br>

Once started, the SW will transmit a signal on the wanted frequency, power during a certain time before stopping.
This is for safety reason and to keep the LoRa module safe.

To make a new measure, you need to press the reset button.
