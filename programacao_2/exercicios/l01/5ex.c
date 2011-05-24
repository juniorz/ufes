/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 5
 ****************************/

#include <stdio.h>

main()
{
    //Decalra variáveis
    int cord_x, cord_y, quadrante = 0;

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 5\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe um ponto no plano XY (x, y) ");
    scanf("%d %d", &cord_x, &cord_y);

    if(cord_x == 0 && cord_y == 0)
    {
        //Retorna a saida
        printf("O ponto esta localizado na origem do sistema");
    }
    else
    {
        if(cord_y > 0)
        {
            quadrante = (cord_x > 0) ? 1 : 2;
        }
        else
        {
            quadrante = (cord_x < 0) ? 3 : 4;
        }    

        //Retorna a saida
        printf("O ponto esta localizado no quadrante %d", quadrante);
    }        
}
