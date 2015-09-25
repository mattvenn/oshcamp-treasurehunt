#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// #define DISAPPEAR //uncomment to make disappearing AP

#define LINK "<html>the data you need might be <a href='/file?file=/bust.jpg'>here</a></html>\n\n"
const char *ssid = "glimpse";
const char *pw = "492duxwx";
ESP8266WebServer server(9600);
const int timeout = 60 * 1000; //1 minute
const int reboot = 60 * 3000; //3 minutes
bool connected = false;

void setup()
{
    WiFi.softAP(ssid, pw);
    IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
    Serial.print("AP IP address: ");
	Serial.println(myIP);
    connected = true;

	server.on("/", []() { server.send(200, "text/html", LINK );});
	server.on("/file", handleDownload);
	server.onNotFound(handleNotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
    #ifdef DISAPPEAR
    if(millis() < timeout)
        server.handleClient();
    if(millis() > timeout && connected == true)
    {
        Serial.println("closing AP");
        WiFi.softAPdisconnect();
        connected = false;
    }
    if(millis() > reboot)
        ESP.restart();
    #else
    server.handleClient();
    #endif
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

