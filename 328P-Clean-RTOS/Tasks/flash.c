/**
 * This version of flash .c is for use on systems that have limited stack space
 * and no display facilities.  The complete version can be found in the 
 * Demo/Common/Full directory.
 * 
 * Three tasks are created, each of which flash an LED at a different rate.  The first 
 * LED flashes every 200ms, the second every 400ms, the third every 600ms.
 *
 * The LED flash tasks provide instant visual feedback.  They show that the scheduler 
 * is still operational.
 *
 */


#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo program include files. */
#include "partest.h"
#include "flash.h"

#define ledSTACK_SIZE		configMINIMAL_STACK_SIZE
#define ledNUMBER_OF_LEDS	( 1 )
#define ledFLASH_RATE_BASE	( ( TickType_t ) 333 )

float rate = 120.0/600.0;

/* Variable used by the created tasks to calculate the LED number to use, and
the rate at which they should flash the LED. */
static volatile UBaseType_t uxFlashTaskNumber = 4;

static volatile char chTest[24] = "This is where I hide!!!!";
static volatile char chTestA[24] = "                        ";

/* The task that is created three times. */
static portTASK_FUNCTION_PROTO( vLEDFlashTask, pvParameters );
TickType_t tckElapsedTicks;

/*-----------------------------------------------------------*/

void vStartLEDFlashTasks( UBaseType_t uxPriority )
{
	xTaskCreate( vLEDFlashTask, "LEDx", ledSTACK_SIZE, NULL, uxPriority, ( TaskHandle_t * ) NULL );
}
/*-----------------------------------------------------------*/

static portTASK_FUNCTION( vLEDFlashTask, pvParameters )
{
TickType_t xFlashRate, xLastFlashTime, xTickCalculation;
UBaseType_t uxLED;
unsigned char vIntercept = 5;

	/* The parameters are not used. */
	( void ) pvParameters;
	
	// Set the right DEBUG LED port Number
	uxLED = uxFlashTaskNumber;
	
	xFlashRate = ledFLASH_RATE_BASE + ( ledFLASH_RATE_BASE * ( TickType_t ) uxLED );
	xFlashRate /= portTICK_PERIOD_MS;

	/* We will turn the LED on and off again in the delay period, so each
	delay is only half the total period. */
	//xFlashRate /= ( TickType_t ) 2;
	xFlashRate = 0x00D0;

	/* We need to initialize xLastFlashTime prior to the first call to 
	vTaskDelayUntil(). */
	xLastFlashTime = xTaskGetTickCount();

	tckElapsedTicks = 0x0000;
	xTickCalculation = 0x0000;
	for(;;)
	{
		xTickCalculation = 230.0 - rate * tckElapsedTicks;
		if (xTickCalculation < 1)
		{
			vTaskDelay(1);
		}
		vTaskDelay(1);
		/* Delay for half the flash period then turn the LED on. */
		//vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		//vParTestToggleLED( uxLED );

		/* Delay for half the flash period then turn the LED off. */
		//vTaskDelayUntil( &xLastFlashTime, xFlashRate );
		//vParTestToggleLED( uxLED );
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

