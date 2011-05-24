/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 2
 ****************************/

#include <stdio.h>
#include <math.h>
#define PI          3.1415
#define PRECISAO    2.5

main()
{
    //Declara variáveis
    float primeira_area, area, raio, ultima_area;
    int denominador = 1;
    int i = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 2\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Entrada do usuario
    printf("Digite o valor do raio ");
    scanf("%f", &raio);

    //Area Maior
    area = primeira_area = pow(raio, 2) * PI;

    //Enquanto o termo for maior que a precisao
    while(area >= PRECISAO)
    {
        ultima_area = area;
        denominador *= 2;
        i++;
        area = pow(raio / denominador, 2) * PI;
    }
    
    printf("Numero de circulos concentricos: %d\n", i);
    printf("Diferenca entre a primeira e a ultima area: %f", primeira_area - ultima_area);
}
