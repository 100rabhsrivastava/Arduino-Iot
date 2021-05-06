/*
 **************************************************************************************************
 * Sketch : Plays sa-re-ga-ma-pa-dha-ni-sa' (aaroh) and sa'-ni-dha-pa-ma-ga-re-sa (avaroh) on a 
            piezo buzzer continuously
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
  int sa=262, re=294, ga=330, ma=349, pa=392, dha=440, ni=494, sa1=524; // freqencies of notes
  int PIEZO=5;      // label pin 5 as PIEZO
  int duration=500; // duration of playing of a note  
  int tempo=667;    // interval between two notes(tempo=1.3*duration)

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
  /* aaroh  */
  tone(PIEZO, sa, duration);  // play 'sa'
  delay(tempo);               
  tone(PIEZO, re, duration);  // play 're'
  delay(tempo);
  tone(PIEZO, ga, duration);  // play 'ga'
  delay(tempo);
  tone(PIEZO, ma, duration);  // play 'ma'
  delay(tempo);
  tone(PIEZO, pa, duration);  // play 'pa'
  delay(tempo);
  tone(PIEZO, dha, duration); // play 'dha'
  delay(tempo);
  tone(PIEZO, ni, duration);  // play 'ni'
  delay(tempo);
  tone(PIEZO, sa1, duration); // play 'sa1'
  delay(tempo);
  /* avaroh  */
  tone(PIEZO, sa1, duration); // play 'sa1'
  delay(tempo);
  tone(PIEZO, ni, duration);  // play 'ni'
  delay(tempo);
  tone(PIEZO, dha, duration); // play 'dha'
  delay(tempo);
  tone(PIEZO, pa, duration);  // play 'pa'
  delay(tempo);
  tone(PIEZO, ma, duration);  // play 'ma'
  delay(tempo);
  tone(PIEZO, ga, duration);  // play 'ga'
  delay(tempo);
  tone(PIEZO, re, duration);  // play 're'
  delay(tempo);
  tone(PIEZO, sa, duration);  // play 'sa'
  delay(tempo);
 }
