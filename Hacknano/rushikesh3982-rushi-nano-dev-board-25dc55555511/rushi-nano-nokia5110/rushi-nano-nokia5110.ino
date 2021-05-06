/*
 **************************************************************************************************
 * Sketch : To test various functions available in Adafruit_GFX and Adafruit_PCD8544 libraries on 
            NOKIA 5110 GLCD
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
/*
 * ------------------------------------------------------------------------------------------------
 * Macros
 * ------------------------------------------------------------------------------------------------
 */
 #define NUMFLAKES 10
 #define XPOS 0
 #define YPOS 1
 #define DELTAY 2
 #define LOGO32_GLCD_HEIGHT 32
 #define LOGO32_GLCD_WIDTH  32
/*
 * ------------------------------------------------------------------------------------------------
 * Global declarations
 * ------------------------------------------------------------------------------------------------
 */
 Adafruit_PCD8544 display = Adafruit_PCD8544(A3, A2, A1); // Hardware SPI (RST,CE,DC)
 
 static const unsigned char PROGMEM logo32_glcd_bmp[] ={
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00,
  0x00, 0xf0, 0x38, 0x00, 0x03, 0x80, 0x0e, 0x00, 0x06, 0x00, 0x03, 0x00, 0x0c, 0x00, 0x01, 0x80,
  0x18, 0x00, 0x00, 0xc0, 0x18, 0x00, 0x00, 0x40, 0x30, 0x00, 0x01, 0xc0, 0x30, 0x00, 0x07, 0x00,
  0x20, 0x00, 0x0c, 0x00, 0x60, 0x00, 0x38, 0x00, 0x60, 0x00, 0x60, 0x00, 0x60, 0x01, 0x80, 0x00,
  0x60, 0x03, 0x80, 0x00, 0x60, 0x00, 0x70, 0x00, 0x60, 0x00, 0x1c, 0x00, 0x20, 0x01, 0x87, 0x80,
  0x30, 0x00, 0xf0, 0xe0, 0x30, 0x00, 0x1c, 0x60, 0x18, 0x00, 0x02, 0xc0, 0x18, 0x00, 0x04, 0xc0,
  0x0c, 0x00, 0x0d, 0x80, 0x07, 0x00, 0x03, 0x00, 0x03, 0x80, 0x0e, 0x00, 0x00, 0xf0, 0x38, 0x00,
  0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

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
  display.begin();                    // Arguments: None
  display.setContrast(60);            // Arguments: 0-255 (try values between 30-50 for best viewing)
  display.clearDisplay();             // Arguments: None
  
  /*  display bitmap image  */
  display.drawBitmap(26,0,logo32_glcd_bmp,32,32,BLACK);// Arguments: x,y,image data,width,height,color
  display.display();              
  
  /*  display text  */
  display.setTextSize(1);             // Arguments: 1-7
  display.setTextColor(BLACK);        // Arguments: Foreground, Background(optional)
  display.setCursor(17,33);           // Arguments: x,y 
  display.println("HACK-MAN");
  display.display();
  delay(2000); 
  display.clearDisplay(); 
    
  /*  draw a single pixel */
  display.drawPixel(42,24, BLACK);   // Arguments: x,y,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a line */
  display.drawLine(0,0,84,48,BLACK);  // Arguments: x0,y0,x1,y1,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a rectangle  */
  display.drawRect(12,14,60,20,BLACK);// Arguments: x,y,width,height,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid rectangle  */
  display.fillRect(12,14,60,20,BLACK);// Arguments: x,y,width,height,color
  display.display();
  delay(1000);
  display.clearDisplay();

   /* draw a rectangle with rounded corners */
  display.drawRoundRect(12,14,60,20,4,BLACK);// Arguments: x,y,width,height,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid rectangle with rounded corners */
  display.fillRoundRect(12,14,60,20,4,BLACK);// Arguments: x,y,width,height,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();
  
  /*  draw a circle */
  display.drawCircle(42,24,20,BLACK); // Arguments: x,y,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a solid circle */
  display.fillCircle(42,24,20,BLACK); // Arguments: x,y,radius,color
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  draw a triangle */
  display.drawTriangle(42,4,82,44,2,44,BLACK);// Arguments: x0,y0,x1,y1,x2,y2,color
  display.display();
  delay(1000);
  display.clearDisplay();
  
  /*  draw a solid triangle */
  display.fillTriangle(42,4,82,44,2,44,BLACK);// Arguments: x0,y0,x1,y1,x2,y2,color
  display.display();
  delay(1000);
  display.clearDisplay();
   
  /* rotate display */
  display.setRotation(0);  // Arguments: 0=0deg/1=90deg/2=180deg/3=270deg
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(28,20);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(1);  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10,38);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(2);  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(28,20);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(3);  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10,38);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setRotation(0);  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(28,20);
  display.println("PIVOT");
  display.display();
  delay(1000);
  display.clearDisplay();

  /*  display bitmap image  */
  display.drawBitmap(26,0,logo32_glcd_bmp,32,32,BLACK);// Arguments: x,y,image data,width,height,color
  display.display();              
  
  /*  display text  */
  display.setTextSize(1);             // Arguments: 1-7
  display.setTextColor(BLACK);        // Arguments: Foreground, Background(optional)
  display.setCursor(5,31);            // Arguments: x,y 
  display.println("keep hacking, keep making!");
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
