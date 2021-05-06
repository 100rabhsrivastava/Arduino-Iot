/*
 **************************************************************************************************
 * Sketch : Turns an LED and a PIEZO ON/OFF from a web server (to be upload to Arduino Nano)
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : Connect jumpers in NORMAL mode.
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 
 
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
 int PIEZO = 5; // label pin 5 as PIEZO  
 int LED = 6;   // label pin 6 as LED  

 char command;
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
    pinMode(PIEZO,OUTPUT);    // set pin 5 as output
    pinMode(LED,OUTPUT);      // set pin 6 as output 
    Serial.begin(115200);     // set serial com at 115200bps                                
    }

/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  if(Serial.available() > 0){ 
    command = Serial.read(); 
  
    switch(command){
    case '0':         // turn LED
      digitalWrite(LED,HIGH);
      break;
    case '1':         // turn LED
       digitalWrite(LED,LOW);
      break;
    case '2':         // turn PIEZO
      digitalWrite(PIEZO,HIGH);
      break;
    case '3':         // turn PIEZO
      digitalWrite(PIEZO,LOW);
      break;
    default:          // default case
      break;
    }
  } 
 }
