/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 4
 ****************************/

#include <stdio.h>

main()
{
    //Declara variáveis
    int i, num_multiplos = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 4\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Entrada do usuario
    printf("Quantos multiplos de 2 deseja exibir?\n");
    scanf("%d", &num_multiplos);

    //Verifica os numeros e exibe a saida
    for(i = 0; i <= num_multiplos; i++)
    {
    	printf("%d	", i * 2);
   	}
}
