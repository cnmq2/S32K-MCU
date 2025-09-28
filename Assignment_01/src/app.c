/*******************************************************************************
 * @file    app.c
 * @brief   Application layer source file.
 * @date    Sep 24, 2025
 * @author  Chu Nhat Minh Quan
 ******************************************************************************/

#include "app.h"
#include "Driver_GPIO.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/** GPIO driver instance (static: no external linkage). */
static ARM_DRIVER_GPIO *s_gpioDriver = &Driver_GPIO0;

/** FSM state. */
static LedState_t s_ledState = LED_STATE_IDLE;

/** Button debounce instances (initialized as released = 1U). */
static ButtonDebounce_t s_btn0 = {1U, 1U, 0U};
static ButtonDebounce_t s_btn1 = {1U, 1U, 0U};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Update debounce logic for a single button.
 *
 * @param[in,out] btn       Pointer to debounce structure.
 * @param[in]     rawInput  Current raw input (0 = pressed, 1 = released).
 */
static void Debounce_Update(ButtonDebounce_t *btn, uint8_t rawInput);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void Debounce_Update(ButtonDebounce_t *btn, uint8_t rawInput)
{
    if (btn == 0U)
    {
        return; /* Defensive: invalid parameter. */
    }

    if (rawInput == btn->stableState)
    {
        /* Input matches current stable state -> reset counter. */
        btn->counter = 0U;
    }
    else
    {
        /* Input different -> increment counter. */
        if (btn->counter < DEBOUNCE_THRESHOLD)
        {
            btn->counter++;
        }
        else
        {
            /* Threshold reached -> accept new stable state. */
            btn->prevStable  = btn->stableState;
            btn->stableState = rawInput;
            btn->counter     = 0U;
        }
    }
}

void LED_FSM_Update(void)
{
    uint8_t rawBtn0;
    uint8_t rawBtn1;

    /* Read inputs. */
    rawBtn0 = s_gpioDriver->GetInput(BUTTON_0); /* 0 = pressed. */
    rawBtn1 = s_gpioDriver->GetInput(BUTTON_1);

    /* Update debounce filters. */
    Debounce_Update(&s_btn0, rawBtn0);
    Debounce_Update(&s_btn1, rawBtn1);

    /* Detect falling edge (released -> pressed). */
    if ((s_btn0.prevStable == 1U) && (s_btn0.stableState == 0U))
    {
        s_ledState = LED_STATE_BLUE_BLINK;
    }
    else if ((s_btn1.prevStable == 1U) && (s_btn1.stableState == 0U))
    {
        s_ledState = LED_STATE_RED_BLINK;
    }
    else
    {
        /* No state change. */
    }

    /* Execute action based on FSM state. */
    switch (s_ledState)
    {
        case LED_STATE_IDLE:
        {
            s_gpioDriver->SetOutput(LED_RED, 1U);
            s_gpioDriver->SetOutput(LED_BLUE, 1U);
            break;
        }

        case LED_STATE_RED_BLINK:
        {
            blink_LED(LED_RED, 10000U);
            s_gpioDriver->SetOutput(LED_BLUE, 1U);
            break;
        }

        case LED_STATE_BLUE_BLINK:
        {
            blink_LED(LED_BLUE, 10000U);
            s_gpioDriver->SetOutput(LED_RED, 1U);
            break;
        }

        default:
        {
            s_ledState = LED_STATE_IDLE;
            break;
        }
    }
}

void delay(const uint32_t delayMs)
{
    volatile uint32_t iterationCounter;
    uint32_t msCounter = delayMs;

    while (msCounter-- > 0U)
    {
        for (iterationCounter = 0U; iterationCounter < CYCLES_PER_MS; iterationCounter++)
        {
            __asm("nop"); /* Prevent compiler optimization. */
        }
    }
}

void blink_LED(uint32_t pin, uint32_t time)
{
    /* Toggle the pin with delay. */
    s_gpioDriver->SetOutput(pin, 1U);
    delay(time);
    s_gpioDriver->SetOutput(pin, 0U);
    delay(time);
}
