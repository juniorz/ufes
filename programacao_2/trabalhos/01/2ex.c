#include <stdio.h>
#include <stdlib.h>

#define NUM_REGISTROS			20
#define ARQUIVO_ENTRADA			"./entrada.dat"
#define ARQUIVO_RESULTADO		"./result.dat"
#define ARQUIVO_TOP_RESULTADO	"./top_result.dat"
#define ARQUIVO_REPROVADOS		"./reprovados.dat"
#define ARQUIVO_ESTATISTICAS	"./estatistica.dat"

//Estrutura de dados
struct estudante {
    int matricula;
    float provas[4];
    float prova_final;
};

//Assinatura das funções
int 	le_dados( struct estudante alunos[] );
float	*menor_prova(float *provas);
void 	troca_prova(float *a, float *b);
float 	calcula_notafinal(struct estudante *aluno);
char 	obtem_conceito(float nota_final);
float	percentual(int parte, int todo);

int main()
{
    //Uma array de ponteiros do tipo estrutura de dados
    struct estudante alunos[NUM_REGISTROS];	//Estruturas de dados facilitam a manipulação
   											//dos diferentes dados de um registro (linha do arquivo).

    int num_alunos[6] = {0, 0, 0, 0, 0, 0};	//Armazenará o numero de alunos com cada conceito
    int *p_num_alunos;						//Ponteiro referenciando para a variavel acima
    int num_registros;						//Numero de registros lidos

    FILE *fp_resultado, *fp_top_resultado, *fp_reprovados, *fp_estatisticas;	//Ponteiros para os arquivos de resultados

    //Funcao de leitura de Dados
    num_registros = le_dados( alunos );

    //Abre os arquivos
    fp_resultado 		= fopen(ARQUIVO_RESULTADO, "w+");
    fp_top_resultado 	= fopen(ARQUIVO_TOP_RESULTADO, "w+");
    fp_reprovados 		= fopen(ARQUIVO_REPROVADOS, "w+");

    //Varre o array de alunos
    int i;
    for(i = 0; i < num_registros; i++)
    {
        //Aponta o ponteiro para o primeiro elemento do array
        p_num_alunos = num_alunos;

        //Obtem o conceito do aluno
        float nota_final = calcula_notafinal(&alunos[i]);
        char conceito = obtem_conceito(nota_final);

        //Ajusta o ponteiro para o contador adequado
        //A ideia é incrementar o ponteiro até que ele aponte para o elemento correto no array
    	switch(conceito)
    	{
    		case 'F':
          		p_num_alunos++;
          	case 'E':
            	//Escreve cada linha de REPROVADOS
               	fprintf(fp_reprovados, "%d	%.2f\n", alunos[i].matricula, nota_final);

          		p_num_alunos++;
          	case 'D':
          		p_num_alunos++;
           	case 'C':
          		p_num_alunos++;
          	case 'B':
          		p_num_alunos++;
          		break;
          	case 'A':
          		//Escreve cada linha de TOP resultado
               	fprintf(fp_top_resultado, "%d	%.2f\n", alunos[i].matricula, nota_final);
          	default:
          		break;
   		}
   		
   		//Incrementa o contador correto
   		//Uma vez que o ponteiro esta apontando para o elemento do array correspondente ao seu conceito
   		(*p_num_alunos)++;

   		//Imprime cada linha do arquivo RESULT
   		fprintf(fp_resultado, "%d	%.2f	%.2f	%.2f	%.2f	%.2f	%c\n", alunos[i].matricula, alunos[i].provas[0],  alunos[i].provas[1],  alunos[i].provas[2], alunos[i].prova_final, nota_final, conceito);
    }

	//Escreve ultima linha de TOP resultado
   	fprintf(fp_top_resultado, "%d	%.2f ", num_alunos[0], percentual(num_alunos[0], NUM_REGISTROS));

    //Fecha os arquivos
    fclose(fp_resultado);
    fclose(fp_top_resultado);
    fclose(fp_reprovados);

    //Abre o arquivo de estatisticas
    fp_estatisticas	= fopen(ARQUIVO_ESTATISTICAS, "w+");

    //Escreve as estaticticas
    fprintf(fp_estatisticas, "conceito A: %4.2f%%\n", percentual(num_alunos[0], NUM_REGISTROS));
    fprintf(fp_estatisticas, "conceito B: %4.2f%%\n", percentual(num_alunos[1], NUM_REGISTROS));
    fprintf(fp_estatisticas, "conceito C: %4.2f%%\n", percentual(num_alunos[2], NUM_REGISTROS));
    fprintf(fp_estatisticas, "conceito D: %4.2f%%\n", percentual(num_alunos[3], NUM_REGISTROS));
    fprintf(fp_estatisticas, "conceito E: %4.2f%%\n", percentual(num_alunos[4], NUM_REGISTROS));
    fprintf(fp_estatisticas, "conceito F: %4.2f%%\n", percentual(num_alunos[5], NUM_REGISTROS));
    fclose(fp_estatisticas);

    //Exie os dados calculados
    printf("\nAlunos com conceito A: %2d\n", num_alunos[0]);
    printf("Alunos com conceito E e F: %2d\n", num_alunos[4] + num_alunos[5]);

    //Finaliza o programa
	exit(0);
}

