/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TEngineTQueue_H
#define TEngineTQueue_H

#include "TEngine.h"
#include "TQueue.h"

/**
 * \brief Engine referente à TQueue
 *
 * Essa engine trata o arquivo de INPUT e de SEARCH e manipula
 * uma estrutura do tipo TQueue diretamente.
 */
template <class T> class TEngineTQueue : public virtual TEngine<T> {
	public:
		TQueue<T> *Fila;		/**< Estrutura do tipo Pilha que será utilizada para armazenar os elementos. */

		/**
		 * Construtor
		 * \param f Estrutura que será gerenciada pela engine
		 */
		TEngineTQueue(TQueue<T> *f) : Fila(f) { };

		//Métodos virtuais sendo implementados nas classes filhas
		void clean() { delete Fila; };
		void InsereElemento(int posicao, T* elemento) { Fila->Append(elemento); };
		T* ProcuraElemento(T* elemento) { int posicao; return (-1 != (posicao = Fila->Search(elemento)) ) ? Fila->Get(posicao) : NULL; };

#ifdef DEBUG
		//Métodos de debugging
		void dump() { Fila->Dump(); };
#endif

};

#endif
