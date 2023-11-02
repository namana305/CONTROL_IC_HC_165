#include <Arduino.h>
bool readBitValueInPosition(uint8_t Register, uint8_t position);
bool READ_ORDER_TYPE = LSBFIRST;
uint8_t REGISTER_165_NOW;
uint8_t REGISTER_165_NOW2;
// Define Connections to 74HC165

// PL pin 1
int load = 11;
// CE pin 15
int clock_pinEnablePin = 10;
// Q7 pin 7
int dataIn = 12;
// CP pin 2
int clock_pin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(13, 1); // clock_pin_pin
  pinMode(12, 0); // serial IN_PUT from 165
  pinMode(11, 1); // latch_pin
  pinMode(10, 1); // clock_pin_enable
}

void loop()
{
  // GỬI 1 xung cho chân latch để đưa 74hc165 vào trạng thái gửi dữ liệu
  digitalWrite(load, 0);
  delayMicroseconds(5);
  digitalWrite(load, 1);
  delayMicroseconds(5);
  // đưa chân clock_pin vào high và chân clock_pin enable về LOW
  // nếu thiếu 2 chân này sẽ nhận dc 7 bit thay vì 8 bit
  digitalWrite(clock_pin, 1);
  digitalWrite(clock_pinEnablePin, 0);
  REGISTER_165_NOW = shiftIn(dataIn, clock_pin, LSBFIRST);
  //--------------shiftIn-to-register1----------------
  // for (uint8_t i = 0; i < 8; ++i)
  // {
  //   digitalWrite(clock_pin, HIGH); //khi 165 phát hiện có thay đổi trạng thái từ 0-1 tại chân clock nó sẽ kích hoạt chân data out của nó thành trạng thái tương ứng tại bit tương ứng
  //   if (READ_ORDER_TYPE == LSBFIRST)
  //     REGISTER_165_NOW |= digitalRead(dataIn) << i;
  //   else
  //     REGISTER_165_NOW |= digitalRead(dataIn) << (7 - i);
  //   digitalWrite(clock_pin, LOW);
  // }
  //--------------End-shiftIn-------------
  REGISTER_165_NOW2 = shiftIn(dataIn, clock_pin, LSBFIRST);
  //--------------shiftIn-to-register2----------------
  // for (uint8_t i = 0; i < 8; ++i)
  // {
  //   digitalWrite(clock_pin, HIGH); //khi 165 phát hiện có thay đổi trạng thái từ 0-1 tại chân clock nó sẽ kích hoạt chân data out của nó thành trạng thái tương ứng tại bit tương ứng
  //   if (READ_ORDER_TYPE == LSBFIRST)
  //     REGISTER_165_NOW2 |= digitalRead(dataIn) << i;
  //   else
  //     REGISTER_165_NOW2 |= digitalRead(dataIn) << (7 - i);
  //   digitalWrite(clock_pin, LOW);
  // }
  //--------------End-shiftIn-------------
  digitalWrite(clock_pinEnablePin, 1);
  Serial.println(readBitValueInPosition(REGISTER_165_NOW, 3));
  Serial.println(REGISTER_165_NOW, BIN);
  // sau khi nhận xong phải kéo clock_pin enable lên HIGH để thực hiện cho vòng lấy tiếp theo

  delay(300);
}
bool readBitValueInPosition(uint8_t Register, uint8_t position) //hàm đọc giá trị của bit tại vị trí nào đó của thanh ghi lưu ý chưa có trình tự đọc LSB HAY MSBFIRST
{
  return ((Register) >> (position)) & 0x01;
};