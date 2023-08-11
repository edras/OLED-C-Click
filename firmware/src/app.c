/*******************************************************************************
  App Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the "application" level functions for the project.

  Description:
    This file contains the application functions for a project at their higher 
    level. 
 *******************************************************************************/
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

#include "hal.h"
#include "app.h"
#include "tasks.h"
#include "OLED/oled.h"
#include <string.h>
#include <stdio.h>

uint16_t temperature = 216;
uint16_t humidity = 498;
uint16_t voc = 1200; 

char msg[100];

void init_modules(void)
{
    // initialize both click boards
    oledc_initialize();
}

void print_oled_data(void)
{
    oledc_fill_screen(BLACK);
    
    sprintf(msg, "Temp: %.1f C    ", (float)temperature/10);
    oledc_draw_string_on_bg(2, 20, 1, 2, msg, GREEN, BLACK);
    sprintf(msg, "Mois: %.1f %%RH ", (float)humidity/10);
    oledc_draw_string_on_bg(2, 40, 1, 2, msg, GREEN, BLACK);
    sprintf(msg, "CO2:  %d ppm     ", voc);
    oledc_draw_string_on_bg(2, 60, 1, 2, msg, GREEN, BLACK);
}

void millisecond_callback(CONTEXT_PTR)
{
    /* This function should be called each 1 millisecond */
    Task_synch();
}