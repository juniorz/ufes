; -----------------------------------------------
; Segundo Trabalho de Linguagem de Montagem
; Ciência da Computação - 2005/01 - UFES
;
; Autor: Reinaldo Junior < juniorz [at] gmail [dot] com >
; 	 http://www.phpbb.com.br/portal/
; -----------------------------------------------
; Criado em: 15/06/2005
; Versão 1.0
; -----------------------------------------------
; Descrição:
; Esse arquivo contém as funções que definem
; o reconhecimento dos comandos e a entrega do
; controle à função do comando.
; -----------------------------------------------


; -----------------------------------------------
;               .:] Changelog [:.
; -----------------------------------------------
; 17/06/2005 21:01
; Criação do arquivo
; -----------------------------------------------

%include "includes/macros.inc"

; Torna disponivel aos outros modulos
global processa_arquivo
global processa_comando

; [trab2.o]
extern s_comando.ptComando
extern s_comando.ptFuncao
extern fimComandos


%ifdef DEBUG

	%include "util/asm_io.inc"
	
	; [std_io.o]
	extern print_z	

	section .data
		; Mensagem de erro
		str_erroComando db "Comando não reconhecido em: ", 0x00
%endif

; -----------------------------------------------
; [nome]  	processa_arquivo
; [descr] 	processa as linhas de um arquivo
; [param] 	descritor do arquivo a processar		(1)
; 		ptr para a funcao que processa cada linha	(2)
;		ptr para os parametros passados a 2		(3)
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [17/06/2005 - 02:15]
; Finaliza a versão 1.0 da função
;
; [17/06/2005 - 03:21]
; Versão 1.1
; Foi adicionado os tratamentos para o caso do buffer estourar
; (adotando o descarte de todo o restante do comando). Solucionado também o problema do ultimo 
; comando nao estar sinalizado com um 0x00
;
; [30/06/2005 - 22:22]
; versão 1.2
; Corrigido problema com o ultimo comando do arquivo. Nao estava inserindo o 0x00 corretamente caso o buffer nao esivesse estourado.
; -----------------------------------------------
processa_arquivo:
	ccc_begin 3				; Prepara o ambiente - 3 variaveis locais

	; Reserva espaço na pilha criando um buffer para a leitura das linhas do arquivo
	; Nesse ponto do trabalho eu descobri o poder da pilha (e comecei a me empolgar com a coisa, decidindo nao fazer NADA em C) ;-)
	mov	[varlocal(2)], dword esp	; Armazena os limites do buffer | varlocal(2) = fimBuffer
	sub	esp, 128			; 128 bytes

	push 	ecx				; Armazena ecx
	mov	ecx, dword esp			; ptr para o buffer
	sub	ecx, 4				; Aponta para a posicao correta
	mov	[varlocal(1)], ecx		; Aponta para o inicio do buffer também (fixo)

	push	eax				; Amazena os registradores
	push	ebx
	push	edx

	;
	; Agora possuo um buffer para jogar as linhas do arquivo
	;

	; Inicializa variaveis
	mov	ebx, [parametro(1)]		; Descritor do arquivo
	mov	edx, 1				; ler 1 byte


  .le_linha

	mov	[varlocal(3)], dword 0x00	; reseta o ptr para os parametros do comando

	
  .ler_byte

	; Le byte a byte
	macro_syscall 3

	; Leu algum byte (chegou ao fim do arquivo) ?
	cmp	eax, 0x00;
	je	.fim_arquivo

	inc	ecx				; Apota para a proxima posicao no buffer

	; Verifica espaço
	cmp	byte [ecx - 1], ' '		; Achou espaço (32), então já possui o comando
	jne	.nao_espaco

	; Se encontrou um espaço, armazena a posição da string de parametros
	cmp	[varlocal(3)], dword 0x00	; Ja havia armazenado ?
	jne	.nao_espaco
	mov 	[varlocal(3)], dword ecx	; Armazena o endereco atual


  .nao_espaco

	; Caracter que nao é espaço
	cmp	byte [ecx - 1], 0xA		; Chegou ao final da linha ?
	je	.fim_linha			; Continua lendo se nao chegou ao fim da linha

	; Verifica se o buffer esta cheio
	cmp	[varlocal(2)], ecx		; ecx chegou ao fim do buffer ?
	jne	.ler_byte			; Nao
	jmp	.buffer_cheio			; Sim


  .fim_arquivo

	; Chegou ao fim do arquivo, precisa verificar se o buffer esta cheio para poder saber onde gravar o 0x0
	cmp	[varlocal(2)], ecx		; ecx chegou ao fim do buffer ?
	je	.fim_linha			; Sim | Substitui o ultimo caractere lido por um 0x0h (fazer o que né, antes perder 1 caractere do que estragar meu trabalho)
	mov	byte [ecx], 0x00		; Coloca o 0x0h no proximo caractere do buffer (já que tem espaço..)
	jmp	.processa			; Processa o comando


  .buffer_cheio

	; Descarta o restante da linha
	push	eax
	push	ecx
	dec	esp				; Reserva mais espaço da pilha para um lixinho (1 byte)


    .descarta

	; Le byte a byte
	mov	ecx,	esp
	macro_syscall 3

	cmp	eax, 0x00			; Se nao leu nada chegou ao final do arquivo (a ultima linah era grande demais)
	jne	.verifica_newline		; Leu alguma coisa, verifica se eh um newline
	mov	[esp + 5], eax			; sobreescreve o velho eax
	jmp	.termina_cerificacao		; ira substituir a ultima letra por 0x00, mas está certo pois o buffer jah tinah acabado mesmo

    .verifica_newline
	cmp	byte [esp], 0xA			; Verifica se o caractere é um newline
	jne	.descarta			; Continua descartando enquanto nao for \n ou fim do arquivo


    .termina_cerificacao

	; Terminou a verificacao
	inc 	esp				; Restaura a pilha
	pop	ecx
	pop	eax


  .fim_linha

	; Encontrou um \n
	mov	[ecx - 1], byte 0x0		; Substitui o \n por um Zero (torna o parametro imprimivel pelas funcoes padrao)


  .processa

	; Trata o caso de o comando nao possuir parametros
	cmp	[varlocal(3)], dword 0x00	; comando sem parametro
	jne	.processa_mesmo
	mov 	[varlocal(3)], dword ecx	; Armazena o endereco atual

  .processa_mesmo

	; Processa o comando
	pushfd	
	push	dword [parametro(3)]		; parametro pra essa funcao 		(3)
	push	dword [varlocal(3)]		; ptr para os parametros		(2)
	push 	dword [varlocal(1)]		; ptr para a string de comando 		(1) | inicio do buffer
	call	dword [parametro(2)]		; chama a funcao definida | processa_comando
	descarta_pilha 3
	popfd

	; Restaura o buffer
	cmp	eax, 0x00			; Chegou aqui sem ler nenhum byte ??
	je	.fim				; Então  oarquivo acabou e deve terminar a leitura

	mov	ecx, [varlocal(1)]		; Senão, Restaura o buffer
	jmp	.le_linha			; E lê a proxima linha

  .fim

	pop	edx				; Restaura os registradores
	pop	ebx
	pop	eax
	pop	ecx
	ccc_end					; Restaura o ambiente
