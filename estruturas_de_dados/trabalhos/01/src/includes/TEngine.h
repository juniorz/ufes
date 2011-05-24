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
 *                   CHANGELOG                         *
 *******************************************************
 * [25/05/2005 01:20] Foi criado o m�todo virtual      *
 * dump() por motivos de debugging                     *
 *******************************************************/

#ifndef TEngine_H
#define TEngine_H

/**
 * \brief Engine abstrata do programa
 *
 * Classe abstrata para definir a "engine" do programa principal facilitando a l�gica do programa
 */
template <class T> class TEngine
{
	public:
		/**
		 * \brief Faz a limpeza dos objetos
		 *
		 * Tem o objetivo de funcionar como um destrutor
		 */
		virtual void clean() = 0;
		
		/**
		 * \brief Insere um elemento na estrutura
		 *
		 * Insere o elemento @c elemento na posicao @c posicao
		 * Esse m�todo � chamado a cada linha lida do arquivo de INPUT
		 * e � respons�vel pela inser��o de cada elemento na estrutura em quest�o
		 * \param posicao Posi��o onde o elemento ser� inserido
		 * \param elemento O elemento que ser� inserido na lista
		 */
		virtual void InsereElemento(int posicao, T* elemento) = 0;

		/**
		 * \brief Procura um elemento na estrutura
		 *
		 * Retorna a posicao do primeiro elemento iagual a @c elemento existente na lista
		 * Esse m�todo � chamado a cada linha lida do arquivo de SEARCH
		 * e � respons�vel pela busca de cada elemento na estrutura em quest�o
		 * \param elemento O elemento que ser� procurado
		 * \return Ponteiro para o elemento encontrado
		 */
		virtual T* ProcuraElemento(T* elemento) = 0;

#ifdef DEBUG
		virtual void dump() = 0;
#endif

};

#endif
