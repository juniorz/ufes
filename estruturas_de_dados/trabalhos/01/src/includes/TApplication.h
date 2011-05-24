/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
/**
 * [23/05/2005 00:40] Desenvolvido o conceito de criar uma
 * classe para ser a aplicação e outra para ser a "engine"
 * de cada estrutura.
 *
 * [24/05/2005 01:55] Finalizada a classe TAplication
 */
#ifndef TApplication_H
#define TApplication_H

#include "TError.h"
#include "TEngineTHashTable.h"
#include "TEngineTList.h"
#include "TEngineTQueue.h"
#include "TEngineTSortedList.h"
#include "TEngineTStack.h"
#include "Pessoa.h"
#include <iostream> 
#include <cstdio>
#include <cmath> 

using namespace std;

/**
 * \brief Classe que implementa a aplicação central
 */
template <class T> class TApplication {
	/**
	* \brief Tipo de estrutura
	*/
	enum tipo_estrutura
	{
		L,	/**< Lista (TList) */
		SL,	/**< Lista Ordenada (TSortedList) */
		S,	/**< Pilha (TStack) */
		Q,	/**< Fila (TQueue) */
		H	/**< Tabela Hash (THashTable) */
	};

	protected:
		TEngine<T> *engine;	/**< Engine especifica da estrutura de dados selecionada */
		char iFile[255];	/**< Nome do arquivo de INPUT */
		char sFile[255];	/**< Nome do arquivo de SEARCH */
		char **argumentos;	/**< Lista de argumentos */
		FILE *input;		/**< Descritor de Arquivo para iFile */
		FILE *search;		/**< Descritor de Arquivo para sFile */
		tipo_estrutura tipo;	/**< Indicador do tipo de estrutura que está sendo utilizada no programa */


	public:
		/**
		 * \brief Destrutor
		 *
		 * Destrói o que deve ser destruído ao se terminar a aplicacao
		 */
		~TApplication();

		/**
		 * \brief Inicializa a aplicação
		 * \param argc Numero de argumentos
		 * \param argv Lista de argumentos
		 */
		void Init(int argc, char *argv[]);
		
		/**
		 * \brief Exibe a tela de ajuda para a aplicação
		 */
		void ShowUsage();
		
		/**
		 * \brief Valida o tipo de estrutura
		 *
		 * Valida o primeiro parâmetro passado ao programa e trata os possíveis erros
		 */
		 bool ValidaTipoEstrutura();

		/**
		 * \brief Valida o arquivo de INPUT
		 *
		 * Valida o segundo parâmetro passado ao programa e trata os possíveis erros
		 */		 
		 bool ValidaArquivoInput();
		 
		/**
		 * \brief Valida o arquivo de SEARCH
		 *
		 * Valida o terceiro parâmetro passado ao programa e trata os possíveis erros
		 */		 
		 bool ValidaArquivoSearch();

		/**
		 * \brief Inicializa a engine especifica de cada estrutura de dados
		 *
		 * Inicializa a parte específica do programa que tratará da estrutura de dados em questão
		 */
		 bool InitEngine();

		/**
		 * \brief Processa o arquivo de INPUT
		 *
		 * Processa o arquivo de INPUT e manipula as estruturas.
		 */
		 bool ProcessaInput();
		 
		/**
		 * \brief Processa o arquivo de SEARCH
		 *
		 * Processa o arquivo de SEARCH e gera a saída do programa.
		 */
		 bool ProcessaSearch();
};





template <class T> void TApplication<T>::Init(int argc, char *argv[])
{
	//Aponta para os argumentos
	argumentos = argv;

	//Verifica se o programa foi chamado da maneira correta
	if(argc < 4 || !strcmp(argv[1], "--help"))
	{
		ShowUsage();
		exit(0);
	}
}



template <class T> void TApplication<T>::ShowUsage()
{
	std::cerr
		<< "Uso: "<< argumentos[0] << " ESTRUTURA INPUT.txt BUSCA.txt" << std::endl << std::endl
		<< "ESTUTURA:" << std::endl
		<< "\t -l \t TList" << std::endl
		<< "\t -sl \t TSortedList" << std::endl
		<< "\t -s \t TStack" << std::endl
		<< "\t -q \t TQueue" << std::endl
		<< "\t -h \t THash" << std::endl;
}



template <class T> bool TApplication<T>::ValidaTipoEstrutura()
{
	//Instancia o objeto
	if(!strcmp(argumentos[1], "-l"))
	{
		tipo = L;
	}
	else if(!strcmp(argumentos[1], "-sl"))
	{
		tipo = SL;
	}
	else if(!strcmp(argumentos[1], "-s"))
	{
		tipo = S;
	}
	else if(!strcmp(argumentos[1], "-q"))
	{
		tipo = Q;
	}
	else if(!strcmp(argumentos[1], "-h"))
	{
		tipo = H;
	}
	else
	{
		const char *txt_erro = "ESTRUTURA inválida: ";
		int tamanho = strlen(txt_erro) + strlen(argumentos[1]);

		char msg_erro[++tamanho];

		TEGeneralError *ErrorHandler = new TEGeneralError(argumentos[0], strcat(strcpy(msg_erro, txt_erro), argumentos[1]));
		ErrorHandler->Exit(1);
	}
	
	return true;
}

