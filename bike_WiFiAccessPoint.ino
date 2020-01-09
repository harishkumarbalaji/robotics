#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#define r1 D5
#define r2 D6
/* Set these to your desired credentials. */
const char *ssid = "Mark3";
const char *password = "vineth@123";
String command;
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
    pinMode(r1, OUTPUT);
    digitalWrite(r1,HIGH);
      pinMode(r2, OUTPUT);
      digitalWrite(r2,HIGH);
	delay(1000);
	Serial.begin(9600);
	Serial.println();
	Serial.print("Configuring access point...");
	WiFi.softAP(ssid, password);
	IPAddress myIP = WiFi.softAPIP();
	Serial.println(myIP);
	server.on("/", handleRoot);
 pinMode(2, OUTPUT);
 digitalWrite(2,LOW);
    digitalWrite(r1,HIGH);
	server.begin();
}

void loop() {
  digitalWrite(r2,HIGH);
	server.handleClient();
  server.onNotFound([](){
    command=server.uri();
  });
  Serial.println(command);
  if(command.equals("/igon"))
  {
    digitalWrite(r1,LOW);
  }
  else if(command.equals("/igoff"))
  {
    digitalWrite(r1,HIGH);
  }
  else if(command.equals("/on"))
  {
    digitalWrite(r2,LOW);
    delay(3000);
    digitalWrite(r2,HIGH);
    command = "";
  }
  delay(50);
}
