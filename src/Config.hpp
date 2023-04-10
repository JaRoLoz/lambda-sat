#ifndef CONFIG_H
#define CONFIG_H

#ifndef DEBUG
#define DEBUG true
#endif

#ifndef MAX_EVENT_NUMBER
#define MAX_EVENT_NUMBER 25
#endif

#ifndef LORA_SYNCWORD
#define LORA_SYNCWORD 0x2A
#endif

#ifndef LORA_CS
#define LORA_CS 12
#endif

#ifndef LORA_MISO
#define LORA_MISO 2
#endif

#ifndef LORA_MOSI
#define LORA_MOSI 4
#endif

#ifndef LORA_SCK
#define LORA_SCK 13
#endif

#ifndef LORA_RST
#define LORA_RST 0
#endif

#ifndef LORA_DIO0
#define LORA_DIO0 16
#endif

#ifndef LORA_RX_MESSAGES
#define LORA_RX_MESSAGES 5
#endif

#ifndef SDA_PIN
#define SDA_PIN 14
#endif

#ifndef SCL_PIN
#define SCL_PIN 15
#endif

#ifndef MPU6050_ADDR
// AD0 = GND -> 0x68
// AD0 = VCC -> 0x69
#define MPU6050_ADDR 0x68
#endif

#ifndef BMP180_ADDR
#define BMP180_ADDR 0x77
#endif

#ifndef SEA_LEVEL_PRESSURE
#define SEA_LEVEL_PRESSURE 102525.0F
#endif

#endif