template <class T> bool TApplication<T>::ValidaArquivoInput()
{
	//Abre o arquivo
	if(strlen(argumentos[2]))
	{
		if ( (input = fopen(argumentos[2], "r")) == NULL )
		{
			const char *txt_erro = "Erro ao abrir o arquivo INPUT: ";
			int tamanho = strlen(txt_erro) + strlen(argumentos[2]);
			
			char msg_erro[++tamanho];
		
			TEGeneralError *ErrorHandler = new TEGeneralError(argumentos[0], strcat(strcpy(msg_erro, txt_erro), argumentos[2]));
			ErrorHandler->Exit(2);

		}

		return true;
	}
	else
	{
		ShowUsage();
	}
}



template <class T> bool TApplication<T>::ValidaArquivoSearch()
{
	//Abre o arquivo
	if(strlen(argumentos[3]))
	{
		if ( (search = fopen(argumentos[3], "r")) == NULL )
		{
			const char *txt_erro = "Erro ao abrir o arquivo SEARCH: ";
			int tamanho = strlen(txt_erro) + strlen(argumentos[3]);
			
			char msg_erro[++tamanho];
		
			TEGeneralError *ErrorHandler = new TEGeneralError(argumentos[0], strcat(strcpy(msg_erro, txt_erro), argumentos[3]));
			ErrorHandler->Exit(3);
		}

		return true;
	}
	else
	{
		ShowUsage();
	}
}



template <class T> bool TApplication<T>::InitEngine()
{
	//Instancia a engine adequada
	switch(tipo)
	{
		//Lista
		case L:
		  engine = new TEngineTList<T>(new TList<T>);
		break;

		//Lista Ordenada
		case SL:
		  engine = new TEngineTSortedList<T>(new TSortedList<T>);
		break;

		//Pilha
		case S:
		  engine = new TEngineTStack<T>(new TStack<T>);
		break;

		//Fila
		case Q:
		  engine = new TEngineTQueue<T>(new TQueue<T>);
		break;

		//Tabela Hash
		case H:
		  //Obtem o numero de elementos que a tabela armazenará
		  //Gera um tamanho levemente menor que o numero de entradas, para fins demonstrativos do espalhamento
		  int tamanho;
		  fscanf(input, "%d", &tamanho);
		  tamanho -= (int) floor(log10(tamanho));

		  engine = new TEngineTHashTable<T>(new THashTable<T>(tamanho));
		  
		  //reaponta o arquivo para o inicio
		  rewind(input);
		break;

		//Nada (impossivel, mas ... )
		default:
		  return false;
		break;
	}
}



template <class T> bool TApplication<T>::ProcessaInput()
{
	//Obtem o numero de comandos
	int numRegistros;
	fscanf(input, "%d", &numRegistros);

#ifdef DEBUG
std::cerr << numRegistros << " inputs " << endl;
#endif

	//Processa o input
	for(; numRegistros > 0; numRegistros--)
	{
		//Cria o elemento
		T *elemento = new T();
		
		//Le a linha
		int posicao, codigo;
		char nome[255];
		fscanf(input, "%d\t%d\t%255[^\n]\n", &posicao, &codigo, &nome);
	
		//Preenche o elemento	
		elemento->SetCodigo(codigo);
		elemento->SetNome(nome);

#ifdef DEBUG
std::cerr << "[pos " << posicao << "]\t[" << elemento << "]\t" << *elemento << std::endl;
#endif
		try {
			engine->InsereElemento(posicao, elemento);
		}
		catch(TEGeneralError *Error)
		{
			Error->toString();
		}
	}


#ifdef DEBUG
std::cerr << std::endl << "Após as inserções: " << std::endl;
engine->dump();
#endif
	
	return true;
}

template <class T> bool TApplication<T>::ProcessaSearch()
{
	//Obtem o numero de comandos
	int numOperacoes;
	fscanf(search, "%d\n", &numOperacoes);

	//Numero de intens nao encontrados
	int naoEncontrados = 0;

#ifdef DEBUG
std::cerr << endl << numOperacoes << " searchs " << endl;
#endif

	//Processa o input
	for(; numOperacoes > 0; numOperacoes--)
	{
		//Cria o elemento
		T *elemento = new T();
		
		//Le a linha
		int codigo;
		fscanf(search, "%d\n", &codigo);
	
		//Preenche o elemento	
		elemento->SetCodigo(codigo);

#ifdef DEBUG
std::cerr << "[" << elemento << "]\t" << *elemento << std::endl;
#endif

		try {
			//Procura o elemento
			if (NULL != (elemento = engine->ProcuraElemento(elemento)) )
			{
				//Estranho.. Utilizando a otimização (g++ -O3 [...] ) de repente isso havia parado de funcionar :-D
				//Desabilitei a otimização e foi...
		
				//Encontrou
				std::cout << *elemento << std::endl;
			}
			else
			{
				//Nao encontrou
				std::cout << codigo << " - [Item not found]" << std::endl;
				naoEncontrados++;
			}
		}
		catch(TEGeneralError *Error)
		{
			Error->toString();
		}
	}

	//Numero de itens nao encotrados
	std::cout << "=> " << naoEncontrados << " item(s) not found." << std::endl;

	return true;
}


template <class T> TApplication<T>::~TApplication()
{
	//Fecha os arquivos
	fclose(input);
	fclose(search);

	//Limpa a engine
	engine->clean();
}

#endif
