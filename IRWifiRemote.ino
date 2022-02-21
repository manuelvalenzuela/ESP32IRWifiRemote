#include <LittleFS.h>
#include <ArduinoJson.h>
#include "RemoteHotspot.cpp"

DynamicJsonDocument doc(200);

#define FORMAT_LITTLEFS_IF_FAILED false

class Config{
  public:
    const char* deviceMode;
    const char* ssid;
    const char* password;
    Config(const char* deviceMode, const char* ssid, const char* password)
    {
      this->deviceMode = deviceMode;
      this->ssid = ssid;
      this->password = password;
    }
};

Config readConfig(fs::FS &fs){
  File file = fs.open("/config.json");
  deserializeJson(doc, file);
  const char* deviceMode = doc["mode"];
  const char* ssid = doc[deviceMode]["ssid"];
  const char* password = doc[deviceMode]["password"];

  Config configuration = Config(deviceMode, ssid, password);
  file.close();

  return configuration;
}

void setup() {
  Serial.begin(115200);
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LittleFS Mount failed");
    return;
  }

  Serial.println("LittleFS Mount successful");
  Config configuration = readConfig(LittleFS);

  Serial.printf("mode=%s\n", configuration.deviceMode);
  Serial.printf("ssid=%s\n", configuration.ssid);
  Serial.printf("password=%s\n", configuration.password);

  LittleFS.end();

  // look at the mode and decide what to do
  // if is hotspot then create the hotspot
  // create web to configure the router
  // else connect to router
  
  //Added this temporarily in order to develop hotspot to configure local router connection
  RemoteHotspot hotspot = RemoteHotspot(configuration.ssid, configuration.password);
  hotspot.StartServer();
}

void loop() {
  
}
