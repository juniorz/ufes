/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabrício V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TPessoa_H
#define TPessoa_H

/**
 * \brief Pessoa genérica para exemplificar a aplicação das estruturas de dados
 */
class Pessoa {
	private:
		int codPessoa;		/**< Código da Pessoa */
		char strNome[255];	/**< Nome da Pessoa */

	public:
		//Construtor
		Pessoa() : codPessoa(-1) { strcpy(strNome, ""); };

		//Destrutor
		~Pessoa() { delete strNome; };

		/**
		 * \brief Obtém o nome da pessoa
		 * \return Nome da Pessoa
		 */
		//Obtém o nome da pessoa
		char *GetNome() { return strNome; };
		
		/**
		 * \brief Obtém o Código da pessoa
		 * \return Código da Pessoa
		 */
		//Obtém o código da pessoa
		int GetCodigo() { return codPessoa; };

		/**
		 * \brief Define o nome da pessoa
		 * \param nome Nome da Pessoa
		 */
		//Define o nome da pessoa
		void SetNome(char *nome) { strncpy(strNome, nome, 255); };
		
		/**
		 * \brief Define o Código da pessoa
		 * \param codigo Código da Pessoa
		 */
		//Define o código da pessoa
		void SetCodigo(int codigo) { codPessoa = codigo; };
		
		/**
		 * \brief Sobreescreve o operador @b >
		 */
		//Sobreescreve o operador >
		friend bool operator>(const Pessoa& a, const Pessoa& b) { return a.codPessoa > b.codPessoa; };

		/**
		 * \brief Sobreescreve o operador @b <
		 */
		//Sobreescreve o operador <
		friend bool operator<(const Pessoa& a, const Pessoa& b) { return a.codPessoa < b.codPessoa; };

		/**
		 * \brief Sobreescreve o operador @b ==
		 */
		//Sobreescreve o operador ==
		friend int operator==(const Pessoa& a, const Pessoa& b) { return a.codPessoa == b.codPessoa; };
		
		/**
		 * \brief Sobreescreve o operador @b >=
		 */
		//Sobreescreve o operador >=
		friend bool operator>=(const Pessoa& a, const Pessoa& b) { return a.codPessoa >= b.codPessoa; };
		
		/**
		 * \brief Sobreescreve o operador @b <=
		 */
		//Sobreescreve o operador <=
		friend bool operator<=(const Pessoa& a, const Pessoa& b) { return a.codPessoa <= b.codPessoa; };

		/**
		 * \brief Sobreescreve o operador @b << (para um stream de saida)
		 */
		//Sobreescreve o operador << (para um stream de saida)
		friend ostream& operator<<(ostream& out, const Pessoa& a) { out << a.codPessoa; out << " - "; out << a.strNome;  };
		
		/**
		 * \brief Faz a conversão de Pessoa para (int)
		 */
		//Faz a conversão de Pessoa para (int)
		operator const int() const { return codPessoa; };
		
		/**
		 * \brief Faz a conversão de Pessoa para (float)
		 */
		//Faz a conversão de Pessoa para (float)
		operator const float() const { return (float) codPessoa; };
};

#endif
