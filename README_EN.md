# LoRa E220 STM32 Library 🚀

A library for **LoRa E220** communication using **STM32**.  
Simplifies configuration and data transmission between two LoRa modules via **UART**.

---

## 📌 **Features**
✅ Support for **configuration and operation modes**  
✅ Functions for **register reading and writing**  
✅ Tested on **STM32** with HAL  
✅ Includes **transmitter and receiver example codes**  

---

## 📡 **How to Use**
### **1️⃣ Connect the Pins**
| **LoRa E220** | **STM32** |
|--------------|---------|
| **VCC** (3.3V) | 3.3V |
| **GND** | GND |
| **TX** | RX (UART) |
| **RX** | TX (UART) |
| **M0** | GPIO (e.g., PB2) |
| **M1** | GPIO (e.g., PB10) |

### **2️⃣ Clone the Repository**
```sh
git clone https://github.com/your-username/LoRa-E220-STM32.git
cd LoRa-E220-STM32
```

### **3️⃣ Add to STM32 Project**
- Copy `lora_e220.h` and `lora_e220.c` into your project.
- Include `#include "lora_e220.h"` in your `main.c`.

---

## ⚡ **Example Code**
### **Transmitter**
```c
#include "lora_e220.h"

LoRa_E220_t lora;
uint8_t msg[32] = "Hello LoRa!";

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    lora.uart = &huart1;
    lora.m0_port = GPIOB; lora.m0_pin = GPIO_PIN_2;
    lora.m1_port = GPIOB; lora.m1_pin = GPIO_PIN_10;

    LoRa_E220_Init(&lora);

    while (1) {
        LoRa_E220_Send(&lora, msg, sizeof(msg));
        HAL_Delay(2000);
    }
}
```

### **Receiver**
```c
#include "lora_e220.h"

LoRa_E220_t lora;
uint8_t buffer[32];

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    lora.uart = &huart1;
    lora.m0_port = GPIOB; lora.m0_pin = GPIO_PIN_2;
    lora.m1_port = GPIOB; lora.m1_pin = GPIO_PIN_10;

    LoRa_E220_Init(&lora);

    while (1) {
        int received = LoRa_E220_Receive(&lora, buffer, sizeof(buffer));
        if (received > 0) {
            printf("Received: %s
", buffer);
        }
        HAL_Delay(500);
    }
}
```

---

## 🔧 **Available Functions**
```c
void LoRa_E220_Init(LoRa_E220_t *lora);
void LoRa_E220_SetMode(LoRa_E220_t *lora, uint8_t mode);
int LoRa_E220_Send(LoRa_E220_t *lora, uint8_t *data, uint16_t size);
int LoRa_E220_Receive(LoRa_E220_t *lora, uint8_t *data, uint16_t size);
int LoRa_E220_ReadRegister(LoRa_E220_t *lora, uint8_t address);
int LoRa_E220_WriteRegister(LoRa_E220_t *lora, uint8_t address, uint8_t value);
```

---

## 📜 **License**
MIT License.  

📢 **Want to contribute?** Fork the repository and let's code! 🚀🔥
