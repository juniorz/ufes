/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TEngineTStack_H
#define TEngineTStack_H

#include "TEngine.h"
#include "TStack.h"

/**
 * \brief Engine referente à TList
 *
 * Essa engine trata o arquivo de INPUT e de SEARCH e manipula
 * uma estrutura do tipo TList diretamente.
 */
template <class T> class TEngineTStack : public virtual TEngine<T> {
	public:
		TStack<T> *Pilha; /**< Estrutura do tipo Pilha que será utilizada para armazenar os elementos. */

		/**
		 * Construtor
		 * \param p Estrutura que será gerenciada pela engine
		 */
		TEngineTStack(TStack<T> *p) : Pilha(p) { };

		//Métodos virtuais sendo implementados nas classes filhas
		void clean() { delete Pilha; };
		void InsereElemento(int posicao, T* elemento) { Pilha->Push(elemento); };
		T* ProcuraElemento(T* elemento) { int posicao; return (-1 != (posicao = Pilha->Search(elemento)) ) ? Pilha->Get(posicao) : NULL; };

#ifdef DEBUG
		//Métodos de TESTE
		void dump() { Pilha->Dump(); };
#endif

};

#endif
