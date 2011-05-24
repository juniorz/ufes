#include <stdio.h>

main(int num_argumentos, char *argumento[])
{
    int i, tamanho_string;
    char *string;

    //Exibe o uso correto do programa
	if(1 == num_argumentos)
	{
		printf("+---------------------+\n");
		printf("|Lista 6 - Exercicio 1|\n");
		printf("+---------------------+\n\n");
		printf("Verifica se uma string esta em ordem crescente.\n");
		printf("Uso: 1ex <string>\n\n");
		printf("Exemplo:\n$ 1ex abcdefg\n");
		exit(1);
	}

	tamanho_string = strlen(argumento[1]);
	string = argumento[1];

	//Varre a string
	for(i=0; i < tamanho_string-1; i++)
	{
     	//Compara
		if(toupper(string[i]) > toupper(string[i+1]))
		{
			printf("A string %s nao esta em ordem crescente.\n", argumento[1]);
			exit(1);
		}
	}

	printf("A string %s esta em ordem crescente.\n", argumento[1]);
	exit(0);
}
