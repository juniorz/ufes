/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 1
 ****************************/

#include <stdio.h>
#define PRECISAO 0.0001
 
main()
{
    //Declara variáveis
    float soma = 0, termo = 4;
    int sinal = 1, denominador = 1;
    int i = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 1\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Enquanto o termo for maior que a precisao
    do
    {
        soma += termo;

        denominador += 2;
        sinal *= -1;
        i++;

        termo = (float) sinal * 4 / denominador;
    }
    while((fabs(termo)) >= PRECISAO);

    printf("O valor da soma e %f\n", soma);
    printf("A soma foi obtida com %d termos", i);
}
