; -----------------------------------------------
; Segundo Trabalho de Linguagem de Montagem
; Ciência da Computação - 2005/01 - UFES
; -----------------------------------------------
; Autor: Reinaldo Junior < juniorz [at] gmail [dot] com >
; 	 http://www.phpbb.com.br/portal/
; -----------------------------------------------
; Criado em: 15/06/2005
; Versão 0.0.1
; -----------------------------------------------
; Descrição:
; Esse arquivo contem funçoes de manipulação de arquivo
; -----------------------------------------------



; -----------------------------------------------
;               .:] Changelog [:.
; -----------------------------------------------
; 17/06/2005 11:15
; Criado o arquivo
; -----------------------------------------------

%include "includes/macros.inc"

global abre_arquivo
global fecha_arquivo

; -----------------------------------------------
; [nome]  	abre_arquivo
; [descr] 	abre um arquivo e armazena seu descritor
; [param] 	(1) ptr para o nome do arquivo
; [return]	(eax) desc de arquivos
; -----------------------------------------------
abre_arquivo:
	ccc_begin			; Prepara o ambiente

	push 	ebx
	push 	ecx
	push 	edx

	mov 	ebx, [parametro(1)]	; Nome do arquivo
	mov 	ecx, 00			; file access bits: readonly
	mov 	edx, 00004		; file permission flag: read by others

	macro_syscall 	5		; syscall: open (fs/open.c)

	pop	edx			; Restaura os registradores
	pop	ecx
	pop	ebx

	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa


; -----------------------------------------------
; [nome]  	fecha_arquivo
; [descr] 	fecha um arquivo
; [param] 	(1) desc do arquivo
; [return]	(eax) sucesso ou erro
; -----------------------------------------------
fecha_arquivo:
	ccc_begin			; Prepara o ambiente
	push	ebx

	mov	ebx, [parametro(1)]	; descritor do arquivo
	
	macro_syscall 6			; syscall: close (fs/open.c)

	pop	ebx
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa