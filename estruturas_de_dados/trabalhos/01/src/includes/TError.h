/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/
 
#ifndef TError_H
#define TError_H

#include <iostream>

/**
 * @brief Classe genérica de tratamento de erro.
 * A classe TEGeneralError trata as exceções de maneira genérica, 
 * amazenando informações sobre a exceção em sí e as circunstâncias
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
		 * @param gerador Método que gerou a exceção
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
		 * Imprime o conteúdo do erro no formato: "[GeradorErro] ~> MensagemErro" para a saída padrão de erro
		 */
		void toString() {std::cerr << "[" << GeradorErro << "] ~> " << MensagemErro << std::endl;};
		
		/**
		 * @brief Finaliza o programa e exibe o erro
		 *
		 * Imprime o conteúdo do erro e aborta o programa com o código de saida @c cod
		 * \param cod Código de saída do programa
		 */
		void Exit(int cod) { toString(); exit(cod); };

	protected:
		const char *GeradorErro;	/**< Nome do Método que gerou a exceção */
		const char *MensagemErro;	/**< Mensagem de erro que descreve a exceção gerada */

		/**
		 * @brief Define o método que gerou o erro.
		 *
		 * @param gerador Método que gerou o erro
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
 * @brief Exceção "Out of Bounds"
 *
 * Indica que uma ação excedeu os limites da lista.
 */
class TEOutOfBounds : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador Método que gerou a exceção
		 */
		TEOutOfBounds(const char* gerador) { SetGerador(gerador); SetMensagem("Index Out of Bounds"); };
};

/**
 * @brief Exceção "Null Element"
 *
 * Indica que uma ação tentou manipular um elemento nulo (que aponta para um ponteiro não definido).
 */
class TENullElement : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador Método que gerou a exceção
		 */
		TENullElement(const char* gerador) { SetGerador(gerador); SetMensagem("Tried to manipulate a NULL element"); };
};

/**
 * @brief Exceção "Stack Underflow"
 *
 * Indica que a pilha sofreu um Underflow
 */
class TEStackUnderflow : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador Método que gerou a exceção
		 */
		TEStackUnderflow(const char* gerador) { SetGerador(gerador); SetMensagem("Stack Underflow"); };
};

/**
 * @brief Exceção "Invalid Hash Function"
 *
 * Indica que de alguam maneira a função que gera a chave Hash não funcionou como o esperado.
 */
class TEInvalidHashFunction : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador Método que gerou a exceção
		 */
		TEInvalidHashFunction(const char* gerador) { SetGerador(gerador); SetMensagem("Invalid Hash Function"); };
};

/**
 * @brief Exceção "Invariant"
 *
 * Indica que um Invariante foi violado. Utilizada apenas em tempo de desenvolvimento das classes
 */
class TEInvariant : public TEGeneralError {
	public:
		/**
		 * Construtor
		 * @param gerador Método que gerou a exceção
		 */
		TEInvariant(const char* gerador) { SetGerador(gerador); SetMensagem("Invariant Error"); };
};

#endif
