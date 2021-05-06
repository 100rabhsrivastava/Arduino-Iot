/*
 **************************************************************************************************
 * Sketch : Fades and brightens an LED continously
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : LED -> 6 
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
 int LED=6;            // label pin 6 as LED
 int brightness = 0;   // for storing brightness value
 int fadeAmount = 10;  // step size for brightness 

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
  pinMode(LED,OUTPUT);    // set pin 6 as output  
  } 
  
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  analogWrite(LED, brightness);             // set LED brightness
  brightness = brightness + fadeAmount;     // change the brightness by fadeAmount
  if (brightness <= 0 || brightness >= 250) // maximum dark(0) or bright(250) level is reached
    fadeAmount = -fadeAmount;               // negate the fadeAmount
  delay(100);                               // delay to see the dimming effect 
 }
