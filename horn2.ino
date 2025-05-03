#include <SoftwareSerial.h>

SoftwareSerial mp3(15, 14); // RX YX5300 MP3 Player Module <-----> TX(7) SoftwareSerial Arduino Uno.
//SoftwareSerial mp3(6, 7);
void sendCommand(byte command, byte dat1, byte dat2) {
  delay(20);
  byte Send_buf[8] = {0x7E, 0xFF, 0x06, command, 0x01, dat1, dat2, 0xEF};
  for (uint8_t i = 0; i < 8; i++) {
    mp3.write(Send_buf[i]);
  }
}

void setup() {
  Serial.begin(9600);
  mp3.begin(9600);
  delay(500);

  Serial.println("Hardware Serial and Software Serial begin.");
  delay(500);

  Serial.println();

  Serial.println("Select storage device to TF card.");
  sendCommand(0x09, 0, 0x02); // CMD_SEL_DEV, 0, DEV_TF
  delay(500);

  Serial.println();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();//here i need to give file number according to receiving logic
    if (c >= '1' && c <= '9') {
      int fileNumber = c - '0';
      Serial.print("Playing file ");
      Serial.println(fileNumber);
      sendCommand(0x03, 0, fileNumber); // CMD_PLAY_W_INDEX, 0, fileNumber
    }
  }
  delay(100);
}
