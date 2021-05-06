/*
 **************************************************************************************************
 * Sketch : To test various functions available in Adafruit_GFX and Adafruit_SSD1306 libraries on 
            0.96" I2C OLED
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : SDA ->  A4
            SCL ->  A5
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
 #include <Wire.h>              // allows to communicate with I2C / TWI devices
 #include <Adafruit_GFX.h>      // core graphics library for all displays 
                                // (https://github.com/adafruit/Adafruit-GFX-Library) 
 #include <Adafruit_SSD1306.h>  // SSD1306 oled driver library for monochrome 128x64, 128x32 OLEDs
                                // (https://github.com/adafruit/Adafruit_SSD1306)
 
/*
 * ------------------------------------------------------------------------------------------------
 * Macros
 * ------------------------------------------------------------------------------------------------
 */
 #define OLED_RESET 4
 #define NUMFLAKES 10
 #define XPOS 0
 #define YPOS 1
 #define DELTAY 2
 #define LOGO24_GLCD_HEIGHT 24
 #define LOGO24_GLCD_WIDTH  24
 
/*
 * ------------------------------------------------------------------------------------------------
 * Global declarations
 * ------------------------------------------------------------------------------------------------
 */
 Adafruit_SSD1306 display(OLED_RESET);
 static const unsigned char PROGMEM logo24_glcd_bmp[] ={
  0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x01, 0xc1, 0xc0, 0x03, 0x00, 0x70, 0x06, 0x00, 0x18, 0x0c,
  0x00, 0x08, 0x18, 0x00, 0x0c, 0x10, 0x00, 0x18, 0x30, 0x00, 0x70, 0x30, 0x00, 0xc0, 0x20, 0x03,
  0x80, 0x20, 0x06, 0x00, 0x20, 0x0f, 0x00, 0x30, 0x01, 0xc0, 0x30, 0x06, 0x78, 0x10, 0x03, 0x8c,
  0x18, 0x00, 0x7c, 0x0c, 0x00, 0x0c, 0x06, 0x00, 0x78, 0x03, 0x00, 0x70, 0x01, 0xc1, 0xc0, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  #if (SSD1306_LCDHEIGHT != 32)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
  #endif

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
  /*  basic display functions */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// Arguments: None
  display.clearDisplay();                   // Arguments: None
  
  /*  display bitmap image  */
  display.drawBitmap(52,0,logo24_glcd_bmp,24,24,WHITE);// Arguments: x,y,image data,width,height,color
  display.display();              
  
  /*  display text  */
  display.setTextSize(1);             // Arguments: 1-7
  display.setTextColor(WHITE);        // Arguments: Foreground, Background(optional)
  display.setCursor(40,25);           // Arguments: x,y 
  display.println("HACK-MAN");
  display.display();
  delay(2000); 
  display.clearDisplay(); 
    
  /*  draw a single pixel */
  display.drawPixel(64,16, WHITE);   // Arguments: x,y,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a line */
  display.drawLine(0,0,128,32,WHITE);  // Arguments: x0,y0,x1,y1,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a rectangle  */
  display.drawRect(4,2,120,28,WHITE);// Arguments: x,y,width,height,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid rectangle  */
  display.fillRect(4,2,120,28,WHITE);// Arguments: x,y,width,height,color
  display.display();
  delay(1000);
  display.clearDisplay();

   /* draw a rectangle with rounded corners */
  display.drawRoundRect(4,2,120,28,4,WHITE);// Arguments: x,y,width,height,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid rectangle with rounded corners */
  display.fillRoundRect(4,2,120,28,4,WHITE);// Arguments: x,y,width,height,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();
  
  /*  draw a circle */
  display.drawCircle(64,16,15,WHITE); // Arguments: x,y,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid circle */
  display.fillCircle(64,16,15,WHITE); // Arguments: x,y,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a triangle */
  display.drawTriangle(64,1,124,31,4,31,WHITE);// Arguments: x0,y0,x1,y1,x2,y2,color
  display.display();
  delay(1000);
  display.clearDisplay();
  
  /*  draw a solid triangle */
  display.fillTriangle(64,1,124,31,4,31,WHITE);// Arguments: x0,y0,x1,y1,x2,y2,color
  display.display();
  delay(1000);
  display.clearDisplay();
   
  /* rotate display */
  display.setRotation(0);  // Arguments: 0=0deg/1=90deg/2=180deg/3=270deg
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,13);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(1);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,60);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(2);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,13);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(3);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,60);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(0);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,13);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  display bitmap image  */
  display.drawBitmap(4,7,logo24_glcd_bmp,24,24,WHITE);// Arguments: x,y,image data,width,height,color
  display.display();              
  
  /*  display text  */
  display.setTextSize(1);             // Arguments: 1-7
  display.setTextColor(WHITE);        // Arguments: Foreground, Background(optional)
  display.setCursor(40,10);            // Arguments: x,y 
  display.println("keep hacking,");
  display.setCursor(41,20);            // Arguments: x,y 
  display.println("keep making!");
  display.display();
  delay(2000);  
  }
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  
  }
