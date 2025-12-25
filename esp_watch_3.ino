// ====================== LIBRARIES ======================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <EEPROM.h>
#include <GyverPortal.h>

// ====================== STRUCT ======================
struct LoginPass {
  char ssid[20];
  char pass[20];
  int timezone;
  bool Checkgmtm;
};

LoginPass lp;

// ====================== OBJECTS ======================
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

LiquidCrystal_I2C lcd(0x27, 16, 2);
GyverPortal GP;

// ====================== VARS ======================
unsigned long startAttemptTime;
int LM = -1;

// ====================== EEPROM ======================
void loadEEPROM() {
  EEPROM.begin(sizeof(LoginPass));
  EEPROM.get(0, lp);

  if ((uint8_t)lp.ssid[0] == 0xFF) {
    memset(&lp, 0, sizeof(lp));
    EEPROM.put(0, lp);
    EEPROM.commit();
  }
}

// ====================== CUSTOM CHARS ======================
byte L[8] = 
{
  B01011,
  B01101,
  B01110,
  B01011,
  B01011,
  B01110,
  B01101,
  B01011
};
byte R[8] =
{
  B11010,
  B10110,
  B01110,
  B11010,
  B11010,
  B01110,
  B10110,
  B11010
};
byte T[8] =
{
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte D[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte TR[8] =
{
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte DL[8] =
{
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B10000,
  B11000
};
byte DR[8] =
{
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00011
};
byte TD[8] =
{
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

// ====================== GROUPING CHARS TO NUMBERS ======================
void custom0(int x)
{ // составим из блоков цифру 0

  lcd.setCursor(x,0); // курсор на 0 строку
  lcd.write(0);  // и прописываем все блоки
  lcd.write(2);  // которые есть в этой строке
  lcd.write(1);  // у цифры 0
  lcd.setCursor(x, 1); // курсор на 1 строку
  lcd.write(0);  // и прописываем все блоки
  lcd.write(3);  // которые есть в этой строке
  lcd.write(1);  // у цифры 0
}

void custom1(int x)
{ // составим из блоков цифру 1
  lcd.setCursor(x,0);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(1);
  lcd.setCursor(x,1);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(1);
}

void custom2(int x)
{ // составим из блоков цифру 2
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(0);
  lcd.write(4);
  lcd.write(5);
}

void custom3(int x)
{ // составим из блоков цифру 3
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1); 
}

void custom4(int x)
{ // составим из блоков цифру 4
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(2);
  lcd.write(1);
}

void custom5(int x)
{ // составим из блоков цифру 5
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(x, 1);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1);
}

void custom6(int x)
{ // составим из блоков цифру 6
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(x, 1);
  lcd.write(0);
  lcd.write(4);
  lcd.write(1);
}

void custom7(int x)
{ // составим из блоков цифру 7
  lcd.setCursor(x,0);
  lcd.write(7);
  lcd.write(2);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(1);
}

void custom8(int x)
{ // составим из блоков цифру 8
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(4);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(0);
  lcd.write(4);
  lcd.write(1);
}

void custom9(int x)
{ // составим из блоков цифру 9
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(4);
  lcd.write(1);
  lcd.setCursor(x, 1);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1);
}

void printDigits(int digits, int x){
  
  switch (digits) {
  case 0:  
    custom0(x);
    break;
  case 1:  
    custom1(x);
    break;
  case 2:  
    custom2(x);
    break;
  case 3:  
    custom3(x);
    break;
  case 4:  
    custom4(x);
    break;
  case 5:  
    custom5(x);
    break;
  case 6:  
    custom6(x);
    break;
  case 7:  
    custom7(x);
    break;
  case 8:  
    custom8(x);
    break;
  case 9:  
    custom9(x);
    break;

  }
} 

void digitchars() {
  lcd.createChar(0,L);
  lcd.createChar(1,R);
  lcd.createChar(2,T);
  lcd.createChar(3,D);
  lcd.createChar(4,TD);
  lcd.createChar(5,DL);
  lcd.createChar(6,DR);
  lcd.createChar(7,TR);
}

// ====================== PORTAL ======================
void build() {
  String s;
  BUILD_BEGIN(s);
  add.THEME(GP_DARK);

  add.FORM_BEGIN("/login");

  add.LABEL("WiFi SSID");
  add.TEXT("lg", "", lp.ssid);
  add.BREAK();

  add.LABEL("WiFi Password");
  add.PASS("ps", "", lp.pass);
  add.BREAK();

  add.LABEL("Timezone (hours)");
  add.NUMBER("tz", "", lp.timezone);
  add.BREAK();

  add.CHECK("chgmtm", lp.Checkgmtm);
  add.LABEL("Minus timezone");
  add.BREAK();

  add.SUBMIT("Save");
  add.FORM_END();

  BUILD_END();
}

// ====================== WIFI ======================
void portalAction() {
  if (GP.form("/login")) {
    GP.copyStr("lg", lp.ssid);
    GP.copyStr("ps", lp.pass);
    lp.timezone = GP.getInt("tz");
    lp.Checkgmtm = GP.getCheck("chgmtm");

    EEPROM.put(0, lp);
    EEPROM.commit();
    ESP.restart();
  }
}

// ====================== WIFI FUNCTION ======================
void wifiMode() {
  unsigned long startTime = millis();
  unsigned long timeout = 20UL * 1000UL;

  if (strlen(lp.ssid) > 0 && (uint8_t)lp.ssid[0] != 0xFF) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(lp.ssid, lp.pass);

    while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < timeout) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connecting");
      lcd.setCursor(0,1);
      lcd.print(millis() / 500 % 2 ? ".   " : "..."); 
      delay(500);
      yield();
    }

    if (WiFi.status() == WL_CONNECTED) {
      lcd.clear();
      lcd.print("WiFi Connected");
      lcd.setCursor(0,1);
      lcd.print("IP " + WiFi.localIP().toString());
      delay(5000);
      return;
    }
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP Watch");

  lcd.clear();
  lcd.print("AP on ESP Watch");

  while (WiFi.getMode() == WIFI_AP) {
    GP.tick();
    portalAction();

    lcd.setCursor(0,1);
    lcd.print(WiFi.softAPIP());
    delay(500);
    yield();
  }
}


