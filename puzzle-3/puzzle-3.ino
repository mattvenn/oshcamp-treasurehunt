#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "secrets.h"
#include <Ticker.h>

//this will be changed to match oshcamp network
const char *ssid = "WutheringBytes";
WiFiServer server(1337);
#define STROBE 15

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
    Serial.println(WiFi.localIP());
}

void setup()
{
    WiFi.mode(WIFI_STA);
    Serial.begin(9600);
    pinMode(STROBE, OUTPUT);
    //transitor controls nfet so inverted
    digitalWrite(STROBE, true);

    server.begin();
    t_status.attach(10, status);
}

void loop() 
{
    if (WiFi.status() != WL_CONNECTED) 
    {
        WiFi.mode(WIFI_STA);
        Serial.print("connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid);

        if (WiFi.waitForConnectResult() != WL_CONNECTED)
            return;
        Serial.println("WiFi connected");
        WiFi.mode(WIFI_STA);
        Serial.println(WiFi.localIP());
    }
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
