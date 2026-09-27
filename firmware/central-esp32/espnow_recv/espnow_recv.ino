#include <esp_now.h>
#include <WiFi.h>

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  Serial.print("Received: ");
  Serial.write(data, len);
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver ready");
}

void loop() {
}