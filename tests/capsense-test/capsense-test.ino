#define OUT 33
#define IN 32

void setup() {
  pinMode(OUT, OUTPUT);
  pinMode(IN, INPUT);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(OUT, LOW);
  delay(10);

  long startTime = micros();

  digitalWrite(OUT, HIGH);
  while(digitalRead(IN) == LOW);
  long senseVal = micros() - startTime;
  Serial.println(senseVal);

}
