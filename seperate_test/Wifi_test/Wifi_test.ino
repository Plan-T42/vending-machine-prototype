#define BROKER_IP    "192.168.2.134"
#define DEV_NAME     "mqttdevice"
#define MQTT_USER    "mqtt_user"
#define MQTT_PW      "mqtt_password"

const char ssid[] = "TMSBatch9";
const char pass[] = 
"12345678";
#include <MQTT.h>
#include <WiFiNINA.h>

WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;


void connect() {
 Serial.print("checking wifi...");
 while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(1000);
 }
 Serial.print("\nconnecting...");
 while (!client.connect(DEV_NAME, MQTT_USER, MQTT_PW)) {
   Serial.print(".");
   delay(1000);
 }
 Serial.println("\nconnected!");
 client.subscribe("/hello"); //SUBSCRIBE TO TOPIC /hello
}
void messageReceived(String &topic, String &payload) {
 Serial.println("incoming: " + topic + " - " + payload);
 if (topic == "/hello") {
   if (payload == "open") {
     Serial.println("open");
     digitalWrite(LED_BUILTIN, HIGH); 
   } else if (payload == "closed") {
     Serial.println("closed");
     digitalWrite(LED_BUILTIN, LOW); 
   }
 }
}
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, pass);
 pinMode(LED_BUILTIN,OUTPUT);

 //
 // MQTT brokers usually use port 8883 for secure connections.
 client.begin(BROKER_IP, 1883, net);
 client.onMessage(messageReceived);
 connect();
}
void loop() {
 client.loop();
 if (!client.connected()) {
   connect();
 }
 // publish a message roughly every second.
 if (millis() - lastMillis > 1000) {
   lastMillis = millis();
   client.publish("/hello", "world"); //PUBLISH TO TOPIC /hello MSG world
 }
}
