#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverAddress[] = {
  0xB0, 0xA7, 0x32, 0x16, 0x3B, 0x6C
};

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Sender ready");
}

void loop() {
  const char message[] = "Hello";

  esp_err_t result = esp_now_send(
    receiverAddress,
    (const uint8_t *)message,
    sizeof(message)
  );

  if (result == ESP_OK) {
    Serial.println("Sent: Hello");
  } else {
    Serial.println("Send failed");
  }

  delay(1000);
}