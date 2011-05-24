#include <stdio.h>

main(int num_argumentos, char *argumento[])
{
    int i, tamanho_string, num_vogais = 0;
    char *string;

    //Exibe o uso correto do programa
	if(1 == num_argumentos)
	{
		printf("+---------------------+\n");
		printf("|Lista 6 - Exercicio 2|\n");
		printf("+---------------------+\n\n");
		printf("Conta o numero de vogais.\n");
		printf("Uso: 2ex <string>\n\n");
		printf("Exemplo:\n$ 2ex abcdefg\n");
		exit(1);
	}

	tamanho_string = strlen(argumento[1]);
	string = argumento[1];

	//Varre a string
	for(i=0; i < tamanho_string-1; i++)
	{
     	//Verifica se e vogal
     	switch(toupper(string[i]))
     	{
          case 'A':
          case 'E':
          case 'I':
          case 'O':
          case 'U':
          	num_vogais++;
     	}
	}

	printf("A string %s contem %d vogais.\n", argumento[1], num_vogais);
	exit(0);
}
