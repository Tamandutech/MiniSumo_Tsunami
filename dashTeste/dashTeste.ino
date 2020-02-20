#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

const char* ssid = "luccakipc"; // Your WiFi SSID
const char* password = "hitmanreborn"; // Your WiFi Password

bool status = false;

void buttonClicked(const char* id){
   Serial.println("Button Clicked - "+String(id));
   status = !status;
   if(status) ESPDash.updateStatusCard("sts", 1);
   else ESPDash.updateStatusCard("sts", 0);
}


void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    ESPDash.init(server);   // Initiate ESPDash and attach your Async webserver instance
    ESPDash.addButtonCard("btn1", "Blink Button");
    ESPDash.attachButtonClick(buttonClicked);
    ESPDash.addStatusCard("sts","status", 0);

    server.begin();
}

void loop() {

}
