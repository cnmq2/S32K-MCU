/*******************************************************************************
 * @file    app.h
 * @brief   Application layer header file.
 * @date    Sep 24, 2025
 * @author  Chu Nhat Minh Quan
 ******************************************************************************/

#ifndef _APP_H_
#define _APP_H_

#include "Driver_GPIO.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define CPU_CLOCK_FREQ       (80000UL)
#define CYCLES_PER_MS        (80UL)

#define GPIO_PIN(port, pin)  (((port) << 8) | (pin))

#define LED_RED              GPIO_PIN(3U, 15U)
#define LED_BLUE             GPIO_PIN(3U, 0U)
#define BUTTON_0             GPIO_PIN(2U, 13U)
#define BUTTON_1             GPIO_PIN(2U, 12U)

#define DEBOUNCE_THRESHOLD   (2U)    /**< Consecutive samples required for state change */

/*******************************************************************************
 * Variables
 ******************************************************************************/

extern ARM_DRIVER_GPIO Driver_GPIO0;

/*******************************************************************************
 * Definitions - Types
 ******************************************************************************/

/**
 * @brief Structure for button debounce handling.
 */
typedef struct
{
    uint8_t stableState;   /**< Stable state: 0 = pressed, 1 = released. */
    uint8_t prevStable;    /**< Previous stable state for edge detection. */
    uint8_t counter;       /**< Counter for debounce filtering. */
} ButtonDebounce_t;

/**
 * @enum LedState_t
 * @brief LED finite state machine states.
 *
 * This enumeration defines the different LED states used by the FSM.
 */
typedef enum
{
    LED_STATE_IDLE = 0U,   /**< No LED blinking. */
    LED_STATE_RED_BLINK,   /**< Red LED is blinking. */
    LED_STATE_BLUE_BLINK   /**< Blue LED is blinking. */
} LedState_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief Delay function (blocking).
 *
 * @param[in] delayMs  Time to delay in milliseconds.
 * @return    None
 */
void delay(uint32_t delayMs);

/**
 * @brief Blink an LED pin.
 *
 * @param[in] pin     GPIO pin encoded with GPIO_PIN().
 * @param[in] time    Blink duration in milliseconds.
 * @return    None
 */
void blink_LED(uint32_t pin, uint32_t time);

/**
 * @brief Update LED FSM (Finite State Machine).
 *
 * This function should be called periodically. It performs:
 * - Button debounce
 * - Button press event detection
 * - FSM state update
 * - LED output control
 *
 * @return None
 */
void LED_FSM_Update(void);

#endif /* _APP_H_ */

