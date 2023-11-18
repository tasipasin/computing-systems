/*
 * Autor: Tasi Guilhen Pasin
 * Curso: Engenharia de Computa��o
 */


#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Define a quantidade m�xima do valor aleat�rio gerado de Batimentos Card�acos
#define MAX_HEART_BEAT_RAND 140
// Define a quantidade m�nima do valor aleat�rio gerado de Batimentos Card�acos
#define MIN_HEART_BEAT_RAND 20
// Define o valor de Batimento Card�aco que passa a ser Muito Baixo
#define LOW_HEART_BEAT 50
// Define o valor de Batimento Card�aco que passa a ser Muito Alto
#define HIGH_HEART_BEAT 90

// Define a quantidade m�xima do valor aleat�rio gerado de Satura��o de Oxig�nio
#define MAX_OXIGEN_SAT_RAND 100
// Define a quantidade m�nima do valor aleat�rio gerado de Satura��o de Oxig�nio
#define MIN_OXIGEN_SAT_RAND 80
// Define o valor de Satura��o de Oxig�nio que passa a ser Muito Baixo
#define LOW_OXIGEN_SAT 90

// Define a quantidade m�xima do valor aleat�rio gerado de Temperatura
#define MAX_TEMP_RAND 41
// Define a quantidade m�nima do valor aleat�rio gerado de Temperatura
#define MIN_TEMP_RAND 34
// Define o valor de Temperatura que passa a ser Muito Baixo
#define LOW_TEMP 35
// Define o valor de Temperatura que passa a ser Muito Alto
#define HIGH_TEMP 37.5

// Contabiliza��o de milissegundos e um segundo
#define SECOND_MILISSECONDS 1000

// Handler da tarefa de Controle de Batimentos Card�acos
xTaskHandle taskHandlerHeartBeat;
// Handler da tarefa de Controle de Satura��o de Oxig�nio
xTaskHandle taskHandlerOxigenSat;
// Handler da tarefa de Controle de Temperatura
xTaskHandle taskHandlerTemperature;

/*
 * Implementa��o da Tarefa de Controle de Batimentos Card�acos
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskHeartBeat(void *pvParameters);

/*
 * Implementa��o da Tarefa de Controle de Satura��o de Oxig�nio
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskOxigenSat(void *pvParameters);

/*
 * Implementa��o da Tarefa de Controle de Temperatura
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskTemperature(void *pvParameters);

/*
 * Implementa��o da Tarefa de Controle de Batimentos Card�acos
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskHeartBeat(void *pvParameters)
{
	// Recebe o par�metro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleat�rio do batimento cardiaco limitado por um valor m�nimo e um m�ximo
		int heartBeatValue = (rand() % (MAX_HEART_BEAT_RAND - MIN_HEART_BEAT_RAND + 1) + MIN_HEART_BEAT_RAND);
		// Imprime a informa��o do batimento cardiaco gerado aleat�riamente
		// com a string recebida por parametro
		vPrintStringAndNumber(msg, heartBeatValue);
		// Verifica se o valor de batimento cardiaco gerado � menor que o valor m�nimo
		if (LOW_HEART_BEAT > heartBeatValue) {
			// Imprime informa��o de batimento cardiaco baixo
			vPrintString("Batimentos Cardiacos muito baixos\n");
		}
		// Verifica se o valor de batimento cardiaco gerado � maior que o valor m�ximo
		else if (HIGH_HEART_BEAT < heartBeatValue) {
			// Imprime informa��o de batimento cardiaco alto
			vPrintString("Batimentos Cardiacos muito altos\n");
		}
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclus�o da tarefa
	vTaskDelete(NULL);
}

/*
 * Implementa��o da Tarefa de Controle de Satura��o de Oxig�nio
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskOxigenSat(void *pvParameters)
{
	// Recebe o par�metro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleat�rio da satura��o de oxigenio limitado por um valor m�nimo e um m�ximo
		int oxigenSatValue = (rand() % (MAX_OXIGEN_SAT_RAND - MIN_OXIGEN_SAT_RAND + 1) + MIN_OXIGEN_SAT_RAND);
		// Imprime a informa��o da satura��o de oxigenio gerado aleat�riamente
		// com a string recebida por parametro
		printf("%s%d%s\n", msg, oxigenSatValue, "%");
		// Verifica se o valor de satura��o de oxigenio gerado � menor que o valor m�nimo
		if (LOW_OXIGEN_SAT > oxigenSatValue) {
			// Imprime informa��o de satura��o de oxigenio baixo
			vPrintString("Saturacao de Oxigenio baixa no sangue\n");
		}
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclus�o da tarefa
	vTaskDelete(NULL);
}

/*
 * Implementa��o da Tarefa de Controle de Temperatura
 * @param pvParameters Par�metros enviados na inicializa��o da Tarefa
 */
void vTaskTemperature(void *pvParameters)
{
	// Recebe o par�metro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleat�rio da temperatura limitado por um valor m�nimo e um m�ximo
		float tempValue = (rand() % (MAX_TEMP_RAND - MIN_TEMP_RAND + 1) + MIN_TEMP_RAND);
		// Imprime a informa��o da temperatura gerado aleat�riamente
		// com a string recebida por parametro
		printf("%s%.0f%c\n", msg, tempValue, (char)248);
		// Verifica se o valor de temperatura gerado � menor que o valor m�nimo
		if (LOW_TEMP > tempValue) {
			// Imprime informa��o de temperatura baixa
			vPrintString("Hipotermia\n");
		}
		// Verifica se o valor de temperatura gerado � maior que o valor m�ximo
		else if (HIGH_TEMP < tempValue) {
			// Imprime informa��o de temperatura alta
			vPrintString("Febre\n");
		}
		// Imprime linha em branco
		vPrintString("\n");
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclus�o da tarefa
	vTaskDelete(NULL);
}

int main_(void)
{
	// Cria a tarefa de controle dos batimentos card�acos
	xTaskCreate(vTaskHeartBeat, "Heartbeat", 1000, (void*) "Batimentos Cardiacos: ", 1, &taskHandlerHeartBeat);
	// Cria a tarefa de controle de Satura��o de Oxig�nio
	xTaskCreate(vTaskOxigenSat, "OxigenSat", 1000, (void*)"Saturacao de Oxigenio: ", 1, &taskHandlerOxigenSat);
	// Cria a tarefa de controle de Temperatura
	xTaskCreate(vTaskTemperature, "Temp", 1000, (void*)"Temperatura: ", 1, &taskHandlerTemperature);
	// Inicializa o agendador
	vTaskStartScheduler();
	for (;; );
	return 0;
}
