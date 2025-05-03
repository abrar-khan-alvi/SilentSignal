#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>
#include <SoftwareSerial.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";
String str = "";
SoftwareSerial mp3(6, 7);

int buttonPin = 2;  // Change to the pin where your DPDT button is connected
int ledPin = 6;     // Change to the pin where your LED is connected

void sendCommand(byte command, byte dat1, byte dat2) {
  delay(20);
  byte Send_buf[8] = { 0x7E, 0xFF, 0x06, command, 0x01, dat1, dat2, 0xEF };
  for (uint8_t i = 0; i < 8; i++) {
    mp3.write(Send_buf[i]);
  }
}

void setup() {
  Serial.begin(9600);
  mp3.begin(9600);
  delay(500);
  Serial.println();
  sendCommand(0x09, 0, 0x02);  // CMD_SEL_DEV, 0, DEV_TF
  delay(500);
  Serial.println();
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

double convertToDecimalDegrees(int degrees, int minutes, double seconds) {
  return degrees + (minutes / 60.0) + (seconds / 3600.0);
}

void extractDegreesMinutesSeconds1(const char* text, double& received_lat, double& received_lon) {
  // Initialize variables to store extracted values
  received_lat = received_lon = 0.0;
  // Convert the C-style string to a String object
  String readString = String(text);
  // Print the input string for debugging
  Serial.println("Input String1: " + readString);
  // Find the first occurrence of degrees symbol '°'
  int deg1 = readString.indexOf('°');
  // Find the first occurrence of minutes symbol '
  int min1 = readString.indexOf('\'');
  // Find the first occurrence of seconds symbol "
  int sec1 = readString.indexOf('\"');
  // Find the second occurrence of degrees symbol '°' starting from the position after the first occurrence
  int deg2 = readString.indexOf('°', deg1 + 1);
  // Find the second occurrence of minutes symbol ' starting from the position after the first occurrence
  int min2 = readString.indexOf('\'', min1 + 1);

  String lat_deg = readString.substring(0, deg1 - 1);
  String lat_min = readString.substring(deg1 + 2, min1);
  String lat_sec = readString.substring(min1 + 2, sec1 - 1);
  // Extract longitude substrings
  String lon_deg = readString.substring(sec1 + 3, deg2 - 1);  // Assuming longitude always starts at deg2 + 1 and has 3 digits
  String lon_min = readString.substring(deg2 + 2, min2);      // Assuming minutes always have 2 digits
  String lon_sec = readString.substring(min2 + 2, min2 + 6);  // Assuming seconds always have 5 digits
  // Convert substrings to integer values
  int lat_deg_int = lat_deg.toInt();
  int lat_min_int = lat_min.toInt();
  double lat_sec_double = lat_sec.toDouble();

  int lon_deg_int = lon_deg.toInt();
  int lon_min_int = lon_min.toInt();
  double lon_sec_double = lon_sec.toDouble();
  // Serial.println("///////////////start 1////////////////");
  // Serial.println("latitude");
  // Serial.println(lat_deg_int);
  // Serial.println(lat_min_int);
  // Serial.println(lat_sec_double);
  // Serial.println("longtitude");
  // Serial.println(lon_deg_int);
  // Serial.println(lon_min_int);
  // Serial.println(lon_sec_double);
  // Serial.println("////////////////end 1///////////////");

  // Convert degrees, minutes, and seconds to decimal degrees
  received_lat = convertToDecimalDegrees(lat_deg_int, lat_min_int, lat_sec_double);
  received_lon = convertToDecimalDegrees(lon_deg_int, lon_min_int, lon_sec_double);
}

void extractDegreesMinutesSeconds2(const char* dat, double& reference_lat, double& reference_lon) {
  // Initialize variables to store extracted values
  reference_lat = reference_lon = 0.0;
  // Convert the C-style string to a String object
  String readString = String(dat);
  // Print the input string for debugging
  //Serial.println("Input String2: " + readString);
  // Find the first occurrence of degrees symbol '°'
  int deg1 = readString.indexOf('°');
  // Find the first occurrence of minutes symbol '
  int min1 = readString.indexOf('\'');
  // Find the first occurrence of seconds symbol "
  int sec1 = readString.indexOf('\"');
  // Find the second occurrence of degrees symbol '°' starting from the position after the first occurrence
  int deg2 = readString.indexOf('°', deg1 + 1);
  // Find the second occurrence of minutes symbol ' starting from the position after the first occurrence
  int min2 = readString.indexOf('\'', min1 + 1);

  String lat_deg = readString.substring(0, deg1 - 1);
  String lat_min = readString.substring(deg1 + 2, min1);
  String lat_sec = readString.substring(min1 + 2, sec1 - 1);
  // Extract longitude substrings
  String lon_deg = readString.substring(sec1 + 3, deg2 - 1);  // Assuming longitude always starts at deg2 + 1 and has 3 digits
  String lon_min = readString.substring(deg2 + 2, min2);      // Assuming minutes always have 2 digits
  String lon_sec = readString.substring(min2 + 2, min2 + 6);  // Assuming seconds always have 5 digits
  // Convert substrings to integer values
  int lat_deg_int = lat_deg.toInt();
  int lat_min_int = lat_min.toInt();
  double lat_sec_double = lat_sec.toDouble();
  int lon_deg_int = lon_deg.toInt();
  int lon_min_int = lon_min.toInt();
  double lon_sec_double = lon_sec.toDouble();
  // Serial.println("///////////////start 2////////////////");
  // Serial.println("latitude");
  // Serial.println(lat_deg_int);
  // Serial.println(lat_min_int);
  // Serial.println(lat_sec_double);
  // Serial.println("longtitude");
  // Serial.println(lon_deg_int);
  // Serial.println(lon_min_int);
  // Serial.println(lon_sec_double);
  // Serial.println("///////////////end 2////////////////");
  // Convert degrees, minutes, and seconds to decimal degrees
  reference_lat = convertToDecimalDegrees(lat_deg_int, lat_min_int, lat_sec_double);
  reference_lon = convertToDecimalDegrees(lon_deg_int, lon_min_int, lon_sec_double);
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
  const double earthRadius = 6371.0;
  lat1 = lat1 * PI / 180.0;
  lon1 = lon1 * PI / 180.0;
  lat2 = lat2 * PI / 180.0;
  lon2 = lon2 * PI / 180.0;
  double dLat = lat2 - lat1;
  double dLon = lon2 - lon1;
  double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
  double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
  double distance = earthRadius * c;
  return distance;
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  char dataToSend[32];

  if (buttonState == LOW) {  // Button pressed, send data
    digitalWrite(ledPin, HIGH);
    
    // ... (your sending logic, modify as needed)

    radio.stopListening();
    radio.write(&dataToSend, sizeof(dataToSend));
    radio.startListening();
    delay(1000);
  } else {  // Button not pressed, receive data
    digitalWrite(ledPin, LOW);
    double reference_lat = 0.0;
    double reference_lon = 0.0;
    double received_lat = 0.0;
    double received_lon = 0.0;
    double distance;
    char dat[32];

    if (Serial.available() > 0) {
      // ... (same as before)
    }

    if (radio.available()) {
      // ... (same as before)
    }
  }
}
