/*
Small software to test the output power of LoRa modules used with an Arduino pro-mini

written by TK5EP march 2025
https://egloff.eu
https://github.com/tk5ep
*/


/***************************************
 ____       _   _   _                 
/ ___|  ___| |_| |_(_)_ __   __ _ ___ 
\___ \ / _ \ __| __| | '_ \ / _` / __|
 ___) |  __/ |_| |_| | | | | (_| \__ \
|____/ \___|\__|\__|_|_| |_|\__, |___/
                            |___/ 
****************************************/

#define WITH_SX1278

// TX transmission delay in ms 
int TXdelay   = 10000;
// TX frequency in MHz
double TXfreq = 433.775;
// Freq error in MHz, start with 0 and after reading the frequency on a frequencymeter, enter correction. ie if +21kHz offset => -0.021
double FREQ_ERR = 0;
// TX power in dBm max 22 with a SX1268 and 20 with a SX1278
int TXpower =20;

/*****************************************
  ____             __ _       
 / ___|___  _ __  / _(_) __ _ 
| |   / _ \| '_ \| |_| |/ _` |
| |__| (_) | | | |  _| | (_| |
 \____\___/|_| |_|_| |_|\__, |
                        |___/ 
*****************************************/
// include the libraries
#include <Arduino.h>
#include <RadioLib.h>

/* PINs mapping SPI LoRa Radio
comment out the one you use or make or own
*/
/*
// Board IIRIS V3
  #define LORA_SCK      13
  #define LORA_MISO     12
  #define LORA_MOSI     11
  #define LORA_SS       10
  #define LORA_DIO0     26
  #define LORA_DIO1     33  // pin LoRa1 on header not connected to IO pin
  //#define LORA_BUSY     32  // pin LoRa2 on header
  #define LORA_RST      23
*/
  // IIRIS BOARD V4.1
  #define LORA_SCK      13
  #define LORA_MISO     12
  #define LORA_MOSI     11
  #define LORA_SS       10
  #define LORA_DIO0     2
  #define LORA_DIO1     3
   #define LORA_RST     4

// instance for LoRa module
  SX1278 radio = new Module(LORA_SS, LORA_DIO0, LORA_RST, LORA_DIO1);

/*****************************
 _____      _               
/  ___|    | |              
\ `--.  ___| |_ _   _ _ __  
 `--. \/ _ \ __| | | | '_ \ 
/\__/ /  __/ |_| |_| | |_) |
\____/ \___|\__|\__,_| .__/ 
                     | |    
                     |_|    
******************************/
void setup() {
  Serial.begin(115200);

    // initialize SX1278 with default settings
    Serial.print(F("[SX1278] Initializing ... "));

  int state = radio.beginFSK(TXfreq);
  if(state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Initializing OK"));
  } else {
    Serial.print(F("failed, code "));
    while(true);
  }

    // set over current protection limit to 80 mA (accepted range is 45 - 140 mA)
    // NOTE: set value to 0 to disable overcurrent protection
    if (radio.setCurrentLimit(140) == RADIOLIB_ERR_INVALID_CURRENT_LIMIT) {
        Serial.println(F("Selected current limit is invalid for this module!"));
        while (true);
    }

  state = radio.setFrequency(TXfreq + FREQ_ERR);   // set the frequency
    if(state == RADIOLIB_ERR_NONE) {
    Serial.println(String(TXfreq,3) + " frequency setting success!");
  } else {
    Serial.print(F("Frequency setting failed, code "));
    Serial.println(state);
    while(true);
  }

  state = radio.setOutputPower(TXpower);
  if(state == RADIOLIB_ERR_NONE) {
    Serial.println("+" +String(TXpower) + "dBm power setting success!");
  } else {
    Serial.print(F("Power setting failed, code "));
    Serial.println(state);
    //while(true);
  }
} // END setup()

/*****************************
 _                       
| |                      
| |     ___   ___  _ __  
| |    / _ \ / _ \| '_ \ 
| |___| (_) | (_) | |_) |
\_____/\___/ \___/| .__/ 
                  | |    
                  |_|    
*****************************/
void loop() {
  radio.transmitDirect();

  Serial.println("Transmitting +" + String(TXpower) +"dBm FM carrier ...\n ");
  delay(TXdelay);
  radio.standby();

  Serial.print("Stop transmitting for safety reason. Press RESET button to start again.");
  Serial.println("Change TXdelay parameter for a longer transmission.");
  while(1) {
    //do nothing in here
  }
}
