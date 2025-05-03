#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Use the appropriate pins for your setup
RF24 radio(9, 8);  // CE, CSN for NRF24L01
const byte nrfAddress[6] = "00001";  // NRF24L01 address

String bluetoothData = ""; // To read state of serial data from HC05 module
int bluetoothCounter = 0;

#define nrfCEPin 9  // Replace with the actual pin connected to the NRF module's CE pin
RF24 nrfRadio(9, 10);  // CE, CSN for NRF24L01
const byte nrfReceiveAddress[6] = "00001";  // NRF24L01 receive address

void setup() {
  Serial.begin(9600);
  
  // Bluetooth setup
  Serial.println("Bluetooth and NRF24L01 Test");
  Serial.begin(9600); // Default communication rate of the Bluetooth module

  // NRF24L01 setup
  radio.begin();
  radio.openWritingPipe(nrfAddress);
  radio.stopListening();

  nrfRadio.begin();
  nrfRadio.openReadingPipe(1, nrfReceiveAddress);
  nrfRadio.startListening();
}

void loop() {
  // Bluetooth communication
  if (Serial.available() > 0) {
    bluetoothCounter++;
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
      Serial.println(bluetoothData);
      // Process Bluetooth data as needed
      processBluetoothData(bluetoothData);
      bluetoothData = "";
    } else {
      bluetoothData += receivedChar;
    }
  }

  // NRF24L01 communication
  if (nrfRadio.available()) {
    char text[32] = "";
    nrfRadio.read(&text, sizeof(text));

    int rssi = nrfRadio.readRssi();
    float distance = rssiToDistance(rssi);

    Serial.print("Received message (NRF24L01): ");
    Serial.println(text);
    Serial.print("RSSI: ");
    Serial.println(rssi);
    Serial.print("Estimated distance: ");
    Serial.print(distance);
    Serial.println(" meters");
  }
}

void processBluetoothData(String data) {
  // Process Bluetooth data as needed
  Serial.print("Received message (Bluetooth): ");
  Serial.println(data);
}

float rssiToDistance(int rssi) {
  // This is a simple linear approximation; the actual relationship depends on various factors
  // Experimentally determine a relationship between RSSI and distance in your specific environment
  // This is just a starting point and may need calibration
  float distance = 10.0 * pow(10, ((-60 - rssi) / 20.0));
  return distance;
}