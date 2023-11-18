#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include "time.h"
#include <stdlib.h>

// Define o prot�tipo das tarefas 
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

// Cria a vari�vel para o sem�foro
xSemaphoreHandle xSemaphore = NULL;

// Cria uma vari�vel buffer de string
char buffer[7];
// Vari�vel de tempo em segundos
time_t segundos;
// Vari�vel do tempo atual
struct tm * dateTimeNow;
// Valor m�ximo de temperatura
float maxTemp = 45;

/**
 * Fun��o inicial. 
 */
int main_(void)
{
		// Fun��o para criar um sem�foro mutex
		xSemaphore = xSemaphoreCreateMutex();

		// Cria tr�s tarefas
		xTaskCreate(vTask1, "Task 1", 1000, (void*) 1, 1, NULL);
		xTaskCreate(vTask2, "Task 2", 1000, (void*) 2, 1, NULL);
		xTaskCreate(vTask3, "Task 3", 1000, (void*) 3, 1, NULL);

		// Inicializa o escalonador
		vTaskStartScheduler();

	for (;; );
	return 0;
}

/**
* Implementa��o da Task 1 para impress�o da Data atual.
* @param pvParameters Par�metros enviados na inicializa��o da Tarefa.
*/
void vTask1(void* pvParameters)
{
	// Recupera o valor recebido por par�metro
	long taskNmbr = (long) pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o sem�foro foi criado
		if (xSemaphore != NULL) {
			// Verifica se o sem�foro est� dispon�vel, se n�o estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Retorna o calend�rio atual
				time(&segundos);
				// Formata o calend�rio para a hora local
				dateTimeNow = localtime(&segundos);
				// Recupera informa��o de dia do calend�rio
				int dia = dateTimeNow->tm_mday;
				// Recupera informa��o de m�s do calend�rio
				int mes = dateTimeNow->tm_mon + 1;
				// Recupera informa��o de ano do calend�rio
				int ano = dateTimeNow->tm_year + 1900;
				// Cria a string para impress�o com os valores de data na vari�vel global de buffer
				sprintf(buffer, "Task %ld: %d/%d/%d\n", taskNmbr, dia, mes, ano);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o sem�foro para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			printf("O sem�foro n�o foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}

	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask2(void* pvParameters)
{
	// Recupera o valor recebido por par�metro
	long taskNmbr = (long)pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o sem�foro foi criado
		if (xSemaphore != NULL) {
			// Verifica se o sem�foro est� dispon�vel, se n�o estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Retorna o calend�rio atual
				time(&segundos);
				// Formata o calend�rio para a hora local
				dateTimeNow = localtime(&segundos);
				// Recupera informa��o de hora do calend�rio
				int hour = dateTimeNow->tm_hour;
				// Recupera informa��o de minutos do calend�rio
				int min = dateTimeNow->tm_min;
				// Recupera informa��o de segundos do calend�rio
				int sec = dateTimeNow->tm_sec;
				// Cria a string para impress�o com os valores de hora na vari�vel global de buffer
				sprintf(buffer, "Task %ld: %02d:%02d:%02d\n", taskNmbr, hour, min, sec);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o sem�foro para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			printf("O sem�foro n�o foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask3(void* pvParameters)
{
	// Recupera o valor recebido por par�metro
	long taskNmbr = (long)pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o sem�foro foi criado
		if (xSemaphore != NULL) {
			// Verifica se o sem�foro est� dispon�vel, se n�o estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Gera temperatura aleat�ria
				float temp = ((float)rand() / (float)(RAND_MAX)) * maxTemp;
				// Formata string com o nome da cidade e a temperatura
				sprintf(buffer, "Task %ld: Curitiba %.2foC\n\n", taskNmbr, temp);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o sem�foro para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o sem�foro n�o tenha sido criado
			printf("O sem�foro n�o foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}
	// A fun��o vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
