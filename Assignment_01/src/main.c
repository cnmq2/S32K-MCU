/*******************************************************************************
 * @file    main.c
 * @brief   Application entry point.
 * @date    Sep 25, 2025
 * @author  Chu Nhat Minh Quan
 ******************************************************************************/

#include "S32K144.h"
#include "Driver_GPIO.h"
#include "app.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    /* Configure BUTTON_0 as input with pull-up. */
    s_gpioDriver->Setup(BUTTON_0, NULL);
    s_gpioDriver->SetDirection(BUTTON_0, ARM_GPIO_INPUT);
    s_gpioDriver->SetPullResistor(BUTTON_0, ARM_GPIO_PULL_UP);

    /* Configure BUTTON_1 as input with pull-up. */
    s_gpioDriver->Setup(BUTTON_1, NULL);
    s_gpioDriver->SetDirection(BUTTON_1, ARM_GPIO_INPUT);
    s_gpioDriver->SetPullResistor(BUTTON_1, ARM_GPIO_PULL_UP);

    /* Configure LED_RED as output and turn it off (logic high). */
    s_gpioDriver->Setup(LED_RED, NULL);
    s_gpioDriver->SetDirection(LED_RED, ARM_GPIO_OUTPUT);
    s_gpioDriver->SetOutput(LED_RED, 1U);

    /* Configure LED_BLUE as output and turn it off (logic high). */
    s_gpioDriver->Setup(LED_BLUE, NULL);
    s_gpioDriver->SetDirection(LED_BLUE, ARM_GPIO_OUTPUT);
    s_gpioDriver->SetOutput(LED_BLUE, 1U);

    while (1)
    {
        /* Update LED FSM periodically. */
        LED_FSM_Update();
    }

    return 0;
}
