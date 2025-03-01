#include <SPI.h>
#include <RF24.h>

// Pin definitions for NRF24L01
#define CE_PIN   9
#define CSN_PIN  10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for communication
const byte address[6] = "00001";

// Define variables for message reception
char receivedMessage[32];  // Array to hold the received message

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the NRF24L01 module
  radio.begin();
  radio.openReadingPipe(1, address);  // Set the reading pipe (same address as the transmitter)
  radio.setPALevel(RF24_PA_HIGH);    // Set the power level (higher range)
  radio.startListening();            // Start listening for incoming messages

  // Print that the receiver is ready
  Serial.println("Receiver ready...");
}

void loop() {
  // Check if data is available to read
  if (radio.available()) {
    // Read the received message
    radio.read(&receivedMessage, sizeof(receivedMessage));

    // Print the received message to the serial monitor
    Serial.print("Received message: ");
    Serial.println(receivedMessage);

    // Add additional logic to respond, like playing a sound or signaling
    if (strcmp(receivedMessage, "HONK") == 0) {
      // Trigger sound alert or any other response
      Serial.println("Triggering sound alert...");
      // Code to trigger the sound (e.g., using a speaker) can go here
    }
  }
}
