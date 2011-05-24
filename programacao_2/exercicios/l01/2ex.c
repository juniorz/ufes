/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 2
 ****************************/

#include <stdio.h>

main()
{
    //Decalra variáveis
    int valor1, valor2 = 0;
    float maior;
    
    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 2\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    printf("Informe 2 numeros inteiros ");
    scanf("%d %d", &valor1, &valor2);

    //Obtem o maior dos 2
    maior = (valor1 < valor2) ? valor2 : valor1;
    
    //Retorno ao usuario
    printf("A raiz quadrada do maior dos 2 valores e: %.5f", sqrt(maior));
}    