ret



; -----------------------------------------------
; [nome]  	processa_comando
; [descr] 	Procesa o comando de uma linha do arquivo
; [param] 	ptr para a string de comando 	(1)
;		ptr para os parametros		(2)
;		ptr para a tabela de comandos	(3)
; [return]	numero de bytes lidos como parametros do comando (eax)
; -----------------------------------------------
; 17/06/2005 02:34
; Finaliza a versão 0.9 da função
;
; 17/06/2005 20:43
; Finalizada a versão 1.0. A função já passa o controle ao manipulador do comando.
; Falta agora apenas implementar os comandos ;-p (que é a parte fácil do trabalho hehe)
; -----------------------------------------------
processa_comando:
	ccc_begin			; Prepara o ambiente
	push 	eax			; Armazena os registradores
	push	ebx
	push	ecx


	;ebx armazenara o tamanho do comando
	mov	ebx, dword [parametro(2)]
	sub	ebx, dword [parametro(1)]
	dec	ebx

	mov	ecx, dword [parametro(3)]		; ecx armazena o comando sendo comparado atualmente

	cld	; limpa o flag de direcao


  .compara_comando

	;ecx aponta para o elemento atual na TABELA de comandos

	mov	esi, dword [parametro(1)]		; aponta esi para a string a ser processada
	mov 	edi, [ecx]				; aponta edi para o comando atual
	mov	edi, [edi + s_comando.ptComando]	; aponta edi para a string do comando atual

	push	ecx					; armazena o comando atual a ser comparado

	;
	; Compara enquanto for igual
	;
	mov	ecx, ebx				; numero de caracteres a comparar
	repe	cmpsb					; compara enquanto as strings coincidirem E enquanto houver algum caractere a comparar (ecx > 0)

	pop	ecx					; ecx aponta novamente para o comando que foi comparado

	je	.processa				; os comandos coincidem

	;
	; Comando atual nao coincidiu
	;

	cmp	ecx, fimComandos			; Chegou ao ultimo comando a comparar?
%ifdef DEBUG
	je 	.erro_comando				; Erro no comando
%else
	je 	.termina				; Terminou o processamento
%endif

	add 	ecx, 4					; Aponta para o proximo comando
	jmp	.compara_comando			; Compara com o proximo comando da tabela


%ifdef DEBUG
  .erro_comando	

	; Exibe o ero de comando nao reconhecido
	push eax					; print_z retorna o numer ode bytes escritos

	print_str dword str_erroComando, 2		; mensagem de erro
	print_str dword [parametro(1)], 2		; string do comando
	_newline 2					; Nova linha

	pop eax						; Restaura

	jmp	.termina
%endif


  .processa

	; Chama a funcao adequada para o comando encontrado
	mov 	ecx, [ecx]				; Aponta ecx para o comando atual
	push	dword [parametro(2)]			; (1) ptr para string do comando
	call	dword [ecx + s_comando.ptFuncao]	; Chama a funcao
	descarta_pilha 1


  .termina

	; Termina o algoritmo  
	pop 	ecx					; Restaura os registradores
	pop	ebx
	pop 	eax
	ccc_end						; Restaura o ambiente
ret