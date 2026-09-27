#include <esp_now.h>
#include <WiFi.h>

// Data Packet Init
struct DataPacket {
  uint8_t deviceID;
  uint16_t adcValue;
};

DataPacket receivedPacket;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {

  // Make sure the packet is the size we expect
  if (len != sizeof(DataPacket)) {
    Serial.println("Invalid packet size");
    return;
  }

  // Copy received data into our packet structure
  memcpy(&receivedPacket, data, sizeof(receivedPacket));

  // Print
  Serial.print("Device: ");
  Serial.print(receivedPacket.deviceID);
  Serial.print(" | Force: ");
  Serial.println(receivedPacket.adcValue);
}

void setup() {

  // Set baud rate to 115200
  Serial.begin(115200);

  // ESP WiFi station mode
  WiFi.mode(WIFI_STA);

  // Check if esp-now is initialized
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  // ESP-now receiving data
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver ready");
}

void loop() {
}