#include "button.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

static ButtonState_t s_buttonState[BUTTON_ID_MAX];

/*******************************************************************************
 * Code
 ******************************************************************************/

void BUTTON_Init(void)
{
    unsigned int i;

    for (i = 0U; i < BUTTON_ID_MAX; i++)
    {
        s_buttonState[i] = BUTTON_STATE_RELEASED;
    }
}

void BUTTON_Update(ButtonId_t buttonId, unsigned int isPressed)
{
    ButtonState_t currentState;

    currentState = s_buttonState[buttonId];

    switch (currentState)
    {
        case BUTTON_STATE_RELEASED:
            if (isPressed != 0U)
            {
                s_buttonState[buttonId] = BUTTON_STATE_PRESSED;
            }
            break;

        case BUTTON_STATE_PRESSED:
            if (isPressed == 0U)
            {
                s_buttonState[buttonId] = BUTTON_STATE_RELEASED;
            }
            break;

        default:
            /* Should not reach here. */
            s_buttonState[buttonId] = BUTTON_STATE_RELEASED;
            break;
    }
}

unsigned int BUTTON_IsPressed(ButtonId_t buttonId)
{
    unsigned int result;

    if (s_buttonState[buttonId] == BUTTON_STATE_PRESSED)
    {
        result = 1U;
    }
    else
    {
        result = 0U;
    }

    return result;
}


