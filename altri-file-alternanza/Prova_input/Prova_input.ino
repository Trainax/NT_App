int input=7;
int valore;

void setup() {
  // put your setup code here, to run once:
  pinMode(input, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 valore=digitalRead(input);
 if(valore==HIGH){
  Serial.println("ALTO");
  }
 else{
  Serial.println("BASSO");
  }
  delay(100); 
}
