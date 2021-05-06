/*
 **************************************************************************************************
 * Sketch : Turns an LED ON/OFF over a bluetooth link using HC-05/HC-06 module 
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : TXD ->  2
            RXD ->  3
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include<SoftwareSerial.h>
 
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
 SoftwareSerial mySerial(2, 3); 
 int LED = 6;
 int BUZZ =5;
 char key;

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
 void setup(){
    pinMode(LED,OUTPUT);    // set pin 6 as output
    pinMode(BUZZ,OUTPUT);    // set pin 5 as output
    Serial.begin(9600);     // set serial com at 9600bps                                 
    mySerial.begin(9600);   // set myserial com at 9600bps
    }

/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  if(mySerial.available()>0){
    key = mySerial.read();
    if(key=='1') {               // configure button in bluetooth app as '1' to turn ON an LED
      digitalWrite(LED,HIGH);
      digitalWrite(BUZZ,HIGH);
    }
    else if(key=='0') {           // configure button in bluetooth app as '0' to turn OFF an LED
      digitalWrite(LED,LOW);
      digitalWrite(BUZZ,LOW);
    }
   }
  }
