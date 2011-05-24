#include <stdio.h>

void le_matriz(int iA, int jA, int matriz[iA][jA]);
void imprime_municipio_populoso(int iA, int jA, int matrizA[iA][jA]);
float calcula_media_capitais(int matrizPopulacao[26][10]);

int main()
{
    //Define constantes
    int const num_estados 		= 26;
    int const num_municipios	= 10;

    float populacao_media_capitais;

    //Inicializa variaveis
    int matrizPopulacao[num_estados][num_municipios];

    //Le os dados
    le_matriz(num_estados, num_municipios, matrizPopulacao);
    
    //Imprime o municiio mais populoso
    imprime_municipio_populoso(num_estados, num_municipios, matrizPopulacao);

    //Calcula a media da população das capitais
    populacao_media_capitais = calcula_media_capitais(matrizPopulacao);

    exit(0);
}


//Le uma arquivo de texto e convete em uma matriz
void le_matriz(int iA, int jA, int matriz[iA][jA])
{
    //constantes
    char const arquivo[] 	= "./7ex_populacao.txt";

	FILE *fp;
	int i = 0;

	if( (fp = fopen(arquivo, "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo %s para leitura.", arquivo);
		exit(1);
	}

	//Le o cada linha
	while( !feof(fp) )
	{
     	fscanf(fp, "%d %d %d %d %d %d %d %d %d %d", &matriz[i][0], &matriz[i][1], &matriz[i][2], &matriz[i][3], &matriz[i][4], &matriz[i][5], &matriz[i][6], &matriz[i][7], &matriz[i][8], &matriz[i][9]);
     	i++;
	}
	
	fclose(fp);
}

//
//Encontra o municipio mais populoso
//
void imprime_municipio_populoso(int iA, int jA, int matrizA[iA][jA])
{
    //Inicializa variaveis
	int i, j;

	//
	//Obtem primeiro o municipio mais populoso de cada estado
	//

	//Array que armazenara o municipio mais populosos de cada estado
	int municipios_populosos[iA];

	for(i = 0; i < iA; i++)
	{
     	//Inicializa o ponteiro apontando para o primeiro municipio do estado
     	municipios_populosos[i] = 0;

		for(j = 1; j < jA; j++)
     	{
          	//Municipio mais populoso
          	if(*(matrizA[i] + municipios_populosos[i]) < matrizA[i][j])
          	{
          		municipios_populosos[i] = j;
    		}
        }
    }

    //
    //Encontra o estado que possui o municipios mais pupuloso
    //

	//Municipio mais populoso
	int municipio_mais_populoso = municipios_populosos[0];
	int estado_municipio = 0;

    for(i = 1; i < iA; i++)
    {
        //Municipio mais populoso
    	if(matrizA[estado_municipio][municipio_mais_populoso] < *(matrizA[i] + municipios_populosos[i]))
    	{
    		municipio_mais_populoso = municipios_populosos[i];
    		estado_municipio = i;
    	}
    }

    //
    //Imprime os dados
    //
    printf("Municipio mais populoso: %d, pertence ao estado %d\n", municipio_mais_populoso, estado_municipio);
}


//
//Calcula a media
//
float calcula_media_capitais(int matrizA[26][10])
{
    int i;
    float media = 0.0;
    
    for(i = 0; i < 26; i++)
    {
        media += (float) matrizA[i][0];
    }
    
    return media / 10.0;
}
