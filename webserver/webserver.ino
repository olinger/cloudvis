#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "72 Pinewoods_2.4GHz";
const char* password = "JOSSWG72";

//int ledPin = 2; // GPIO2
WiFiServer server(80);

//NEOPIXEL stuff
#define PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
Serial.begin(115200);
delay(10);

//pinMode(ledPin, OUTPUT);
//digitalWrite(ledPin, LOW);

// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");

//neopixel setup
  Serial.begin(115200);
  delay(100);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println("new client");
while(!client.available()){
delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Match the request

/*int value = LOW;
if (request.indexOf("/LED=ON") != -1) {
digitalWrite(ledPin, HIGH);
value = HIGH;
}
if (request.indexOf("/LED=OFF") != -1) {
digitalWrite(ledPin, LOW);
value = LOW;
}

// Set ledPin according to the request
//digitalWrite(ledPin, value);*/

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("Led pin is now: ");

/*if(value == HIGH) {
client.print("On");
} else {
client.print("Off");
}*/
client.println("<br><br>");
client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br>");
client.println("</html>");

delay(1);
Serial.println("Client disonnected");
Serial.println("");

}

void turnColor(uint32_t c)
{
//  for(int i = 0; i < strip.numLeds()
}


