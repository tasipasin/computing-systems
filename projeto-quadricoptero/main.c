#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Definindo o protótipo das tarefas 
void guinada(void *pvParameters);
void arfagem(void *pvParameters);
void rolagem(void *pvParameters);

// Criando a variável para o semáforo
xSemaphoreHandle xSemaphore = NULL;

long motor0 = 100;
long motor1 = 100;
long motor2 = 100;
long motor3 = 100;

// Criando uma variável buffer para ma
char buffer[7];

int main_(void)
{
	// Função para criar um semáforo binário
	vSemaphoreCreateBinary(xSemaphore);

	// Cria tarefa de Guinada
	xTaskCreate(guinada, "Guinada", 1000, (void*)1, 1, NULL);
	// Cria tarefa de Arfagem
	xTaskCreate(arfagem, "Arfagem", 1000, (void*)1, 1, NULL);
	// Cria tarefa de Rolagem
	xTaskCreate(rolagem, "Rolagem", 1000, (void*)1, 1, NULL);

	// Inicializa o escalonador
	vTaskStartScheduler();

	for (;; );
	return 0;
}

void guinada(void* pvParameters)
{

	boolean way = ((int)pvParameters) == 1;
	for (;; )
	{
		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Determina o sentido da guinada
				// Se o valor for TRUE, é sentido horário
				// Se o valor for FALSE, é sentido anti-horário
				way = rand() & 1;
				int motor02 = 100;
				int motor13 = 100;
				// Verifica se é guinada no sentido horario
				if (way) {
					motor02 *= -1;
				}
				else
				{
					motor13 *= -1;
				}
				motor0 = motor2 += motor02;
				motor1 = motor3 += motor13;
				sprintf(buffer, "\nGuinada\n");
				//sprintf(buffer, "\nGuinada\nMotor 0: %d\nMotor 1: %d\nMotor 2: %d\nMotor 3: %d\n", motor0, motor1, motor2, motor3);
				vPrintString(buffer);
				xSemaphoreGive(xSemaphore);
				// Efetua delay de 10ms
				vTaskDelay(portTICK_RATE_MS * 10);
				
			}
		}
	}

	// Liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void arfagem(void* pvParameters)
{
	boolean front = ((int)pvParameters) == 1;
	for (;; )
	{
		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				front = rand() & 1;
				int motor23 = 100;
				int motor01 = 100;
				if (front) {
					motor01 *= -1;
				}
				else
				{
					motor23 *= -1;
				}
				motor2 = motor3 += motor23;
				motor0 = motor1 += motor01;
				sprintf(buffer, "\nArfagem\n");
				//sprintf(buffer, "Motor 0: %l\nMotor 1: %l\nMotor 2: %l\nMotor 3: %l", motor0, motor1, motor2, motor3);
				vPrintString(buffer);
				xSemaphoreGive(xSemaphore);
				// Adiciona delay de 40ms
				vTaskDelay(portTICK_RATE_MS * 40);
				
			}
		}
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void rolagem(void* pvParameters)
{
	boolean right = ((int)pvParameters) == 1;
	for (;; )
	{
		if (xSemaphore != NULL) {
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				right = rand() & 1;
				int motor03 = 100;
				int motor12 = 100;
				if (right) {
					motor12 *= -1;
				}
				else
				{
					motor03 *= -1;
				}
				motor0 = motor3 += motor03;
				motor1 = motor2 += motor12;
				sprintf(buffer, "\nRolagem\n");
				//sprintf(buffer, "Motor 0: %l\nMotor 1: %l\nMotor 2: %l\nMotor 3: %l", motor0, motor1, motor2, motor3);
				vPrintString(buffer);
				xSemaphoreGive(xSemaphore);
				// Adiciona delay de 20ms
				vTaskDelay(portTICK_RATE_MS * 20);
				
			}
		}
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
