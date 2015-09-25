#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "secrets.h"

//this will be changed to match oshcamp network
const char *ssid = "First-Puzzle";
WiFiServer server(1337);
#define STROBE 13

void setup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);
    IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    pinMode(STROBE, OUTPUT);
    //transitor controls nfet so inverted
    digitalWrite(STROBE, true);

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
    
    // If this was defcon I'd be worried by this
    String req = client.readStringUntil('\n');
    Serial.println(req);
    client.flush();
    
    // Match the request
    String s;
    int val;
    if(req.indexOf(password) != 0)
    {
        Serial.println("bad password");
        client.print("bad password");
        client.stop();
        return;
    }

    if (req.indexOf("strobe_on") != -1)
    {
        client.print("strobe on");
        digitalWrite(STROBE, false);
    }
    else if (req.indexOf("strobe_off") != -1)
    {
        client.print("strobe off");
        digitalWrite(STROBE, true);
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
