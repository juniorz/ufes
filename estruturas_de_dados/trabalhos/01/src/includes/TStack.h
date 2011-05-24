/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TStack_H
#define TStack_H

#include "TAbstractList.h"
#include "TError.h"

/**
 * Lista genérica. Implementa listas genéricas.
 */
template <class T> class TStack : public TAbstractList<T> {
	public:
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
		 * Top()
		 **********************************************
		 * Retorna o dado do elemento do topo da pilha
		 **********************************************/
		/**
		 * \brief Retorna o dado do elemento do topo da pilha
		 *
		 * \return Dado do elemento do topo da pilha
		 */
		T* Top() { TAbstractList<T>::MoveFirst(); return TAbstractList<T>::GetCurrent(); };

		/**********************************************
		 * Base()
		 **********************************************
		 * Retorna o dado do elemento da base da pilha
		 **********************************************/
		/**
		 * \brief Retorna o dado do elemento da base da pilha
		 *
		 * \return Dado do elemento da base da pilha
		 */
		T* Base() { TAbstractList<T>::MoveLast(); return TAbstractList<T>::GetCurrent(); };

		/**********************************************
		 * Pop()
		 **********************************************
		 * Desempilha um elemento
		 **********************************************/
		/**
		 * \brief Desempilha um elemento
		 *
		 * Remove o elemento do topo da pilha e retorna-o
		 *
		 * \return Dado do elemento do topo da pilha
		 *
		 * \throw TEStackUnderflow* caso a pilha esteja vazia
		 * \see TEGeneralError
		 */
		T* Pop() { if(TAbstractList<T>::Count() == 0) { throw new TEStackUnderflow("TStack::Pop"); } T* retorno = Top(); TAbstractList<T>::Del(0); return retorno; };
		
		/**********************************************
		 * Push()
		 **********************************************
		 * Empilha um elemento
		 **********************************************/
		/**
		 * \brief Empilha um elemento
		 *
		 * Empilha um elemento no topo da pilha e retorna a posição do topo da pilha
		 *
		 * \param data Ponteiro para um elemento que será inserido na lista
		 * \return Posição do topo da Pilha
		 *
		 * \throw TENullElement* caso @c data seja nulo (não aponta para nada). @b Veja: TENullElement
		 * @see TEGeneralError
		 */
		int Push(T* data) { return TAbstractList<T>::Insert(data, 0); };

		/**********************************************
		 * Get()
		 **********************************************
		 * Retorna um elemento de uma posição específica
		 **********************************************/
		T* Get(int pos) {return TAbstractList<T>::Get(pos); };
		
		/**********************************************
		 * Search()
		 **********************************************
		 * Procura por um elemento
		 **********************************************/
		int Search(T* procurado) { return TAbstractList<T>::Search(procurado); } ;
		
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
