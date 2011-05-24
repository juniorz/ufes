/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 7
 ****************************/

#include <stdio.h>
#include "./funcao_ordena.c"
  
main()
{
    //Decalra variáveis
    int maior, medio, menor, temporario = 0;

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 7\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe 3 numeros distintos ");
    scanf("%d %d %d", &menor, &medio, &maior);

    //Utiliza uam funcao externa
    ordenaTresNumeros(&menor, &medio, &maior);

    //Retorna a saida
    //Usa um typecasting para ter certeza que a saida sera um float
    printf("A media dos valores extremos e %.5f", (float) (menor + maior) / 2);
}
