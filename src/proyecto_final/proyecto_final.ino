#include "Arduino.h"

#include <SoftwareSerial.h>

#include <PubSubClient.h>

#include "WiFiEsp.h"

#define SSID	"Galaxy A5219B3"
#define PWD		"qske8262"
#define FAN_PIN 7
#define PUMP_PIN 8
#define FAN_INT 2
#define PUMP_INT 3
#define TEMP_PIN "A5"
#define WATER_PIN "A0"


int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiEspClient espClient;
PubSubClient client(espClient);

char* mqtt_server = "iot.eie.ucr.ac.cr";
int mqtt_port = 1883;

char* mqtt_clientID = "";
char* mqtt_password = "";
char* mqtt_username = "3qwxx4qojgsndw0jch05";

char* mqtt_publish_topic = "v1/devices/me/telemetry";
char* mqtt_subscribe_topic = "v1/devices/me/telemetry";

SoftwareSerial Serial1(5, 6);

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, 0);

  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}


void setup_wifi() {

  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);
  
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_clientID,mqtt_username,mqtt_password)) {
      Serial.println("connected");

      //Subscribe
      client.subscribe(mqtt_subscribe_topic);
      Serial.println("subscribed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char msg[50];
int val0 = 0;
int val1 = 0;
int fan_status = 0;
int water_status = 0;
int counter = 0;

void loop() {
  if (counter++ > 20) {
    counter = 0;
    if (!client.connected()) {
      reconnect();
    }
  }
  val0 = analogRead(A5);
  val1 = analogRead(A0);
  water_status = val1 > 220 ? 1 : 0;
  if (fan_status == 1) {
    fan_status = val0 > 460 ? 0 : 1;
  } else if (fan_status == 0) {
    fan_status = val0 < 440 ? 1 : 0;
  }
  digitalWrite(FAN_PIN,fan_status == 1 ? 1 : 0);

  val0 = ((-1*val0)+(740))/10;
  val1 = (val1*100)/470;

  delay(100);

  Serial.print(F("Publish message: "));
  String msg_a = "{\"x\": " + String(val0) + ", \"y\": " + String(val1) + ", \"z\": " + String(fan_status) + ", \"w\": " + String(water_status) + "}";
  msg_a.toCharArray(msg, 50);
  Serial.println(msg);

  client.publish(mqtt_publish_topic, msg); 
  delay(100);


}

