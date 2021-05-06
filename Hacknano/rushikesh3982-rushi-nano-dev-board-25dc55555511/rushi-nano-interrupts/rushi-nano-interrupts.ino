/*
 **************************************************************************************************
 * Sketch : Configures NANO for interrupts and ISR prints status on serial monitor 
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : INT2 -> 2 
            INT3 -> 3 
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
 int INT2=2; // label pin 2 as INT2
 int INT3=3; // label pin 3 as INT3

/*
 * ------------------------------------------------------------------------------------------------
 * Functions, ISRs
 * ------------------------------------------------------------------------------------------------
 */
 /* ISR for interrpt 2 */
 void ISR2() {                             
  Serial.println("Interrupted on pin 2"); // print message
 }
 /* ISR for interrpt 3 */
 void ISR3() {                             
  Serial.println("Interrupted on pin 3"); // print message
 }
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your setup code here, to run once:
 * ------------------------------------------------------------------------------------------------
 */
 void setup() {
  pinMode(INT2, INPUT_PULLUP);                                  // set pin 2 as input pullup
  pinMode(INT3, INPUT_PULLUP);                                  // set pin 3 as input pullup
  attachInterrupt(digitalPinToInterrupt(INT2), ISR2, FALLING);  // set interrupt 2
  attachInterrupt(digitalPinToInterrupt(INT3), ISR3, FALLING);  // set interrupt 3
  Serial.begin(9600);                                           // set serial com at 9600bps      
 } 
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  // do nothing
 }
