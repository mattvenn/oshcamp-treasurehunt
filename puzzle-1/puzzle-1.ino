#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

#define CLUE "form data: dGFrZSBhIGJyZWFrIGFuZCB3YWl0IGZvciBhIGdsaW1wc2Ugd2l0aCA0OTJkdXh3eA==\n"
#define RICK "http://ven.nz/solution-stage1"
#define STEG "http://ven.nz/stegz"
#define STEG_PASS "xojezj"

const char *ssid = "elzzuptsrif";
ESP8266WebServer server(800);

Ticker t_status;
void status()
{
    /*
    WL_NO_SHIELD = 255,
    WL_IDLE_STATUS = 0,
    WL_NO_SSID_AVAIL = 1
    WL_SCAN_COMPLETED = 2
    WL_CONNECTED = 3
    WL_CONNECT_FAILED = 4
    WL_CONNECTION_LOST = 5
    WL_DISCONNECTED = 6
    */
    WiFi.printDiag(Serial);
    Serial.println(WiFi.status());
}


void setup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
	IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
	Serial.print("AP IP address: ");
	Serial.println(myIP);
    t_status.attach(2, status);

	server.on("/", handleRoot);
	server.on("/3", []() { server.send(200, "text/plain", RICK);});
	server.on("/100", []() { server.send(200, "text/plain", STEG_PASS);});
	server.on("/173", []() { server.send(200, "text/plain", CLUE);});
	server.on("/180", []() { server.send(200, "text/plain", STEG);});

	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
	server.handleClient();
}

void handleRoot()
{
	String message = "<html>the data you need might be <a href='/1'>here</a></html>\n\n";
    Serial.println("/");
	server.send(200, "text/html", message);
}

void handleNotFound()
{
    Serial.println("not found");
	String message = "<html>hmm. try another number?</html>\n\n";
	server.send(404, "text/html", message);
}
