#include <iostream>
#include <string>

using namespace std;
// a função abaixo faz com que o valor inserido se ajuste a partir de um valor máximo e mínimo
int sensor(int medida, int min, int max) {
    medida = (medida - min) * 100; 
    int delt = max - min; 
    int result = (medida - min) * 100 / (max - min); 
    cout << result;
    
	return (medida - min) * 100 / (max - min);
}
// a função abaixo recebe um valor que será inserido em um vetor e qual posição que ele quer ser inserido.
int insertValue(int value, int* vector, int maxValue, int vectorIndex) {
    if (vectorIndex< maxValue) {         
		vector[vectorIndex] = value;  
		vectorIndex += 1;
		return vectorIndex;
}
// estabelece as variáveis que irão guardar os vetores (nome e direção)
char *direcoes[4] = {
	(char *) "Direita",
	(char *) "Esquerda",
	(char *) "Frente",
	(char *) "Tras"};
// a função abaixo calcula o maior caminho dentre as direções passadas
char* maxDirection(int* vector, int* distancia); {
	int index = 0;         
	int maxValue = vector[0]; 
	for (int i = 1; i<4; i++){
		if (vector[i] > maxValue) {  
				maxValue = vector[i];    
			index = i;         
		}
	}

	*distancia = maxValue;                              
	return direcoes [index]; 
}
// a função abaixo irá perguntar ao usuário se ele deseja continuar o mapeamento
int leComando() { 
    char answer; 
    cout << "Deseja continuar? (y/n) "; 
    cin >> answer; 
    if (answer == 'y') {
        return 1;
    } else {
        return 0; 
    }
}

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	int maping = 1;
	while(dirigindo){
		 printf("Mapeamento %d \n", maping);		
		int medida; 
		for (int i = 0; i<4; I ++){ //// o loop pega as 4 direções e suas respectivas informações e guarda no vetor passado pelos parâmetros chamando a função que insere os valores dos vetores
			printf("Escreva a distância do robô até o lado %s: ", direcoes[i]);
			cin>>medida;
			medida = sensor(medida,0,830);
			posAtualVetor = insertValue(medida, vetorMov, maxVetor,postAtualVetor);
			}
		dirigindo = leComando(); // confere se o usuário ainda quer continuar o mapeamento
		maping += 1; // vai atualizar o número do mapeamento		
	}
	return posAtualVetor;
}
// a função abaixo percorre o maior vetor (que contem todas os valores coletados) e mostra para o usuário quais direção e valor da maior distância do programa
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char *direcao = maxDirection(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}