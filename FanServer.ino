#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"
#include "xml.h"

ESP8266WebServer server(80);

const char* ssid = "M"; //Enter Wi-Fi SSID
const char* password =  ""; //Enter Wi-Fi Password


 
void setup() {
  Serial.begin(115200); //Begin Serial at 115200 Baud
  WiFi.begin(ssid, password);  //Connect to the WiFi network
  
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
      delay(500);
      Serial.println("Waiting to connect...");
  }
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
  
   if (!MDNS.begin("esp8266",WiFi.localIP())) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
   MDNS.addService("http", "tcp", 80);
  MDNS.addService("wled", "tcp", 80);   
  
  server.on("/", handle_index);
  server.on("/win", win);
  server.on("/win&call", wincall);//Handle Index page
  
  server.begin(); //Start the server
  Serial.println("Server listening");
}

void loop() {
  MDNS.update();

  server.handleClient(); //Handling of incoming client requests
}

void handle_index() {
  //Print Hello at opening homepage
  String page = main_index;
  server.send(200, "text/html", page);
}

void win(){
  String page = main_xml;
  server.send(200,"text/xml", page);
}

void wincall(){
  String page = main_xml;
  server.send(200,"text/xml", page);
}
