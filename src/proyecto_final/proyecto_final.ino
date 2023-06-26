#include "Arduino.h"
//#include "WiFi.h"
//#include "ESP8266.h"

//#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>

#include <PubSubClient.h>
#include "WiFiEsp.h"

#define SSID	"ARRIBA1"
#define PWD		"L4c4s402"


int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiEspClient espClient;
PubSubClient client(espClient);

char* mqtt_server = "iot.eie.ucr.ac.cr";
int mqtt_port = 1883;

char* mqtt_clientID = "";
char* mqtt_username = "19me1xr4k0tmae3tgbz4";
char* mqtt_password = "";

char* mqtt_publish_topic = "v1/devices/me/telemetry";
char* mqtt_subscribe_topic = "v1/devices/me/attributes";

SoftwareSerial Serial1(5, 6);

void setup() {
  pinMode(2, OUTPUT);
  // initialize the LED pin as an output:
  //pinMode(LED_PIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
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
  // We start by connecting to a WiFi network
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

  // Switch on the LED if an 1 was received as first character
  /*
  if ((char)payload[0] == '1') {
    digitalWrite(LED_PIN, HIGH);   // Turn the LED on
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn the LED off
  }
  */

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
//int buttonState = 0;

void loop() {
  //if (!client.connected()) {
  //  reconnect();
  //}
  //client.loop();
  val0 = analogRead(A0);  // read the input pin
  //Serial.println(val);
  val1 = analogRead(A1);  // read the input pin
  delay(600);
  //if(!digitalRead(BUTTON_PIN) != buttonState){
  Serial.print(F("Publish message: "));
  String msg_a = "{\"x\": " + String(val0) +", \"y\": " + String(val1) + ", \"z\": 0,\"bateria\": 0}";
  msg_a.toCharArray(msg, 50);
  Serial.println(msg);
    //Publish
  client.publish(mqtt_publish_topic, msg); 
  delay(600);
  //Serial.println(val);
  //digitalWrite(2, !digitalRead(2));
    //buttonState = !digitalRead(BUTTON_PIN);
  //}

}

/*
//WiFiEspUdp espClient;

WiFiEspClient espClient;
PubSubClient client(espClient);

char* mqtt_server = "iot.eie.ucr.ac.cr";
int mqtt_port = 1883;

char* mqtt_clientID = "";
char* mqtt_username = "19me1xr4k0tmae3tgbz4";
char* mqtt_password = "";

char* mqtt_publish_topic = "v1/devices/me/telemetry";

SoftwareSerial Serial1(5, 6);

void setup() {
  delay(4000);
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1, true);
  WiFi.begin(SSID, PWD);
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
   client.connect(mqtt_clientID,mqtt_username,mqtt_password);
  }
}

char msg[50];

void loop() {

  delay(1000);
  //Serial.print("AT+GMR\n\r");
  //Serial.println(WiFi.localIP());
  //client.subscribe(mqtt_publish_topic);
  
  String msg_a = "{\"x\": 0, \"y\": 0, \"z\": 0,\"bateria\": 0}";
  msg_a.toCharArray(msg, 50);
  
  client.publish(mqtt_publish_topic, msg);
  
  

}
*/



/*
//WiFiClient Wifi;

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, 1);
  delay(10000);
  digitalWrite(7, 0);
	char	*ipAddress, ap[31];

	WiFi.reset(WIFI_RESET_HARD);
	WiFi.begin(9600);
	if (WiFi.join(SSID, PWD) == WIFI_ERR_OK) {
		ipAddress = WiFi.ip(WIFI_MODE_STA);
		if (WiFi.isConnect(ap))
			digitalWrite(7, 1);
		else
			digitalWrite(7, 0);
	} else
		while (1);
}

void loop() {
	if (WiFi.connect((char *)"www.google.co.jp", 80) == WIFI_ERR_CONNECT) {

		if (WiFi.send((const uint8_t *)"GET / HTTP/1.1\r\n\r\n") == WIFI_ERR_OK) {
			int16_t	c;
			uint16_t len = WiFi.listen(10000UL);
			while (len)
				if ((c = WiFi.read()) > 0) {
					digitalWrite(7, 1);
					len--;
				}
		} else
			digitalWrite(7, 0);

		WiFi.close();

	} else
		digitalWrite(7, 0);

	WiFi.disconnect();

	while (1);
  {
    delay(1000);
    digitalWrite(7, 0);
    delay(1000);
    digitalWrite(7, 1);
  }
}

*/