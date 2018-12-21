#include "index.h"
WebSocketsServer webSocket = WebSocketsServer(81);;

void handleRoot(){
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

// Called when receiving any WebSocket message
void webSocketEvent(uint8_t num, int type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        //webSocket.sendTXT(num, "Connected");
        webSocket.broadcastTXT("{\"info\": \"New client\"}");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);

      // send message to client
      // webSocket.sendTXT(num, "message here");

      // send data to all connected clients
      
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\n", num, length);

      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
  case WStype_ERROR:			
  case WStype_FRAGMENT_TEXT_START:
  case WStype_FRAGMENT_BIN_START:
  case WStype_FRAGMENT:
  case WStype_FRAGMENT_FIN:
    break;
  }

}

long lastSent= 0 ;
void sendVoltage(){
  if(millis() - lastSent > 100){
    String data = "{\"adc\": \"";
    data += getADCValue();
    data += "\"}";
    webSocket.broadcastTXT(data);
    lastSent = millis();
  }
}

void initWEbSocket(){
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void webSocketLoop(){
  webSocket.loop();
  sendVoltage();
}