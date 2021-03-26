/*
  ESP8266 current monitor with MQTT
  See config.h for Wifi and MQTT settings
*/

#include <ESP8266WiFi.h>                    // Needed for EPS8266
#include <WiFiClient.h>                     // WiFi client

// Watchdog items
#include <Ticker.h>
Ticker secondTick;
volatile int watchdogCount = 0;

#include "config.h"

WiFiClient espClient;                       // Required for ESP8266 boards
#include <PubSubClient.h>                   // from http://pubsubclient.knolleary.net/api.html
PubSubClient client(espClient);             // ESP pubsub client
#include "WiFi_Functions.h"
#include "MQTT_Functions.h"

void ISRwatchdog() {
  watchdogCount++;
  if (watchdogCount == Watchdog_Timout) {
   // watchdog triggered
    ESP.reset();
  } 
}

void setup(void) {
  delay(500);

  pinMode(StatusLED, OUTPUT);
  StatusLED_Off;

  secondTick.attach(1, ISRwatchdog);          // Start watchdog timer

  Get_Wifi();
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  LastMsg = millis();
  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if ((millis() - LastMsg) > Heatbeat || Report_Request == 1) {

    LastMsg = millis();
    Report_Request = 0;

    ++Heart_Value;
    if (Heart_Value > Heartbeat_Range) {
      Heart_Value = 1;
    }

    StatusLED_Off;
    ReadAmps();
    StatusLED_On; // let teh user know we're working.
    

    String Report = Status_Report();
    char Report_array[(Report.length() + 1)];
    Report.toCharArray(Report_array, (Report.length() + 1));


    client.publish(InStatus, Report_array);


    if (Event == "REBOOT") {
    }
    
  } // heartbeat

}

