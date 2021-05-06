/*
 **************************************************************************************************
 * Sketch : Menu driven demo program for HACK-NANO board on Nokia 5110 GLCD
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : Reset(RST)       ->  A3 
            Chip Enable(CE)  ->  A2
            Data/Command(DC) ->  A1
            Data Input(DIN)  ->  11(MOSI)
            Clock(CLK)       ->  13(SCLK) 
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************
 */
 
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include <SPI.h>               // library for SPI devices             
 #include <Adafruit_GFX.h>      // core graphics library for all displays 
                                // (https://github.com/adafruit/Adafruit-GFX-Library) 
 #include <Adafruit_PCD8544.h>  // PCD8544 supports monochrome LCDs found on old Nokia phones
                                // (https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library) 
 #include <ClickEncoder.h>      // include rotary encoder library (https://github.com/0xPIT/encoder)
 #include <TimerOne.h>          // include Timer 1 library (https://github.com/PaulStoffregen/TimerOne)
 #include <SD.h> 
/*
 * ------------------------------------------------------------------------------------------------
 * Macros
 * ------------------------------------------------------------------------------------------------
 */
 #define NUMFLAKES 10
 #define XPOS 0
 #define YPOS 1
 #define DELTAY 2
 
/*
 * ------------------------------------------------------------------------------------------------
 * Global declarations
 * ------------------------------------------------------------------------------------------------
 */
 Adafruit_PCD8544 display = Adafruit_PCD8544(A3, A2, A1); // Adafruit_PCD8544(RST,CE,DC)
 
 /* Menu items  */
 const char* menuItem1 = "Contrast";
 const char* menuItem2 = "LED ON/OFF";
 const char* menuItem3 = "LED Intensity";
 const char* menuItem4 = "INT2/SW2";
 const char* menuItem5 = "INT3/SW3";
 const char* menuItem6 = "LDR";
 const char* menuItem7 = "Buzzer";
 const char* menuItem8 = "uSD card";

 char menuitem = 1;
 char frame = 1;
 char page = 1;
 char lastMenuItem = 1;

 int contrast=55;   // Arguments: 0-255 (try values between 30-50 for best viewing)

 /* Rotary Encoder Buttons  */
 boolean up = false;        
 boolean down = false;
 boolean middle = false;
 ClickEncoder *encoder;
 int16_t last, value;
 
 /* Flags for LED and Piezo */
 bool lit = false;
 bool beep = false;

 /* PWM variable  */
 int duty=0;

 /* LDR variables */
 char lightString [4];
 String str; 
 int lightIntensity = 0;
 
