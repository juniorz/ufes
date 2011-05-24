/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercícios 4 e 6
 ****************************/
void ordenaTresNumeros(int *menor, int *medio, int *maior)
{
    //Distingue o maior, medio e menor
    //Uma adaptacao do metodo da bolha
    int temporario = 0;
    int i;

    for(i=0; i < 2; i++)
    {
        if(*menor > *medio)
        {
            temporario = *medio;
            *medio = *menor;
            *menor = temporario;
        }
    
        if(*medio > *maior)
        {
            temporario = *maior;
            *maior = *medio;
            *medio = temporario;
        }
    }
}
