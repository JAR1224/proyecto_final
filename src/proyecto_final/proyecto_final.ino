#include "Arduino.h"
#include "ESP8266.h"


#define portmqtt 1883
#define SSID	"ARRIBA1"
#define PWD		"L4c4s402"


// the setup function runs once when you press reset or power the board
void setup() {
  char	*ipAddress, ap[31];
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  /*
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
*/

}


void loop() {

  /*
	if (WiFi.connect((char *)"iot.eie.ucr.ac.cr", portmqtt) == WIFI_ERR_CONNECT) {

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
*/

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  delay(1000);                      // wait for a second
}