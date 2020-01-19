//Applicazione per il controllo di macchinari industriali. Versione per Arduino UNO

float tempAmbiente;
float tempSettata=24;
float deltaTemp=0,5;
float tempEsterna;
float tempMandata;
float tempRipresa;
float tempSurriscaldamento;
float tempSottoriscaldamento;
float tempCondensazione;

int vent1=3; //pin ai quali saranno connessi i relè per comandare i ventilatori
int vent2=4;
int vent3=5;
int vent4=6;

int motore1=7; //pin ai quali saranno connessi i relè per comandare i motori
int motore2=8;
int motore3=9;
int motore4=10;

int pinTempAmbiente=A0; //pin analogici dai quali verrà letta la temperatura mediante sensori
int pinTempEsterna=A1;
int pinTempMandata=A2;
int pinTempRipresa=A3;
int pinTempSurriscaldamento=A4;
int pinTempSottoriscaldamento=A5;


void setup() {
  // put your setup code here, to run once:
  pinMode(vent1, OUTPUT);
  pinMode(vent2, OUTPUT);
  pinMode(vent3, OUTPUT);
  pinMode(vent4, OUTPUT);
  pinMode(motore1, OUTPUT);
  pinMode(motore2, OUTPUT);
  pinMode(motore3, OUTPUT);
  pinMode(motore4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  tempAmbiente=analogRead(pinTemperaturaAmbiente);
  tempEsterna=analogRead(pinTemperaturaEsterna);
  tempMandata=analogRead(pinTemperaturaMandata);
  tempRipresa=analogRead(pinTemperaturaRipresa);
  tempSurriscaldamento=analogRead(pinTemperaturaSurriscaldamento);
  tempSottoriscaldamento=analogRead(pinTemperaturaSottoriscaldamento);

  if(tempAmbiente<tempAmbiente-deltaTemp || tempAmbiente>tempAmbiente+deltaTemp){
    //Cose da fare per ripristinare la temperatura
    digitalWrite(vent1, HIGH);
    digitalWrite(vent2, HIGH);
  }
  else{
    digitalWrite(vent1, LOW);
    digitalWrite(vent3, LOW);
  }
}
