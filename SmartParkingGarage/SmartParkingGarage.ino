#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// IR Sensörları tanımlama
int GirisSensoru1 = 13;
int CikisSensoru1 = 12;
int GirisSensoru2 = 11;
int CikisSensoru2 = 10;
int GirisSensoru3 = 9;
int CikisSensoru3 = 8;

// Servo motorları tanımlama
int servo1 = 7;
int servo2 = 6;
int servo3 = 5;

int ldr = A0;
int led1 = 4;
int led2 = 3;
int led3 = 2;

// LCD tanımlama
// SDA : A4, SCL : A5
LiquidCrystal_I2C LCD1(0x26, 20, 4);
LiquidCrystal_I2C LCD2(0x27, 20, 4);
  
  

  // Servo motorların
  int servoKapiKapali = 180, servoKapiAcik = 90;

  Servo servoKapi[3];
  bool GirisKapisiFlag[3] = { false, false, false };
  bool CikisKapisiFlag[3] = { false, false, false };
  int bosParkYer[3] = { 3, 3, 3 };

  unsigned long timerStart[3] = { 0, 0, 0 };     
  bool timerActive[3] = { false, false, false };  


  void setup() {
    setUpAbdul(servoKapi[0], servo1, GirisSensoru1, CikisSensoru1);
    setUpAbdul(servoKapi[1], servo2, GirisSensoru2, CikisSensoru2);
    setUpAbdul(servoKapi[2], servo3, GirisSensoru3, CikisSensoru3);

    pinMode(ldr, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    LCD1.init();
    LCD1.backlight();
    LCD2.init();
    LCD2.backlight();

    Serial.begin(9600);
  }

  void loop() {
    ManageKapi(0, GirisSensoru1, CikisSensoru1, &GirisKapisiFlag[0], &CikisKapisiFlag[0], servoKapi[0]);
    ManageKapi(1, GirisSensoru2, CikisSensoru2, &GirisKapisiFlag[1], &CikisKapisiFlag[1], servoKapi[1]);
    ManageKapi(2, GirisSensoru3, CikisSensoru3, &GirisKapisiFlag[2], &CikisKapisiFlag[2], servoKapi[2]);
    screenYazdirma(0,LCD1);
    screenYazdirma(1,LCD2);
    isikKontrol();
    delay(1);
  }

  void ManageKapi(int parkID, int GirisSensor, int CikisSensor, bool *IRGirisFlag, bool *IRCikisFlag, Servo servoKapi) {
    if (digitalRead(GirisSensor) == 0 && *IRGirisFlag == false) {
      if (bosParkYer[parkID] > 0) {
        *IRGirisFlag = true;  
        if (*IRCikisFlag == false) {
          servoKapi.write(servoKapiAcik);  
          bosParkYer[parkID] = bosParkYer[parkID] - 1;
        }
      } else {
        Serial.println(String(parkID) + " PARK DOLU");
        
      }
    }

    if (digitalRead(CikisSensor) == 0 && *IRCikisFlag == false) {
      if (bosParkYer[parkID] < 3) {
        *IRCikisFlag = true;  
        if (*IRGirisFlag == false) {
          servoKapi.write(servoKapiAcik);  
          bosParkYer[parkID] = bosParkYer[parkID] + 1;
        }
      }
    }

    if( (*IRGirisFlag && digitalRead(GirisSensor) == 1) || (*IRCikisFlag && digitalRead(CikisSensor) == 1)){
      if (!timerActive[parkID]) {
        timerStart[parkID] = millis();  
        timerActive[parkID] = true;
        Serial.println(String(parkID+1)+": Timer Başladı.");
      }
    }

    if (timerActive[parkID]) {
      if (millis() - timerStart[parkID] >= 3000) {  
        if (*IRGirisFlag && !*IRCikisFlag && digitalRead(GirisSensor) == 1 && digitalRead(CikisSensor) == 1) {
          bosParkYer[parkID] = bosParkYer[parkID] + 1;  
          *IRGirisFlag = false;                         
          servoKapi.write(servoKapiKapali);  
          timerActive[parkID] = false;      
        } else if (*IRCikisFlag && !*IRGirisFlag && digitalRead(GirisSensor) == 1 && digitalRead(CikisSensor) == 1) {
          bosParkYer[parkID] = bosParkYer[parkID] - 1;  
          *IRCikisFlag = false;                         
          servoKapi.write(servoKapiKapali); 
          timerActive[parkID] = false;       
        }
      }
    }

    if (*IRGirisFlag && *IRCikisFlag) {
      delay(1000);
      servoKapi.write(servoKapiKapali);  
      *IRGirisFlag = false;              
      *IRCikisFlag = false;              
      timerActive[parkID] = false;       
    }
  }

  void setUpAbdul(Servo servoKapi, int servoKapiPin, int kapiGirisIR, int kapiCikisIR) {
    servoKapi.attach(servoKapiPin);
    servoKapi.write(servoKapiKapali);

    pinMode(kapiGirisIR, INPUT);
    pinMode(kapiCikisIR, INPUT);
  }

   int enYakinOtopark(int lcdIndis){
    if( lcdIndis == 0 ){
      for(int i = 0 ; i < 3 ; i++){
        if(bosParkYer[i] > 0){
          return i+1;
        }
      } 
    }else if(lcdIndis == 1){
      for(int i = 2 ; i >= 0 ; i--){
      if(bosParkYer[i] > 0){
        return i+1;
      }
    }
    }
    Serial.println("Hepsi DOLU");
    return -1;
    }


 void screenYazdirma(int lcdIndis, LiquidCrystal_I2C lcd){
    int bosOtoparkIndis = enYakinOtopark(lcdIndis);

    lcd.setCursor(0, 0);
    lcd.print("Otopark 1: " + String((3 - bosParkYer[0])) + "/3");

    lcd.setCursor(0, 1);
    lcd.print("Otopark 2: " + String((3 - bosParkYer[1])) + "/3");

    lcd.setCursor(0, 2);
    lcd.print("Otopark 3: " + String((3 - bosParkYer[2])) + "/3");

    lcd.setCursor(0, 3);
    if(bosOtoparkIndis != -1){
      lcd.print("En Yakin Otopark : "+String(bosOtoparkIndis));
    }else{
      lcd.print("Bos Otopark Yok     ");
    }
  }


void isikKontrol(){
  int isik = analogRead(ldr);
  if (isik > 50) { //Okunan ışık değeri 250'den büyük ise
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);//LED yanmasın
      digitalWrite(led3, LOW);
      }

  if (isik < 50) { //Okunan ışık değeri 200'den küçük ise
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);//LED yansın
      digitalWrite(led3, HIGH);
    }
  }
