/* ************************************************************************** 
 *  Hardware Layer definition
 *
 *  @Company
 *    Microchip Technology Inc.
 *
 *  @File Name
 *    hw_layer.h
 *
 *  @Summary
 *    Prototypes and defines for hardware layer.
 *
 *  @Description
 *    Definitions and function prototypes of hardware related functions and 
 *    definitions.
 *
 ****************************************************************************/

/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef _HW_LAYER_H    /* Guard against multiple inclusion */
#define _HW_LAYER_H

#include "definitions.h"

#define BOARD_LABEL             "SAME51 Curiosity Nano"
#define TIMER_DelayMs           SYSTICK_DelayMs

#define CONTEXT_PTR             uintptr_t context

void HardwareLayer_init(void);

#endif /* _HW_LAYER_H */

/* *****************************************************************************
 End of File
 */
