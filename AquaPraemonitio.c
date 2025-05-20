#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "hardware/pwm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include "pico/bootrom.h"

/// @brief Define a porta I2C utilizada pelo OLED.
#define I2C_PORT i2c1

/// @brief Definições dos pinos do display OLED.
#define OLED_SDA 14
#define OLED_SCL 15
#define OLED_ADDR 0x3C
#define OLED_BAUDRATE 400000  ///< Taxa de comunicação I2C para o display OLED.

/// @brief Definições dos pinos do joystick.
#define JOYSTICK_VRX 27  ///< Pino do eixo X do joystick.
#define JOYSTICK_VRY 26  ///< Pino do eixo Y do joystick.
#define JOYSTICK_PB  22  ///< Pino do botão do joystick.

/// @brief Definições dos pinos do LED RGB.
#define RED_PIN   13  ///< Pino do LED vermelho.
#define BLUE_PIN  12  ///< Pino do LED azul.
#define GREEN_PIN 11  ///< Pino do LED verde.

/// @brief Macros para verificar se um botão foi pressionado.
#define JOYSTICK_SW_PRESSED gpio == 22
#define BUTTON_A_PRESSED gpio == BUTTON_A
#define BUTTON_B_PRESSED gpio == BUTTON_B

/// @brief Ativa o modo de boot USB para atualizar o firmware.
#define set_bootsel_mode() reset_usb_boot(0, 0)
#define botaoB 6

typedef struct
{
    uint16_t tipping_bucket;
    uint16_t submersible_pressure;
    bool alert_mode;
} praemonitio_t;

QueueHandle_t xQueueJoystickData;


void vSystemFeederTask(void *pvParameters);
void vDisplayTask(void *pvParameters);
void vLedRGBTask(void *pvmParameters);
void vLedMatrixTask(void *pvParameters);
void vBuzzerTask(void *pvParameters);
void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    // Cria a fila para compartilhamento de valor do joystick
    xQueueJoystickData = xQueueCreate(5, sizeof(praemonitio_t));

    // Criação das tasks
    xTaskCreate(vSystemFeederTask, "System Feeder Task", 256, NULL, 1, NULL);
    xTaskCreate(vDisplayTask, "Display Task", 512, NULL, 1, NULL);
    xTaskCreate(vLedRGBTask, "LED RGB Task", 256, NULL, 1, NULL);
    xTaskCreate(vLedMatrixTask, "LED Matrix Task", 256, NULL, 1, NULL);
    xTaskCreate(vBuzzerTask, "Buzzer Task", 256, NULL, 1, NULL);
    // Inicia o agendador
    vTaskStartScheduler();
    panic_unsupported();
}

void gpio_irq_handler(uint gpio, uint32_t events) { set_bootsel_mode(); }

void vSystemFeederTask(void *pvParameters)
{
    // TODO
}

void vDisplayTask(void *pvParameters)
{
    // TODO
}

void vLedRGBTask(void *pvmParameters)
{
    // TODO
}

void vLedMatrixTask(void *pvParameters)
{
    // TODO
}

void vBuzzerTask(void *pvParameters)
{
    // TODO
}