/*
 * ------------------------------------------------------------------------------------------------
 * Functions, ISRs
 * ------------------------------------------------------------------------------------------------
 */
  void drawMenu() {
    /*  PAGE 1  */
    if (page==1) {
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(BLACK, WHITE);
      display.setCursor(15, 0);
      display.print("HACK-NANO");
      display.drawFastHLine(0,10,83,BLACK);
      
      if(menuitem == 1 && frame == 1)             // menu: 1, frame 1: menu 1,2,3
      {
        displayMenuItem(menuItem1, 15,true);
        displayMenuItem(menuItem2, 25,false);
        displayMenuItem(menuItem3, 35,false);
      }
      else if(menuitem == 2 && frame == 1)        // menu: 2, frame 1: menu 1,2,3
      {
        displayMenuItem(menuItem1, 15,false);
        displayMenuItem(menuItem2, 25,true);
        displayMenuItem(menuItem3, 35,false);
      }
      else if(menuitem == 3 && frame == 1)        // menu: 3, frame 1: menu 1,2,3        
      {
        displayMenuItem(menuItem1, 15,false);
        displayMenuItem(menuItem2, 25,false);
        displayMenuItem(menuItem3, 35,true);
      }
      else if(menuitem == 4 && frame == 2)        // menu: 4, frame 2:menu 2,3,4
      {
        displayMenuItem(menuItem2, 15,false);
        displayMenuItem(menuItem3, 25,false);
        displayMenuItem(menuItem4, 35,true);
      }
      else if(menuitem == 3 && frame == 2)        // menu: 3, frame 2: menu 2,3,4
      {
        displayMenuItem(menuItem2, 15,false);
        displayMenuItem(menuItem3, 25,true);
        displayMenuItem(menuItem4, 35,false);
      }
      else if(menuitem == 2 && frame == 2)        // menu: 2, frame 2: menu 2,3,4
      {
        displayMenuItem(menuItem2, 15,true);
        displayMenuItem(menuItem3, 25,false);
        displayMenuItem(menuItem4, 35,false);
      }
      else if(menuitem == 5 && frame == 3)        // menu: 5, frame 3: menu 3,4,5
      {
        displayMenuItem(menuItem3, 15,false);
        displayMenuItem(menuItem4, 25,false);
        displayMenuItem(menuItem5, 35,true);
      }

      else if(menuitem == 4 && frame == 3)        // menu: 4, frame 3: menu 3,4,5
      {
        displayMenuItem(menuItem3, 15,false);
        displayMenuItem(menuItem4, 25,true);
        displayMenuItem(menuItem5, 35,false);
      }
    
      else if(menuitem == 3 && frame == 3)        // menu: 3, frame 3: menu 3,4,5      
      {
        displayMenuItem(menuItem3, 15,true);
        displayMenuItem(menuItem4, 25,false);
        displayMenuItem(menuItem5, 35,false);
      }
      else if(menuitem == 6 && frame == 4)        // menu: 6, frame 4: menu 4,5,6                  
      {
        displayMenuItem(menuItem4, 15,false);
        displayMenuItem(menuItem5, 25,false);
        displayMenuItem(menuItem6, 35,true);
      }
      else if(menuitem == 5 && frame == 4)        // menu: 5, frame 4: menu 4,5,6      
      {
        displayMenuItem(menuItem4, 15,false);
        displayMenuItem(menuItem5, 25,true);
        displayMenuItem(menuItem6, 35,false);
      }
      else if(menuitem == 4 && frame == 4)        // menu: 4, frame 4: menu 4,5,6      
      {
        displayMenuItem(menuItem4, 15,true);
        displayMenuItem(menuItem5, 25,false);
        displayMenuItem(menuItem6, 35,false);
      }
      else if(menuitem == 7 && frame == 5)        // menu: 7, frame 5: menu 5,6,7      
      {
        displayMenuItem(menuItem5, 15,false);
        displayMenuItem(menuItem6, 25,false);
        displayMenuItem(menuItem7, 35,true);
      }   
      else if(menuitem == 6 && frame == 5)        // menu: 6, frame 5: menu 5,6,7      
      {
        displayMenuItem(menuItem5, 15,false);
        displayMenuItem(menuItem6, 25,true);
        displayMenuItem(menuItem7, 35,false);
      }
      else if(menuitem == 5 && frame == 5)        // menu: 5, frame 5: menu 5,6,7      
      {
        displayMenuItem(menuItem5, 15,true);
        displayMenuItem(menuItem6, 25,false);
        displayMenuItem(menuItem7, 35,false);
      }
      else if(menuitem == 8 && frame == 6)        // menu: 8, frame 6: menu 6,7,8      
      {
        displayMenuItem(menuItem6, 15,false);
        displayMenuItem(menuItem7, 25,false);
        displayMenuItem(menuItem8, 35,true);
      }   
      else if(menuitem == 7 && frame == 6)        // menu: 7, frame 6: menu 6,7,8      
      {
        displayMenuItem(menuItem6, 15,false);
        displayMenuItem(menuItem7, 25,true);
        displayMenuItem(menuItem8, 35,false);
      }
      else if(menuitem == 6 && frame == 6)        // menu: 6, frame 6: menu 6,7,8      
      {
        displayMenuItem(menuItem6, 15,true);
        displayMenuItem(menuItem7, 25,false);
        displayMenuItem(menuItem8, 35,false);
      }

      display.display();
      }
      /*  PAGE 2  */  
      else if (page==2 && menuitem == 1) {  
         displayIntMenuPage(menuItem1, "turn knob < >", contrast);
      }
      else if (page==2 && menuitem == 2) {  
        if(lit == true)
          displayStringMenuPage(menuItem2, "turn knob < >", "ON");
        else
          displayStringMenuPage(menuItem2, "turn knob < >", "OFF");
      }
      else if (page==2 && menuitem == 3) {
        displayIntMenuPage(menuItem3, "turn knob < >", duty);
      }
      else if (page==2 && menuitem == 4) {
        if(digitalRead(2) == HIGH)
          displayStringMenuPage(menuItem4, "SW2 status", "OPEN");
        else
          displayStringMenuPage(menuItem4, "SW2 status", "CLOSE");
      }
      else if (page==2 && menuitem == 5) {
        if(digitalRead(3) == HIGH) 
          displayStringMenuPage(menuItem5, "SW3 status", "OPEN");
        else
          displayStringMenuPage(menuItem5, "SW3 status", "CLOSE");        
      }
      else if (page==2 && menuitem == 6) { 
        lightIntensity = analogRead(A7);
        lightIntensity = map(lightIntensity, 1050, 20, 0, 100);
        str = String(lightIntensity)+"%";
        str.toCharArray(lightString,4); 
        printBar();
        fillBar(lightIntensity);   
        //displayIntMenuPage(menuItem6, "Light", 600-analogRead(A7));
        delay(100);
      }
      else if (page==2 && menuitem == 7) {
        if(beep == true)
          displayStringMenuPage(menuItem7, "turn knob < >", "beep!");
        else
          displayStringMenuPage(menuItem7, "turn knob < >", "mute");
      }
      else if (page==2 && menuitem == 8) {
        SDcard();
      }
  }

  void timerIsr() {
  encoder->service();
  } 

  void readRotaryEncoder() {
    value += encoder->getValue();
  
    if (value/2 > last) {
      last = value/2;
      down = true;
      delay(150);
    }
    else   if (value/2 < last) {
      last = value/2;
      up = true;
      delay(150);
    }
  }

  void displayMenuItem(String item, int position, boolean selected) {
    if(selected)
      display.setTextColor(WHITE, BLACK);
    else
      display.setTextColor(BLACK, WHITE);
    display.setCursor(0, position);
    display.print(">"+item);
  }

  void displayStringMenuPage(const char* menuItem, const char* type, const char* value) {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
    display.print(type);
    display.setTextSize(2);
    display.setCursor(0, 25);
    display.print(value);
    display.display();
  }

  void displayIntMenuPage(const char* menuItem, const char* type, int value) {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.print(menuItem);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
    display.print(type);
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(value);
    display.setTextSize(2);
    display.display();
  }

  void setContrast() {
    display.setContrast(contrast);
    display.display();
  }

  void printBar() {  
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.print(menuItem6);
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
    display.print("light meter");
    display.setCursor(35, 30);
    display.print(lightString);
    display.drawRect(2,40,81,5,BLACK);            // Arguments: x,y,width,height,color
    display.display();
  }

  void fillBar(int percent) {
    percent = map(percent,0,100,2,81);     
    display.drawLine(2, 41, percent, 41, BLACK);  // Arguments: x0,y0,x1,y1,color
    display.drawLine(2, 42, percent, 42, BLACK);
    display.drawLine(2, 43, percent, 43, BLACK);
    display.drawLine(2, 44, percent, 44, BLACK);
    display.display();   
   }
  
  void SDcard() {
    Sd2Card card;
    SdVolume volume;
    SdFile root;
    const char chipSelect = 10;
    
    if (!card.init(SPI_HALF_SPEED, chipSelect))
      displayStringMenuPage(menuItem8, "card health", "not OK");
    else {
      /*
      uint32_t volumesize;
      volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
      volumesize *= volume.clusterCount();       // we'll have a lot of clusters
      volumesize *= 512;                         // SD card blocks are always 512 bytes
      volumesize /= 1024;
      displayIntMenuPage(menuItem8, "card health", volumesize);
      */
      displayStringMenuPage(menuItem8, "card health", "OK");
    }
  }
 
