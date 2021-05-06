/*
 **************************************************************************************************
 * Sketch : Reads a rotary encoder and prints its status on serial monitor 
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : CLK ->  4
            DT  ->  7
            SW  ->  8
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include <ClickEncoder.h> // include rotary encoder library (https://github.com/0xPIT/encoder)
 #include <TimerOne.h>     // include Timer 1 library (https://github.com/PaulStoffregen/TimerOne)
 
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
 ClickEncoder *encoder;    // set the pointer of class ClickEncoder
 int16_t last, value;      // variables to store previous and current values

/*
 * ------------------------------------------------------------------------------------------------
 * Functions, ISRs
 * ------------------------------------------------------------------------------------------------
 */
 void timerIsr() {           // ISR for Timer 1
  encoder->service();       // access structure member by pointer
 }
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your setup code here, to run once:
 * ------------------------------------------------------------------------------------------------
 */
 void setup() {
  Serial.begin(9600);                   // set serial com at 9600bps
  encoder = new ClickEncoder(4, 7, 8);  // CLK=4, DT=7, SW=8
  Timer1.initialize(1000);              // initialize Timer 1
  Timer1.attachInterrupt(timerIsr);     // set Timer 1 interrupt
  last = -1;                            // set the previous value  
 }
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  value += encoder->getValue();         // read encoder value
  if (value != last) {                  // not equal to previous
    last = value;                       // set previous as current 
    Serial.print("Encoder Value: ");    // print the title
    Serial.println(value);              // print the value
  } 
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::Clicked)
      case ClickEncoder::DoubleClicked:
          Serial.println("ClickEncoder::DoubleClicked");
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
          Serial.print("  Acceleration is ");
          Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
    }
  }    
 }
