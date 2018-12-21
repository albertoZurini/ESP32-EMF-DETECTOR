void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  initADC();
	initWiFi();
	initWEbSocket();
}