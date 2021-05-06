#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 
double temp_amb;
double temp_obj;
double calibration = 2.36;
 
char auth[] = "LD1g0X4hiJ0oVGpXavxa6X3pg9IqfSJC";    // You should get Auth Token in the Blynk App.
char ssid[] = "DIR-615-A612";                       // Your WiFi credentials.
char pass[] = "12345678";

 
void setup()
{
  Serial.begin(9600);
  mlx.begin();         //Initialize MLX90614
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  Blynk.begin(auth, ssid, pass);
  
  Serial.println("Temperature Sensor MLX90614");
 
  display.clearDisplay();
  display.setCursor(25,15);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Thermometer");
  display.setCursor(25,35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(2500);
}
 
void loop()
{
  //Reading room temperature and object temp
  //for reading Fahrenheit values, use
  //mlx.readAmbientTempF() , mlx.readObjectTempF() )
  Blynk.run();
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
 
  //Serial Monitor
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);
 
  display.clearDisplay();
  display.setCursor(25,0);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Temperature");
  
  display.setCursor(10,20);
  display.setTextSize(1);
  display.print("Ambient: ");
  display.print(temp_amb);
  display.print((char)247);
  display.print("C");
 
  display.setCursor(10,40);
  display.setTextSize(1);
  display.print("Object: ");
  display.print(temp_obj + calibration);
  display.print((char)247);
  display.print("C");
  
  display.display();
  
  Blynk.virtualWrite(V1, temp_amb);
  Blynk.virtualWrite(V2, (temp_obj + calibration));
  
  delay(1000);
}
