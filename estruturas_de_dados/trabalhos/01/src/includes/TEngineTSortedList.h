/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TEngineTSortedList_H
#define TEngineTSortedList_H

#include "TEngine.h"
#include "TSortedList.h"

/**
 * \brief Engine referente � TSortedList
 *
 * Essa engine trata o arquivo de INPUT e de SEARCH e manipula
 * uma estrutura do tipo TSortedList diretamente.
 *
 */
template <class T> class TEngineTSortedList : public virtual TEngine<T> {
	public:
		TSortedList<T> *Lista;		/**< Estrutura do tipo Lista Ordenada que ser� utilizada para armazenar os elementos. */

		/**
		 * Construtor
		 * \param l Estrutura que ser� gerenciada pela engine
		 */
		TEngineTSortedList(TSortedList<T> *l) : Lista(l) { };

		//M�todos virtuais sendo implementados nas classes filhas
		void clean() { delete Lista; };
		void InsereElemento(int posicao, T* elemento){ Lista->Insert(elemento); };
		T* ProcuraElemento(T* elemento) { int posicao; return (-1 != (posicao = Lista->Search(elemento)) ) ? Lista->Get(posicao) : NULL; };

#ifdef DEBUG
		//M�todos de debugging
		void dump() { Lista->Dump(); };
#endif

};

#endif
