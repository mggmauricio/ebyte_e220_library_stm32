#ifndef LORA_E220_H
#define LORA_E220_H

#include "main.h"
#include "usart.h"
#include "gpio.h"


/**
 * @brief Endereços dos registradores do LoRa E220.
 */
#define LORA_REG_ADDR_HIGH       0x00  // Byte alto do endereço do módulo
#define LORA_REG_ADDR_LOW        0x01  // Byte baixo do endereço do módulo
#define LORA_REG_UART_CONFIG     0x02  // Configuração da UART
#define LORA_REG_RF_CONFIG       0x03  // Configuração do RF (Air Data Rate, Sub-Packet, Potência)
#define LORA_REG_CHANNEL         0x04  // Canal de operação
#define LORA_REG_TRANSMISSION    0x05  // Método de transmissão (transparente/fixo, LBT, WOR)
#define LORA_REG_CRYPT_H         0x06  // Chave de criptografia (High Byte)
#define LORA_REG_CRYPT_L         0x07  // Chave de criptografia (Low Byte)

/**
 * @brief Máscaras para configuração do registrador UART (0x02)
 */
#define LORA_UART_BAUD_1200      (0b000 << 5)
#define LORA_UART_BAUD_2400      (0b001 << 5)
#define LORA_UART_BAUD_4800      (0b010 << 5)
#define LORA_UART_BAUD_9600      (0b011 << 5)  // Default
#define LORA_UART_BAUD_19200     (0b100 << 5)
#define LORA_UART_BAUD_38400     (0b101 << 5)
#define LORA_UART_BAUD_57600     (0b110 << 5)
#define LORA_UART_BAUD_115200    (0b111 << 5)

#define LORA_UART_PARITY_8N1     (0b00 << 3)   // Default
#define LORA_UART_PARITY_8O1     (0b01 << 3)
#define LORA_UART_PARITY_8E1     (0b10 << 3)

/**
 * @brief Máscaras para configuração do registrador RF (0x03)
 */
#define LORA_AIR_RATE_2K4        (0b000)
#define LORA_AIR_RATE_4K8        (0b001)
#define LORA_AIR_RATE_9K6        (0b010)
#define LORA_AIR_RATE_19K2       (0b011)
#define LORA_AIR_RATE_38K4       (0b100)
#define LORA_AIR_RATE_62K5       (0b111)

#define LORA_SUB_PACKET_200      (0b00 << 6)   // Default
#define LORA_SUB_PACKET_128      (0b01 << 6)
#define LORA_SUB_PACKET_64       (0b10 << 6)
#define LORA_SUB_PACKET_32       (0b11 << 6)

#define LORA_RSSI_DISABLE        (0b0 << 5)  // Default
#define LORA_RSSI_ENABLE         (0b1 << 5)

#define LORA_POWER_22DBM         (0b00 << 0)  // Default
#define LORA_POWER_17DBM         (0b01 << 0)
#define LORA_POWER_13DBM         (0b10 << 0)
#define LORA_POWER_10DBM         (0b11 << 0)

/**
 * @brief Máscaras para configuração do registrador TRANSMISSION (0x05)
 */
#define LORA_RSSI_BYTE_DISABLE   (0b0 << 7)  // Default
#define LORA_RSSI_BYTE_ENABLE    (0b1 << 7)

#define LORA_TRANSPARENT_MODE    (0b0 << 6)  // Default
#define LORA_FIXED_MODE          (0b1 << 6)

#define LORA_LBT_DISABLE         (0b0 << 4)  // Default
#define LORA_LBT_ENABLE          (0b1 << 4)


/**
 * @brief Estrutura para armazenar as configurações do módulo LoRa E220.
 */
typedef struct {
    UART_HandleTypeDef *uart;  // UART usada para comunicação
    GPIO_TypeDef *m0_port;     // Porta do pino M0
    uint16_t m0_pin;           // Pino M0
    GPIO_TypeDef *m1_port;     // Porta do pino M1
    uint16_t m1_pin;           // Pino M1
} LoRa_E220_t;

/**
 * @brief Inicializa o módulo LoRa E220.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 */
void LoRa_E220_Init(LoRa_E220_t *lora);

/**
 * @brief Define o modo do módulo LoRa E220.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 * @param mode Modo do rádio (0 = Normal, 1 = Configuração, 2 = Sleep, 3 = Wake-Up).
 */
void LoRa_E220_SetMode(LoRa_E220_t *lora, uint8_t mode);

/**
 * @brief Envia um pacote de dados via LoRa.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 * @param data Ponteiro para os dados a serem enviados.
 * @param size Tamanho dos dados em bytes.
 * @return int 0 se sucesso, -1 se falha.
 */
int LoRa_E220_Send(LoRa_E220_t *lora, uint8_t *data, uint16_t size);

/**
 * @brief Recebe um pacote de dados via LoRa.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 * @param data Ponteiro para armazenar os dados recebidos.
 * @param size Tamanho máximo dos dados a serem recebidos.
 * @return int Número de bytes recebidos, -1 se falha.
 */
int LoRa_E220_Receive(LoRa_E220_t *lora, uint8_t *data, uint16_t size);

/**
 * @brief Lê um registrador do LoRa E220.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 * @param address Endereço do registrador a ser lido.
 * @return int Valor do registrador ou -1 se falha.
 */
int LoRa_E220_ReadRegister(LoRa_E220_t *lora, uint8_t address);

/**
 * @brief Escreve um valor em um registrador do LoRa E220.
 * @param lora Ponteiro para a estrutura LoRa_E220_t.
 * @param address Endereço do registrador a ser escrito.
 * @param value Valor a ser escrito no registrador.
 * @return int 0 se sucesso, -1 se falha.
 */
int LoRa_E220_WriteRegister(LoRa_E220_t *lora, uint8_t address, uint8_t value);


#endif // LORA_E220_H
