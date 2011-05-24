/***************************************
 *	Segundo trabalho de Programacao II
 ***************************************
 * Alunos: Reinaldo de Souza Junior
 *         Rafael Garcia Birro
 ***************************************/
	
#include <stdio.h>
#include <stdlib.h>


//Tipos de dados
typedef struct caminho {
    char rota[255];
	float distancia;
	float gasto;
} caminho;

typedef struct estrada {
    int origem;
    int destino;
	float distancia;
	float pedagio;
} estrada;


//Prototipo das funcoes
int le_dados(char const arquivo[], estrada buffer[100]);
int compara_estradas(estrada const *arg1, estrada const *arg2);
int compara_caminhos_barato(caminho const *arg1, caminho const *arg2);
int compara_caminhos_curto(caminho const *arg1, caminho const *arg2);
void processa_matriz(estrada buffer[100], int num_trechos, int num_cidades, float malha[num_cidades][num_cidades]);
void achar_caminhos(int origem, int destino, int num_cidades, float malha[num_cidades][num_cidades], int *num_caminhos, caminho *caminhos, char const sufixo[], float const distancia, float const gasto);
void armazena_dados(char const arquivo[], int num_caminhos, caminho caminhos[num_caminhos], int destino);



int main()
{
	//
    //Define constantes
    //
    char const arquivo_saida[]	= "./caminhos_possiveis.txt";
    char const arquivo_dados[]	= "./dados_malha.txt";

	//
	//Variaveis
	//
    FILE *fp;				//Ponteiro para o arquivo de gravacao
    int num_estradas = 0;	//Numero de estradas lidas do arquivo
    int num_cidades = 0; 	//Numero de cidades
    int origem, destino;	//Origem e destino
	estrada buffer[100];	//Buffer temporario que armazenara as estardas

	//Le o numero de linhas
    num_estradas = le_dados(arquivo_dados, buffer);

	//Coloca as estradas em ordem crescente para obter o numero maximo de cidades
	qsort(buffer, num_estradas, sizeof(estrada), compara_estradas);

	//O numero de cidades é o numero da ultima-destino da ultima estrada
	num_cidades = buffer[num_estradas-1].destino;

    //Define a malha com seu tamanho real
    float dados_malha[num_cidades][num_cidades];

    //Processa os dados dos trechos para uma matriz no formato pedido pelo problema
    processa_matriz(buffer, num_estradas, num_cidades, dados_malha);

	//
	//Obtem dados do usuario
	//
    printf("Informe duas cidades: ");
    scanf("%d %d", &origem, &destino);

	//Certifica-se que está realmente indo de i para j com i < j
	if(origem > destino)
	{
		printf("As estradas sao de mao unica e portanto voce deve ir de uma cidade i para uma cidade j com i < j");
		exit(1);
	}

	//Cidade nao existente na malha
	if(destino > num_cidades)
	{
		printf("A cidade de destino nao consta na malha");
		exit(1);
	}


	//Matriz de caminhos para saida de dados
	int num_caminhos = 0;
	caminho caminhos[100];

	//
	//Encontra todos os caminhos e escreve no arquivo
	//
    achar_caminhos(origem, destino, num_cidades, dados_malha, &num_caminhos, caminhos, "", 0.0, 0.0);

	printf("\n");

	//
	//Armazena os dados
	//
	if(num_caminhos > 0)
	{
    	//Ordena os caminhos por ordem de gastos
    	qsort(caminhos, num_caminhos, sizeof(caminho), compara_caminhos_barato);

		//Armazena os dados
		armazena_dados(arquivo_saida, num_caminhos, caminhos, destino);

		//Exibe o caminho mais curto
		printf("Caminho mais barato: R$ %.2f - [%s%d]\n", caminhos[0].gasto, caminhos[0].rota, destino);

    	//Ordena os caminhos por ordem de distancia
    	qsort(caminhos, num_caminhos, sizeof(caminho), compara_caminhos_curto);

		printf("Caminho mais curto: %.2f KM - [%s%d]\n", caminhos[0].distancia, caminhos[0].rota, destino);

	}
	else
	{
     	printf("Nao existem caminhos entre %d e %d\n", origem, destino);
     	exit(1);
	}

	exit(0);
}






/************************************************
 * Le os dados do arquivo de entrada e armazena
 * os dados numa matriz temporaria.
 * Em seguida os dados serao processados por outro procedimento.
 *
 * A matriz temporaria utiliza outra estrutura de dados
 * Para facilitar a manipulacao dos dados.
 *
 * Essa funcao e chamada pela funcao qsort()
 ************************************************/
