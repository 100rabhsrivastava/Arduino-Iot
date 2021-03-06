/*
 **************************************************************************************************
 * Sketch : Beeps a piezo buzzer continuously
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : PIEZO -> 5 
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
 int PIEZO=5;      // label pin 5 as PIEZO  
 int tempo=100;    // interval between two notes
 
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
  pinMode(PIEZO, OUTPUT); // set pin 5 as output  
  } 
  
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  /* use either digitalWrite or analogWrite functions */
  digitalWrite(PIEZO,HIGH);
  //analogWrite(PIEZO,255); // set PWM to 255
  delay(tempo);
  digitalWrite(PIEZO,LOW);
  //analogWrite(PIEZO,100); // set PWM to 100
  delay(tempo);
 }
