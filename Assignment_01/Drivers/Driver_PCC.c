#include "Driver_PCC.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PCC_REG(periph) (*(volatile PCC_Reg_t *)((PCC_BASE_ADDR) + (periph)))

/* Bit fields for PCC (from Reference Manual) */
#define PCC_CGC_MASK       (1UL << 30U)     /* Clock Gate Control bit */
#define PCC_PCS_MASK       (0x7UL << 24U)   /* Peripheral Clock Source bits */
#define PCC_PCS_SHIFT      (24U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static int32_t PCC_Setup(PCC_Peripheral_t periph);
static int32_t PCC_EnableClock(PCC_Peripheral_t periph);
static int32_t PCC_DisableClock(PCC_Peripheral_t periph);
static int32_t PCC_SetClockSource(PCC_Peripheral_t periph, uint32_t source);
static int32_t PCC_GetClockSource(PCC_Peripheral_t periph, uint32_t *source);

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief   Initialize PCC peripheral.
 * @param   periph  Peripheral index (offset).
 * @return  Execution status.
 */
static int32_t PCC_Setup(PCC_Peripheral_t periph)
{
    int32_t result;

    result = ARM_DRIVER_OK;

    if (periph > 0x1FFU)
    {
        result = ARM_DRIVER_ERROR_PARAMETER;
    }
    else
    {
        /* Disable clock by default */
        PCC_REG(periph) &= ~PCC_CGC_MASK;
    }

    return result;
}

/**
 * @brief   Enable clock for a peripheral.
 * @param   periph  Peripheral index (offset).
 * @return  Execution status.
 */
static int32_t PCC_EnableClock(PCC_Peripheral_t periph)
{
    int32_t result;

    result = ARM_DRIVER_OK;

    if (periph > 0x1FFU)
    {
        result = ARM_DRIVER_ERROR_PARAMETER;
    }
    else
    {
        PCC_REG(periph) |= PCC_CGC_MASK;
    }

    return result;
}

/**
 * @brief   Disable clock for a peripheral.
 * @param   periph  Peripheral index (offset).
 * @return  Execution status.
 */
static int32_t PCC_DisableClock(PCC_Peripheral_t periph)
{
    int32_t result;

    result = ARM_DRIVER_OK;

    if (periph > 0x1FFU)
    {
        result = ARM_DRIVER_ERROR_PARAMETER;
    }
    else
    {
        PCC_REG(periph) &= ~PCC_CGC_MASK;
    }

    return result;
}

/**
 * @brief   Set clock source for a peripheral.
 * @param   periph  Peripheral index (offset).
 * @param   source  Clock source value.
 * @return  Execution status.
 */
static int32_t PCC_SetClockSource(PCC_Peripheral_t periph, uint32_t source)
{
    int32_t result;

    result = ARM_DRIVER_OK;

    if (periph > 0x1FFU)
    {
        result = ARM_DRIVER_ERROR_PARAMETER;
    }
    else
    {
        PCC_REG(periph) &= ~PCC_PCS_MASK;
        PCC_REG(periph) |= ((source << PCC_PCS_SHIFT) & PCC_PCS_MASK);
    }

    return result;
}

/**
 * @brief   Get clock source of a peripheral.
 * @param   periph  Peripheral index (offset).
 * @param   source  Pointer to return clock source.
 * @return  Execution status.
 */
static int32_t PCC_GetClockSource(PCC_Peripheral_t periph, uint32_t *source)
{
    int32_t result;

    result = ARM_DRIVER_OK;

    if ((periph > 0x1FFU) || (source == NULL))
    {
        result = ARM_DRIVER_ERROR_PARAMETER;
    }
    else
    {
        *source = (PCC_REG(periph) & PCC_PCS_MASK) >> PCC_PCS_SHIFT;
    }

    return result;
}

/*******************************************************************************
 * Variables
 ******************************************************************************/

/**
 * @brief PCC driver access structure.
 */
ARM_DRIVER_PCC Driver_PCC0 =
{
    PCC_Setup,
    PCC_EnableClock,
    PCC_DisableClock,
    PCC_SetClockSource,
    PCC_GetClockSource,
};
