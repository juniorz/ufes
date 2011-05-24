/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 5
 ****************************/

#include <stdio.h>

main()
{
    //Declara variáveis
    float a, b, c;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 5\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Entrada dos dados
    while(1)
    {
        //Entrada do usuario
        printf("Digite 3 numeros\n");
        scanf("%f %f %f", &a, &b, &c);

        if(a >= 0 && b >= 0 && c >= 0)
        {
            //Entrada do usuario
            printf("\nA soma dos numeros e: %f \n\n\n", a + b + c);
       	}
       	else
       	{
            break;
       	}
    }
}
