/****************************
 * Reinaldo de Souza Junior *
 ****************************
 * Folha 1
 * Exercício 3
 ****************************/

#include <stdio.h>

main()
{
    //Decalra variáveis
    float consumo, fatura, excedente = 0;

    //Exibe um cabeçalho
    printf("Folha 1 - Exercicio 3\n");
    printf("Aluno:    Reinaldo de Souza Jr\n\n");

    //Le os Dados
    printf("Informe seu consumo (KW) ");
    scanf("%f", &consumo);

    //Calcula a fatura
    if(consumo <= 150)
    {
        fatura = consumo * 0.18;
    }

    if(consumo > 150)
    {
        fatura = 150 * 0.18 + (consumo - 150) * 0.2;
    }
    
    if(consumo > 370)
    {
        fatura += (consumo - 370) * 0.28;
    }    
    
    //Retorna a saida
    printf("Sua fatura e: %.2f", fatura);
}
