#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

class RemoteHotspot{
  private:
    WiFiServer server = WiFiServer(80);
    
  public:
    const char* ssid;
    const char* password;
    RemoteHotspot(const char* ssid, const char* password)
    {
      this->ssid = ssid;
      this->password = password;
    }

    void StartServer()
    {
      Serial.println("Configuring access point...");
      WiFi.softAP(ssid, password);
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
      server.begin();
    
      Serial.println("Server started");
    }
};
