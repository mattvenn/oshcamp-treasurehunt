#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "First-Clue";
ESP8266WebServer server(800);

void setup ()
{
    WiFi.softAP(ssid);
	IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
	Serial.print("AP IP address: ");
	Serial.println(myIP);

	server.on("/file", handleDownload);
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
	server.handleClient();
}

void handleNotFound() 
{
	String message = "<html>no such file</html>\n\n";
	server.send(404, "text/html", message);
}

void handleDownload()
{
    if(!SPIFFS.begin()) 
    {
        Serial.println("SPIFFS failed to mount!");                    
        server.send(500, "text/plain", "spiffs failed");
        return;
    }

    if(!server.hasArg("file"))
    {
        Serial.println("need file parameter");                    
        server.send(500, "text/plain", "need file parameter");
        return;
    }
        
    File f = SPIFFS.open(server.arg("file"), "r");
    if(!f) 
    {
        Serial.println(server.arg(0));
        Serial.println("Can't open SPIFFS file !\r\n");          
        server.send(404, "text/plain", "no such file");
        return;
    }

    if(server.streamFile(f, "text/plain") != f.size())
    {
        Serial.println("Sent less data than expected!");
    }
    f.close();
}

