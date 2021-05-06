# rushi-nano-dev-board
Tested OK codes written for Arduino NANO Development Board.
/*
 **************************************************************************************************
 * Title  : README file 
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Sketch : 1) Blinks an LED continuously
	    2) Reads switches and prints their status (OPEN/CLOSE) on serial monitor
	    3) Reads an LDR and prints its value (0-~512) on serial monitor
	    4) Fades and brightens an LED continuously
            5) Beeps a piezo buzzer continuously
	    6) Plays sa-re-ga-ma-pa-dha-ni-sa' (aaroh) and sa'-ni-dha-pa-ma-ga-re-sa (avaroh) on a 
            piezo buzzer continuously
	    7) Configures NANO for interrupts and ISR prints status on serial monitor
	    8) Reads a rotary encoder and prints its status on serial monitor
	    9) To test various functions available in Adafruit_GFX and Adafruit_PCD8544 libraries on 
            NOKIA 5110 GLCD
	    10) To test various functions available in Adafruit_GFX and Adafruit_SSD1306 libraries on 
            0.96" I2C OLED
	    11) Reads an LDR and send its value (0-~512) over a RF link
	    12) Receive an LDR values (0-~512) over a RF link
            13) Turns an LED ON/OFF over a bluetooth link using HC-05/HC-06 module
	    14) Turns an LED and a PIEZO ON/OFF over a WiFi link
	    15) Menu driven code to test on-board peripherals and uSD card module using Nokia5110 GLCD
	    and a rotary encoder
 * NOTE	  : 1) All example codes from Arduino IDE (File->Examples->SD) will work on HACK-NANO board
	    by making chipSelect=10
	    2) Download Rtc by Makuna from https://github.com/Makuna/Rtc. Its a feature packed
	    library works flawlessly on HACK-NANO board.
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************
 */
