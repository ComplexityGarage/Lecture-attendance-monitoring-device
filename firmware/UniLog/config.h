#ifndef CONFIG_H
#define CONFIG_H

#if __has_include("secrets.h")
#include "secrets.h"
#endif

// Lang
#define EN 0
#define PL 1

// Wifi
#define WIFI_CONNECTION_TIMEOUT 60000 // 1 minute

// Display
#define I2C_ADDRESS 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Rfid RC 522
#define SS_PIN T5
#define RST_PIN RST
#define SCK_PIN SCK
#define MOSI_PIN MOSI
#define MISO_PIN MISO

#endif