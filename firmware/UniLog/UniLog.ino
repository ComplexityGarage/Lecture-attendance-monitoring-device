#include <U8g2lib.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "config.h"
#include "images.h"

#if LANGUAGE == EN
#include "lang.h"
#elif LANGUAGE == PL
#include "lang_pl.h"
#else
#error "Language not defined"
#endif

#if WIFI_USE_STA
#include "esp_eap_client.h"
#endif

MFRC522DriverPinSimple ss_pin(SS_PIN);
MFRC522DriverSPI driver(ss_pin);
MFRC522 mfrc522(driver);

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// Setup methods
void initDisplay()
{
  Serial.println("Display init");

  display.begin();
  display.clearBuffer();
  display.enableUTF8Print();

#if LANGUAGE == PL
  display.setFont(u8g2_font_unifont_t_polish);
#else
  display.setFont(u8g2_font_6x10_tf);
#endif
}

void initMfrc()
{
  Serial.println("MFRC522 init");

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  mfrc522.PCD_Init();
}

void connectWifi()
{
  Serial.println("WiFi connecting.");

  displayTextWithAnimation(TXT_CONNECT_WIFI, {eyes_left, eyes_right});

#if WIFI_USE_STA
  WiFi.mode(WIFI_STA);

  esp_eap_client_set_identity((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME));
  esp_eap_client_set_username((uint8_t *)WIFI_USERNAME, strlen(WIFI_USERNAME));
  esp_eap_client_set_password((uint8_t *)WIFI_PASSWORD, strlen(WIFI_PASSWORD));
  esp_wifi_sta_enterprise_enable();

  WiFi.begin(WIFI_SSID);
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  long startConnectionTime = millis();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    if ((millis() - startConnectionTime) > WIFI_CONNECTION_TIMEOUT)
    {
      displayTextWithAnimation(TXT_WIFI_ERROR, {eyes_sad, eyes_sad_regular});
      break;
    }
  }
}
// End Setup methods

void setup()
{
  Serial.begin(9600);
  delay(250);

  initDisplay();
  initMfrc();
  connectWifi();
}

// Loop methods
void sendRequest(String uid)
{
  HTTPClient http;

  http.begin(API_URL);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "hash=" + uid;
  int httpResponseCode = http.POST(httpRequestData);

  http.end();
}

void displayTextWithAnimation(String message, std::initializer_list<const unsigned char *> images)
{
  Serial.println(message);

  for (const auto &image : images)
  {
    display.clearBuffer();

    display.drawXBMP(0, 0, SCREEN_WIDTH, 40, image);

    int width = display.getStrWidth(message.c_str());
    int x = width < 60 ? (SCREEN_WIDTH - width) / 2 : 1;
    display.setCursor(x, 60);
    display.print(message.c_str());

    display.sendBuffer();

    delay(750);
  }
}

String getCurrentUid()
{
  String hex = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    if (mfrc522.uid.uidByte[i] < 0x10)
    {
      hex += "0";
    }
    hex += String(mfrc522.uid.uidByte[i], HEX);
  }

  hex.toUpperCase();

  return hex;
}
// End Loop methods

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    displayTextWithAnimation(TXT_WIFI_ERROR, {eyes_sad, eyes_sad_regular});
    delay(1000);
    return;
  }

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    displayTextWithAnimation(TXT_WAITING_CARD, {eyes_regular, eyes_bottom});
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  static String lastUid;
  String currentUid = getCurrentUid();

  if (currentUid == lastUid)
  {
    displayTextWithAnimation(TXT_CARD_USED, {eyes_sad, eyes_sad_regular});
    delay(250);
    return;
  }

  lastUid = currentUid;

  displayTextWithAnimation(TXT_PROCESSING, {eyes_left, eyes_right});
  sendRequest(currentUid);
  displayTextWithAnimation(TXT_SUCCESS, {eyes_regular, eyes_bottom});
  delay(250);
}
