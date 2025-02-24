# LoRa E220 STM32 Library 🚀

Biblioteca para comunicação com o módulo **LoRa E220** usando **STM32**.  
Facilita a configuração e transmissão de dados entre dois módulos via **UART**.

---

## 📌 **Recursos**
✅ Comunicação confiável entre módulos LoRa E220  
✅ Suporte para **modo de configuração e operação**  
✅ Funções para **leitura e escrita de registradores**  
✅ Testado em **STM32** com HAL  
✅ Exemplo de **transmissor e receptor** incluído  

---

## 📡 **Como Usar**
### **1️⃣ Conectar os pinos**
| **LoRa E220** | **STM32** |
|--------------|---------|
| **VCC** (3.3V) | 3.3V |
| **GND** | GND |
| **TX** | RX da UART |
| **RX** | TX da UART |
| **M0** | GPIO (ex: PB2) |
| **M1** | GPIO (ex: PB10) |

### **2️⃣ Clonar o Repositório**
```sh
git clone https://github.com/seu-usuario/LoRa-E220-STM32.git
cd LoRa-E220-STM32
```

### **3️⃣ Adicionar ao Projeto STM32**
- Copie os arquivos `lora_e220.h` e `lora_e220.c` para seu projeto.
- Inclua `#include "lora_e220.h"` no `main.c`.

---

## ⚡ **Exemplo de Código**
### **Transmissor**
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

### **Receptor**
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
            printf("Recebido: %s
", buffer);
        }
        HAL_Delay(500);
    }
}
```

---

## 🔧 **Funções Disponíveis**
```c
void LoRa_E220_Init(LoRa_E220_t *lora);
void LoRa_E220_SetMode(LoRa_E220_t *lora, uint8_t mode);
int LoRa_E220_Send(LoRa_E220_t *lora, uint8_t *data, uint16_t size);
int LoRa_E220_Receive(LoRa_E220_t *lora, uint8_t *data, uint16_t size);
int LoRa_E220_ReadRegister(LoRa_E220_t *lora, uint8_t address);
int LoRa_E220_WriteRegister(LoRa_E220_t *lora, uint8_t address, uint8_t value);
```

---

## 📜 **Licença**
MIT License.  

📢 **Quer contribuir?** Faça um fork e bora codar! 🚀🔥
