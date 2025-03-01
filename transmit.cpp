#include <SPI.h>
#include <RF24.h>

// Pin definitions for NRF24L01
#define CE_PIN   9
#define CSN_PIN  10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for communication
const byte address[6] = "00001";

// Define an example signal message
char message[] = "HONK";

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the NRF24L01 module
  radio.begin();
  radio.openWritingPipe(address);  // Set the receiver address
  radio.setPALevel(RF24_PA_HIGH); // Set the power level (higher range)
  
  // Print that the transmitter is ready
  Serial.println("Transmitter ready...");
}

void loop() {
  // Sending the message
  Serial.println("Sending signal...");
  radio.write(&message, sizeof(message));  // Send the honk message

  delay(5000); // Wait for 5 seconds before sending again
}
