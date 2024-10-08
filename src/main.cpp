// #include <Arduino.h>

// #include <WiFi.h>
// #include <esp_wifi.h>

// #include <esp_now.h>

// void readMacAddress() {
// 	Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
// 	uint8_t baseMac[6];
// 	esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
// 	if (ret == ESP_OK) {
// 		Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
// 			baseMac[0], baseMac[1], baseMac[2],
// 			baseMac[3], baseMac[4], baseMac[5]);
// 	}
// 	else {
// 		Serial.println("Failed to read MAC address");
// 	}
// }

// size_t min(size_t a, size_t b) {
// 	if (a < b)
// 		return a;
// 	return b;
// }

// uint8_t buffer[100];

// // callback function that will be executed when data is received
// void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
// 	memcpy(&buffer, incomingData, min(len, sizeof(buffer)));
	
// 	Serial.printf("Bytes received: %d\n", len);
// 	for (int i = 0; i < len; i++){
// 		Serial.printf("%02x, ", incomingData[i]);
// 		if (!(i % 8))
// 			Serial.println();
// 	}

// 	Serial.printf("\nReceived From:\n%02x:%02x:%02x:%02x:%02x:%02x\n",
// 		mac[0], mac[1], mac[2],
// 		mac[3], mac[4], mac[5]);
// }

// void setup() {
// 	// Initialize Serial Monitor
// 	Serial.begin(115200);


// 	// Set device as a Wi-Fi Station
// 	WiFi.mode(WIFI_STA);
// 	// Init ESP-NOW
// 	if (esp_now_init() != ESP_OK) {
// 		Serial.println("Error initializing ESP-NOW");
// 		return;
// 	}

// 	Serial.println("Wifi Init.");
// 	// readMacAddress();

// 	// Once ESPNow is successfully Init, we will register for recv CB to
// 	// get recv packer info
// 	esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
// }

// void loop() {

// }