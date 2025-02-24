#include "e220.h"

void LoRa_E220_Init(LoRa_E220_t *lora) {
    // Definir o módulo no modo normal (M0 = 0, M1 = 0)
    HAL_GPIO_WritePin(lora->m0_port, lora->m0_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(lora->m1_port, lora->m1_pin, GPIO_PIN_RESET);
    HAL_Delay(100);
}

void LoRa_E220_SetMode(LoRa_E220_t *lora, uint8_t mode) {
    switch (mode) {
        case 0: // Normal Mode (M0=0, M1=0)
            HAL_GPIO_WritePin(lora->m0_port, lora->m0_pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(lora->m1_port, lora->m1_pin, GPIO_PIN_RESET);
            break;
        case 1: // Configuration Mode (M0=1, M1=0)
            HAL_GPIO_WritePin(lora->m0_port, lora->m0_pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(lora->m1_port, lora->m1_pin, GPIO_PIN_RESET);
            break;
        case 2: // Sleep Mode (M0=0, M1=1)
            HAL_GPIO_WritePin(lora->m0_port, lora->m0_pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(lora->m1_port, lora->m1_pin, GPIO_PIN_SET);
            break;
        case 3: // Wake-Up Mode (M0=1, M1=1)
            HAL_GPIO_WritePin(lora->m0_port, lora->m0_pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(lora->m1_port, lora->m1_pin, GPIO_PIN_SET);
            break;
        default:
            return; // Modo inválido
    }
    HAL_Delay(100);
}

int LoRa_E220_Send(LoRa_E220_t *lora, uint8_t *data, uint16_t size) {
    if (HAL_UART_Transmit(lora->uart, data, size, 1000) == HAL_OK) {
        return 0; // Sucesso
    }
    return -1; // Falha
}

int LoRa_E220_Receive(LoRa_E220_t *lora, uint8_t *data, uint16_t size) {
    if (HAL_UART_Receive(lora->uart, data, size, 1000) == HAL_OK) {
        return size; // Retorna o número de bytes recebidos
    }
    return -1; // Falha
}


int LoRa_E220_ReadRegister(LoRa_E220_t *lora, uint8_t address) {
    uint8_t send_data[3] = {0xC1, address, 0x01};  // Comando para ler 1 byte
    uint8_t receive_data[4] = {0};  // Resposta esperada

    // Envia o comando de leitura
    if (HAL_UART_Transmit(lora->uart, send_data, 3, 100) != HAL_OK) {
        return -1;  // Falha na transmissão
    }

    // Recebe a resposta
    if (HAL_UART_Receive(lora->uart, receive_data, 4, 100) != HAL_OK) {
        return -1;  // Falha na recepção
    }

    // Verifica se a resposta é válida
    if (receive_data[0] == 0xC1 && receive_data[1] == address && receive_data[2] == 0x01) {
        return receive_data[3];  // Retorna o valor do registrador
    }

    return -1;  // Resposta inválida
}

int LoRa_E220_WriteRegister(LoRa_E220_t *lora, uint8_t address, uint8_t value) {
    uint8_t send_data[4] = {0xC0, address, 0x01, value};  // Comando de escrita
    uint8_t receive_data[4] = {0};  // Resposta esperada

    // Envia o comando de escrita
    if (HAL_UART_Transmit(lora->uart, send_data, 4, 100) != HAL_OK) {
        return -1;  // Falha na transmissão
    }

    // Recebe a resposta
    if (HAL_UART_Receive(lora->uart, receive_data, 4, 100) != HAL_OK) {
        return -1;  // Falha na recepção
    }

    // Verifica se a resposta confirma a escrita
    if (receive_data[0] == 0xC1 && receive_data[1] == address && receive_data[2] == 0x01 && receive_data[3] == value) {
        return 0;  // Sucesso
    }

    return -1;  // Falha na escrita
}


