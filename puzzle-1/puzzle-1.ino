#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "First-Clue";
ESP8266WebServer server(800);

void handleRoot()
{
	String message = "<html>the data you need might be <a href='/1'>here</a></body>\n\n";
	server.send(200, "text/html", message);
}

void handleNotFound()
{
	String message = "<html>hmm. try another number?</html>\n\n";
	server.send(404, "text/html", message);
}

void setup()
{
    WiFi.softAP(ssid);
	IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
	Serial.print("AP IP address: ");
	Serial.println(myIP);

	server.on("/", handleRoot);
	server.on("/173", []() {
		server.send ( 200, "text/plain", "aGF2ZSBhIHNlYXQgYW5kIHdhaXQgZm9yIFNTSUQ9Z2xpbXBzZSBQVz00OTJkdXh3\n");
	} );
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
	server.handleClient();
}
