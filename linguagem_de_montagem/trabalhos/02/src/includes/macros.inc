; -----------------------------------------------
; Segundo Trabalho de Linguagem de Montagem
; Ciência da Computação - 2005/01 - UFES
;
; Autores:
;	Reinaldo Junior < juniorz@gmail.com >
;	http://www.phpbb.com.br/portal/
;
;	Rafael Garcia Birro < rgbirro@gmail.com >
; -----------------------------------------------
; Criado em: 15/06/2005
; Versão 1.0
; -----------------------------------------------
; Descrição:
; Esse arquivo contem as macros utilizadas no programa
; -----------------------------------------------


; Status do telefone (mascara)
;				xxxx	 	telefone entrou? (possui linha)
;				    yyyy 	telefone ocupado? (fora do gancho)
%define MSK_TEL_FORA_GANCHO	00001111b	; Fora do gancho (nao importa se esta fazendo ou recebendo ligações)
%define MSK_TEL_LIVRE		00000000b	; No gancho e sem comunicação
%define MSK_TEL_TEM_LINHA	11110000b	; Em comunicação (agora um telefone pode estar em comunicaão e estar no gancho - como na vida real :-P )


; Constantes do sistema de alocacao
%define ST_CELULA_LIVRE		0x00
%define ST_CELULA_OCUPADA	0x01
%define ST_CELULA_DISPONIVEL	0xFF

; Mapas para o sistema de alocação
%define MAPA_CADASTRO 0
%define MAPA_CONVERSA 1
%define MAPA_MENSAGEM 2

; Numero de estruturas
%define NUM_CADASTROS 200
%define NUM_CONVERSAS 100

; Estruturas
%define TAM_ST_MEMORIA 7
%define TAM_ST_CADASTRO 13
%define TAM_ST_CONVERSA 12
%define TAM_ST_MENSAGEM 12


; -----------------------------------------------
;                .:] Macros [:.
; -----------------------------------------------

; -----------------------------------------------
; [macro] _newline
; [descr] imprime um \n
; [param] descritor de arquivos destino para o \n
; -----------------------------------------------
%macro	_newline 0-1 1
	push 	eax		; eax recebe retorno de print_z	
	print_char 0xA, %1
	pop	eax		; Restaura eax
%endmacro


; -----------------------------------------------
; [macro] print_char
; [descr] imprime um caractere
; [param] (1) caractere
; 	  (2) descritor de arquivos destino para o caractere
; -----------------------------------------------
%macro	print_char 1-2 1
	mov al, %1
	mov ah, %2
	call printchar_z
%endmacro


; -----------------------------------------------
; [macro] print_str
; [descr] imprime uma string
; [param] (1) ptr para a string (zero-terminated)
; 	  (2) descritor de arquivos destino
; -----------------------------------------------
%macro	print_str 1-2 1
	push %1
	push %2
	call print_z
	descarta_pilha 2
%endmacro


; -----------------------------------------------
; [macro] printn_str
; [descr] imprime 'n' caracteres de uma string
; [param] (1) ptr para a string
;	  (2) numero de caracteres a imprimir
; 	  (3) descritor de arquivos destino
; -----------------------------------------------
%macro	printn_str 2-3 1
	push %2
	push %1
	push %3
	call printn_z
	descarta_pilha 3
%endmacro


; -----------------------------------------------
; [macro] macro_syscall
; [descr] executa uma syscall
; [param] (1) numero da syscall
; -----------------------------------------------
%macro	macro_syscall	1
	mov eax, dword %1	; Numero da syscall
	int 80h			; Chama o kernel
%endmacro


; -----------------------------------------------
; [macro] termina_programa
; [descr] finaliza o processo
; [param] (1) codigo de saida do processo
; -----------------------------------------------
%macro termina_programa 1
	mov 	ebx, %1		; codigo de saida
	macro_syscall 1		; syscall: exit (kernel/exit.c)
%endmacro


; -----------------------------------------------
; [macro] descarta_pilha
; [descr] descarta um numero de elementos do topo da pilha
; [param] (1) numero de elemntos
; -----------------------------------------------
%macro descarta_pilha 1
	add esp, 4 * %1		; Descarta 4 * num_elementos bytes da pilha
%endmacro


; -----------------------------------------------
; [macro] ccc_begin
; [descr] faz os preparativos iniciais para que um procedimento utilize a convenção de chamada do C
; [param] (1) numero de variaveis locais que o proceidmento precisará
; -----------------------------------------------
%macro ccc_begin 0-1 0
	push	ebp		; Empilha ebp
	mov	ebp, esp	; Prepara a pilha para poder ser utilizada no subprocedimento sem que se perca os parametros
	sub	esp, 4 * %1	; Reserva espaço para variaveis locais
%endmacro


; -----------------------------------------------
; [macro] ccc_end
; [descr] restaura a pilha para o estado inicial da chamada do procedimento
; -----------------------------------------------
%macro ccc_end 0
	mov	esp, ebp	; Restaura esp
	pop	ebp		; Restaura ebp
%endmacro


; -----------------------------------------------
; [macro] parametro
; [descr] expande para o endereço de um determinado parametro do procedimento
; [param] (1) numero do parametro (contado da esquerda para a direita)
; -----------------------------------------------
%define 	parametro(x)	ebp + 4 + 4 * x


; -----------------------------------------------
; [macro] varlocal
; [descr] expande para o endereço de uma determinada variavel local do procedimento
; [param] (1) numero do da variavel local
; -----------------------------------------------
%define 	varlocal(x)	ebp - 4 * x
