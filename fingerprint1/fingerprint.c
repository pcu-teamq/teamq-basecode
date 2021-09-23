#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

hd44780_I2Cexp lcd; //lcd 객체 선언
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
String nameArr[3] = {"Ella", "Liam", "James"};
int logArr[3] = {0, 0, 0};

void setup()
{
  //시리얼 통신 시작
  Serial.begin(9600);
  //lcd 통신 시작
  lcd.begin(16, 2);

  //엑셀에 출력될 라벨(타이틀) 출력
  Serial.println("CLEARDATA");
  Serial.println("LABEL, TIME, ID, NAME, LOG");
  
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  //Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  //지문인식 센서 통신 시작
  finger.begin(57600);
  delay(5);
  //지문인식 센서 디바이스 연결 확인
  if (finger.verifyPassword()) {
    //Serial.println("Found fingerprint sensor!");
  } else {
    //Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  //Serial.println(F("Reading sensor parameters"));
  //지문인식 센서 정보 확인
  finger.getParameters();
//  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
//  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
//  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
//  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
//  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
//  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
//  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  //등록된 지문 유무 판단
  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    //Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
//    Serial.println("Waiting for valid finger...");
//      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void loop()                     // run over and over again
{
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Put your finger");
  lcd.setCursor(0, 1);
  lcd.print("on the sensor!");
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    //Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    //Serial.println("Did not find a match");
    return p;
  } else {
    //Serial.println("Unknown error");
    return p;
  }

  // found a match!
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("#");
  lcd.print(finger.fingerID);
  lcd.print(" ");
  lcd.print(nameArr[finger.fingerID - 1]);
  lcd.print(" ");

  Serial.print("DATA, TIME, ");
  Serial.print(finger.fingerID);
  Serial.print(", ");
  Serial.print(nameArr[finger.fingerID - 1]);
  Serial.print(", ");

  if(logArr[finger.fingerID - 1] == 0){
    logArr[finger.fingerID - 1] = 1;
    Serial.println("Log In");
    lcd.print("Log In");
    lcd.setCursor(0, 1);
    lcd.print("Have a nice day!");
  }
  else{
    logArr[finger.fingerID - 1] = 0;
    Serial.println("Log Out");
    lcd.print("Log Out");
    lcd.setCursor(0, 1);
    lcd.print("See you again!");
  }
  delay(2000);
//  Serial.print("Found ID #"); Serial.print(finger.fingerID);
//  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
// 지문 인식 실패시 -1 반환, 다른 경우라면 ID 리턴
//int getFingerprintIDez() {
//  uint8_t p = finger.getImage();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  p = finger.image2Tz();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  p = finger.fingerFastSearch();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  // found a match!
//  Serial.print("Found ID #"); Serial.print(finger.fingerID);
//  Serial.print(" with confidence of "); Serial.println(finger.confidence);
//  return finger.fingerID;
//}
