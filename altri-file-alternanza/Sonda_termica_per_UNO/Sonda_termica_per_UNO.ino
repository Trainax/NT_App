int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;
float temperatura=0;
float var=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println("Valore sensore: ");
  Serial.println(sensorValue);
  Serial.println("Temperatura: ");
  var=sensorValue;
  temperatura=var/6,;
  Serial.println(temperatura);
  if(temperatura > 30){
    digitalWrite(ledPin, HIGH);
    Serial.println("Temperatura troppo alta!");
    }
  else{
    digitalWrite(ledPin, LOW);
    }
  delay(1000);
}
