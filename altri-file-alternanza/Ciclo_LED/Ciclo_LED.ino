int i=3;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(i, HIGH);
  
  if(i > 6){
    for(int j=3;j<7;j++){
      digitalWrite(j, LOW);
      }
    i=2;
    }
    delay(random(100, 5000));
    i++;
}
