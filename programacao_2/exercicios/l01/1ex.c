/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 1
 ****************************/

#include <stdio.h>

main()
{
    //Declara variaveis
    float a, b, c;
    float resposta[5];
    int i;

    //Inicializa variáveis
    a = 1.0;
    b = 3.0;
    c = -5.0;

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 1\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Calcula as respostas
    resposta[0] = a * (b + c) / (c + 2) * 3;
    resposta[1] = a + b / 2 * 3 - c;
    resposta[2] = (a + b) / 2 * (3 - c);
    resposta[3] = !(5 > 3) && 0 <= -1 && (3 > 4);
    resposta[4] = a <= b || b == 3 && !(a != 3);

    //Imprime os resultados
    for(i = 0; i < 5; i++)
    {
        int valor = resposta[i];
        printf("Resposta %d: %.2f \n", i+1, resposta[i]);
    }
}    
