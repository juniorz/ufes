#include <stdio.h>

void le_matriz(int iA, int jA, float matriz[iA][jA]);
float calcula_media_aluno(int num_notas, float aluno[num_notas+1]);
void ordena_medias(int num_alunos, float medias[num_alunos][2]);
void troca_posicao(float *num1, float *num2);
float calcula_maior_media(int num_alunos, float medias[num_alunos][2]);
int calcula_alunos_media_superior(int num_alunos, float medias[num_alunos][2], float media);
void imprime_alunos_media(int num_alunos, float medias[num_alunos][2], float maior_media);

int main()
{
    //Constantes
    int const num_alunos = 	51;
    int const num_notas = 	9;

    //Matriz de matriculas
    float mat[num_alunos][num_notas+1];
    float medias[num_alunos][2];

    //Maaior media
    float maior_media;

    //Leitura dos dados
    le_matriz(num_alunos, num_notas+1, mat);

    //
    //Calcula as medias de cada aluno
    // E imprime-a
    int i, j;
    for(i = 0; i < num_alunos; i++)
    {
        //Array com as medias
        medias[i][0] = mat[i][0];
    	medias[i][1] = calcula_media_aluno(num_notas, mat[i]);
        printf("%.2f\n", medias[i][1]);
    }

    //Organiza as medias em ordem crescente para obter uma melhor performance nas proximas funcoes
    ordena_medias(num_alunos, medias);

    //Calcula a maior media
    maior_media = calcula_maior_media(num_alunos, medias);

    //Imprime os alunos que possuem a maior media
    imprime_alunos_media(num_alunos, medias, maior_media);
    
    //Calcula o numero de alunos com media superior a 7
    int num_alunos_media_superior;
    num_alunos_media_superior = calcula_alunos_media_superior(num_alunos, medias, 7.0);

    exit(0);
}

//Le uma arquivo de texto e convete em uma matriz
void le_matriz(int iA, int jA, float matriz[iA][jA])
{
    //constantes
    char const arquivo[] 	= "./8ex_alunos.txt";

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
     	fscanf(fp, "%f %f %f %f %f %f %f %f %f %f", &matriz[i][0], &matriz[i][1], &matriz[i][2], &matriz[i][3], &matriz[i][4], &matriz[i][5], &matriz[i][6], &matriz[i][7], &matriz[i][8], &matriz[i][9]);
     	i++;
	}

	fclose(fp);
	
	return;
}

//Calcula a media de um aluno
float calcula_media_aluno(int num_notas, float aluno[num_notas+1])
{
    int i;
    float media = 0.0;

    for(i = 1; i <= num_notas; i++)
    {
        media += aluno[i];
    }

    return media / num_notas;
}


//Calcula a maior media da turma
//Como a matriz esta ordenada, apenas pega o ultimo elemento
float calcula_maior_media(int num_alunos, float medias[num_alunos][2])
{
	return medias[num_alunos-1][1];
}

//Imprime os alunos que possuem a media informada
//Como a matriz esta em ordem crescente, retira os alunos do final
void imprime_alunos_media(int num_alunos, float medias[num_alunos][2], float maior_media)
{
    int i = num_alunos - 1;

    printf("\nAlunos que tiraram a maior media:\n");

    do
    {
        printf("Aluno %d: %.2f\n", (int) medias[i][0], medias[i][1]);
        i--;
    }
    while(!(maior_media > medias[i][1]));
}

//Calcula o numero de alunos que possuem media superios a `media`
int calcula_alunos_media_superior(int num_alunos, float medias[num_alunos][2], float media)
{
    int i = num_alunos-1;
    int retorno = 0;

    do
    {
        i--;
        retorno++;
    }
    while(media < medias[i][1]);
    
    return retorno;
}

//Ordenação crescente
void ordena_medias(int num_alunos, float medias[num_alunos][2])
{
    int i, j;
    for(i = num_alunos; i > 0; i--)
    {
    	for(j = 0; j+1 < i; j++)
    	{
    		if(medias[j][1] > medias[j+1][1])
    		{
   				troca_posicao(&medias[j][0], &medias[j+1][0]);
				troca_posicao(&medias[j][1], &medias[j+1][1]);
   			}
    	}
    }
}

//Troca dois ponteiros de posicao
void troca_posicao(float *num1, float *num2)
{
	float aux;

	aux = *num1;
	*num1 = *num2;
	*num2 = aux;
}
