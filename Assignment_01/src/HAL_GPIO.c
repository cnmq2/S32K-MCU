/*******************************************************************************
 * @file    HAL_GPIO.h
 * @brief   Hardware abstraction layer for GPIO C file.
 * @date    Sep 24, 2025
 * @author  Chu Nhat Minh Quan
 ******************************************************************************/
#include "HAL_GPIO.h"
#include "S32K144.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void HAL_GPIO_Init(const uint8_t portNumber, const uint8_t pinNumber)
{
    switch (portNumber)
    {
        case HAL_GPIO_PORT_A:
            IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK;
            IP_PORTA->PCR[pinNumber] |= PORT_PCR_MUX(0x01U);
            break;

        case HAL_GPIO_PORT_B:
            IP_PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;
            IP_PORTB->PCR[pinNumber] |= PORT_PCR_MUX(0x01U);
            break;

        case HAL_GPIO_PORT_C:
            IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
            IP_PORTC->PCR[pinNumber] |= PORT_PCR_MUX(0x01U);
            break;

        case HAL_GPIO_PORT_D:
            IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
            IP_PORTD->PCR[pinNumber] |= PORT_PCR_MUX(0x01U);
            break;

        case HAL_GPIO_PORT_E:
            IP_PCC->PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK;
            IP_PORTE->PCR[pinNumber] |= PORT_PCR_MUX(0x01U);
            break;

        default:
            /* Invalid port number, do nothing */
            break;
    }
}

void HAL_GPIO_SetDirection(const uint8_t portNumber, const uint8_t pinNumber, HAL_GPIO_Dir_t direction)
{
    uint32_t shiftedDirection;

    shiftedDirection = (direction << pinNumber);

    switch (portNumber)
    {
        case HAL_GPIO_PORT_A:
            IP_PTA->PDDR |= shiftedDirection;
            break;

        case HAL_GPIO_PORT_B:
            IP_PTB->PDDR |= shiftedDirection;
            break;

        case HAL_GPIO_PORT_C:
            IP_PTC->PDDR |= shiftedDirection;
            break;

        case HAL_GPIO_PORT_D:
            IP_PTD->PDDR |= shiftedDirection;
            break;

        case HAL_GPIO_PORT_E:
            IP_PTE->PDDR |= shiftedDirection;
            break;

        default:
            /* Invalid port number, do nothing */
            break;
    }
}

void HAL_GPIO_SetPullResistor(const uint8_t portNumber, const uint8_t pinNumber, HAL_GPIO_Pull_t mode)
{
	uint32_t pullUpMask;

	if ((mode == HAL_GPIO_PULL_DOWN) || (mode == HAL_GPIO_PULL_UP))
	{

		pullUpMask = PORT_PCR_PE(0x1U)|PORT_PCR_PS(mode);

		switch(portNumber)
		{
			case HAL_GPIO_PORT_A:
				IP_PORTA->PCR[pinNumber] |= pullUpMask;
				break;

			case HAL_GPIO_PORT_B:
				IP_PORTB->PCR[pinNumber] |= pullUpMask;
				break;

			case HAL_GPIO_PORT_C:
				IP_PORTC->PCR[pinNumber] |= pullUpMask;
				break;

			case HAL_GPIO_PORT_D:
				IP_PORTD->PCR[pinNumber] |= pullUpMask;
				break;

			case HAL_GPIO_PORT_E:
				IP_PORTE->PCR[pinNumber] |= pullUpMask;
				break;

			default:
				/* Invalid port number, do nothing */
				break;
		}

	}
	else
	{
		/* Do nothing */
	}

}

//static void HAL_GPIO_SetEventTrigger(const uint8_t portNumber, const uint8_t pinNumber, HAL_GPIO_Interrupt_t mode)
//{
//
//}


void HAL_GPIO_WritePin(const uint8_t portNumber,const uint8_t pinNumber,const uint32_t mode)
{

//	GPIO_Type gpioBases[5] = { IP_PTA, IP_PTB, IP_PTC, IP_PTD, IP_PTE };
    if (mode == 0U)
    {
    	IP_PTD->PCOR = (1U << pinNumber);  /* Set */
    }
    else if (mode == 1U)
    {
    	IP_PTD->PSOR = (1U << pinNumber);  /* Set */
//    	gpioBases[portNumber]->PCOR = (1UL << pinNumber);  /* Clear */
    }
    else
    {
        /* Invalid mode, do nothing */
    }
}

uint32_t HAL_GPIO_ReadPin(const uint8_t portNumber, const uint8_t pinNumber)
{
    uint32_t pinState = 0U;
    const uint32_t pinMask = (1U << pinNumber);

    switch (portNumber)
    {
        case HAL_GPIO_PORT_A:
            pinState = (IP_PTA->PDIR & pinMask);
            break;

        case HAL_GPIO_PORT_B:
            pinState = (IP_PTB->PDIR & pinMask);
            break;

        case HAL_GPIO_PORT_C:
            pinState = (IP_PTC->PDIR & pinMask);
            break;

        case HAL_GPIO_PORT_D:
            pinState = (IP_PTD->PDIR & pinMask);
            break;

        case HAL_GPIO_PORT_E:
            pinState = (IP_PTE->PDIR & pinMask);
            break;

        default:
            /* Invalid port number, keep pinState = 0U */
            break;
    }

    return (pinState != 0U) ? 1U : 0U;
}
