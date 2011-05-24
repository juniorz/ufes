/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 3
 ****************************/

#include <stdio.h>

//Funcao auxiliar
void solicitaLimiteInferior(float *superior, float inferior)
{
    printf("\nDigite o limite superior\n");
    scanf("%f", superior);
    
    if(*superior < inferior)
    {
        solicitaLimiteInferior(superior, inferior);
    }    
}    

main()
{
    //Declara variáveis
    float numeros[5], limite_inferior, limite_superior;
    int i = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 3\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Entrada do usuario
    printf("Digite 5 numeros (seguidos de enter)\n");
    for(i = 0; i < 5; i++)
    {
        scanf("%f", &numeros[i]);
    }

    //Entrada do usuario
    printf("\nDigite o limite inferior\n");
    scanf("%f", &limite_inferior);

    //Solicita o limite inferior mais de uma vez para evitar erros
    solicitaLimiteInferior(&limite_superior, limite_inferior);

    //Verifica os numeros e exibe a saida
    for(i = 0; i < 5; i++)
    {
        if(numeros[i] >= limite_inferior && numeros[i] <= limite_superior)
        {
                printf("%.2f        ", numeros[i]);
        }    
    }
}
