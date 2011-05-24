/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
 /**
 * \mainpage Estrutura de Dados - Trabalho 1
 * Ciência da Computação - UFES 2005/01
 *
 * \section descricao Descrição do trabalho
 * Esse trabalho tem como objetivo apresentar uma implementação das seguintes estruturas lineares:
 * - \link TQueue Fila \endlink
 * - \link TList Lista \endlink
 * - \link TSortedList Lista Ordenada \endlink
 * - \link TStack Pilha \endlink
 * - \link THashTable Tabela Hash \endlink
 *
 * Para tal, foi desenvolvido um aplicativo para explorar essas estruturas de maneira genérica.
 *
 * A linguagem adotada para a implementação do trabalho foi o @b C++, utilizando o paradigma de programação orientada a objetos e o recurso de @e templates.
 * Esta documentação foi gerada com o auxílio da ferramenta Doxygen < http://www.doxygen.org >
 *
 * Todo o trabalho é disponibilizado sob os termos da licensa @b GPL. ( veja docs/LICENSE )
 *
 * \subsection autor Autor
 * Reinaldo de Souza Junior < juniorz@phpbb.com.br >
 *
 * \subsection professor Professor
 * Fabrício V. Matos < fabricio@qualidata.com.br >
 */

#include "debug.h"
 
#include <iostream>
#include <fstream> 
using namespace std;

#include "Pessoa.h"
#include "TApplication.h"
