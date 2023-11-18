/*
 * Autor: Tasi Guilhen Pasin
 * Curso: Engenharia de Computação
 */


#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Define a quantidade máxima do valor aleatório gerado de Batimentos Cardíacos
#define MAX_HEART_BEAT_RAND 140
// Define a quantidade mínima do valor aleatório gerado de Batimentos Cardíacos
#define MIN_HEART_BEAT_RAND 20
// Define o valor de Batimento Cardíaco que passa a ser Muito Baixo
#define LOW_HEART_BEAT 50
// Define o valor de Batimento Cardíaco que passa a ser Muito Alto
#define HIGH_HEART_BEAT 90

// Define a quantidade máxima do valor aleatório gerado de Saturação de Oxigênio
#define MAX_OXIGEN_SAT_RAND 100
// Define a quantidade mínima do valor aleatório gerado de Saturação de Oxigênio
#define MIN_OXIGEN_SAT_RAND 80
// Define o valor de Saturação de Oxigênio que passa a ser Muito Baixo
#define LOW_OXIGEN_SAT 90

// Define a quantidade máxima do valor aleatório gerado de Temperatura
#define MAX_TEMP_RAND 41
// Define a quantidade mínima do valor aleatório gerado de Temperatura
#define MIN_TEMP_RAND 34
// Define o valor de Temperatura que passa a ser Muito Baixo
#define LOW_TEMP 35
// Define o valor de Temperatura que passa a ser Muito Alto
#define HIGH_TEMP 37.5

// Contabilização de milissegundos e um segundo
#define SECOND_MILISSECONDS 1000

// Handler da tarefa de Controle de Batimentos Cardíacos
xTaskHandle taskHandlerHeartBeat;
// Handler da tarefa de Controle de Saturação de Oxigênio
xTaskHandle taskHandlerOxigenSat;
// Handler da tarefa de Controle de Temperatura
xTaskHandle taskHandlerTemperature;

/*
 * Implementação da Tarefa de Controle de Batimentos Cardíacos
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskHeartBeat(void *pvParameters);

/*
 * Implementação da Tarefa de Controle de Saturação de Oxigênio
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskOxigenSat(void *pvParameters);

/*
 * Implementação da Tarefa de Controle de Temperatura
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskTemperature(void *pvParameters);

/*
 * Implementação da Tarefa de Controle de Batimentos Cardíacos
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskHeartBeat(void *pvParameters)
{
	// Recebe o parâmetro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleatório do batimento cardiaco limitado por um valor mínimo e um máximo
		int heartBeatValue = (rand() % (MAX_HEART_BEAT_RAND - MIN_HEART_BEAT_RAND + 1) + MIN_HEART_BEAT_RAND);
		// Imprime a informação do batimento cardiaco gerado aleatóriamente
		// com a string recebida por parametro
		vPrintStringAndNumber(msg, heartBeatValue);
		// Verifica se o valor de batimento cardiaco gerado é menor que o valor mínimo
		if (LOW_HEART_BEAT > heartBeatValue) {
			// Imprime informação de batimento cardiaco baixo
			vPrintString("Batimentos Cardiacos muito baixos\n");
		}
		// Verifica se o valor de batimento cardiaco gerado é maior que o valor máximo
		else if (HIGH_HEART_BEAT < heartBeatValue) {
			// Imprime informação de batimento cardiaco alto
			vPrintString("Batimentos Cardiacos muito altos\n");
		}
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclusão da tarefa
	vTaskDelete(NULL);
}

/*
 * Implementação da Tarefa de Controle de Saturação de Oxigênio
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskOxigenSat(void *pvParameters)
{
	// Recebe o parâmetro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleatório da saturação de oxigenio limitado por um valor mínimo e um máximo
		int oxigenSatValue = (rand() % (MAX_OXIGEN_SAT_RAND - MIN_OXIGEN_SAT_RAND + 1) + MIN_OXIGEN_SAT_RAND);
		// Imprime a informação da saturação de oxigenio gerado aleatóriamente
		// com a string recebida por parametro
		printf("%s%d%s\n", msg, oxigenSatValue, "%");
		// Verifica se o valor de saturação de oxigenio gerado é menor que o valor mínimo
		if (LOW_OXIGEN_SAT > oxigenSatValue) {
			// Imprime informação de saturação de oxigenio baixo
			vPrintString("Saturacao de Oxigenio baixa no sangue\n");
		}
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclusão da tarefa
	vTaskDelete(NULL);
}

/*
 * Implementação da Tarefa de Controle de Temperatura
 * @param pvParameters Parâmetros enviados na inicialização da Tarefa
 */
void vTaskTemperature(void *pvParameters)
{
	// Recebe o parâmetro esperando que seja uma string, ou cadeia de chars
	char* msg = (char*)pvParameters;
	for (;; )
	{
		// Gera o valor aleatório da temperatura limitado por um valor mínimo e um máximo
		float tempValue = (rand() % (MAX_TEMP_RAND - MIN_TEMP_RAND + 1) + MIN_TEMP_RAND);
		// Imprime a informação da temperatura gerado aleatóriamente
		// com a string recebida por parametro
		printf("%s%.0f%c\n", msg, tempValue, (char)248);
		// Verifica se o valor de temperatura gerado é menor que o valor mínimo
		if (LOW_TEMP > tempValue) {
			// Imprime informação de temperatura baixa
			vPrintString("Hipotermia\n");
		}
		// Verifica se o valor de temperatura gerado é maior que o valor máximo
		else if (HIGH_TEMP < tempValue) {
			// Imprime informação de temperatura alta
			vPrintString("Febre\n");
		}
		// Imprime linha em branco
		vPrintString("\n");
		// Determina delay para que a task execute novamente
		vTaskDelay(pdMS_TO_TICKS(SECOND_MILISSECONDS));
	}
	// Explicita a exclusão da tarefa
	vTaskDelete(NULL);
}

int main_(void)
{
	// Cria a tarefa de controle dos batimentos cardíacos
	xTaskCreate(vTaskHeartBeat, "Heartbeat", 1000, (void*) "Batimentos Cardiacos: ", 1, &taskHandlerHeartBeat);
	// Cria a tarefa de controle de Saturação de Oxigênio
	xTaskCreate(vTaskOxigenSat, "OxigenSat", 1000, (void*)"Saturacao de Oxigenio: ", 1, &taskHandlerOxigenSat);
	// Cria a tarefa de controle de Temperatura
	xTaskCreate(vTaskTemperature, "Temp", 1000, (void*)"Temperatura: ", 1, &taskHandlerTemperature);
	// Inicializa o agendador
	vTaskStartScheduler();
	for (;; );
	return 0;
}
