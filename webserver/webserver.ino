#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "TheMulligan-2.4";
const char* password = "7CC4LCDCHHHKAH3C";

//int ledPin = 2; // GPIO2
WiFiServer server(80);
boolean alreadyConnected = false; // whether or not the client was connected previously

//NEOPIXEL stuff
#define PIN 4

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
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
// Check if a client has connected
  WiFiClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    while(client.connected())
    {
      if(client.available())
      {
        String in = client.readStringUntil('\r');
        Serial.println(in);
        turnColor(strip.Color(in.toInt(), in.toInt(), 255));
      }
    }
  }
  else
  {
    return;
  }
}
/*
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

int value = LOW;
if (request.indexOf("/LED=RED") != -1) {
turnColor(strip.Color(255,0,0));
value = HIGH;
}
if (request.indexOf("/LED=GREEN") != -1) {
turnColor(strip.Color(0,255,0));
value = LOW;
}

// Set ledPin according to the request
//digitalWrite(ledPin, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("Led pin is now: ");

if(value == HIGH) {
client.print("Red");
} else {
client.print("Green");
}
client.println("<br><br>");
client.println("Click <a href=\"/LED=RED\">here</a> turn the LEDs RED<br>");
client.println("Click <a href=\"/LED=GREEN\">here</a> turn the LEDs GREEN<br>");
client.println("</html>");

/*delay(1);
Serial.println("Client disonnected");
Serial.println("");*/

void turnColor(uint32_t c)
{
  for(int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

