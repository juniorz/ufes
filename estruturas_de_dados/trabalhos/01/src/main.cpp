/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
/*******************************************************
 *                   CHANGELOG                         *
 *******************************************************
 * [23/05/2005 00:40]                                  *
 * Toda a fun��o main() foi migrada para as            *
 * classes de aplica��o e "engines", tornando-a muito  *
 * mais elegante e logicamente estruturada.            *
 *                                                     *
 * [25/05/2005 00:40]                                  *
 * Foi estabelecido o ambiente de debugging com o      *
 * aux�ilio de macros e classes auxiliares.            *
 *******************************************************/

#include "includes/main.h"

int main(int argc, char *argv[])
{
	//Instancia a aplica��o central
	TApplication<Pessoa> *app = new TApplication<Pessoa>();
	
	//Inicializa a aplica��o
	app->Init(argc, argv);

	//Valida��o dos dados
	if( app->ValidaTipoEstrutura() && app->ValidaArquivoInput() && app->ValidaArquivoSearch() )
	{
		//Instancia a aplica��o especifica
		app->InitEngine();

		//Processa o arquivo de input
		app->ProcessaInput();

		//Gera a saida
		app->ProcessaSearch();
	}

	//Destroi a aplicacao
	delete app;
}

