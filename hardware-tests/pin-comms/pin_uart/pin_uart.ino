#define RX0 14
#define TX0 15
#define BAUD_RATE 9600

#define IS_LISTENER 1

void setup() {
  // put your setup code here, to run once:
  if (IS_LISTENER) {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX0, TX0);
  } else {
    Serial.begin(9600, SERIAL_8N1, RX0, TX0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IS_LISTENER) {
    Serial.print("Data Received: ");
    Serial.println(Serial2.readString());
    delay(200);
  } else {
    Serial.println("100");
    delay(1500);
  }
}
