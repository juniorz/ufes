/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TQueue_H
#define TQueue_H

#include "TError.h"
#include "TAbstractList.h"

/**
 * \brief Fila
 *
 * Estrutura de Fila
 *
 * \version	1.0
 * \author	Reinaldo de Souza Junior <juniorz@gmail.com.br>
 * \date	05/2005
 */
template <class T> class TQueue : public TAbstractList<T> {
	public:
		/**********************************************
		 * Append()
		 **********************************************
		 * Insere um elemento no final da fila
		 **********************************************/
		/**
		 * \brief Insere um elemento no final da fila
		 *
		 * \param data Ponteiro para um elemento que ser� inserido na fila
		 * \return Posi��o do elemento inserido na fila
		 *
		 * \throw TENullElement* caso @c data seja nulo (n�o aponta para nada). @b Veja: TENullElement
		 * @see TEGeneralError
		 */
		int Append(T* data) { return TAbstractList<T>::Insert(data, Count()); };

		/**********************************************
		 * Get()
		 **********************************************
		 * Retorna um elemento de uma posi��o espec�fica
		 **********************************************/
		/**
		 * \brief Retorna um elemento de uma posi��o espec�fica.
		 *
		 * Retorna um ponteiro para elemento da lista que ocupa a posi��o @c pos
		 *
		 * \param pos Posi��o do elemento que se deseja obter
		 * \return Ponteiro associado ao n� que ocupa a posi��o @c pos na lista.
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		T* Get(int pos) { return TAbstractList<T>::Get(pos); };

		/**********************************************
		 * GetCurrent()
		 **********************************************
		 * Retorna o elemento corrente
		 **********************************************/
		/**
		 * \brief Retorna o elemento corrente da lista.
		 * \return Ponteiro associado ao n� que ocupa a posi��o corrente na lista.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		T* GetCurrent() { return TAbstractList<T>::GetCurrent(); };

		/**********************************************
		 * Count()
		 **********************************************
		 * Retorna o numero de elementos da pilha
		 **********************************************/
		/**
		 * Retorna o numero de elementos da pilha
		 * @see TAbstractList::Size
		 */
		int Count() { return TAbstractList<T>::Count(); };
		
		/**********************************************
		 * MoveFirst()
		 **********************************************
		 * Aponta o elemento corrente para o primeiro elemento da lista
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o primeiro elemento da lista.
		 *
		 * \return Posi��o do elemento corrente da lista (usualmente retorna 0)
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveFirst() { return TAbstractList<T>::MoveFirst(); };

		/**********************************************
		 * MoveNext()
		 **********************************************
		 * Aponta o elemento corrente para pr�ximo elemento da lista
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para pr�ximo elemento da lista
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveNext() { return TAbstractList<T>::MoveNext(); };

		/**********************************************
		 * MovePrior()
		 **********************************************
		 * Aponta o elemento corrente para o elemento anterior da lista.
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o elemento anterior da lista
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MovePrior() { return TAbstractList<T>::MovePrior(); };

		/**********************************************
		 * MoveLast()
		 **********************************************
		 * Aponta o elemento corrente para o �ltimo elemento da lista
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o �ltimo elemento da lista.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveLast() { return TAbstractList<T>::MoveLast(); };
		
		/**********************************************
		 * ResetCurrent()
		 **********************************************
		 * Reseta o elemento corrente da fila
		 **********************************************/
		/**
		 * \brief Reseta o elemento corrente da fila
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		void ResetCurrent() { TAbstractList<T>::ResetCurrent(); };
		
		/**********************************************
		 * Search()
		 **********************************************
		 * Busca um elemento na fila
		 **********************************************/
		/**
		 * \brief Busca um elemento na fila.
		 *
		 * Busca o primeiro elemento da fila que seja igual a "procurado" e retorna sua posi��o.
		 *
		 * \param procurado Elemento a ser buscado na fila
		 * \return Posi��o do elemento, caso tenha encontrado algum, ou -1 caso o elemento n�o tenha sido encontrado.
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int Search(T* procurado) { return TAbstractList<T>::Search(procurado); } ;
		
		/**********************************************
		 * Del()
		 **********************************************
		 * Remove o primeiro elemento da fila
		 **********************************************/
		/**
		 * \brief Remove o primeiro elemento da fila
		 *
		 * \return Posi��o do elemento corrente da fila ap�s a remo��o.
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		int Del() { return TAbstractList<T>::Del(0); };
		
		/**********************************************
		 * DelAll()
		 **********************************************
		 * Remove todos os elemento da pilha
		 **********************************************/
		/**
		 * \brief Remove todos os elemento da pilha
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void DelAll() { TAbstractList<T>::DelAll(); };

		/**********************************************
		 * Kill()
		 **********************************************
		 * Destr�i o primeiro elemento da fila
		 **********************************************/
		/**
		 * \brief Destr�i o primeiro elemento da fila
		 *
		 * Libera a mem�ria ocupada pelo primeiro elemento da fila e retira-o.
		 * Ap�s a chamada desse m�todo o elemento, qualquer refer�ncia ao elemento destru�do ser� inv�lida.
		 *
		 * \return Posi��o do elemento corrente da fila.
		 *
		 * \b Complexidade: @f$O(n)@f$
		 */
		int Kill() { return TAbstractList<T>::Kill(0); };
		
		/**********************************************
		 * KillAll()
		 **********************************************
		 * Destr�i todos os elemento da pilha
		 **********************************************/
		/**
		 * \brief Destr�i todos os elemento da pilha
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void KillAll() { TAbstractList<T>::KillAll(); };
};

#endif
