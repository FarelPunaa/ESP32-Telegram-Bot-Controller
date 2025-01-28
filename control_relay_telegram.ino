#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";

#define BOTtoken "" //token bot
#define CHAT_ID "" //id 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int led1 = 13;
const int led2 = 12;
const int buzzer = 14;
const int relay1 = 21;
const int relay2 = 22;
const int relay3 = 23;

bool ledState = LOW;
bool relayState = LOW;

void chatBaru(int angkaPesan) {
  Serial.println("Pesan terbaru diterima");
  for (int i = 0; i < angkaPesan; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "User tidak ditemukan", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println("Pesan: " + text);

    String from_name = bot.messages[i].from_name;

    if (text == "/mulai") {
      String sambutan = "Hi, " + from_name + ".\n";
      sambutan += "Gunakan perintah berikut:\n";
      sambutan += "/led1_on, /led1_off\n";
      sambutan += "/led2_on, /led2_off\n";
      sambutan += "/buzzer_on, /buzzer_off\n";
      sambutan += "/relay1_on, /relay1_off\n";
      sambutan += "/relay2_on, /relay2_off\n";
      sambutan += "/relay3_on, /relay3_off";
      bot.sendMessage(chat_id, sambutan, "");
    }
    if (text == "/led1_on") {
      bot.sendMessage(chat_id, "LED1 dinyalakan", "");
      ledState = HIGH;
      digitalWrite(led1, ledState);
    } 
    if (text == "/led1_off") {
      bot.sendMessage(chat_id, "LED1 dimatikan", "");
      ledState = LOW;
      digitalWrite(led1, ledState);
    } 
    if (text == "/led2_on") {
      bot.sendMessage(chat_id, "LED2 dinyalakan", "");
      ledState = HIGH;
      digitalWrite(led2, ledState);
    } 
    if (text == "/led2_off") {
      bot.sendMessage(chat_id, "LED2 dimatikan", "");
      ledState = LOW;
      digitalWrite(led2, ledState);
    } 
    if (text == "/buzzer_on") {
      bot.sendMessage(chat_id, "Buzzer dinyalakan", "");
      tone(buzzer, 1000);
    } 
    if (text == "/buzzer_off") {
      bot.sendMessage(chat_id, "Buzzer dimatikan", "");
      noTone(buzzer);
    } 
    if (text == "/relay1_on") {
      bot.sendMessage(chat_id, "Relay1 dinyalakan", "");
      relayState = HIGH;
      digitalWrite(relay1, relayState);
    } 
    if (text == "/relay1_off") {
      bot.sendMessage(chat_id, "Relay1 dimatikan", "");
      relayState = LOW;
      digitalWrite(relay1, relayState);
    } 
    if (text == "/relay2_on") {
      bot.sendMessage(chat_id, "Relay2 dinyalakan", "");
      relayState = HIGH;
      digitalWrite(relay2, relayState);
    } 
    if (text == "/relay2_off") {
      bot.sendMessage(chat_id, "Relay2 dimatikan", "");
      relayState = LOW;
      digitalWrite(relay2, relayState);
    } 
    if (text == "/relay3_on") {
      bot.sendMessage(chat_id, "Relay3 dinyalakan", "");
      relayState = HIGH;
      digitalWrite(relay3, relayState);
    } 
    if (text == "/relay3_off") {
      bot.sendMessage(chat_id, "Relay3 dimatikan", "");
      relayState = LOW;
      digitalWrite(relay3, relayState);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  digitalWrite(led1, ledState);
  digitalWrite(led2, ledState);
  digitalWrite(buzzer, ledState);
  digitalWrite(relay1, relayState);
  digitalWrite(relay2, relayState);
  digitalWrite(relay3, relayState);

  Serial.print("Menghubungkan ke WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi");
  Serial.println("IP: " + WiFi.localIP().toString());

  client.setInsecure();
  Serial.print("Menghubungkan ke Telegram...");
  if (client.connect("api.telegram.org", 443)) {
    Serial.println("Berhasil terhubung ke server Telegram");
  } else {
    Serial.println("Gagal terhubung ke server Telegram");
  }
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int angkaPesan = bot.getUpdates(bot.last_message_received + 1);
    while (angkaPesan) {
      chatBaru(angkaPesan);
      angkaPesan = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
