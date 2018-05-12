/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>

int indice = 0, n = 0, n_primos = 0;	
unsigned long int vet[100];				//vetor que contem os numeros de entrada
pthread_mutex_t lock_obtem_valor;
pthread_mutex_t lock_primos;
#define thread_max 4				   //numero maximo de threads a ser gerado

int verifica_primo(unsigned long int primo);
void* funcao_thread(void *arg);
int64_t obtem_valor();

int main() {
	int i = 0;
  	char str[100], *s = str, *t = NULL;
  	pthread_t threads[3]; 
			
	fgets(s, 100, stdin);

	// Remove \n da string
	while(str[i] != '\n') i++;
		str[i] = '\0';

	// Tokeniza e insere em um vetor de unsigned long int.
	while ((t = strtok(s, " ")) != NULL) {
		s = NULL;		
		vet[n++] = atoi(t);
	}	

	for(i = 0;(i < thread_max);i++)
       pthread_create(&(threads[i]), NULL, funcao_thread, NULL);
    for (i = 0; i < thread_max; i++) 
		pthread_join(threads[i], NULL);
    
    printf("%d\n",n_primos);		

	return 0;
}
//funcao que verifica se o numero e primo ou nao
int verifica_primo(unsigned long int primo){
	unsigned long int i, div = 0; 
	for (i = 1; i <= primo; i++) {
    if (primo % i == 0)   
    	div++;
    if(primo % 2 == 0 && primo != 2)
    	return 0;
    if(div > 2)
    	return 0;
  }
    
  if (div == 2)
    return 1;
  else
    return 0;
  }
 //funcao invocada pela thread
 void* funcao_thread(void *arg) {
  int flag;
  int64_t numero;

  while(numero != -1){
  	pthread_mutex_lock(&lock_obtem_valor);
  	numero = obtem_valor();
 	pthread_mutex_unlock(&lock_obtem_valor);
  
  	flag = verifica_primo(numero);
        
    pthread_mutex_lock(&lock_primos);
    n_primos += flag;
    pthread_mutex_unlock(&lock_primos);   
  }
}

int64_t obtem_valor(){
    int64_t valor;
    if(indice < n){
        valor = vet[indice++];
        return valor;
    }else
   		 return (-1);
    
}