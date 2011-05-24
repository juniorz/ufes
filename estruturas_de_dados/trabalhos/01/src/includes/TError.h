/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
#ifndef TError_H
#define TError_H

#include <iostream>

/**
 * @brief Classe gen�rica de tratamento de erro.
 * A classe TEGeneralError trata as exce��es de maneira gen�rica, 
 * amazenando informa��es sobre a exce��o em s� e as circunst�ncias
 * que a causaram.
 */
class TEGeneralError {
	public:
		/**************
		 * Construtor
		 **************/
		TEGeneralError() : GeradorErro(""), MensagemErro("") {};

		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 * @param mensagem Mensagem de erro
		 */		
		TEGeneralError(const char* gerador, const char* mensagem) : GeradorErro(gerador), MensagemErro(mensagem) {};

		/**
		 * Destrutor
		 */
		~TEGeneralError() { GeradorErro = NULL; MensagemErro = NULL;};

		/**
		 * @brief Imprime o erro.
		 *
		 * Imprime o conte�do do erro no formato: "[GeradorErro] ~> MensagemErro" para a sa�da padr�o de erro
		 */
		void toString() {std::cerr << "[" << GeradorErro << "] ~> " << MensagemErro << std::endl;};
		
		/**
		 * @brief Finaliza o programa e exibe o erro
		 *
		 * Imprime o conte�do do erro e aborta o programa com o c�digo de saida @c cod
		 * \param cod C�digo de sa�da do programa
		 */
		void Exit(int cod) { toString(); exit(cod); };

	protected:
		const char *GeradorErro;	/**< Nome do M�todo que gerou a exce��o */
		const char *MensagemErro;	/**< Mensagem de erro que descreve a exce��o gerada */

		/**
		 * @brief Define o m�todo que gerou o erro.
		 *
		 * @param gerador M�todo que gerou o erro
		 * @see SetMensagem
		 */
		void SetGerador(const char* gerador) { GeradorErro = gerador; };
		
		/**
		 * @brief Define a mensagem de erro
		 *
		 * @param mensagem Mensagem de erros
		 * @see SetGerador
		 */
		void SetMensagem(const char* mensagem) { MensagemErro = mensagem; };
};

/**
 * @brief Exce��o "Out of Bounds"
 *
 * Indica que uma a��o excedeu os limites da lista.
 */
class TEOutOfBounds : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 */
		TEOutOfBounds(const char* gerador) { SetGerador(gerador); SetMensagem("Index Out of Bounds"); };
};

/**
 * @brief Exce��o "Null Element"
 *
 * Indica que uma a��o tentou manipular um elemento nulo (que aponta para um ponteiro n�o definido).
 */
class TENullElement : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 */
		TENullElement(const char* gerador) { SetGerador(gerador); SetMensagem("Tried to manipulate a NULL element"); };
};

/**
 * @brief Exce��o "Stack Underflow"
 *
 * Indica que a pilha sofreu um Underflow
 */
class TEStackUnderflow : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 */
		TEStackUnderflow(const char* gerador) { SetGerador(gerador); SetMensagem("Stack Underflow"); };
};

/**
 * @brief Exce��o "Invalid Hash Function"
 *
 * Indica que de alguam maneira a fun��o que gera a chave Hash n�o funcionou como o esperado.
 */
class TEInvalidHashFunction : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 */
		TEInvalidHashFunction(const char* gerador) { SetGerador(gerador); SetMensagem("Invalid Hash Function"); };
};

/**
 * @brief Exce��o "Invariant"
 *
 * Indica que um Invariante foi violado. Utilizada apenas em tempo de desenvolvimento das classes
 */
class TEInvariant : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador M�todo que gerou a exce��o
		 */
		TEInvariant(const char* gerador) { SetGerador(gerador); SetMensagem("Invariant Error"); };
};

#endif
