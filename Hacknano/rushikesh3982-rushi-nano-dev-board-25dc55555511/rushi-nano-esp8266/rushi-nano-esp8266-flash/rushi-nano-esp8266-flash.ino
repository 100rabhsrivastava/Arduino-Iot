/*
 **************************************************************************************************
 * Sketch : Turns an LED and a PIEZO ON/OFF from a web server (to be flashed into ESP8266 01)
            For flashing ESP8266, first upload a blank sketch to Arduino Nano. 
            Then select NodeMCU 0.9 (ESP-12 Module) board and upload this sketch.
 * Board  : RUSHI-NANO-DEVELOPMENT-BOARD
 * Wiring : Connect jumpers in FLASH mode. Press both RESET and FLASH buttons at the same time,
            release RESET first and then FLASH to enter into FLASH mode.
 * Author : Written by Rushikesh Deshmukh for http://www.rushikesh.cf
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */
  
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include <ESP8266WiFi.h>
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
 /* enter your network credentials here */
 const char* ssid     = "OnePlus 7 Pro";
 const char* password = "9096774585";

 WiFiServer server(80); // set web server port number to 80
 /*
 IPAddress ip(192, 168, 43, 135);
 IPAddress gateway(192, 168, 43, 1);
 IPAddress subnet(255, 255, 255, 0);
 IPAddress DNS(192, 168, 43, 1);
 */
 
 String header; // variable to store the HTTP request

 /* variables to store the current output state */
 String LED = "OFF";
 String PIEZO = "OFF";
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
  Serial.begin(115200);                     // set serial com at 115200bps
  
  /* connect to Wi-Fi network with SSID and password  */
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {   // while connecting print ...
    delay(500);
    Serial.print(".");
  }
  /*  print local IP address and start web server */
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
 } 
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          /*  if the current line is blank, you got two newline characters in a row.
          That's the end of the client HTTP request, so send a response */
          if (currentLine.length() == 0) {
            /*  HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            and a content-type so the client knows what's coming, then a blank line */      
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println('0');
              LED = "ON";
            } 
            else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println('1');
              LED = "OFF";
            }
            else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println('2');
              PIEZO = "ON";
            } 
            else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println('3');
              PIEZO = "OFF";
            }
                             
            /*  display the HTML web page  */
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            /*  CSS to style the on/off buttons (change to suit your style) */
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #00ff00; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #ff0000;}</style></head>");
            
            /* web page heading */
            client.println("<body><h1>ESP8266 Web Server for HACK-NANO board</h1>");
            
            /*  display current state and ON/OFF buttons  */  
            client.println("<p>LED " + LED + "</p>");    
            if (LED == "OFF")         // if LED is OFF, display the ON button       
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>"); 
            else 
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
           
            client.println("<p>PIEZO " + PIEZO + "</p>");
            if (PIEZO == "OFF")       // if PIEZO is OFF, display the ON button       
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            else 
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");

            client.println("</body></html>");
            client.println();       // HTTP response ends with another blank line
            break;                  // break out of the while loop
          } 
          else                      // if you got a newline, then clear currentLine
            currentLine = "";          
        } 
        else if (c != '\r')         // if you got anything else but a carriage return character,
          currentLine += c;         // add it to the end of the currentLine
      }
    }
    header = "";                    // Clear the header variable and close the connection
  }
}
