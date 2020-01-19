

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>


BridgeServer server;
String startString;
long hits = 0;
float var=0;
float var2=0;
int LedPin=5;
int errore=6;
int sensorValue;
float temperature;
int sensorValue2;
float temperature2;
int sensorValue3;
float temperature3;
int allarme=9;
int allarmeBasso=8;
float conversione=6.96296296;
float var3=0;


float tempImpostata=35;
float diff=1;




void animazione(){
  digitalWrite(LedPin, HIGH);
  delay(500);
  digitalWrite(errore, HIGH);
  delay(500);
  digitalWrite(allarme, HIGH);
  delay(500);
  digitalWrite(allarmeBasso, HIGH);
  delay(1500);
  digitalWrite(LedPin, LOW);
  delay(200);
  digitalWrite(errore, LOW);
  delay(200);
  digitalWrite(allarme, LOW);
  delay(200);
  digitalWrite(allarmeBasso, LOW);
  }

void setup() {
  SerialUSB.begin(9600);

  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, LOW);
  pinMode(errore, OUTPUT);
  digitalWrite(errore, LOW);
  pinMode(allarme, OUTPUT);
  digitalWrite(allarme, LOW);
  pinMode(allarmeBasso, OUTPUT);
  digitalWrite(allarmeBasso, LOW);

  animazione();

  server.listenOnLocalhost();
  server.begin();

  // get the time that this sketch started:
  Process startTime;
  startTime.runShellCommand("date");
  while (startTime.available()) {
    char c = startTime.read();
    startString += c;
  }
}

void loop() {
  sensorValue = analogRead(A5);
  sensorValue2 = analogRead(A4);
  sensorValue3 = analogRead(A3);
  var=sensorValue;
  var2=sensorValue2;
  var3=sensorValue3;
  temperature = var/conversione;
  temperature2=var2/conversione;
  temperature3=var3/conversione;
  
  if(temperature == 0 || temperature2 == 0 || temperature3 == 0 ){
       digitalWrite(errore, HIGH);
    }
    else{
        digitalWrite(errore, LOW);
    }
  if(temperature > tempImpostata+diff || temperature2 > tempImpostata+diff || temperature3 > tempImpostata+diff){
    digitalWrite(allarme, HIGH);
    }
  else{
    digitalWrite(allarme, LOW);
    }
  if((temperature < tempImpostata-diff && temperature !=0) || (temperature2 < tempImpostata-diff && temperature2 !=0) || (temperature3 < tempImpostata-diff && temperature3 !=0)){
    digitalWrite(allarmeBasso, HIGH);
    }
  else{
    digitalWrite(allarmeBasso, LOW);
    }
  // Get clients coming from server
  
  
  
  BridgeClient client = server.accept();
  // There is a new client?
  if (client) {
    // read the command
    digitalWrite(LedPin, HIGH);
    String command = client.readString();
    command.trim();        //kill whitespace
    SerialUSB.println(command);
    // is "temperature" command?
    if (command == "temperature") {

      // get the time from the server:
      Process time;
      time.runShellCommand("date");
      String timeString = "";
      while (time.available()) {
        char c = time.read();
        timeString += c;
      }
      SerialUSB.println(timeString);
      // print the temperature:
      client.println("<title>Centralina sensori Arduino</title>");
      client.println("<h1>Visualizzazione remota temperatura sensori</h1>");
      client.print("<br>Ora corrente: ");
      client.println(timeString);
      client.println("<br><br>Temperatura impostata: ");
      client.print(tempImpostata);
      client.println("<br>Differenziale impostato: ");
      client.print(diff);
      client.print("<br><br>Valore tensione sensore 1 corrente: ");
      client.println(sensorValue);
      client.print("<br>Temperatura corrente sensore 1: ");
      client.print(temperature);
      client.print(" &deg;C");
      client.println("<br><br>Valore tensione sensore 2 corrente: ");
      client.print(sensorValue2);
      client.println("<br>Temperatura corrente caldaia: ");
      client.print(temperature2);
      client.print(" &deg;C");
      client.println("<br><br>Valore tensione sensore 3 corrente: ");
      client.print(sensorValue3);
      client.println("<br>Temperatura corrente sensore 3: ");
      client.print(temperature3);
      client.print(" &deg;C");

        
      if(temperature > tempImpostata+diff){
        client.println("<br><br>Temperatura sonda 1 troppo alta!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature2 > tempImpostata+diff){
        client.println("<br><br>Temperatura sonda 2 troppo alta!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature3 > tempImpostata+diff){
        client.println("<br><br>Temperatura sonda 3 troppo alta!!! Il LED di avvertimento &egrave stato acceso");
        }
        
      if(temperature < tempImpostata-diff && temperature != 0){
        client.println("<br><br>Temperatura sonda 1 troppo bassa!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature2 < tempImpostata-diff && temperature2 !=0){
        client.println("<br><br>Temperatura sonda 2 troppo bassa!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature3 < tempImpostata-diff && temperature3 != 0){
        client.println("<br><br>Temperatura sonda 3 troppo bassa!!! Il LED di avvertimento &egrave stato acceso");
        }
        
      if(temperature == 0){
        client.println("<br><br>Errore nelle sonda 1! Sonda disconnessa e/o rotta!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature2 == 0){
        client.println("<br><br>Errore nelle sonda 2! Sonda disconnessa e/o rotta!!! Il LED di avvertimento &egrave stato acceso");
        }
      if(temperature3 == 0){
        client.println("<br><br>Errore nelle sonda 3! Sonda disconnessa e/o rotta!!! Il LED di avvertimento &egrave stato acceso");
        }
    }

    client.println("<br><br>Prossima manutenzione del macchinario: 22/09/2027");

    // Close connection and free resources.
    digitalWrite(LedPin, LOW);
    client.stop();
    hits++;
  }
    
  delay(25);
}
