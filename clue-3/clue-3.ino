#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "secrets.h"

//this will be changed to match oshcamp network
const char *ssid = "First-Clue";
WiFiServer server(1337);

void setup()
{
    WiFi.softAP(ssid);
    IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.begin();
}

void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if(!client)
    {
        return;
    }
    
    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available())
    {
        delay(1);
    }
    
    // TODO limit chars being read!
    // Read the first line of the request
    String req = client.readStringUntil('\n');
    Serial.println(req);
    client.flush();
    
    // Match the request
    String s;
    int val;
    if(req.indexOf(password) == -1)
    {
        Serial.println("bad password");
        client.print("bad password");
        client.stop();
        return;
    }

    if (req.indexOf("strobe_on") != -1)
    {
        client.print("strobe on");
        //digitalWrite(STROBE, true);
    }
    else if (req.indexOf("strobe_off") != -1)
    {
        client.print("strobe off");
        //digitalWrite(STROBE, false);
    }
    else
    {
        Serial.println("invalid request");
        client.print("invalid request");
    }

    client.flush();
    delay(1);
    // when the function returns and 'client' object is destroyed
    Serial.println("Client disconnected");
}
