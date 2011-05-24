/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TEngineTHashTable_H
#define TEngineTHashTable_H

#include "TEngine.h"
#include "THashTable.h"

/**
 * \brief Engine referente � THashTable
 *
 * Essa engine trata o arquivo de INPUT e de SEARCH e manipula
 * uma estrutura do tipo THashTable diretamente.
 */
template <class T> class TEngineTHashTable : public virtual TEngine<T> {
	public:
		THashTable<T> *TabelaHash;		/**< Estrutura do tipo Lista que ser� utilizada para armazenar os elementos. */

		/**
		 * Construtor
		 * \param t Estrutura que ser� gerenciada pela engine
		 */
		TEngineTHashTable(THashTable<T> *t) : TabelaHash(t) { };

		//M�todos virtuais sendo implementados nas classes filhas
		void clean() { delete TabelaHash; };
		void InsereElemento(int posicao, T* elemento) { TabelaHash->Add(elemento); };
		T* ProcuraElemento(T* elemento) { return TabelaHash->Get(elemento); };

#ifdef DEBUG
		//M�todos de debugging
		void dump() { TabelaHash->Dump(); };
#endif

};

#endif