// ====================== NTP ======================
void ntpTime() {
  float tz = lp.timezone;

  if (lp.Checkgmtm) tz = -abs(tz);
  else tz = abs(tz);

  long offset = (long)(tz * 3600.0);
  timeClient.setTimeOffset(offset);
  timeClient.setUpdateInterval(60000);
  timeClient.begin();
}

// ====================== LCD PRINT DIGITS ======================
void switchwatch() {
      timeClient.update();

      int h = timeClient.getHours(); 
      int m = timeClient.getMinutes();

      if(m != LM){

      LM = m;

      int h1 = h / 10; 
      int h2 = h % 10; 
      int m1 = m / 10; 
      int m2 = m % 10;

      lcd.clear();
      printDigits(h1,0); 
      printDigits(h2,3); 
      lcd.setCursor(7,0);
      lcd.print(".");
      lcd.setCursor(7,1);
      lcd.print(".");
      printDigits(m1, 9);
      printDigits(m2, 12);

    }
        delay(1000);
}

// ====================== SETUP ======================
void setup() {
  Serial.begin(115200);
  Wire.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Abdosh's");
  lcd.setCursor(0,1);
  lcd.print("Technologies");
  delay(3000);

  loadEEPROM();
  GP.attachBuild(build);
  GP.start();

  digitchars();

  wifiMode();
  ntpTime();
}

// ====================== LOOP ======================
void loop() {
  GP.tick();
  portalAction();

  if (WiFi.status() == WL_CONNECTED) {
    //printTime();
    switchwatch();
  }

  delay(500);
}
