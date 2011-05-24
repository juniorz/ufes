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
 *                    CHANGELOG                        *
 *******************************************************
 * [07/05/2005 - 13:33]                                *
 * Finalizada a documenta��o da classe TAbstractList   *
 *                                                     *
 * [07/05/2005 13:35]                                  *
 * Alguns m�todos foram implementados na propria       *
 * defini��o da classe por serem extremamente simples  *
 *                                                     *
 * [12/05/2005 00:10]                                  *
 * Implementados os metodos protegidos para tratar     *
 * de maneira segura a tarefa de setar os elementos    *
 * anterior e posterior de um n�.                      *
 *                                                     *
 * [21/05/2005 18:35]                                  *
 * Os arquivo .h e .cpp foram mesclados devido �       *
 * maneira como os templates s�o tratados pelo compi-  *
 * lador.                                              *
 *                                                     *
 * [25/05/2005 01:33]                                  *
 * Foram criados 2 novos m�todos _ToNext() e _ToPrior  *
 * unica e exclusivamente com o objetivo de tornar o   *
 * m�todo GoTo() mais seguro e intelig�vel.            *
 *                                                     *
 * Foi adicionado tamb�m um invariante ao m�todo       *
 * Insert() - apenas no desenvolvimento. Acho que      *
 * agora o Insert() est� realmente funcionando.        *
 *                                                     *
 * [30/05/2005 21:40]                                  *
 * Implementado o m�todo Sort (utilizando o algoritmo  *
 * Bubblesort) e com isso foi finalizada o template    *
 * TAbstractList<T>                                    *
 *******************************************************/

#ifndef TAbstractList_H
#define TAbstractList_H

#include "TError.h"
#include <iostream>
#include <cstdlib>

/**
 * \brief Lista Abstrata.
 *
 * Classe abstrata da qual a maioria das outras estruturas lineares derivam.
 *
 * \version	1.0.1
 * \author	Reinaldo de Souza Junior <juniorz@gmail.com.br>
 * \date	05/2005
 */
