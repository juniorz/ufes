/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
/*******************************************************
 *                   CHANGELOG                         *
 *******************************************************
 * [23/05/2005 00:40]                                  *
 * Toda a função main() foi migrada para as            *
 * classes de aplicação e "engines", tornando-a muito  *
 * mais elegante e logicamente estruturada.            *
 *                                                     *
 * [25/05/2005 00:40]                                  *
 * Foi estabelecido o ambiente de debugging com o      *
 * auxíilio de macros e classes auxiliares.            *
 *******************************************************/

#include "includes/main.h"

int main(int argc, char *argv[])
{
	//Instancia a aplicação central
	TApplication<Pessoa> *app = new TApplication<Pessoa>();
	
	//Inicializa a aplicação
	app->Init(argc, argv);

	//Validação dos dados
	if( app->ValidaTipoEstrutura() && app->ValidaArquivoInput() && app->ValidaArquivoSearch() )
	{
		//Instancia a aplicação especifica
		app->InitEngine();

		//Processa o arquivo de input
		app->ProcessaInput();

		//Gera a saida
		app->ProcessaSearch();
	}

	//Destroi a aplicacao
	delete app;
}

