#define REC
#ifdef REC

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

char seq_idx = 0;
int packets_payload_broke = 0;
int packets_len_broke = 0;
int packets_seq_broke = 0;
int packets_rec = 0;
int packets_ok = 0;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
	char px;
	// char payload[32];
	char r;
	char g;
	char b;
} struct_message;

// Create a struct_message called myData
struct_message myData;
size_t data_len = sizeof(struct_message);

void readMacAddress() {
	Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
	uint8_t baseMac[6];
	esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
	if (ret == ESP_OK) {
		Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
			baseMac[0], baseMac[1], baseMac[2],
			baseMac[3], baseMac[4], baseMac[5]);
	}
	else {
		Serial.println("Failed to read MAC address");
	}
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
	packets_rec++;
	memcpy(&myData, incomingData, 4);
	if (len != 4) {
		packets_len_broke++;
		Serial.printf("Len: %d\n", len);
		delay(1000);
		return;
	}

	if (myData.px != (char)(seq_idx + 1)) {
		Serial.print("Seq Error");
		Serial.printf("%d: 0x%02x, 0x%02x, 0x%02x |", (int)myData.px, myData.r, myData.g, myData.b);
		packets_seq_broke++;
		return;
	}

	if (myData.r != 0xDA && myData.g != 0x88 && myData.b != 0xFF) {
		Serial.print("Data Error");
		Serial.printf("%d: 0x%02x, 0x%02x, 0x%02x |", (int)myData.px, myData.r, myData.g, myData.b);
		packets_payload_broke++;
		return;
	}

	packets_ok++;
	seq_idx = myData.px;
	// Serial.printf("%d: 0x%02x, 0x%02x, 0x%02x |", (int)myData.px, myData.r, myData.g, myData.b);
	
	// packets_rec++;
	// Serial.printf("Rec Len: %d / %d\n", len, data_len);
	// if (len != data_len) {
	// 	packets_len_broke++;
	// 	return;
	// }
	// memcpy(&myData, incomingData, sizeof(myData));

	// myData.payload[31] = '\0';

	// Serial.printf("%d:%s\n",myData.seq,myData.payload);

	// if (seq_idx != myData.seq) {
	// 	Serial.printf("Seq: %d / %d\n", myData.seq, seq_idx);
	// 	seq_idx = myData.seq;
	// 	packets_seq_broke++;
	// 	return;
	// }

	// // Serial.print("Bytes received: ");
	// if (!strncmp(myData.payload, "THIS IS A CHAR", 15)) {
	// 	Serial.printf("Body: %s / %s\n", myData.payload, "THIS IS A CHAR");
	// 	packets_payload_broke++;
	// 	return;
	// }
	// seq_idx++;
	// packets_ok++;
	// myData.a[31] = '\0';
	// Serial.println(myData.a);
	// Serial.println(len);
}

void setup() {
	// Initialize Serial Monitor
	Serial.begin(115200);

	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);

	// Init ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	readMacAddress();

	// Once ESPNow is successfully Init, we will register for recv CB to
	// get recv packer info
	esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

}


ulong last_frame = 0;
int sec_interval = 10;
void loop() {
	if (millis() > last_frame + 1000 * sec_interval) {
		last_frame = millis();

		Serial.printf("\n\n----------\n"
			"Packets Rec: %d\n"
			"Packets OK: %d\n"
			"Packets Ratio %f\n"
			"Packets Len Broke %d\n"
			"Packets Payload Broke %d\n"
			"Packets Seq Broke %d\n"
			"Data Rate %dB/s\n"
			"----------\n\n",
			packets_rec, packets_ok, (float)packets_ok / (float)packets_rec,
			packets_len_broke, packets_payload_broke, packets_seq_broke, packets_rec * 4 / sec_interval);

		packets_rec = 0;
		packets_ok = 0;
		packets_len_broke = 0;
		packets_payload_broke = 0;
		packets_seq_broke = 0;
	}
}

#endif