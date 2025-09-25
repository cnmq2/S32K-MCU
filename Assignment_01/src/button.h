#ifndef _BUTTON_H_
#define _BUTTON_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** Button states. */
typedef enum
{
    BUTTON_STATE_RELEASED = 0,
    BUTTON_STATE_PRESSED = 1
} ButtonState_t;

/** Button ID. */
typedef enum
{
    BUTTON_ID_1 = 0,
    BUTTON_ID_2 = 1
} ButtonId_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief Initialize button state machines.
 */
void BUTTON_Init(void);

/**
 * @brief Update button state machines, should be called periodically.
 *
 * @param buttonId Button identifier.
 * @param isPressed Current raw input (1 if pressed, 0 if released).
 */
void BUTTON_Update(ButtonId_t buttonId, unsigned int isPressed);

/**
 * @brief Check if a button is pressed.
 *
 * @param buttonId Button identifier.
 * @return 1 if button is in PRESSED state, 0 otherwise.
 */
unsigned int BUTTON_IsPressed(ButtonId_t buttonId);

#endif /* _BUTTON_H_ */
