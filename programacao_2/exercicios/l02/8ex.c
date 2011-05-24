/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 8
 ****************************/

//Essa funcao esta apresentando problemas pois os numeros da variavel fatorial estao saindo do range de um inteiro.
//Tentei com long int e nada


#include <stdio.h>
#include <math.h>

#define 	LIMITE 	0.0001

main()
{
    //Declara variáveis
    long int fatorial = 1, numerador;
    float exponencial_x, soma, termo;
    int i = 1, x = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 8\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    printf("Digite o numero Xo: ");
    scanf("%d", &x);
    exponencial_x = exp( (float) x);

//    printf("Exponencial %f", exponencial_x);

    numerador = soma = x;
    //Entrada dos dados
    do
    {
        termo = (float) (numerador / fatorial);
        soma += termo;
        fatorial *= i;
        numerador *= x;

//    	printf("%f\n", termo);
//    	printf("%d! = %d\n", i, fatorial);
//    	printf("soma = %f\n", soma);

    	i++;
    }
    while( fabs(exponencial_x - soma) >= LIMITE);

    printf("Valor de Xo: %f\n", x);
    printf("Calculo pela serie: %f\n", soma);
    printf("Calculo pela funcao exp(): %f\n", exponencial_x);
    printf("Termos utilizados: %d\n", i);

}
