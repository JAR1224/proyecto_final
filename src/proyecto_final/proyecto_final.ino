#include "Arduino.h"
#include "ESP8266.h"



#define SSID	"ARRIBA1"
#define PWD		"L4c4s402"

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