#include <esp_now.h>
#include <WiFi.h>

// Device Configuration
const uint8_t DEVICE_ID = 1;

// ADC configuration
const int ADC_PIN = 34;

// MAC ID
uint8_t receiverAddress[] = {
  0xB0, 0xA7, 0x32, 0x16, 0x3B, 0x6C
};

// Packet init
struct DataPacket {
  uint8_t deviceID;
  uint16_t force;
  uint32_t timestamp;
};

DataPacket packet;

void setup() {

  // Set baud rate to 115200... make sure seriel monitor is set to 115200 also 
  Serial.begin(115200);

  // Configure adc pin as an input
  pinMode(ADC_PIN, INPUT);

  // ESP-now command to set to station mode
  WiFi.mode(WIFI_STA);

  // Check if ESP-now is good
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  // Use MAC ID for peer info
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Check if peer is added
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Sender ready");
}

void loop() {

  // Temporary message
  const char message[] = "Hello";

  // Send message
  esp_err_t result = esp_now_send(
    receiverAddress,
    (const uint8_t *)message,
    sizeof(message)
  );

  // Check if message is sent
  if (result == ESP_OK) {
    Serial.println("Sent: Hello");
  } else {
    Serial.println("Send failed");
  }
  
/*
  // Read FSR
  uint16_t force = analogRead(ADC_PIN);

  // Get packet ready to send
  packet.deviceID = DEVICE_ID;
  packet.force = force;

  // Send packet
  esp_err_t result = esp_now_send(
    receiverAddress,
    (uint8_t *)&packet,
    sizeof(packet)
  );

  if (result == ESP_OK) {
    Serial.print("Sent | Device: ");
    Serial.print(packet.deviceID);
    Serial.print(" | Force: ");
    Serial.println(packet.force);
  } else {
    Serial.println("Send failed");
  }
*/

  delay(1000);
}