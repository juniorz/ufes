/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 2
 * Exercício 7
 ****************************/
#include <stdio.h>
#define	LIMITE	5

main()
{
    //Declara variáveis
    char parametro[5];
    float soma_maiores = 0, media = 0;
    int num_maiores = 0, num_menores = 0;

    //Exibe um cabeçalho
    printf("Folha 2 - Exercicio 6\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    printf("Digite os numeros: (Q para Sair) ");

    //Entrada dos dados
    do
    {
    	//Constroi o termo
    	scanf("%5s", &parametro);

    	//Soma os maiores para tirar a media
    	if( atoi(parametro) > LIMITE )
    	{
    		soma_maiores += atoi(parametro);
    		num_maiores++;
       	}
       	else if(0 != isdigit(parametro[0]) )
       	{
    		num_menores++;
       	}
    }
    while(toupper(parametro[0]) != 'Q');

    //Exibe a repsosta
    media = (num_maiores > 0) ? soma_maiores / num_maiores : 0;

    printf("Media dos valores maiores que %d: %f\n", LIMITE, media);
    printf("Numero de elementos menores que %d: %d\n", LIMITE, num_menores);

}
