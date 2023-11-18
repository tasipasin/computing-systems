#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include "time.h"
#include <stdlib.h>

// Define o protótipo das tarefas 
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

// Cria a variável para o semáforo
xSemaphoreHandle xSemaphore = NULL;

// Cria uma variável buffer de string
char buffer[7];
// Variável de tempo em segundos
time_t segundos;
// Variável do tempo atual
struct tm * dateTimeNow;
// Valor máximo de temperatura
float maxTemp = 45;

/**
 * Função inicial. 
 */
int main_(void)
{
		// Função para criar um semáforo mutex
		xSemaphore = xSemaphoreCreateMutex();

		// Cria três tarefas
		xTaskCreate(vTask1, "Task 1", 1000, (void*) 1, 1, NULL);
		xTaskCreate(vTask2, "Task 2", 1000, (void*) 2, 1, NULL);
		xTaskCreate(vTask3, "Task 3", 1000, (void*) 3, 1, NULL);

		// Inicializa o escalonador
		vTaskStartScheduler();

	for (;; );
	return 0;
}

/**
* Implementação da Task 1 para impressão da Data atual.
* @param pvParameters Parâmetros enviados na inicialização da Tarefa.
*/
void vTask1(void* pvParameters)
{
	// Recupera o valor recebido por parâmetro
	long taskNmbr = (long) pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o semáforo foi criado
		if (xSemaphore != NULL) {
			// Verifica se o semáforo está disponível, se não estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Retorna o calendário atual
				time(&segundos);
				// Formata o calendário para a hora local
				dateTimeNow = localtime(&segundos);
				// Recupera informação de dia do calendário
				int dia = dateTimeNow->tm_mday;
				// Recupera informação de mês do calendário
				int mes = dateTimeNow->tm_mon + 1;
				// Recupera informação de ano do calendário
				int ano = dateTimeNow->tm_year + 1900;
				// Cria a string para impressão com os valores de data na variável global de buffer
				sprintf(buffer, "Task %ld: %d/%d/%d\n", taskNmbr, dia, mes, ano);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o semáforo para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}

	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask2(void* pvParameters)
{
	// Recupera o valor recebido por parâmetro
	long taskNmbr = (long)pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o semáforo foi criado
		if (xSemaphore != NULL) {
			// Verifica se o semáforo está disponível, se não estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Retorna o calendário atual
				time(&segundos);
				// Formata o calendário para a hora local
				dateTimeNow = localtime(&segundos);
				// Recupera informação de hora do calendário
				int hour = dateTimeNow->tm_hour;
				// Recupera informação de minutos do calendário
				int min = dateTimeNow->tm_min;
				// Recupera informação de segundos do calendário
				int sec = dateTimeNow->tm_sec;
				// Cria a string para impressão com os valores de hora na variável global de buffer
				sprintf(buffer, "Task %ld: %02d:%02d:%02d\n", taskNmbr, hour, min, sec);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o semáforo para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTask3(void* pvParameters)
{
	// Recupera o valor recebido por parâmetro
	long taskNmbr = (long)pvParameters;
	// Loop infinito
	for (;; )
	{
		// Verifica se o semáforo foi criado
		if (xSemaphore != NULL) {
			// Verifica se o semáforo está disponível, se não estiver
			// espera a quantidade de tempo para verificar novamente
			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				// Gera temperatura aleatória
				float temp = ((float)rand() / (float)(RAND_MAX)) * maxTemp;
				// Formata string com o nome da cidade e a temperatura
				sprintf(buffer, "Task %ld: Curitiba %.2foC\n\n", taskNmbr, temp);
				// Imprime o valor presente no buffer global
				vPrintString(buffer);
				// Entrega o semáforo para outra atividade
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Efetua um delay na tarefa a cada 400 ticks
		vTaskDelay(portTICK_RATE_MS * 400);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}
