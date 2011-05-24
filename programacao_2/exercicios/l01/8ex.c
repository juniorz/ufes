/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 8
 ****************************/

#include <stdio.h>
  
main()
{
    //Declara variáveis
    int cpf, preco, secao = 0;
    float preco_secao[11] = {0, 20, 20, 20, 31.0, 31.0, 45.50, 45.50, 45.50, 50.90, 50.90};

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 8\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe seu CPF (apenas os numeros) ");
    scanf("%d", &cpf);

    printf("Informe sua secao ");
    scanf("%d", &secao);

    //Retorna a saida
    if(secao >= 1 && secao <= 10)
    {
        printf("O preco do ticket e %.2f", preco_secao[secao]);
    }
    else
    {
        printf("Secao invalida.");
    }    
}
