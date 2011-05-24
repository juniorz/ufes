/*******************************************************
 *              Estrutura de Dados                     *
 *******************************************************
 * Trabalho 1                                          *
 * Professor: Fabr�cio V. Matos                        *
 *******************************************************
 * Aluno: Reinaldo de Souza Junior                     *
 * Licensa: GPL vs2.0 [ veja /docs/LICENSE.txt ]       *
 *******************************************************/

#ifndef TPessoa_H
#define TPessoa_H

/**
 * \brief Pessoa gen�rica para exemplificar a aplica��o das estruturas de dados
 */
class Pessoa {
	private:
		int codPessoa;		/**< C�digo da Pessoa */
		char strNome[255];	/**< Nome da Pessoa */

	public:
		//Construtor
		Pessoa() : codPessoa(-1) { strcpy(strNome, ""); };

		//Destrutor
		~Pessoa() { delete strNome; };

		/**
		 * \brief Obt�m o nome da pessoa
		 * \return Nome da Pessoa
		 */
		//Obt�m o nome da pessoa
		char *GetNome() { return strNome; };
		
		/**
		 * \brief Obt�m o C�digo da pessoa
		 * \return C�digo da Pessoa
		 */
		//Obt�m o c�digo da pessoa
		int GetCodigo() { return codPessoa; };

		/**
		 * \brief Define o nome da pessoa
		 * \param nome Nome da Pessoa
		 */
		//Define o nome da pessoa
		void SetNome(char *nome) { strncpy(strNome, nome, 255); };
		
		/**
		 * \brief Define o C�digo da pessoa
		 * \param codigo C�digo da Pessoa
		 */
		//Define o c�digo da pessoa
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
		 * \brief Faz a convers�o de Pessoa para (int)
		 */
		//Faz a convers�o de Pessoa para (int)
		operator const int() const { return codPessoa; };
		
		/**
		 * \brief Faz a convers�o de Pessoa para (float)
		 */
		//Faz a convers�o de Pessoa para (float)
		operator const float() const { return (float) codPessoa; };
};

#endif
