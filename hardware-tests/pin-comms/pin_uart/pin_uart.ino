#define RX0 14
#define TX0 15
#define BAUD_RATE 9600

// This flag determines whether the device send or listen for UART messages
#define IS_LISTENER 1

void setup() {
  if (IS_LISTENER) {
    // Listener device should print data on 115200 but receive on 9600
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RX0, TX0);
  } else {
    // Sender device should send data on 9600
    Serial.begin(9600, SERIAL_8N1, RX0, TX0);
  }
}

void loop() {
  if (IS_LISTENER) {
    // Listener device prints data received
    Serial.print("Data Received: ");
    Serial.println(Serial2.readString());
    delay(200);
  } else {
    // Sender device sends "100" ever 1.5 seconds
    Serial.println("100");
    delay(1500);
  }
}
