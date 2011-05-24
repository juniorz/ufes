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
    int a, b, d, e = 0;
    
    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 2\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe os coeficientes A e B da equacao da primeira reta   [Ax + By = C] ");
    scanf("%d %d", &a, &b);

    printf("Informe os coeficientes C e D da equacao da segunda reta    [Dx + Ey = F] ");
    scanf("%d %d", &d, &e);
    
    //Retas paralelas
    if(a*e == b*d)
    {
        printf("As retas sao paralelas");
    }
    //Perpendicular
    else if(a*d + b*e == 0)
    {
        printf("As retas sao perpendiculares");
    }
    else
    {
        printf("As retas nao sao nem perpendiculares nem paralelas");
    }
}
