/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
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
		 * \brief Construtor padr�o
		 *
		 * Fornecido para permitir que classes sejam implementadas a partir de THashTable
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		 
		THashTable() : fHash(NULL) {};

		/**
		 * Construtor
		 * \param tamanho Tamanho da tabela hash
		 * \param funcao Fun��o que gera o hash
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
		 * \return Posi��o na tabela hash onde foi inserido o elemento
		 *
		 * \throw TENullElement* caso @c data seja NULL. @b Veja: TENullElement
		 * \throw TEInvalidHashFunction* caso o hash gerado seja inv�lido. @b Veja: TEInvalidHashFunction
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
		 * \return Elemento caso seja encontrado, ou NULL caso contr�rio.
		 *
		 * \throw TENullElement* caso @c data seja NULL. @b Veja: TENullElement
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		T* Get(T * data);

		/**********************************************
		 * Count()
		 **********************************************
		 * Retorna o n�mero de elementos da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Retorna o n�mero de elementos da tabela hash
		 * \return N�mero de elementos armazenados na tabela hash
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
		 * Esse m�todo n�o destr�i o elemento apontado pelo n�, apenas retira-o da estrutura, para destru�-lo use Kill()
		 *
		 * \param data Elemento a ser removido da lista.
		 * \return True caso o elemento exista na tabela hash, False caso contr�rio.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		bool Del(T* data);

		/**********************************************
		 * Kill()
		 **********************************************
		 * Remove e destr�i um elemento da tabela hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Remove e destr�i um elemento da tabela hash
		 *
		 * Libera a mem�ria ocupada pelo elemento que corresponde a @c data e retira-o da estrutura.
		 * Ap�s a chamada desse m�todo o elemento, qualquer refer�ncia ao elemento destru�do ser� inv�lida.
		 *
		 * \param data Elemento a ser destru�do.
		 * \return True caso o elemento exista na tabela hash, False caso contr�rio.
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
		 * Remove e destr�i todos os elemento da tabela hash
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
		 * Faz um dump dos dados da tabela hash na sa�ida padr�o de erro.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		void Dump();
#endif
		
	protected:
		int iSize;		/**< Tamanho da tabela hash */
		int iCount;		/**< N�mero de elementos que a tabela possui */
		TList<T>* Table;	/**< Array de listas. � o cora��o da tabela Hash */
		int(*fHash)(T*, int);	/**< Fun��o que calcula o hash */
		
	private:
		/**********************************************
		 * Hash()
		 **********************************************
		 * Algoritmo padr�o de c�lculo do Hash
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * Calcula o hash de um elemento
		 * \param data Dado a ser� manipulado
		 * \param tamanho Tamanho da tabela hash
		 * \return Posi��o na tabela hash onde o elemento ser� inserido
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
	//Isso deleta todos os elementos e chama o destrutor padr�o de todos automaticamente
	delete[] Table;
}


/******************************************************
 * public THashTable<T>::THashTable()
 ******************************************************
 * Construtor
 ******************************************************/
template <class T> THashTable<T>::THashTable(int tamanho, int(*funcao)(T*, int)) : iSize(tamanho), fHash(funcao)
{
	//Aloca espa�o para a tabela
	//N�o precisa iniciar cada Lista, pois o construtor padr�o � chamado automaticamente.
	Table = new TList<T>[iSize];

	/*
	 * Preferi n�o gerar a exce��o e caso a funcao n�o seja informada,
	 * utilizar a fun��o sugerida pelo professor
	 */
}


/******************************************************
 * public THashTable<T>::Hash()
 ******************************************************
 * Gera o hash para um elemento (fun��o padr�o)
 ******************************************************/
template <class T> int THashTable<T>::Hash(T* data, int tamanho)
{
	//Constante m�gica sugerida pelo Sr. Donald E. Knuth
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
	 * Utiliza por padr�o a fun��o fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

#ifdef DEBUG
	std::cerr << "[chave] " << chave << std::endl;
#endif
	
	//Fun��o inv�lida
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
	 * Utiliza por padr�o a fun��o fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exce��o que ser� gerada ao passar uma posi��o inv�lida para o m�todo Get()
	//caso o elemento n�o seja encontrado
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
	 * Utiliza por padr�o a fun��o fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exce��o que ser� gerada ao passar uma posi��o inv�lida para o m�todo Get()
	//caso o elemento n�o seja encontrado
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
 * Destr�i um elemento
 ******************************************************/
template <class T> bool THashTable<T>::Kill(T* data)
{
	//Elemento nulo
	if(data == NULL)
		throw new TENullElement("THashTable::Kill");

	/*
	 * Chave do item
	 * Utiliza por padr�o a fun��o fornecida pela classe
	 */
	int chave = (NULL != fHash) ? fHash(data, iSize) : Hash(data, iSize);

	//Aproveita-se da exce��o que ser� gerada ao passar uma posi��o inv�lida para o m�todo Get()
	//caso o elemento n�o seja encontrado
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
 * Destr�i todos os elementos
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
