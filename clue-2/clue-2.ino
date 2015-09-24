#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char *ssid = "First-Clue";
ESP8266WebServer server ( 800 );

void setup ( void ) {
    WiFi.softAP(ssid);
	IPAddress myIP = WiFi.softAPIP();
    Serial.begin(9600);
	Serial.print("AP IP address: ");
	Serial.println(myIP);

	server.on ( "/", handleDownload );
	server.begin();
	Serial.println ( "HTTP server started" );
}

void loop ( void ) {
	server.handleClient();
}

void handleDownload(){
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS failed to mount !\r\n");                    
  }
  else {
    String str = "";
    File f = SPIFFS.open(server.arg(0), "r");
    if (!f) {
      Serial.println(server.arg(0));
      Serial.println("Can't open SPIFFS file !\r\n");          
    }

  String dataType="text/plain";
  if (server.hasArg("download")) dataType = "application/octet-stream";

  if (server.streamFile(f, dataType) != f.size()) {
    Serial.println("Sent less data than expected!");
  }

  f.close();
  /*
    else {
      char buf[1024];
      int siz = f.size();
      while(siz > 0) {
        Serial.println(siz);
        size_t len = std::min((int)(sizeof(buf) - 1), siz);
        f.read((uint8_t *)buf, len);
        buf[len] = 0;
        str += buf;
        siz -= sizeof(buf) - 1;
      }
      f.close();
      server.send(200, "text/plain", str);
    }
  }
  */
}
}

