ESP32WebServer server(80); //Server on port 80

void handleRoot();

void initWiFi(){
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid);

	Serial.print("ESP IP: ");
	Serial.println(WiFi.softAPIP());

	server.on("/", handleRoot);

	server.begin();
}

void wifiLoop(){
	server.handleClient();
}