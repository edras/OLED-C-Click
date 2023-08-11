/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Microchip Technology Inc.

  @File Name
    hw_layer.c

  @Summary
    Implementation of hardware layer functions.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "hal.h"
#include "app.h"

/* This section lists the other files that are included in this file.
 */

void HardwareLayer_init(void)
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
       
    SYSTICK_TimerStart();    
    SYSTICK_TimerCallbackSet(millisecond_callback, 0);
}


/* *****************************************************************************
 End of File
 */
