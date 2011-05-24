#include <stdio.h>
#include <stdlib.h>

//Definicao das funcoes
void le_matriz(char const arquivo[], float matriz[100][100], int *iMatriz, int *jMatriz);
void copia_matriz(float matrizBuffer[100][100], int iA, int jA, float matrizA[iA][jA]);
void multiplica_matrizes(int iA, int jA, float matrizA[iA][jA], int iB, int jB, float matrizB[iB][jB], float prod[iA][jB]);
void imprime_matriz(int iM, int jM, float matrizM[iM][jM]);

int main()
{
	//Constantes
    char const nome_arquivoA[] = "./4ex_matrizA.txt";
    char const nome_arquivoB[] = "./4ex_matrizB.txt";

    //Inicializa variaveis
    float matrizBuffer[100][100];
    int iA, jA, iB, jB;

    //Le a matriz A do arquivo para um buffer
    le_matriz(nome_arquivoA, matrizBuffer, &iA, &jA);

    //Agora que conhece o tamanho inicializa a matriz
    float matrizA[iA][jA];

    //E em seguida copia os valores
    copia_matriz(matrizBuffer, iA, jA, matrizA);

    //Repete o mesmo com B
    le_matriz(nome_arquivoB, matrizBuffer, &iB, &jB);
    float matrizB[iB][jB];
    copia_matriz(matrizBuffer, iB, jB, matrizB);

    //Verifica se a multiplicacao pode ser efetuada
    if(iB != jA)
    {
        printf("As matrizes nao podem ser multiplicads pois nao sao do formato A[m][n] e B[n][m]\n");
        exit(1);
    }

    //Define o produto
    float prod[iA][jB];

    //Efetua a multiplicacao
    multiplica_matrizes(iA, jA, matrizA, iB, jB, matrizB, prod);

    printf("Matriz prod[%d][%d]\n\n", iA, jB);
    imprime_matriz(iA, jB, prod);

   	exit(0);
}


//Le uma arquivo de texto e convete em uma matriz
//O limite do arquivo é uma matriz 100x100
void le_matriz(char const arquivo[], float matriz[100][100], int *iMatriz, int *jMatriz)
{
    char numero_atual[255] 	= "";
    char char_atual[2] 		= {' ', 0};

	FILE *fp;

	if( (fp = fopen(arquivo, "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo %s para leitura.", arquivo);
		exit(1);
	}

	int i = 0, j = 0;

	//Le o numero de linhas e de colunas do arquivo de texto
	while( !feof(fp) )
	{
		*char_atual = fgetc(fp);

		if( 0 == strcmp(" ", char_atual) || 0 == strcmp("\n", char_atual) || feof(fp))
     	{
            matriz[i][j] = atof(numero_atual);
            strcpy(numero_atual, "");

			if(0 == strcmp("\n", char_atual))
			{
            	i++;
             	j = 0;
			}
			else if(! feof(fp) )
			{
	            j++;
	        }

        }
        else
        {
            strcat(numero_atual, char_atual);
        }
	}

   	fclose(fp);

	//Retorna o tamanho da matriz lida
	*iMatriz = i+1;
	*jMatriz = j+1;
}

//
//Copia o conteudo da matriz buffer para uma matriz com o tamnaho definido
//Utilizo essa funcao para evitar definir as matrizes A e B sendo do tamanho [100][100]
//O que exige uma grande quantidade de memoria
void copia_matriz(float matrizBuffer[100][100], int iA, int jA, float matrizA[iA][jA])
{
    int i, j;

    for(i =0; i < iA; i++)
    {
        for(j = 0; j < jA; j++)
        {
            matrizA[i][j] = matrizBuffer[i][j];
        }
    }
}

//Multiplica as matrizes
void multiplica_matrizes(int iA, int jA, float matrizA[iA][jA], int iB, int jB, float matrizB[iB][jB], float prod[iA][jB])
{
    //jA = iB
    int i, j, k;

    //Para prod i vai de 0 a iA
    //e
    // j vai de 0 a jB
    for(i = 0; i < iA; i++)
    {
    	for(j = 0; j < jB; j++)
    	{
         	//Inicializa
    		prod[i][j] = 0.0;

    		//Soma a multiplicacao da linha i de A pela coluna j de B
			for(k = 0; k < jA; k++)
         	{
         		prod[i][j] += (matrizA[i][k] * matrizB[k][j]);
			}
    	}
    }
}


//Exibe o ]s dados da matriz na tela
void imprime_matriz(int iM, int jM, float matrizM[iM][jM])
{
    int i, j;
    for(i = 0; i < iM; i++)
    {
        for(j = 0; j < jM; j++)
        {
            printf("[%f] ", matrizM[i][j]);
        }
        printf("\n");
    }
}
