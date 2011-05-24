/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 4
 ****************************/

#include <stdio.h>
#include "./funcao_ordena.c"
  

main()
{
    //Decalra variáveis
    int maior, medio, menor, temporario = 0;

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 4\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe 3 numeros distintos ");
    scanf("%d %d %d", &menor, &medio, &maior);

    //Utiliza uam funcao externa
    ordenaTresNumeros(&menor, &medio, &maior);

    //Retorna a saida
    printf("Os numeros em ordem sao: %d, %d, %d", menor, medio, maior);
}
