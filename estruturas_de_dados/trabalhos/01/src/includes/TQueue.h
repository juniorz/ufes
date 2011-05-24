/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
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
		 * \param data Ponteiro para um elemento que será inserido na fila
		 * \return Posição do elemento inserido na fila
		 *
		 * \throw TENullElement* caso @c data seja nulo (não aponta para nada). @b Veja: TENullElement
		 * @see TEGeneralError
		 */
		int Append(T* data) { return TAbstractList<T>::Insert(data, Count()); };

		/**********************************************
		 * Get()
		 **********************************************
		 * Retorna um elemento de uma posição específica
		 **********************************************/
		/**
		 * \brief Retorna um elemento de uma posição específica.
		 *
		 * Retorna um ponteiro para elemento da lista que ocupa a posição @c pos
		 *
		 * \param pos Posição do elemento que se deseja obter
		 * \return Ponteiro associado ao nó que ocupa a posição @c pos na lista.
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
		 * \return Ponteiro associado ao nó que ocupa a posição corrente na lista.
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
		 * \return Posição do elemento corrente da lista (usualmente retorna 0)
		 *
		 * @b Complexidade: @f$O(1)@f$
		 */
		int MoveFirst() { return TAbstractList<T>::MoveFirst(); };

		/**********************************************
		 * MoveNext()
		 **********************************************
		 * Aponta o elemento corrente para próximo elemento da lista
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para próximo elemento da lista
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
		 * Aponta o elemento corrente para o último elemento da lista
		 **********************************************/
		/**
		 * \brief Aponta o elemento corrente para o último elemento da lista.
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
		 * Busca o primeiro elemento da fila que seja igual a "procurado" e retorna sua posição.
		 *
		 * \param procurado Elemento a ser buscado na fila
		 * \return Posição do elemento, caso tenha encontrado algum, ou -1 caso o elemento não tenha sido encontrado.
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
		 * \return Posição do elemento corrente da fila após a remoção.
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
		 * Destrói o primeiro elemento da fila
		 **********************************************/
		/**
		 * \brief Destrói o primeiro elemento da fila
		 *
		 * Libera a memória ocupada pelo primeiro elemento da fila e retira-o.
		 * Após a chamada desse método o elemento, qualquer referência ao elemento destruído será inválida.
		 *
		 * \return Posição do elemento corrente da fila.
		 *
		 * \b Complexidade: @f$O(n)@f$
		 */
		int Kill() { return TAbstractList<T>::Kill(0); };
		
		/**********************************************
		 * KillAll()
		 **********************************************
		 * Destrói todos os elemento da pilha
		 **********************************************/
		/**
		 * \brief Destrói todos os elemento da pilha
		 *
		 * @b Complexidade: @f$O(n)@f$
		 */
		void KillAll() { TAbstractList<T>::KillAll(); };
};

#endif
