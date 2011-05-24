#include <stdio.h>

float calcula_maior(int n, float matriz[n]);
int main();

int main()
{
    //Inicializa variaveis
    char const nome_arquivo[] = "./3ex_resultado.txt";
    int n, i, j;
    char *padrao;
   	FILE *fp;
    
    printf("Por favor informe o n da Matriz: ");
    scanf("%d", &n);

    //Reserva memoria para as matrizes
    float matriz[n][n];
    float maiores[n];
    
    //Preenche a matriz
    for(i = 0; i < n; i++)
    {
    	printf("\nDigite os elementos da linha %d da Matriz\n", i+1);
    	
    	for(j = 0; j < n; j++)
    	{
        	printf("Elemento %d: ", j+1);
        	scanf("%f", &matriz[i][j]);
    	}
   	}
   	
   	//Abre o arquivo
   	if( (fp = fopen(nome_arquivo, "w")) == NULL)
    {
        printf("Erro ao abrir o arquivo %s para escrita\n", nome_arquivo);
        exit(1);
    }
   	
   	printf("\n");
   	
   	//Agora que a matriz esta preenchida, efetua os calculos
   	for(i = 0; i < n; i++)
   	{
        maiores[i] = calcula_maior(n, matriz[i]);

        for(j = 0; j < n; j++)
        {
        	matriz[i][j] = matriz[i][j] / maiores[i];
        	
        	printf("[%.2f] ", matriz[i][j]);
        	fprintf(fp, "[%.2f] ", matriz[i][j]);
        }

       	printf("\n");
       	fprintf(fp, "\n");
   	}
   	
   	fclose(fp);
   	
   	exit(0);
}

float calcula_maior(int n, float matriz[n])
{
    float *maior = matriz;
    int i;

    for(i = 0; i < n; i++)
    {
        if(*maior < fabs(matriz[i]))
        {
            maior = matriz+i;
        }
    }
    
    return *maior;
}
