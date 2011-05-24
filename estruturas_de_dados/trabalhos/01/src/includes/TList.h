/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TList_H
#define TList_H

#include "TAbstractList.h"

/**
 * \brief Lista
 *
 * Estrutura de Lista
 *
 * \version	1.0
 * \author	Reinaldo de Souza Junior <juniorz@gmail.com.br>
 * \date	05/2005
 */
template <class T> class TList : public TAbstractList<T> {
	public:
		/**********************************************
		 * Count()
		 **********************************************
		 * Retorna o numero de elementos da lista
		 **********************************************/
		int Count() { return TAbstractList<T>::Count(); };

		/**********************************************
		 * Get()
		 **********************************************
		 * Retorna um elemento de uma posição específica
		 **********************************************/
		T* Get(int pos) { return TAbstractList<T>::Get(pos); };

		/**********************************************
		 * GetCurrent()
		 **********************************************
		 * Retorna o elemento corrente
		 **********************************************/
		T* GetCurrent() { return TAbstractList<T>::GetCurrent(); };

		/**********************************************
		 * Insert()
		 **********************************************
		 * Insere um elemento em uma posição específica
		 **********************************************/
		int Insert(T* data, int pos) { return TAbstractList<T>::Insert(data, pos); };

		/**********************************************
		 * Del()
		 **********************************************
		 * Remove um elemento da lista
		 **********************************************/
		int Del(int pos) { return TAbstractList<T>::Del(pos); };

		/**********************************************
		 * DelAll()
		 **********************************************
		 * Remove todos os elemento da lista
		 **********************************************/
		void DelAll() { TAbstractList<T>::DelAll(); };

		/**********************************************
		 * Kill()
		 **********************************************
		 * Destrói um elemento da lista
		 **********************************************/
		int Kill(int pos) { return TAbstractList<T>::Kill(pos); };

		/**********************************************
		 * KillAll()
		 **********************************************
		 * Destrói todos os elemento da lista
		 **********************************************/
		void KillAll() { TAbstractList<T>::KillAll(); };

		/**********************************************
		 * MoveFirst()
		 **********************************************
		 * Aponta o elemento corrente para o primeiro elemento da lista
		 **********************************************/
		int MoveFirst() { return TAbstractList<T>::MoveFirst(); };

		/**********************************************
		 * MoveNext()
		 **********************************************
		 * Aponta o elemento corrente para próximo elemento da lista
		 **********************************************/
		int MoveNext() { return TAbstractList<T>::MoveNext(); };

		/**********************************************
		 * MovePrior()
		 **********************************************
		 * Aponta o elemento corrente para o elemento anterior da lista
		 **********************************************/
		int MovePrior() { return TAbstractList<T>::MovePrior(); };

		/**********************************************
		 * MoveLast()
		 **********************************************
		 * Aponta o elemento corrente para o último elemento da lista
		 **********************************************/
		int MoveLast() { return TAbstractList<T>::MoveLast(); };

		/**********************************************
		 * GoTo()
		 **********************************************
		 * Aponta o elemento corrente para para o elemento na posição "posicao"
		 **********************************************/
		int GoTo(int pos) { return TAbstractList<T>::GoTo(pos); };

		/**********************************************
		 * ResetCurrent()
		 **********************************************
		 * Reseta o elemento corrente da lista
		 **********************************************/
		void ResetCurrent() { TAbstractList<T>::ResetCurrent(); };

		/**********************************************
		 * Search()
		 **********************************************
		 * Busca um elemento na lista
		 **********************************************/
		int Search(T* procurado) { return TAbstractList<T>::Search(procurado); };

		/**********************************************
		 * Sort()
		 **********************************************
		 * Ordena a lista
		 **********************************************/
		void Sort() { TAbstractList<T>::Sort(); };
};

#endif
