#include <stdio.h>
#include <stdlib.h>

void le_matriz(char const arquivo[], float matriz[100][100], int *iMatriz, int *jMatriz);
void copia_matriz(float matrizBuffer[100][100], int iA, int jA, float matrizA[iA][jA]);
void verifica_simetria(int iA, int jA, float matrizA[iA][jA]);

int main()
{
	//Constantes
    char const nome_arquivo[] = "./6ex_matriz.txt";

    //Inicializa variaveis
    float matrizBuffer[100][100];
    int iA, jA;

    //Le a matriz A do arquivo para um buffer
    le_matriz(nome_arquivo, matrizBuffer, &iA, &jA);

    if(iA != jA)
    {
        printf("A matriz fornecida nao e quadrada, como propoe o problema");
        exit(1);
    }

    //Agora que conhece o tamanho inicializa a matriz
    float matrizA[iA][jA];

    //E em seguida copia os valores
    copia_matriz(matrizBuffer, iA, jA, matrizA);
    
    //Verifica se a matriz é simetrica
    verifica_simetria(iA, jA, matrizA);
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

//
//Verifica a simetria da matriz
//
void verifica_simetria(int iA, int jA, float matrizA[iA][jA])
{
    int i, j;

    for(i = 0; i < iA; i++)
    {
        //j = i+1 - percorre apenas os elementos acima da diagonal principal
        //comparando-os com os elementos abaixo da diagonal principal

        //Evita que a mesma comparacao seja feita 2 vezes
        //E evita tambem que os elementos pertencentes a diagonal principal sejam comparados com eles mesmos
        for(j = i+1; j < jA; j++)
        {
            if(matrizA[i][j] != matrizA[j][i])
            {
                printf("nao simetrica\n");
                exit(1);
           	}
        }
    }

    //matriz simetrica
    printf("simetrica\n");
    exit(0);
}
