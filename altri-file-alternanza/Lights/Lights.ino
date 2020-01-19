#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 
 
YunServer server;
String response;
String response2;
String response3;


 
void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11, OUTPUT);
}
 
void loop() {
  YunClient client = server.accept();
  if (client) {
    String command = client.readString();
    command.trim();
    
    if (command == "lights-on") {
      digitalWrite(13,LOW);
    }
    else if (command == "lights-off") {
      digitalWrite(13,HIGH);
    }
    else if (command == "lights-toggle") {
      digitalWrite(13,!digitalRead(13));
    }

    if (command == "lights2-on") {
      digitalWrite(12,LOW);
    }
    else if (command == "lights2-off") {
      digitalWrite(12,HIGH);
    }

    if (command == "estate-on") {
      digitalWrite(11,LOW);
    }
    else if (command == "estate-off") {
      digitalWrite(11,HIGH);
    }
    
    response = String(digitalRead(13));
    response2= String(digitalRead(12));
    client.print(String("{\"state\":"+response+"}"));
    client.stop();
  }
 
  delay(50);
}