int le_dados(char const arquivo[], estrada buffer[100])
{
    FILE *fp;
    int i = 0;

    if((fp = fopen(arquivo, "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }

    while( !feof(fp) && i < 100 )
    {
    	fscanf(fp, "%d %d %f %f\n", &buffer[i].origem, &buffer[i].destino, &buffer[i].distancia, &buffer[i].pedagio);
    	i++;
    }

    fclose(fp);

    return i;
}


/************************************************
 * Funcao auxiliar para ordenar
 * as estradas crescente de origem-destino.
 * Isso ajudara a saber qual o numero de cidades
 *
 * Essa funcao e chamada pela funcao qsort()
 ************************************************/
int compara_estradas(estrada const *arg1, estrada const *arg2)
{
	if( arg1->origem > arg2->origem )
	{
     	return 1;
	}

	if( arg1->origem < arg2->origem )
	{
     	return -1;
	}

	//Nesse ponto arg1 e arg2 tem a mesma origem
	if( arg1->destino > arg2->destino)
	{
     	return 1;
	}
	else
	{
     	return -1;
	}

	return 0;
}


/************************************************
 * Funcao auxiliar para ordenar
 * os caminhos por ordem crescente de gastos
 *
 * Essa funcao e chamada pela funcao qsort()
 ************************************************/
int compara_caminhos_barato(caminho const *arg1, caminho const *arg2)
{
    if(arg1->gasto < arg2->gasto)
    {
        return -1;
	}

	if(arg1->gasto > arg2->gasto)
	{
     	return 1;
	}

	return 0;
}


/************************************************
 * Funcao auxiliar para ordenar
 * os caminhos por ordem crescente de distancia
 *
 * Essa funcao e chamada pela funcao qsort()
 ************************************************/
int compara_caminhos_curto(caminho const *arg1, caminho const *arg2)
{
    if(arg1->distancia < arg2->distancia)
    {
        return -1;
	}

	if(arg1->distancia > arg2->distancia)
	{
     	return 1;
	}

	return 0;
}


/* ************************************************
 * Copia o conteudo da matriz temporaria
 * para a matriz de dados da malha, no
 * formato exigido pelo problema
 **************************************************/
void processa_matriz(estrada buffer[100], int num_trechos, int num_cidades, float malha[num_cidades][num_cidades])
{
    int i, j;
    int origem, destino;

    //Inicializa a matriz de dados da malha
    for(i = 0; i < num_cidades; i++)
    {
       	malha[i][i] = 0;

        for(j = i+1; j < num_cidades; j++)
        {
        	malha[i][j] = 0;
         	malha[j][i] = 0;
        }
    }

    //Copia valores
    for(i = 0; i < num_trechos; i++)
    {
		origem = buffer[i].origem - 1;
		destino = buffer[i].destino - 1;

    	malha[origem][destino] = buffer[i].distancia;
    	malha[destino][origem] = buffer[i].pedagio;
    }
}


/****************************************
 * Procedimento para encontrar todos os
 * caminhos entre <origem> e <destino>
 ****************************************/
void achar_caminhos(int origem, int destino, int num_cidades, float malha[num_cidades][num_cidades], int *num_caminhos, caminho *caminhos, char const sufixo[], float const distancia, float const gasto)
{
	//Constantes
    float const preco_combustivel	= 5.00;	//R$ 5,00 a cada litro
    float const consumo_combustivel	= 0.05;	//0,05 litros/km

	//Variaveis
	int escala;
	char sufixo_atual[255] 	= "";	//Armazena o caminho atual
	caminho *caminho_atual;			//Aponta para o elemento atual da matriz de caminhos
	float distancia_atual 	= 0;	//Utilizada para calcular a soma do saldo
	float gasto_atual 		= 0;	//Utilizada para calcular a soma dos gastos

   /************************************************
	* O algoritmo consiste no seguinte raciocinio:
	*
	* O caminho i->j é igual a i->(j-1)->j, desde que
	* ambas as estradas i->(j-1) e (j-1)->j existam.
	* Essa regra tambem vale para i->(j-1) e (j-1)->j
	* e por isso a funcao e chamada recursivamente.
	*
	* O algoritmo utiliza esse raciocinio para montar
	* todos os camnhos possiveis entre i->j
	************************************************/
    for(escala = (destino - origem); escala > 0; escala--)
    {
		//Existe a estrada (j-1)->j ?
		if(malha[escala-1][destino-1] > 0.0)
		{
          	//Adiciona a origem atual a caminho
      		sprintf(sufixo_atual, "%d-", escala);

			//sufixo_atual += sufixo
			strcat(sufixo_atual, sufixo);

			//Calcula o gasto atual
			distancia_atual = distancia + malha[escala-1][destino-1];
			gasto_atual 	= gasto +  malha[destino-1][escala-1];

          	if(escala == origem)
           	{
				//Calcula o gasto
				gasto_atual	+= distancia_atual * consumo_combustivel * preco_combustivel;

				//Adiciona o camiho a matriz de caminhos
				caminho_atual = caminhos + (*num_caminhos);

				strcpy(caminho_atual->rota, sufixo_atual);
				caminho_atual->distancia 	= distancia_atual;
				caminho_atual->gasto 		= gasto_atual;

				//Incrementa o numero de caminhos
				(*num_caminhos)++;
           	}
			else if(origem < escala)
			{
       			//Acha os caminhos entre i e j-1
       			achar_caminhos(origem, escala, num_cidades, malha, num_caminhos, caminhos, sufixo_atual, distancia_atual, gasto_atual);
			}

		}
	}
}


/****************************************
 * Armazena os dados no arquivo de saida
 *
 * A matriz de caminhos ja esta
 * previamente ordenada
 ****************************************/
void armazena_dados(char const arquivo[], int num_caminhos, caminho caminhos[num_caminhos], int destino)
{
    int i;
    FILE *fp;

	//Escreve a saida
    if((fp = fopen(arquivo, "w")) == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }


    for(i=0; i < num_caminhos; i++)
    {
        //Exibe o caminho no formato 1-2-3 <distancia> <gasto>
    	fprintf(fp, "%s%d %.2f %.2f\n", caminhos[i].rota, destino, caminhos[i].distancia, caminhos[i].gasto);
    }
    fclose(fp);
}
