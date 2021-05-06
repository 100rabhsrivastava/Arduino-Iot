/*
 **************************************************************************************************
 * Sketch : Reads an LDR and send its value (0-~512) over RF link
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : CE  -> A0 
            CSN -> 9
            LDR -> A7
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */ 
 
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include <SPI.h>     // library for SPI devices
 #include <RF24.h>    // Optimized fork of nRF24L01
                      // (https://github.com/nRF24/RF24)
    
/*
 * ------------------------------------------------------------------------------------------------
 * Macros
 * ------------------------------------------------------------------------------------------------
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * Global declarations
 * ------------------------------------------------------------------------------------------------
 */
 RF24 radio(A0, 9); // CE, CSN
 const byte address[6] = "00001";
 int sensorPin = A7;
 int sensorValue = 0;

/*
 * ------------------------------------------------------------------------------------------------
 * Functions, ISRs
 * ------------------------------------------------------------------------------------------------
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your setup code here, to run once:
 * ------------------------------------------------------------------------------------------------
 */
 void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  } 

/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  radio.write(&sensorValue, sizeof(sensorValue));
  delay(500);  
  }