/*
 * ------------------------------------------------------------------------------------------------
 * put your setup code here, to run once:
 * ------------------------------------------------------------------------------------------------
 */
 void setup() { 
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A7,INPUT);
  randomSeed(analogRead(A7));
  
  encoder = new ClickEncoder(4, 7, 8);  // CLK=4, DT=7, SW=8
  encoder->setAccelerationEnabled(false);
   
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = encoder->getValue();
 
  display.begin();                    // Arguments: None
  display.setContrast(contrast);      
  display.clearDisplay();             // Arguments: None    
  
  
  display.drawRect(0,4,42,30,BLACK);// Arguments: x,y,width,height,color
  display.display();
  
  display.fillRect(42,4,42,30,BLACK);// Arguments: x,y,width,height,color
  display.display();
  
  display.setTextSize(1);             // Arguments: 1-7
  display.setTextColor(BLACK);        // Arguments: Foreground, Background(optional)
  display.setCursor(16,15);           // Arguments: x,y 
  display.println("#@(<");
  display.display();
  display.setTextColor(WHITE);        // Arguments: Foreground, Background(optional)
  display.setCursor(43,15);           // Arguments: x,y 
  display.println("-MAN");
  display.display();
  display.setTextColor(BLACK);        // Arguments: Foreground, Background(optional)
  display.setCursor(0,37);           // Arguments: x,y 
  display.println("Hacking4Making");
  display.display();
  delay(3000); 
  display.clearDisplay();
  }
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  drawMenu();
  readRotaryEncoder();
  ClickEncoder::Button b = encoder->getButton();
  
  if (b != ClickEncoder::Open) {
    switch (b) {
      case ClickEncoder::Clicked:middle=true;
      break;
      }
  }    
  
  /*  Rotate clockwise  */
  if (up && page == 1 ) {
    up = false;                       // restore default      
      
    if(menuitem==2 && frame ==2)
      frame--;      
    if(menuitem==3 && frame ==3)
      frame--;
    if(menuitem==4 && frame ==4)
      frame--;      
    if(menuitem==5 && frame ==5)
      frame--;
    if(menuitem==6 && frame ==6)
      frame--;
      
    lastMenuItem = menuitem;
    menuitem--;
    
    if (menuitem==0)
      menuitem=1;
  }
       
  else if (up && page == 2 && menuitem==1 ) {
    up = false;                                   // restore default
    contrast--;
    setContrast();
  }
  
  else if (up && page == 2 && menuitem==2 ) {
    up = false;                                   // restore default
    digitalWrite(6,LOW);
    lit = false;
  }
  
  else if (up && page == 2 && menuitem==3 ) {
    up = false;
    if (duty <= 0) 
      duty = 275;
    duty = duty - 25;
    analogWrite(6,duty);
  }
    
  else if (up && page == 2 && menuitem==4 ) 
    up = false;
    
  else if (up && page == 2 && menuitem==5 ) 
    up = false;
  
  else if (up && page == 2 && menuitem==6 ) 
    up = false;
    
  else if (up && page == 2 && menuitem==7 ) {
    up = false;
    digitalWrite(5,LOW);
    beep = false;
  }   
  else if (up && page == 2 && menuitem==8 ) 
    up = false;

  /*  Rotate clockwise */
  if (down && page == 1)  {
    down = false;
    
    if(menuitem==3 && lastMenuItem == 2)
      frame ++;
    else  if(menuitem==4 && lastMenuItem == 3)
      frame ++;
    else  if(menuitem==5 && lastMenuItem == 4)
      frame ++; 
    else  if(menuitem==6 && lastMenuItem == 5)
      frame ++;
    else  if(menuitem==7 && lastMenuItem == 6 && frame != 6)
      frame ++;

    lastMenuItem = menuitem;
    menuitem++;  
    if (menuitem==9) 
      menuitem--;
  }
  
  else if (down && page == 2 && menuitem==1) {
    down = false;
    contrast++;
    setContrast();
  }
  else if (down && page == 2 && menuitem==2) {
    down = false;
    digitalWrite(6,HIGH);
    lit = true;  
  } 
  else if (down && page == 2 && menuitem==3) {
    down = false;
    if (duty >= 250) 
      duty = -25;
    duty = duty + 25;
    analogWrite(6,duty);
  }
  else if (down && page == 2 && menuitem==4 )
    down = false;
  else if (down && page == 2 && menuitem==5 )
    down = false;
  else if (down && page == 2 && menuitem==6 )
    down = false;
  else if (down && page == 2 && menuitem==7 ) {
    down = false;
    digitalWrite(5,HIGH);
    beep = true; 
  }
  else if (down && page == 2 && menuitem==8 ) 
    down = false;
   
  /*  Middle Button is Pressed  */
  if (middle) {
    middle = false;                             // restore status    
    if (page == 1)
      page=2;
    else if (page == 2) 
      page=1; 
   }  
  }
