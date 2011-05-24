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
 * [24/05/2005 01:55]                                  *
 * Finalizado o m�todo TEngineTList<T>::processaInput  *
 *                                                     *
 * [25/05/2005 01:00]                                  *
 * Foi criado o m�todo dump() por motivos de debugging *
 *                                                     *
 * [30/05/2005 21:45]                                  *
 * Foram finalizados os testes com a estrutura TList   *
 *******************************************************/

#ifndef TEngineTList_H
#define TEngineTList_H

#include "TEngine.h"
#include "TList.h"

/**
 * \brief Engine referente � TList
 *
 * Essa engine trata o arquivo de INPUT e de SEARCH e manipula
 * uma estrutura do tipo TList diretamente.
 */
template <class T> class TEngineTList : public virtual TEngine<T> {
	public:
		TList<T> *Lista;		/**< Estrutura do tipo Lista que ser� utilizada para armazenar os elementos. */

		/**
		 * Construtor
		 * \param l Estrutura que ser� gerenciada pela engine
		 */
		TEngineTList(TList<T> *l) : Lista(l) { };

		//M�todos virtuais sendo implementados nas classes filhas
		void clean() { delete Lista; };
		void InsereElemento(int posicao, T* elemento) { Lista->Insert(elemento, posicao); } ;
		T* ProcuraElemento(T* elemento) { int posicao; return (-1 != (posicao = Lista->Search(elemento)) ) ? Lista->Get(posicao) : NULL; };

#ifdef DEBUG
		//M�todos de debugging
		void dump() { Lista->Dump(); };
#endif

};

#endif
