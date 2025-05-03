/////////////////////////////////NRF send code/////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

// Use the appropriate pins for your setup
RF24 radio(9, 8);  // CE, CSN
int button = 7;
int led = 6;

const byte address[6] = "00001";
String str = "";  // To read state of serial data from HC05 module
int cnt = 0;

void setup() {
  Serial.begin(9600);  // Default communication rate of the Bluetooth module
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {

  char dataToSend[32];
  int state = digitalRead(button);
  if (state == 0) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
    radio.write(&dataToSend, sizeof(dataToSend));
    delay(1000);
  }
  if (Serial.available() > 0) {  // Checks whether data is coming from the serial port
    cnt++;
    char receivedChar = Serial.read();  // Reads the data from the serial port

    if (receivedChar == '\n') {  // Check for the newline character to indicate the end of the string
      Serial.println(str);       // Print the received string

      // Send data via RF
      // Adjust the size based on your data size
      str.toCharArray(dataToSend, sizeof(dataToSend));

      str = "";  // Clear the string for the next data
      //delay(1000);
    } else {
      str += receivedChar;  // Append the character to the string
    }
  }
  // delay(100);
}
