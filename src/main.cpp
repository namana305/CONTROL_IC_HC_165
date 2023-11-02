#include <Arduino.h>
uint8_t REGISTER_165_NOW;
uint8_t REGISTER_165_NOW2;
// Define Connections to 74HC165

// PL pin 1
int load = 11;
// CE pin 15
int clockEnablePin = 10;
// Q7 pin 7
int dataIn = 12;
// CP pin 2
int clockIn = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(13, 1); // clock_pin
  pinMode(12, 0); // serial IN_PUT from 165
  pinMode(11, 1); // latch_pin
  pinMode(10, 1); // clock_enable
}

void loop()
{
  // GỬI 1 xung cho chân latch để đưa 74hc165 vào trạng thái gửi dữ liệu
  digitalWrite(11, 0);
  delayMicroseconds(5);
  digitalWrite(11, 1);
  delayMicroseconds(5);
  // đưa chân clock vào high và chân clock enable về LOW
  // nếu thiếu 2 chân này sẽ nhận dc 7 bit thay vì 8 bit
  digitalWrite(13, 1);
  digitalWrite(10, 0);
  REGISTER_165_NOW = shiftIn(12, 13, LSBFIRST);
  digitalWrite(13, 0);
  REGISTER_165_NOW2 = shiftIn(12, 13, LSBFIRST);
  Serial.println(REGISTER_165_NOW, BIN);
  Serial.println(REGISTER_165_NOW2, BIN);
  // sau khi nhận xong phải kéo clock enable lên HIGH để thực hiện cho vòng lấy tiếp theo
  digitalWrite(10, 1);
  delay(300);
}

// void setup()
// {

//   // Setup Serial Monitor
//   Serial.begin(9600);

//   // Setup 74HC165 connections
//   pinMode(load, OUTPUT);
//   pinMode(clockEnablePin, OUTPUT);
//   pinMode(clockIn, OUTPUT);
//   pinMode(dataIn, INPUT);
// }

// void loop()
// {

//   // Write pulse to load pin
//   digitalWrite(load, LOW);
//   delayMicroseconds(5);
//   digitalWrite(load, HIGH);
//   delayMicroseconds(5);

//   // Get data from 74HC165
//   digitalWrite(clockIn, HIGH);
//   digitalWrite(clockEnablePin, LOW);
//   byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
//   digitalWrite(clockEnablePin, HIGH);

//   // Print to serial monitor
//   Serial.print("Pin States:\r\n");
//   Serial.println(incoming, BIN);
//   delay(200);
// }
