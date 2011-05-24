/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef THashTable_H
#define THashTable_H

#include "TError.h"
#include "TList.h"
#include <iostream>
#include <cmath>

/**
 * \brief Tabela Hash
 *
 * \version	1.0.1
 * \author	Reinaldo de Souza Junior <juniorz@gmail.com.br>
 * \date	05/2005
 */
template <class T> class THashTable {
	public:
	
		/**
		 * \brief Construtor padrão
		 *
		 * Fornecido para permitir que classes sejam implementadas a partir de THashTable
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		 
		THashTable() : fHash(NULL) {};

		/**
		 * Construtor
		 * \param tamanho Tamanho da tabela hash
		 * \param funcao Função que gera o hash
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		THashTable(int tamanho, int(*funcao)(T*, int) = NULL);

		/**
		 * Destrutor
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		~THashTable();

		/**********************************************
		 * Add()
		 **********************************************
		 * Insere um elemento
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Insere um elemento na tabela hash
		 * \param data Dado a ser inserido na tabela hash
		 * \return Posição na tabela hash onde foi inserido o elemento
		 *
		 * \throw TENullElement* caso @c data seja NULL. @b Veja: TENullElement
		 * \throw TEInvalidHashFunction* caso o hash gerado seja inválido. @b Veja: TEInvalidHashFunction
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Add(T* data);

		/**********************************************
		 * Get()
		 **********************************************
		 * Localiza o elemento na tabela
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Localiza um elemento na tabela e retorna-o
		 * \param data Dado a ser procurado
		 * \return Elemento caso seja encontrado, ou NULL caso contrário.
		 *
		 * \throw TENullElement* caso @c data seja NULL. @b Veja: TENullElement
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		T* Get(T * data);

		/**********************************************
		 * Count()
		 **********************************************
		 * Retorna o número de elementos da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Retorna o número de elementos da tabela hash
		 * \return Número de elementos armazenados na tabela hash
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Count() { return Count; };

		/**********************************************
		 * Size()
		 **********************************************
		 * Retorna o tamanho da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Retorna o tamanho da tabela hash
		 * \return Tamanho da tabela
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Size() { return Size; };

		/**********************************************
		 * Del()
		 **********************************************
		 * Remove um elemento da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Remove um elemento da tabela hash
		 *
		 * Remove o elemento da tabela hash que corresponda a @c data.
		 * Esse método não destrói o elemento apontado pelo nó, apenas retira-o da estrutura, para destruí-lo use Kill()
		 *
		 * \param data Elemento a ser removido da lista.
		 * \return True caso o elemento exista na tabela hash, False caso contrário.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		bool Del(T* data);

		/**********************************************
		 * Kill()
		 **********************************************
		 * Remove e destrói um elemento da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Remove e destrói um elemento da tabela hash
		 *
		 * Libera a memória ocupada pelo elemento que corresponde a @c data e retira-o da estrutura.
		 * Após a chamada desse método o elemento, qualquer referência ao elemento destruído será inválida.
		 *
		 * \param data Elemento a ser destruído.
		 * \return True caso o elemento exista na tabela hash, False caso contrário.
		 *
		 * \b Complexidade: @f$O(1)@f$
		 */
		bool Kill(T* data);

		/**********************************************
		 * DelAll()
		 **********************************************
		 * Remove todos os elemento da tabela hash
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove todos os elemento da tabela hash
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void DelAll();

		/**********************************************
		 * KillAll()
		 **********************************************
		 * Remove e destrói todos os elemento da tabela hash
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove todos os elemento da tabela hash
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void KillAll();

#ifdef DEBUG
		/**********************************************
		 * Dump()
		 **********************************************
		 * Exibe os dados do objeto
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Exibe os dados do objeto.
		 *
		 * Faz um dump dos dados da tabela hash na saíida padrão de erro.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		void Dump();
#endif
		
	protected:
		int iSize;		/**< Tamanho da tabela hash */
		int iCount;		/**< Número de elementos que a tabela possui */
		TList<T>* Table;	/**< Array de listas. É o coração da tabela Hash */
		int(*fHash)(T*, int);	/**< Função que calcula o hash */
		
	private:
		/**********************************************
		 * Hash()
		 **********************************************
		 * Algoritmo padrão de cálculo do Hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Calcula o hash de um elemento
		 * \param data Dado a será manipulado
		 * \param tamanho Tamanho da tabela hash
		 * \return Posição na tabela hash onde o elemento será inserido
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Hash(T* data, int tamanho);
};




/******************************************************
 * public THashTable<T>::~THashTable()
 ******************************************************
 * Destrutor
 ******************************************************/
template <class T> THashTable<T>::~THashTable()
{
	//Limpa a memoria
	//Isso deleta todos os elementos e chama o destrutor padrão de todos automaticamente
	delete[] Table;
}


/******************************************************
 * public THashTable<T>::THashTable()
 ******************************************************
 * Construtor
 ******************************************************/
template <class T> THashTable<T>::THashTable(int tamanho, int(*funcao)(T*, int)) : iSize(tamanho), fHash(funcao)
{
	//Aloca espaço para a tabela
	//Não precisa iniciar cada Lista, pois o construtor padrão é chamado automaticamente.
	Table = new TList<T>[iSize];

	/*
	 * Preferi não gerar a exceção e caso a funcao não seja informada,
	 * utilizar a função sugerida pelo professor
	 */
}


/******************************************************
 * public THashTable<T>::Hash()
 ******************************************************
 * Gera o hash para um elemento (função padrão)
 ******************************************************/
template <class T> int THashTable<T>::Hash(T* data, int tamanho)
{
	//Constante mágica sugerida pelo Sr. Donald E. Knuth
	float k = (sqrt(5) - 1) / 2;
	
	return (int) floor( tamanho * ( (int) (*data) * k - floor( (int) (*data) * k ) ) );
}


/******************************************************
 * public THashTable<T>::Add()
 ******************************************************
 * Insere um elemento
 ******************************************************/
template <class T> int THashTable<T>::Add(T* data)
{
	//Elemento nulo
	if(data == NULL)
		throw new TENullElement("THashTable::Add");

	/*
	 * Chave do item
	 * Utiliza por padrão a função fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

#ifdef DEBUG
	std::cerr << "[chave] " << chave << std::endl;
#endif
	
	//Função inválida
	if( chave < 0 || chave >= iSize )
		throw new TEInvalidHashFunction("THashTable::Add");

	//Insere o elemento
	Table[chave].Insert(data, 0);
	
	//Contador
	iCount++;

	//Retorna a posicao da tabela onde o elemento foi inserido
	return chave;
}


/******************************************************
 * public THashTable<T>::Get()
 ******************************************************
 * Obtem um elemento
 ******************************************************/
template <class T> T* THashTable<T>::Get(T* data)
{
	//Elemento nulo
	if(data == NULL)
		throw new TENullElement("THashTable::Get");

	/*
	 * Chave do item
	 * Utiliza por padrão a função fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exceção que será gerada ao passar uma posição inválida para o método Get()
	//caso o elemento não seja encontrado
	try {
		return Table[chave].Get( Table[chave].Search(data) );
	}
	catch(TEOutOfBounds*)
	{
		return NULL;
	}
}


/******************************************************
 * public THashTable<T>::Del()
 ******************************************************
 * Remove um elemento
 ******************************************************/
template <class T> bool THashTable<T>::Del(T* data)
{
	//Elemento nulo
	if(data == NULL)
		throw new TENullElement("THashTable::Del");

	/*
	 * Chave do item
	 * Utiliza por padrão a função fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exceção que será gerada ao passar uma posição inválida para o método Get()
	//caso o elemento não seja encontrado
	try {
		Table[chave].Del( Table[chave].Search(data) );
		iCount--;
		return true;
	}
	catch(TEOutOfBounds*)
	{
		return false;
	}
}


/******************************************************
 * public THashTable<T>::Kill()
 ******************************************************
 * Destrói um elemento
 ******************************************************/
template <class T> bool THashTable<T>::Kill(T* data)
{
	//Elemento nulo
	if(data == NULL)
		throw new TENullElement("THashTable::Kill");

	/*
	 * Chave do item
	 * Utiliza por padrão a função fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exceção que será gerada ao passar uma posição inválida para o método Get()
	//caso o elemento não seja encontrado
	try {
		Table[chave].Kill( Table[chave].Search(data) );	//O(1)
		iCount--;
		return true;
	}
	catch(TEOutOfBounds*)
	{
		return false;
	}
}


/******************************************************
 * public THashTable<T>::DelAll()
 ******************************************************
 * Remove todos os elementos
 ******************************************************/
template <class T> void THashTable<T>::DelAll()
{
	//Varre a tabela
	int i;
	for(i = 0; i < iSize; i++)	//O(n)
	{
		Table[i].DelAll();	//O(1)
	}
}


/******************************************************
 * public THashTable<T>::KillAll()
 ******************************************************
 * Destrói todos os elementos
 ******************************************************/
template <class T> void THashTable<T>::KillAll()
{
	//Varre a tabela
	int i;
	for(i = 0; i < iSize; i++)	//O(n)
	{
		Table[i].KillAll();	//O(1)
	}
}


#ifdef DEBUG
/******************************************************
 * public THashTable<T>::Dump()
 ******************************************************
 * Imprime a estrutura
 ******************************************************/
template <class T> void THashTable<T>::Dump()
{
	std::cerr << endl
			<< "+-----------[THashTable]-----------+" << std::endl
			<< "| iSize \t = " <<	iSize	<< std::endl	
			<< "| iCount \t = " << 	iCount	<< std::endl
			<< "| Table \t = " << 	Table	<< std::endl
			<< "| fHash \t = " << 	fHash	<< std::endl
			<< "+----------------------------------+" << std::endl << std::endl;

	int i;
	for(i = 0; i < iSize; i++)
	{
		std::cerr << "        {###} Table[" << i << "] {###} ";
		Table[i].Dump();
	}
}
#endif

#endif
