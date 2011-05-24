#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO_DADOS	"./dados.dat"

//
//Estruturas de dados
//

//Um ponto
struct ponto {
    float x;
    float y;
};

//
//Assinatura das funções
//
int 	le_dados(float pontos[][2]);
void 	calcula_Ex(double *somatorio, float pontos[][2], int num_registros);
void 	calcula_Ey(double *somatorio, float pontos[][2], int num_registros);
void 	calcula_Exy(double *somatorio, float pontos[][2], int num_registros);
void 	calcula_Ex2(double *somatorio, float pontos[][2], int num_registros);
void 	calcula_Ey2(double *somatorio, float pontos[][2], int num_registros);

int main()
{
	//Numeros muito grandes podem ser utilizados
	float pontos[1][2];
    double Ex = 0.0, Ey = 0.0, Exy = 0.0, Ex2 = 0.0, Ey2 = 0.0;
    int i, n;
    double a, b, R, numerador, denominador;

    //Le os dados
    n = le_dados( pontos );

    //Calcula os somatorios
    calcula_Ex(&Ex, pontos, n);
    calcula_Ey(&Ey, pontos, n);
    calcula_Exy(&Exy, pontos, n);
    calcula_Ex2(&Ex2, pontos, n);
    calcula_Ey2(&Ey2, pontos, n);

    //Coeficientes
    numerador = (double) (n * Exy - Ex * Ey);
    denominador = (double) (n * Ex2 - Ex * Ex);
    a = numerador / denominador;
    b = (double) (Ey * Ex2 - Ex * Exy) / denominador;
    R = numerador / sqrt( denominador * sqrt( (double) n * Ey2 - Ey * Ey ) );

/*
printf("\n 1 ---> %g\n", (double) n * Ey2 - Ey * Ey );
printf("\n 2 ---> %g\n", sqrt( (double) n * Ey2 - Ey * Ey ));
printf("\n 3 ---> %g\n", denominador * sqrt( (double) n * Ey2 - Ey * Ey ));
printf("\n 4 ---> %g\n", sqrt( denominador * sqrt( (double) n * Ey2 - Ey * Ey ) ));
printf("\n 5 ---> %g\n", numerador);

printf("\n Ey2 ---> %g\n", Ey2);
printf("\n Ex2 ---> %g\n", Ex2);
printf("\n Exy ---> %g\n", Exy);
printf("\n Ex ---> %g\n", Ex);
printf("\n Ey ---> %g\n", Ey);
printf("\n n ---> %d\n", n);
printf("\n a ---> %g\n", a);
printf("\n b ---> %g\n", b);
printf("\n R ---> %g\n", R);

//Varre os registros lidos
for(i=0; i < n; i++)
{
	printf("%f %f\n", pontos[i][0], pontos[i][1]);
}
*/


    printf("\na = %g", a);
    printf("\nb = %g", b);
    printf("\nR = %g", R);
    printf("\nEq da reta: y = %gx + %g\n", a, b);

   	exit(0);
}

int le_dados(float pontos[][2])
 {
    FILE *fp;
    char temp[255];	//String temporaria
	float *p;		//Ponteiro para possibilita o aumento do tamnho do array
	
    if ((fp = fopen(ARQUIVO_DADOS, "r")) == NULL)		//Abre o arquivo para leitura
    {
        //previne erros
        printf("Erro ao abrir o arquivo de dados.\n");
        exit(1);
    }

    int i = 0;
    //Le todo o arquivo
	while(!feof(fp))
	{
     	//Inicializa ponteiro
    	p = &pontos[i][0];
     	fgets(temp, sizeof(temp), fp);		//Armazena a linha temporariamente
		sscanf(temp, "%f %f", p, p + 1);	//Passa para o array os valores de X e Y
		i++;								//Incrementa o contador de registros
	}

    fclose(fp);								//Fecha o arquivo

    return i;
}

//Calcula o somatorio de XiYi
void calcula_Exy(double *somatorio, float pontos[][2], int num_registros)
{
    int i = 0;

    //Varre os registros
    for(i=0; i < num_registros; i++)
    {
    	*somatorio += (double) (pontos[i][0] * pontos[i][1]);
    }
}

//Calcula o somatorio de Xi
void calcula_Ex(double *somatorio, float pontos[][2], int num_registros)
{
    int i = 0;

    //Varre os registros
    for(i=0; i < num_registros; i++)
    {
    	*somatorio += (double) pontos[i][0];
    }
}

//Calcula o somatorio de Yi
void calcula_Ey(double *somatorio, float pontos[][2], int num_registros)
{
    int i = 0;

    //Varre os registros
    for(i=0; i < num_registros; i++)
    {
    	*somatorio += (double) pontos[i][1];
    }
}

//Calcula o somatorio de XiXi
void calcula_Ex2(double *somatorio, float pontos[][2], int num_registros)
{
    int i = 0;

    //Varre os registros
    for(i=0; i < num_registros; i++)
    {
    	*somatorio += (double) (pontos[i][0] * pontos[i][0]);
    }
}

//Calcula o somatorio de YiYi
void calcula_Ey2(double *somatorio, float pontos[][2], int num_registros)
{
    int i = 0;

    //Varre os registros
    for(i=0; i < num_registros; i++)
    {
    	*somatorio += (double) (pontos[i][1] * pontos[i][1]);
    }
}
