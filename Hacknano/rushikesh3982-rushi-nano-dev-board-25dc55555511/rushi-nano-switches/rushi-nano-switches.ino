/*
 **************************************************************************************************
 * Sketch : Reads switches and prints their status (OPEN/CLOSE) on serial monitor
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : SW1 -> 2 
            SW2 -> 3
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
 int SW1=2;            // label pin 2 as SW1
 int SW2=3;            // label pin 3 as SW2

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
  pinMode(SW1,INPUT_PULLUP);  // set pin 2 as input pullup
  pinMode(SW2,INPUT_PULLUP);  // set pin 3 as input pullup
  Serial.begin(9600);         // set serial com at 9600bps   
 } 
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
  void loop() {
    if(digitalRead(SW1)==1)                   // reads SW1 and checks its status
      Serial.print("Switch 1 is OPEN \t");
    else
      Serial.print("Switch 1 is CLOSED \t");
    
    if(digitalRead(SW2)==1)                   // reads SW2 and checks its status
      Serial.println("Switch 2 is OPEN");
    else
      Serial.println("Switch 2 is CLOSED");
    
    delay(1);                                 // delay for stability
 }
