/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */

#include <SPI.h>
#include <Ethernet.h>

String readString;
int ledPinRed = 3;
int ledPinGreen = 9;
int ledPinBlue = 5;
int ledConnected = 7;



// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 240);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(ledConnected, OUTPUT);



  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Welcome master mako");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();


if (client) {
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                digitalWrite(ledConnected, HIGH); // connected

                

                //read char by char HTTP request
                if (readString.length() < 100) {

                    //store characters to string
                    readString += c;
                }

                //if HTTP request has ended– 0x0D is Carriage Return \n ASCII
                if (c == 0x0D) {
                    client.println("HTTP/1.1 200 OK"); //send new page
                    client.println("Content-Type: text/html");
                    client.println();

                    client.println("<HTML>");
                    client.println("<HEAD>");
                    client.println("<TITLE>LED MaKo</TITLE>");
                    client.println("</HEAD>");
                    client.println("<BODY>");
                    client.println("<hr>");
                    client.println("<hr>");
                    client.println("<br>");
                    client.println("<H1 style=\"color:green;\">t3kn4rk1st</H1>");
                    client.println("<hr>");
                    client.println("<br>");

                    client.println("<H2><a href=\"/?LEDONRED\"\">Turn On Red LED</a><br></H2>");
                    client.println("<H2><a href=\"/?LEDOFFRED\"\">Turn Off Red LED</a><br></H2>");
                    client.println("<br>");
                    client.println("<H2><a href=\"/?LEDONGREEN\"\">Turn On Green LED</a><br></H2>");
                    client.println("<H2><a href=\"/?LEDOFFGREEN\"\">Turn Off Green LED</a><br></H2>");
                    client.println("<br>");
                    client.println("<H2><a href=\"/?LEDONBLUE\"\">Turn On Blue LED</a><br></H2>");
                    client.println("<H2><a href=\"/?LEDOFFBLUE\"\">Turn Off Blue LED</a><br></H2>");
                    client.println("<br>");


                    client.println("</BODY>");
                    client.println("</HTML>");

                    delay(10);
                    //stopping client
                    client.stop();

                    // control arduino pin
                    if(readString.indexOf("?LEDONRED") > -1) //checks for LEDON
                    {
                            digitalWrite(ledPinRed, LOW); // set pin low
                                Serial.println("Low");
                    }
                    else{
                        if(readString.indexOf("?LEDOFFRED") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPinRed, HIGH); // set pin high
                            Serial.println("Higher");
                        }
                    }

                    if(readString.indexOf("?LEDONGREEN") > -1) //checks for LEDON
                    {
                            digitalWrite(ledPinGreen, LOW); // set pin low
                                Serial.println("Low");
                    }
                    else{
                        if(readString.indexOf("?LEDOFFGREEN") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPinGreen, HIGH); // set pin high
                            Serial.println("Higher");
                        }
                    }

                    if(readString.indexOf("?LEDONBLUE") > -1) //checks for LEDON
                    {
                            digitalWrite(ledPinBlue, LOW); // set pin low
                                Serial.println("Low");
                    }
                    else{
                        if(readString.indexOf("?LEDOFFBLUE") > -1) //checks for LEDOFF
                        {
                            digitalWrite(ledPinBlue, HIGH); // set pin high
                            Serial.println("Higher");
                        }
                    }


                    
                    //clearing string for next read
                    readString="";

                }
            }else{
                     digitalWrite(ledConnected, LOW); // connected
            }
        }
    }
  
}
