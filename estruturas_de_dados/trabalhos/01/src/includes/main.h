/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
 /**
 * \mainpage Estrutura de Dados - Trabalho 1
 * Ci�ncia da Computa��o - UFES 2005/01
 *
 * \section descricao Descri��o do trabalho
 * Esse trabalho tem como objetivo apresentar uma implementa��o das seguintes estruturas lineares:
 * - \link TQueue Fila \endlink
 * - \link TList Lista \endlink
 * - \link TSortedList Lista Ordenada \endlink
 * - \link TStack Pilha \endlink
 * - \link THashTable Tabela Hash \endlink
 *
 * Para tal, foi desenvolvido um aplicativo para explorar essas estruturas de maneira gen�rica.
 *
 * A linguagem adotada para a implementa��o do trabalho foi o @b C++, utilizando o paradigma de programa��o orientada a objetos e o recurso de @e templates.
 * Esta documenta��o foi gerada com o aux�lio da ferramenta Doxygen < http://www.doxygen.org >
 *
 * Todo o trabalho � disponibilizado sob os termos da licensa @b GPL. ( veja docs/LICENSE )
 *
 * \subsection autor Autor
 * Reinaldo de Souza Junior < juniorz@phpbb.com.br >
 *
 * \subsection professor Professor
 * Fabr�cio V. Matos < fabricio@qualidata.com.br >
 */

#include "debug.h"
 
#include <iostream>
#include <fstream> 
using namespace std;

#include "Pessoa.h"
#include "TApplication.h"