template <class T> class TAbstractList {

	/**
	 * Um N� que representa um elemento da lista
	 */
	typedef struct node {
		struct node *pPrior;	/**< Elemento anterior ao n� */
		T *Data;		/**< Dado que o n� cont�m */
		struct node *pNext;	/**< Elemento posterior ao n� */
	} Node;

#ifdef DEBUG
 	public:
		/**********************************************
		 * Dump()
		 **********************************************
		 * Exibe os dados do objeto
		 **********************************************/
		/**
		 * \brief Exibe os dados do objeto.
		 *
		 * Faz um dump dos dados da lista na sa�da padr�o.
		 */
		void Dump();
#endif

	protected:
		int Size;	/**< N�mero de elementos que a lista possui */
		int PosCorrente;/**< Posi��o do elemento apontado por TAbstractList::pFirst */

		Node *pFirst;	/**< Ponteiro para o primeiro elemento da lista */
		Node *pCurrent;	/**< Ponteiro para o elemento corrente da lista. @see TAbstractList::PosCorrente */
		Node *pLast;	/**< Ponteiro para o �ltimo elemento da lista */

		/**********************************************
		 * TAbstractList()
		 **********************************************
		 * Construtor.
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Construtor da Lista Abstrata.
		 *
		 * Instancia um novo objeto TAbstractList
		 * \n @b Complexidade: @f$O(1)@f$
		 */
		TAbstractList() : PosCorrente(0), pFirst(NULL), pCurrent(NULL), pLast(NULL), Size(0) {  };

		/**********************************************
		 * ~TAbstractList()
		 **********************************************
		 * Destrutor
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Destrutor da Lista Abstrata.
		 *
		 * Esse m�todo tamb�m limpa a estrutura.
		 * \n @b Complexidade: @f$O(n)@f$
		 */
		~TAbstractList() { DelAll(); };

		/**********************************************
		 * Count()
		 **********************************************
		 * Retorna o n�mero de elementos da estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Retorna o n�mero de elementos da estrutura
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Count() { return Size; };

		/**********************************************
		 * Get()
		 **********************************************
		 * Retorna um elemento de uma posi��o espec�fica
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Retorna um elemento de uma posi��o espec�fica.
		 *
		 * Retorna um ponteiro para elemento da estrutura que ocupa a posi��o @c pos
		 *
		 * \param pos Posi��o do elemento que se deseja obter
		 * \return Ponteiro associado ao n� que ocupa a posi��o @c pos na estrutura
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		T* Get(int pos) { try { GoTo(pos); } catch (...) { throw; } return GetCurrent(); };

		/**********************************************
		 * GetCurrent()
		 **********************************************
		 * Retorna o elemento corrente
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Retorna o elemento corrente da estrutura.
		 * \return Ponteiro associado ao n� que ocupa a posi��o corrente na estrutura.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		T* GetCurrent() { if(pCurrent == NULL) { throw new TENullElement("TAbstractList::GetCurrent"); } return pCurrent->Data; };

		/**********************************************
		 * Insert()
		 **********************************************
		 * Insere um elemento em uma posi��o espec�fica
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Insere um elemento em uma posi��o espec�fica.
		 *
		 * Insere um elemento que aponta para @c data na posi��o @c pos da estrutura.
		 *
		 * \param data Ponteiro para um elemento que ser� inserido na estrutura
		 * \param pos Posi��o onde o elemento deve ser inserido
		 * \return Posi��o onde o elemento foi inserido
		 *
		 * \throw TENullElement* caso @c data seja nulo (n�o aponta para nada). @b Veja: TENullElement
		 * \throw TEOutOfBounds* caso @c pos seja uma posi��o inv�lida. @b Veja: TEOutOfBounds
		 *
		 * \post \code data == Get(pos); \endcode
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		int Insert(T* data, int pos);

		/**********************************************
		 * Del()
		 **********************************************
		 * Remove um elemento da lista
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove um elemento da estrutura.
		 *
		 * Remove o elemento da estrutura na posi��o @c pos.
		 * Esse m�todo n�o destr�i o elemento apontado pelo n�, apenas retira-o da estrutura, para destru�-lo use Kill()
		 *
		 * \param pos Posi��o do elemento a ser removido da lista.
		 * \return Posi��o do elemento corrente da estrutura ap�s a remo��o.
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		int Del(int pos);

		/**********************************************
		 * DelAll()
		 **********************************************
		 * Remove todos os elemento da lista
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove todos os elemento da estrutura
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void DelAll();

		/**********************************************
		 * Kill()
		 **********************************************
		 * Remove e destr�i um elemento da estrutura
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove e destr�i um elemento da estrutura.
		 *
		 * Libera a mem�ria ocupada pelo elemento na posi��o @c pos e retira-o da estrutura.
		 * Ap�s a chamada desse m�todo o elemento, qualquer refer�ncia ao elemento destru�do ser� inv�lida.
		 *
		 * \param pos Posi��o do elemento a ser destru�do.
		 * \return Posi��o do elemento corrente da estrutura.
		 *
		 * \b Complexidade: @f$O(n)@f$
		 */
		int Kill(int pos);

		/**********************************************
		 * KillAll()
		 **********************************************
		 * Remove e destr�i todos os elemento da estrutura
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Remove e destr�i todos os elemento da estrutura.
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void KillAll();

		/**********************************************
		 * MoveFirst()
		 **********************************************
		 * Aponta o elemento corrente para o primeiro elemento da estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o primeiro elemento da estrutura.
		 *
		 * \return Posi��o do elemento corrente da estrutura (usualmente retorna 0)
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveFirst() { PosCorrente = (Size > 0) ? 0 : -1; pCurrent = pFirst; return PosCorrente; };

		/**********************************************
		 * MoveNext()
		 **********************************************
		 * Aponta o elemento corrente para pr�ximo elemento da estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para pr�ximo elemento da estrutura
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveNext();

		/**********************************************
		 * MovePrior()
		 **********************************************
		 * Aponta o elemento corrente para o elemento anterior da estrutura.
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o elemento anterior da estrutura
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MovePrior();

		/**********************************************
		 * MoveLast()
		 **********************************************
		 * Aponta o elemento corrente para o �ltimo elemento da estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o �ltimo elemento da estrutura.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveLast() { PosCorrente = Size - 1; pCurrent = pLast; return Size; };

		/**********************************************
		 * GoTo()
		 **********************************************
		 * Aponta o elemento corrente para o elemento na posi��o "posicao"
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o elemento na posi��o @c pos.
		 *
		 * \param pos Posi��o do novo elemento corrente
		 * \return Posi��o do novo elemento corrente
		 *
		 * \post #PosCorrente = @c pos
		 *
		 * \throw TEOutOfBounds* caso @c pos seja uma posi��o inv�lida. @b Veja: TEOutOfBounds
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		int GoTo(int pos);

		/**********************************************
		 * ResetCurrent()
		 **********************************************
		 * Reseta o elemento corrente da estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Reseta o elemento corrente da estrutura.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		void ResetCurrent() { pCurrent = NULL; PosCorrente = -1; };

		/**********************************************
		 * Search()
		 **********************************************
		 * Busca um elemento na estrutura
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Busca um elemento na estrutura.
		 *
		 * Busca o primeiro elemento da estrutura que seja igual a  @c procurado e retorna sua posi��o.
		 *
		 * \param procurado Elemento a ser buscado na estrutura
		 * \return Posi��o do elemento, caso tenha encontrado algum, ou -1 caso o elemento n�o tenha sido encontrado.
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		int Search(T* procurado);

		/**********************************************
		 * Sort()
		 **********************************************
		 * Ordena a lista
		 * Complexidade: O(n lg n)
		 **********************************************/
		/**
		 * \brief Ordena a estrutura em ordem crescente.
		 *
		 * Esse m�todo reseta o elemento corrente da estrutura.
		 *
		 * @b Complexidade: @f$O(n \cdot \lg_2 n)@f$
		 */
		void Sort();

	private:
		/**********************************************
		 * _CreateNode()
		 **********************************************
		 * Cria um novo elemento para a estrutura
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Cria um novo elemento para a estrutura.
		 *
		 * Fun��o de apoio para tornar a programa��o ainda mais em alto n�vel.
		 *
		 * \param dado Dado do elemento
		 * \param anterior Apontador para o elemento anterior
		 * \param posterior Apontador para o elemento posterior
		 *
		 * \post \code newNode->pNext = pCurrent \endcode
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		Node* _CreateNode(T* dado, Node* anterior, Node* posterior) { Node *newNode = new Node; newNode->Data = dado; newNode->pPrior = anterior; newNode->pNext = posterior; return newNode; };

		/**********************************************
		 * _NodeSetPrior()
		 **********************************************
		 * Define o pPrior de um n�
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Define o \link Node::pPrior pPrior \endlink de um n� (caso ele realmente seja um n�)
		 *
		 * Aponta o elemento @c anterior como sendo o elemento anterior ao elemento @c node
		 *
		 * \param node Elemento que ter� seu antecessor alterado
		 * \param anterior Elemento que ser� o antecessor
		 * \return @b false caso @c node seja nulo, @b true caso contr�rio.
		 *
		 * \post \code Node* node->pPrior = (Node*) anterior; \endcode (Se @c node for n�o-nulo)
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		bool _NodeSetPrior(Node* node, Node* anterior) { if(node != NULL) { node->pPrior = anterior; return true; } else { return false; } };
		
		/**********************************************
		 * _NodeSetNext()
		 **********************************************
		 * Define o pNext de um n� (caso ele realmente seja um n�)
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Define o \link Node::pNext pNext \endlink de um n� (caso ele realmente seja um n�)
		 *
		 * Aponta o elemento @c posterior como sendo o elemento posteior ao elemento @c node
		 *
		 * \param node Elemento que ter� seu sucessor alterado
		 * \param proximo Elemento que ser� o sucessor
		 * \return @b false caso @c node seja nulo, @b true caso contr�rio.
		 *
		 * \post \code Node* node->pNext = (Node*) proximo; \endcode (Se @c node for n�o-nulo)
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		bool _NodeSetNext(Node* node, Node* proximo) { if(node != NULL) { node->pNext = proximo; return true; } else { return false; } };
		
		/**********************************************
		 * _ToNext()
		 **********************************************
		 * Aponta para o pr�ximo elemento e atualiza a posi��o
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta para o pr�ximo elemento e atualiza a posi��o
		 *
		 * M�todo utilizado apenas para tonar o codigo mais leg�vel e reaproveitar c�digo
		 * @b Complexidade: @f$O(1)@f$
		 */
		bool _ToNext();

		/**********************************************
		 * _ToPrior()
		 **********************************************
		 * Aponta para o elemento anterior e atualiza a posi��o.
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Aponta para o pr�ximo elemento e atualiza a posi��o
		 *
		 * M�todo utilizado apenas para tonar o codigo mais leg�vel e reaproveitar c�digo
		 * @b Complexidade: @f$O(1)@f$
		 */
 		bool _ToPrior();

		/**********************************************
		 * _PrepareDel()
		 **********************************************
		 * Prepara a lista para ser efetuado um Del
		 * Complexidade: O(n)
		 **********************************************/
		/**
		 * \brief Prepara a lista para um #Del
		 *
		 * Prepara a lista para que seja efetuado um #Del e retorna o elemento da ser� o elemento corrente ap�s a remo��o.
		 * M�todo utilizado para tonar o codigo mais leg�vel e reaproveitar c�digo
		 *
		 * \param pos Posi��o do elemento a ser removido
		 *
		 * \post \code pCurrent = GoTo(pos); \endcode
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		Node* _PrepareDel(int pos);

		/**********************************************
		 * _BubbleSort()
		 **********************************************
		 * Executa um Bubblesort na lista
		 * Complexidade: O(n ^2) ??
		 **********************************************/
		/**
		 * Executa um Bubblesort na lista
		 *
		 * @b Complexidade: @f$O(n^{2})@f$
		 */		
		void _BubbleSort();
		
		/**********************************************
		 * _Swap()
		 **********************************************
		 * Troca a posicao de 2 elementos
		 * Complexidade: O(1)
		 **********************************************/
		/**
		 * \brief Troca a posicao de 2 elementos
		 *
		 * Essa fun��o � utilizada para auxiliar o _BubbleSort()
		 *
		 * \param a Primeiro elemento
		 * \param b Segundo elemento
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		void _Swap(Node* a, Node *b) { if ( *(a->Data) < *(b->Data) ) { T* aux = a->Data; a->Data = b->Data; b->Data = aux;} };
};




/******************************************************
 * _Compara()
 ******************************************************
 * Compara 2 elementos
 ******************************************************/
/**
 * \brief Compara 2 elementos
 *
 * Essa fun��o � utilizada para auxiliar o qsort()
 *
 * \param a Primeiro elemento
 * \param b Segundo elemento
 * \return 0 se a � igual a b, um valor maior que zero se a � maior que b, um valor menor que zero se a � menor que b.
 *
 * @b Complexidade: @f$O(1)@f$
 */
template <class T> int _Compara(const void* a, const void* b)
{
	T *p1, *p2;

	p1 = (T*) a;
	p2 = (T*) b;
	
	if(*p1 == *p2)
	{
		return 0;
	}
	else if(*p1 < *p2)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}


/******************************************************
 * private TAbstractList::_PrepareDel()
 ******************************************************
 * Prepara a lista para ser efetuado um Del
 ******************************************************/
template <class T> struct TAbstractList<T>::node* TAbstractList<T>::_PrepareDel(int pos)
{
	//Fora dos limites
	if( pos < 0 || pos >= Size )
		throw new TEOutOfBounds("TAbstractList::_PrepareDel");

	//Armazenar� o proximo pCurrent;
	Node *pProximoCurrent = NULL;

	//Move para a posi��o
	GoTo(pos);	//O(n)

	//
	//Atualiza os ponteiros
	//

	//O elemento seguinte passa a ser o corrente [defini��o no trabalho]
	pProximoCurrent = pCurrent->pNext;

	//Liga o elemento anterior ao elemento posterior
	//Pr�ximo elemento do elemento anterior
	//->
	//Pr�ximo elemento
	if(! _NodeSetNext(pCurrent->pPrior, pCurrent->pNext) ) {	//N�o existe anterior
		pFirst = pCurrent->pNext;				//Cobre o caso em que o elemento que est� sendo retirado � o primeiro da lista
									//Tamb�m cobre o caso em que ele � o �nico elemento (pFirst = NULL)
	}

	//Liga o elemento posterior ao anterior
	//Elemento anterior do proximo elemento
	//->
	//Elemento anterior
	if(! _NodeSetPrior(pCurrent->pNext, pCurrent->pPrior) ) {	//N�o existe pr�ximo
		PosCorrente = (Size > 1) ? PosCorrente - 1 : Size -1;	//Tamb�m cobre o caso de ser o �nico elemento (PosCorrente = -1)
		pProximoCurrent = pLast = pCurrent->pPrior;		//Tamb�m cobre o caso de ser o �nico elemento (pCurrent = pLast = NULL)
	}

	//Retorna o elemento que ser� o pCurrent
	return pProximoCurrent;
}


/******************************************************
 * private TAbstractList<T>::_BubbleSort()
 ******************************************************
 * Ordena a lista
 ******************************************************/
template <class T> void TAbstractList<T>::_BubbleSort()
{
	//Otimiza��o
	register Node *i = NULL;
	register Node *j = NULL;
	
	//
	//BubleSort utilizando ponteiros :-D
	//Muito legal
	//
	for(i = pFirst; i != pLast->pPrior; i = i->pNext)
		for(j = pLast; j != i; j = j->pPrior)
			_Swap(j, j->pPrior);

	//Reseta o elemento corrente
	ResetCurrent();
}


/******************************************************
 * private TAbstractList::_ToNext()
 ******************************************************
 * Aponta para o pr�ximo elemento e atualiza a posi��o
 ******************************************************/
template <typename T> bool TAbstractList<T>::_ToNext()
{
	//Retorna o status dessa ultima tentativa de movimenta��o
	
	//Verifica se � poss�vel mover p/ o proximo
	if(pCurrent->pNext != NULL)
	{
		//Move pro proximo
		PosCorrente++;
		pCurrent = pCurrent->pNext;
		
		return true;
	}

	return false;
}


/******************************************************
 * private TAbstractList::_ToPrior()
 ******************************************************
 * Aponta para o elemento anterior e atualiza a posi��o
 ******************************************************/
template <typename T> bool TAbstractList<T>::_ToPrior()
{
	//Retorna o status dessa ultima tentativa de movimenta��o

	//Verifica se � poss�vel mover p/ o anterior
	if(pCurrent->pPrior != NULL)
	{
		//Move pro anterior
		PosCorrente--;
		pCurrent = pCurrent->pPrior;

		return true;
	}

	return false;
}


/******************************************************
 * TAbstractList::MoveNext()
 ******************************************************
 * Aponta para o proximo elemento da lista
 ******************************************************/
template <typename T> int TAbstractList<T>::MoveNext()
{
	//J� est� resetado
	if(pCurrent == NULL)
		//Estou certo disso (especifica��o)
		return MoveFirst();

	//Ao tentar passar do ultimo, reseta
	if(! _ToNext() )
		ResetCurrent();

	return PosCorrente;
}


/******************************************************
 * TAbstractList::MovePrior()
 ******************************************************
 * Aponta para o elemento anterior da lista
 ******************************************************/
template <typename T> int TAbstractList<T>::MovePrior()
{
	//J� est� resetado
	if(pCurrent == NULL)
		//Estou certo disso (especifica��o)
		return MoveLast();

	//Ao tentar ir para anter do primeiro, reseta
	if(! _ToPrior() )
		ResetCurrent();

	return PosCorrente;
}


/******************************************************
 * TAbstractList::GoTo()
 ******************************************************
 * Aponta para o elemento na posi��o "i" da lista
 ******************************************************/
template <typename T> int TAbstractList<T>::GoTo(int i)
{
	//Fora dos limites
	if(! (i >= 0 && i <= Size ) )
		throw new TEOutOfBounds("TAbstractList::GoTo");

	//Movendo para alguma posicao de uma lista vazia
	if(Size == 0 || i == PosCorrente)
		return PosCorrente;

	//
	//Otimiza a movimenta��o, restringindo o dom�nio
	//para fazer um balanceamento das compara��es
	//

	//Primeira metade
	if(i <= Size / 2) {
		for(MoveFirst(); i > 0; i--)
			_ToNext();
	}
	
	//Segunda metade
	else {
		for(i = Size - i, MoveLast(); i > 1; i--)
			_ToPrior();
	}

	return PosCorrente;
}


/******************************************************
 * protected TAbstractList<T>::Insert()
 ******************************************************
 * Insere um elemento na posi��o `i` da lista 
 ******************************************************/

/******************************************************
 *                   CHANGELOG                        *
 ******************************************************
 * [04/05/2005 01:00] Iniciada                        *
 * [05/05/2005 23:28] Finalizada ver. 0.5             *
 ******************************************************/
template <class T> int TAbstractList<T>::Insert(T* data, int i=0)
{
	Node *prior, *pNew;

	//Inserindo u melemento nulo
	if(data == NULL)
		throw new TENullElement("TAbstractList::Insert");

	//Movimenta
	GoTo(i);

	//Define o n� anterior
	prior = (pCurrent == NULL) ? pCurrent : pCurrent->pPrior;

	//Cria o novo n�
	pNew = _CreateNode(data, prior, pCurrent);

	/****************************************
	* Essa ordem de avalia��o � importante
	****************************************/
	
	//Ultimo elemento
	if(i == Size) {
		pNew->pPrior = pCurrent;
		pNew->pNext = NULL;

		pLast = pNew;	//Atualiza o ultimo
	}
	else {
		pNew->pPrior = pCurrent->pPrior;
		pCurrent->pPrior = pNew;
		//pNew->pNext = pCurrent (por definicao)
	}

	//Primeiro elemento
	if(i == 0) {
		pNew->pPrior = NULL;
		//pNew->pNext = pCurrent (por definicao)

		pFirst = pNew;	//Atualiza o primeiro
	}
	else {
		pNew->pPrior->pNext = pNew;
	}

	//O elemento sendo inserido nao � o unico
	if(pCurrent != NULL) {
		//Primeiro
		if(i == 0)
		pCurrent->pPrior = pNew;

		//Ultimo
		if(i == Size)
		pCurrent->pNext = pNew;
	}

	//Atualiza o elemento corrente
	pCurrent = pNew;
	PosCorrente = i;
	
	//Atualiza o tamanho
	Size++;

#ifdef DEBUG
	//Invariante
	INVARIANTE(data == Get(i), "data == Get(i) | from TAbstractList::Insert ")
#endif

	//Retorna a posi��o
	return i;
}



/******************************************************
 * protected TAbstractList<T>::Del()
 ******************************************************
 * Remove um elemento de uma posi��o espec�fica
 ******************************************************/
 
/******************************************************
 *                   CHANGELOG                        *
 ******************************************************
 * [12/05/2005 00:15]	Finalizada ver. beta          *
 ******************************************************/
template <class T> int TAbstractList<T>::Del(int posicao)
{
	//Organiza a lista para a remo��o e obtem o pCurrent
	Node* pProximoCurrent = _PrepareDel(posicao);

	//Remove o node da lista
	delete pCurrent;

	//Atualiza o pCurrent (evita um novo GoTo)
	pCurrent = pProximoCurrent;

	//Decrementa o tamanho
	Size--;

	return PosCorrente;
}


/******************************************************
 * protected TAbstractList::DelAll()
 ******************************************************
 * Remove todos os elementos da lista
 ******************************************************/

 /*****************************************************
 *                   CHANGELOG                        *
 ******************************************************
 * [12/05/2005 00:21] Finalizada versao beta.         *
 ******************************************************/
template <class T> void TAbstractList<T>::DelAll()
{
	//Preferi utilizar um loop em conjunto com Del() por motivos de:
	//1) Eleg�ncia
	//2) A complexidade continua sendo O(n)

	// Vai para o primeiro
	MoveFirst();	//O(1)

	// n vezes
	while(pCurrent != NULL)
		Del(0);		// Remove o primeiro
				// O(1)
}

/******************************************************
 * protected TAbstractList<T>::Kill()
 ******************************************************
 * Destr�i um elemento da lista
 ******************************************************/
template <class T> int TAbstractList<T>::Kill(int posicao)
{
	//Organiza a lista para a remo��o e obtem o pCurrent
	Node* pProximoCurrent = _PrepareDel(posicao);

	//Remove o elemento da lista
//	BUG 7/Mai/08 - Nao pode dar um free em um ponteiro criado com new
//	free(pCurrent->Data);
	delete pCurrent->Data;
	delete pCurrent;

	//Atualiza o pCurrent (evita um novo GoTo)
	pCurrent = pProximoCurrent;

	//Decrementa o tamanho
	Size--;

	return PosCorrente;
}

/******************************************************
 * protected TAbstractList<T>::DelAll()
 ******************************************************
 * Destr�i todos os elementos da lista
 ******************************************************/
template <class T> void TAbstractList<T>::KillAll()
{
	//Preferi utilizar um loop em conjunto com Del() por motivos de:
	//1) Eleg�ncia
	//2) A complexidade continua sendo O(n)

	// Vai para o primeiro
	MoveFirst();		// O(1)

	// n vezes
	while(pCurrent != NULL)
		Kill(0);	// Remove o primeiro
				// O(1)
}

/******************************************************
 * protected TAbstractList<T>::Search()
 ******************************************************
 * Busca um elemento na lista
 ******************************************************/
template <class T> int TAbstractList<T>::Search(T* procurado)
{
	//Pocurando por u melemento nulo
	if(procurado == NULL)
		throw new TENullElement("TAbstractList::Search");

	//Varre todos os elementos
	MoveFirst();
	while( pCurrent != NULL )
	{
		//Encontrou?
		if( *procurado == *(pCurrent->Data) ) { break; }

		//Proximo...
		MoveNext();
	}

	//Retorna o elemento encontrado
	return PosCorrente;
}

/******************************************************
 * protected TAbstractList<T>::Sort()
 ******************************************************
 * Ordena a lista
 ******************************************************/
template <class T> void TAbstractList<T>::Sort()
{
	//Lista vazia
	if(Size == 0)
	{
		ResetCurrent();
		return;
	}

	//Array para ordena��o
	Node* Espelho[Size];
	register int i;

	//Armazena no array
	for(i = MoveFirst(); i > -1; i = MoveNext())
	{
		Espelho[i] = pCurrent;
	}

	//Ordena com o quicksort da bibliotecapadrao C
	qsort(Espelho, Size, sizeof(Node *), _Compara<T>);

	//Devolve pra lista
	pCurrent = pFirst = Espelho[0];
	pCurrent->pPrior = NULL;
	for(i = 0; i < Size - 1; i++)	//Talvez esse moveNext()
	{
		pCurrent->pNext = Espelho[i+1];
		pCurrent->pNext->pPrior = pCurrent;
		pCurrent = pCurrent->pNext;
	}

	pLast = Espelho[Size-1];
	pLast->pNext = NULL;

	//Reseta o elemento corrente
	ResetCurrent();
}


#ifdef DEBUG
/******************************************************
 * TAbstractList::Dump()
 ******************************************************
 * Exibe os dados do objeto
 ******************************************************/

 /*****************************************************
 *                   CHANGELOG                        *
 ******************************************************
 * [12/05/2005 00:15] Corrigida para n�o interferir   *
 * nos atributos do objeto                            *
 ******************************************************/
template <class T> void TAbstractList<T>::Dump()
{
	int i = 0;
	Node *nodeAtual = NULL;

	std::cerr << endl
			<< "+----------[AbstractList]----------+" << std::endl
			<< "| pFirst \t = " << pFirst 	<< std::endl	
			<< "| pCurrent 	 = " << pCurrent 	<< std::endl
			<< "| pLast \t = " << pLast 	<< std::endl
			<< "| PosCorrente \t = " << PosCorrente << std::endl
			<< "| Size \t\t = " << Size 		<< std::endl
			<< "+----------------------------------+" << std::endl << std::endl;
	
	if(Size > 0){
		std::cerr << "[ELEMENTOS]" << endl;

		nodeAtual = pFirst;
		
		//Percorre cada elemento e imprime-o
		do {
			std::cerr	<< "[" << i << "]\t[" << nodeAtual << "]\t" << *(nodeAtual->Data)  << std::endl
					<< "pPrior \t[" << nodeAtual->pPrior << "]" << std::endl
					<< "Data \t[" << nodeAtual->Data << "]" << std::endl
					<< "pNext \t[" << nodeAtual->pNext << "]" << std::endl << std::endl;

			
			i++;
		}
		while(NULL != (nodeAtual = nodeAtual->pNext));
	}
}
#endif

#endif
