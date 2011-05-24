/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 6
 ****************************/
#include <stdio.h>

main()
{
    //Declara variáveis
    double soma = 0.0;
    int numerador = 1, sinal = 1;
    int i = 0, denominador = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 6\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Entrada dos dados
    for(i = 15; i >= 1; i--)
    {
        //Constroi o termo
        denominador = i * i;
        printf("%d	%d	%d	%d\n", numerador, denominador, i, sinal);
        soma += (double) sinal * numerador / denominador;

        sinal *= -1;
        numerador *= 2;
    }

    printf("O valor da somatoria e: %f", soma);
}
