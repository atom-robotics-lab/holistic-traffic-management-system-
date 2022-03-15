/* Read RFID Tag with RC522 RFID Reader
*/

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;    
int val = 0 ;


MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  rfid.PCD_Init(); 
  pinMode(D8, OUTPUT);
  pinMode(D2, INPUT);
}

void loop() {

  val = digitalRead(D2);
  if(val == HIGH )  
  {  
   
   digitalWrite(D8, HIGH);
   delay(2000);
   digitalWrite(D8, LOW);  
  }  
  
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "1193818595") {
      Serial.println("Access Granted!");
      digitalWrite(D8, HIGH);     
    } 
    else {
      Serial.println("Access Denied!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

}