/*******************************************************************************
 * @file    Driver_GPIO.c
 * @brief   Driver for GPIO C file.
 * @date    Sep 24, 2025
 * @author  Chu Nhat Minh Quan
 ******************************************************************************/

#include "Driver_GPIO.h"
#include "HAL_GPIO.h"

#define GPIO_MAX_PINS           32U
#define PORT_MAX				5U

#define PIN_IS_AVAILABLE(n)     ((n) < GPIO_MAX_PINS)
#define PORT_IS_AVAILABLE(n)	((n) < PORT_MAX)

#define GPIO_PORT(p)        (((p) >> 8) & 0xFFU)
#define GPIO_NUM(p)         ((p) & 0xFFU)

static int32_t GPIO_Setup(ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event)
{
    int32_t result;
    uint8_t callbackStatus;
    uint8_t pinNumber;
    uint8_t portNumber;

    result = ARM_DRIVER_OK;
    callbackStatus = 0U;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        HAL_GPIO_Init(portNumber, pinNumber);

//        callbackStatus = HAL_GPIO_RegisterCallback(pin, cb_event);

        if (0U == callbackStatus)
        {
            result = ARM_GPIO_ERROR_PIN;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}


static int32_t GPIO_SetDirection(ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction)
{
    int32_t result;
    uint8_t pinNumber;
    uint8_t portNumber;

    result = ARM_DRIVER_OK;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        switch (direction)
        {
            case ARM_GPIO_INPUT:
                HAL_GPIO_SetDirection(portNumber, pinNumber, HAL_GPIO_DIR_INPUT);
                break;

            case ARM_GPIO_OUTPUT:

                HAL_GPIO_SetDirection(portNumber, pinNumber, HAL_GPIO_DIR_OUTPUT);

                break;

            default:

                result = ARM_DRIVER_ERROR_PARAMETER;

                break;
        }
    }
    else
    {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetOutputMode(ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode)
{
    int32_t result;
    uint8_t pinNumber;
    uint8_t portNumber;

    result = ARM_DRIVER_OK;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        switch (mode)
        {
            case ARM_GPIO_PUSH_PULL:

//                HAL_GPIO_SetOutputMode(portNumber, pinNumber, ARM_GPIO_PUSH_PULL);

                break;

            case ARM_GPIO_OPEN_DRAIN:

//                HAL_GPIO_SetOutputMode(portNumber, pinNumber, ARM_GPIO_OPEN_DRAIN);

                break;

            default:

                result = ARM_DRIVER_ERROR_PARAMETER;

                break;
        }
    }
    else
    {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetPullResistor(ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor)
{
    int32_t result;
    uint8_t pinNumber;
    uint8_t portNumber;

    result = ARM_DRIVER_OK;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        switch (resistor)
        {
            case ARM_GPIO_PULL_NONE:

                HAL_GPIO_SetPullResistor(portNumber, pinNumber, HAL_GPIO_PULL_NONE);

                break;

            case ARM_GPIO_PULL_UP:

                HAL_GPIO_SetPullResistor(portNumber, pinNumber, HAL_GPIO_PULL_UP);

                break;

            case ARM_GPIO_PULL_DOWN:

                HAL_GPIO_SetPullResistor(portNumber, pinNumber, HAL_GPIO_PULL_DOWN);

                break;

            default:

                result = ARM_DRIVER_ERROR_PARAMETER;

                break;
        }
    }
    else
    {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetEventTrigger(ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger)
{
    int32_t result;
    uint8_t pinNumber;
    uint8_t portNumber;

    result = ARM_DRIVER_OK;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        switch (trigger)
        {
            case ARM_GPIO_TRIGGER_NONE:
//                HAL_GPIO_SetEventTrigger(portNumber, pinNumber, HAL_GPIO_TRIGGER_NONE);
                break;

            case ARM_GPIO_TRIGGER_RISING_EDGE:
//                HAL_GPIO_SetEventTrigger(portNumber, pinNumber, HAL_GPIO_TRIGGER_RISING_EDGE);
                break;

            case ARM_GPIO_TRIGGER_FALLING_EDGE:
//                HAL_GPIO_SetEventTrigger(portNumber, pinNumber, HAL_GPIO_TRIGGER_FALLING_EDGE);
                break;

            case ARM_GPIO_TRIGGER_EITHER_EDGE:
//                HAL_GPIO_SetEventTrigger(portNumber, pinNumber, HAL_GPIO_TRIGGER_EITHER_EDGE);
                break;

            default:
                result = ARM_DRIVER_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = ARM_GPIO_ERROR_PIN;
    }

    return result;
}

static void GPIO_SetOutput(ARM_GPIO_Pin_t pin, uint32_t val)
{
	uint8_t pinNumber;
	uint8_t portNumber;

	pinNumber = GPIO_NUM(pin);
	portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        HAL_GPIO_WritePin(portNumber, pinNumber, val);
    }
    else
    {
        /* Do nothing */
    }
}

static uint32_t GPIO_GetInput(ARM_GPIO_Pin_t pin)
{
    uint32_t value;
    uint8_t pinNumber;
    uint8_t portNumber;

    value = 0U;
    pinNumber = GPIO_NUM(pin);
    portNumber = GPIO_PORT(pin);

    if (PIN_IS_AVAILABLE(pinNumber) && PORT_IS_AVAILABLE(portNumber))
    {
        value = HAL_GPIO_ReadPin(portNumber, pinNumber);
    }
    else
    {
        /* Do nothing */
    }

    return value;
}


ARM_DRIVER_GPIO Driver_GPIO0 =
{
    GPIO_Setup,
    GPIO_SetDirection,
    GPIO_SetOutputMode,
    GPIO_SetPullResistor,
    GPIO_SetEventTrigger,
    GPIO_SetOutput,
    GPIO_GetInput,
};
