#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

int LEDPIN = 13; // your LED PIN
YunServer server;

String command="on";

void setup() {
  // Start our connection
  Serial.begin(9600);
  pinMode(LEDPIN,OUTPUT);
  digitalWrite(LEDPIN,HIGH); // turn on Led while connecting
  Bridge.begin();  

  // Show a fancy flash pattern once connected
  digitalWrite(LEDPIN,LOW); 
  delay(150);
  digitalWrite(LEDPIN,HIGH); 
  delay(150);
  digitalWrite(LEDPIN,LOW); 
  delay(150);
  digitalWrite(LEDPIN,HIGH); 
  delay(150);
  digitalWrite(LEDPIN,LOW); 
  delay(150);
  
  // Disable for some connections:
  // Start listening for connections  
  
  // server.listenOnLocalhost();
  server.begin();
 
}

void loop() {
  // Listen for clients
  YunClient client = server.accept();
  // Client exists?
  if (client) {
    // Lets process the request!
    process(client);
    client.stop();
  }

  Serial.println(command);
  
  if (command == "on") {
    digitalWrite(LEDPIN,HIGH);
  }
  
  // Turn off
  if (command == "off") {
    digitalWrite(LEDPIN,LOW);
  }
  delay(50);
}

void process(YunClient client) {
  // Collect user commands
  command = client.readStringUntil('#'); // load whole string
  
  
  // Enable HTML
  client.println("Status: 200");
  client.println("Content-type: text/html");
  client.println();
  
  // Show UI
  client.println("<B><Center>");
  client.println("<a href='http://192.168.1.5/arduino/on#on'>Turn ON LED</a><br>");
  client.println("<a href='http://192.168.1.5/arduino/off#off'>Turn OFF LED</a><br>");
  client.print("Command: ");
  client.println(command);
  client.println("</B></Center>");
  
  // Check what the user entered ...
  
  // Turn on
  
}
