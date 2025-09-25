#ifndef DRIVER_PCC_H_
#define DRIVER_PCC_H_

#include <stdint.h>
#include "Driver_Common.h"   /* ARM_DRIVER_OK, ARM_DRIVER_ERROR_PARAMETER, ... */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* PCC register width */
typedef uint32_t PCC_Reg_t;

/* PCC base address for S32K144 */
#define PCC_BASE_ADDR      (0x40065000UL)

/* Offsets (example: only a few, more can be added later) */
typedef enum
{
    PCC_FTFC_INDEX   = 0x008U,  /* Flash memory controller */
    PCC_DMAMUX_INDEX = 0x018U,
    PCC_PORTA_INDEX  = 0x124U,
    PCC_PORTB_INDEX  = 0x128U,
    PCC_PORTC_INDEX  = 0x12CU,
    PCC_PORTD_INDEX  = 0x130U,
    PCC_PORTE_INDEX  = 0x134U,
    /* Extend more according to Reference Manual */
} PCC_Peripheral_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/* PCC driver functions */
typedef struct _ARM_DRIVER_PCC
{
    int32_t (*Setup)(PCC_Peripheral_t periph);
    int32_t (*EnableClock)(PCC_Peripheral_t periph);
    int32_t (*DisableClock)(PCC_Peripheral_t periph);
    int32_t (*SetClockSource)(PCC_Peripheral_t periph, uint32_t source);
    int32_t (*GetClockSource)(PCC_Peripheral_t periph, uint32_t *source);
} const ARM_DRIVER_PCC;

extern ARM_DRIVER_PCC Driver_PCC0;

#endif /* DRIVER_PCC_H_ */