//Calcula o percentual
float percentual(int parte, int todo)
{
    return (float) parte / (float) todo * 100.0;
}


//Funcao de leitura de dados
//Retorna o numero de registros lidos (caso leia menos de 20)
int le_dados( struct estudante alunos[] )
{
    //Inicializa variaveis
    FILE *fp;		//Ponteiro do arquivo
    char temp[255]; //String temporaria

    if ((fp = fopen(ARQUIVO_ENTRADA, "r")) == NULL)		//Abre o arquivo para leitura
    {
        //previne erros
        printf("Erro ao abrir o arquivo de dados.\n");
        exit(1);
    }

    int i = 0;
	while(!feof(fp) && i < NUM_REGISTROS )	//Le todo o arquivo ou le NUM_REGISTROS registros
	{
     	fgets(temp, sizeof(temp), fp);	//Armazena a linha
		sscanf(temp, "%d %f %f %f %f %f", &alunos[i].matricula, &alunos[i].provas[0], &alunos[i].provas[1], &alunos[i].provas[2], &alunos[i].provas[3], &alunos[i].prova_final);
		i++;
	}
	
    fclose(fp);								//Fecha o arquivo

    return i;
}

//Funcao que calcula a nota final
float calcula_notafinal(struct estudante *aluno)
{
	float soma = 0, *p_menor_prova;

	//Ponteiro que referencia a menor nota
	p_menor_prova = menor_prova(&aluno->provas[0]);

	//Poe a pior prova no ultimo lugar
	troca_prova(aluno->provas + 3, p_menor_prova);

	//Soma as 3 primeiras que sao as maiores
	int i;
	for(i=0; i < 3; i++)
	{
		soma += aluno->provas[i];
	}

	//Adiciona a prova final
	soma += aluno->prova_final;

	return soma;
}

float *menor_prova(float *provas)
{
    float *menor;
    int i;

   	menor = provas;

    for(i=1; i < 4; i++)
    {
        if(*menor > *(provas+i))
        {
            menor = provas + i;
        }
    }

    return menor;
}

//Troca duas provas de lugar no array
void troca_prova(float *a, float *b)
{
    float *temp;

    *temp = *a;
    *a = *b;
    *b = *temp;
}

//Obtem o conceito
char obtem_conceito(float nota_final)
{
    if(nota_final >= 0.0 && nota_final <= 39.0)
    {
        return 'F';
    }
    else if(nota_final <= 59.0)
    {
        return 'E';
    }
    else if(nota_final <= 69.0)
    {
        return 'D';
    }
    else if(nota_final <= 79.0)
    {
        return 'C';
    }
    else if(nota_final <= 89.0)
    {
        return 'B';
    }
    else if(nota_final <= 100.0)
    {
        return 'A';
    }
}
