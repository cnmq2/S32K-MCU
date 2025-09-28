
#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <stdint.h>
#ifdef  __cplusplus
extern "C"
{
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum
{
    HAL_GPIO_PORT_A = 0U,
    HAL_GPIO_PORT_B,
    HAL_GPIO_PORT_C,
    HAL_GPIO_PORT_D,
    HAL_GPIO_PORT_E,
    HAL_GPIO_PORT_MAX
} HAL_GPIO_Port_t;

typedef enum
{
	HAL_GPIO_DIR_INPUT = 0U,
	HAL_GPIO_DIR_OUTPUT
} HAL_GPIO_Dir_t;



typedef enum
{
	HAL_GPIO_PULL_DOWN = 0U,
	HAL_GPIO_PULL_UP,
	HAL_GPIO_PULL_NONE
} HAL_GPIO_Pull_t;

typedef enum
{
    HAL_GPIO_TRIGGER_NONE,
    HAL_GPIO_TRIGGER_RISING_EDGE,
    HAL_GPIO_TRIGGER_FALLING_EDGE,
    HAL_GPIO_TRIGGER_EITHER_EDGE
} HAL_GPIO_Interrupt_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*******************************************************************************
 * @brief   Initialize a GPIO pin with default configuration.
 *
 * This function enables the clock for the specified port and configures
 * the pin multiplexing for GPIO functionality.
 *
 * @param   portNumber  Port index (HAL_GPIO_PORT_A ... HAL_GPIO_PORT_E).
 * @param   pinNumber   Pin index within the selected port.
 ******************************************************************************/
void HAL_GPIO_Init(const uint8_t portNumber, const uint8_t pinNumber);

/*******************************************************************************
 * @brief   Configure the direction of a GPIO pin.
 *
 * Sets the selected pin as input or output depending on the provided
 * direction parameter.
 *
 * @param   portNumber  Port index (HAL_GPIO_PORT_A ... HAL_GPIO_PORT_E).
 * @param   pinNumber   Pin index within the selected port.
 * @param   direction   Direction setting:
 *                      - HAL_GPIO_DIR_INPUT
 *                      - HAL_GPIO_DIR_OUTPUT
 ******************************************************************************/
void HAL_GPIO_SetDirection(const uint8_t portNumber, const uint8_t pinNumber, HAL_GPIO_Dir_t direction);

/*******************************************************************************
 * @brief   Configure pull-up or pull-down resistor for a GPIO pin.
 *
 * This function enables the internal pull-up or pull-down resistor
 * on the specified pin, or disables it if not needed.
 *
 * @param   portNumber  Port index (HAL_GPIO_PORT_A ... HAL_GPIO_PORT_E).
 * @param   pinNumber   Pin index within the selected port.
 * @param   mode        Pull resistor configuration:
 *                      - HAL_GPIO_PULL_NONE
 *                      - HAL_GPIO_PULL_UP
 *                      - HAL_GPIO_PULL_DOWN
 ******************************************************************************/
void HAL_GPIO_SetPullResistor(const uint8_t portNumber, const uint8_t pinNumber, HAL_GPIO_Pull_t mode);

/*******************************************************************************
 * @brief   Write logic value to a GPIO pin.
 *
 * This function sets the output state of a pin to logic high or low,
 * depending on the mode parameter. The pin must be configured as
 * output beforehand.
 *
 * @param   portNumber  Port index (HAL_GPIO_PORT_A ... HAL_GPIO_PORT_E).
 * @param   pinNumber   Pin index within the selected port.
 * @param   mode        Pin state:
 *                      - 0: Logic low
 *                      - 1: Logic high
 ******************************************************************************/
void HAL_GPIO_WritePin(const uint8_t portNumber, const uint8_t pinNumber, const uint32_t mode);


#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H_ */
