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
; Esse arquivo contem funçoes basicas de saida
; -----------------------------------------------

; -----------------------------------------------
;               .:] Changelog [:.
; -----------------------------------------------
; 14/06/2005
; Criação do arquivo
; Inicio da escrita da documentaçã oo trabalho
; Adotado o método de "Dividir para conquistar"
; -----------------------------------------------

%include "includes/macros.inc"

global strlen_z
global print_z
global strncpy_z
global printn_z
global getparametro_z
global printchar_z
global int2ascii

%include "util/asm_io.inc"


; -----------------------------------------------
; [nome]	getparametro_z
; [desc]	Essa funcao prepara uma string para que possam ser lidos varios parametros dela.
;		Resumidamente, ela converte o primeiro espaço em branco da string por um 0x00. Caso encontre um 0x00 antes de substituir, ela nao faz nada (precaução) :-D
; [params]	(1) ptr para a string
; [return]	(eax) numero de caracteres do parametro
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [01/07/2005 - 00:52]
; Versão 1.0
; -----------------------------------------------
getparametro_z:
	ccc_begin 			; Prepara o ambiente
;	push	ecx			; Armazena ecx
	pushfd

	; Aponta eax pro inicio da string
	mov	eax, [parametro(1)]	; ptr para o buffer de saida
	dec	eax			; Inicializa para poder urilizar o incrementos no inicio do loop
					; e assim permitir que os flags nao sejam alterados apos a comparacao


  .loop

	; Varre byte a byte
	inc	eax

	cmp	byte [eax], ' '		; Espaço ?
	jne	.loop
	mov	byte [eax], 0x00	; Transforma em 0x00

	cmp	byte [eax], 0x00	; 0x00 ?
	jne	.loop

	sub 	eax, [parametro(1)]	; Calcula o deslocamento
					; Retorno em eax

	popfd
;	pop	ecx			; Restarua ecx
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa



; -----------------------------------------------
; [nome]	strlen_z
; [desc]	Calcula o tamanho de uma string "Zero-terminated"
; [params]	(1) ptr para a string
; [return]	(eax) numero de caracteres na string
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [15/06/2005 - 03:00]
; Versão Final
; -----------------------------------------------
strlen_z:
	ccc_begin 			; Prepara o ambiente
;	push	ecx			; Armazena ecx
	pushfd
	
	; Aponta eax pro inicio da string
	mov	eax, [parametro(1)]	; ptr para o buffer de saida
	dec	eax			; Inicializa para poder urilizar o incrementos no inicio do loop
					; e assim permitir que os flags nao sejam alterados apos a comparacao


  .loop

	; Varre byte a byte
	inc	eax
	cmp	byte [eax], 0
	jne	.loop

	sub 	eax, [parametro(1)]	; Calcula o deslocamento
					; Retorno em eax

	popfd
;	pop	ecx			; Restarua ecx
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa



; -----------------------------------------------
; [nome]	print_z
; [desc]	Imprime uma string "Zero-terminated"
; [params]	descritor de arquivo para a saida	(1)
;		ptr pra a string			(2)
; [return]	numero de bytes escritos		(eax)
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [15/06/2005 - 03:10]
; Versão Final
; -----------------------------------------------
print_z:
	ccc_begin 			; Prepara o ambiente
	push	eax
	push	ebx
	push 	ecx
	push 	edx

	push	dword [parametro(2)]	; ptr para a string
	call strlen_z			; Retorno em eax
	descarta_pilha 1		; Descarta q parametro

	; Parametro para syscall
	mov	ebx, [parametro(1)]	; descritor do arquivo (1 stdout)
	mov	edx, eax		; numero de bytes a escrever	
	mov	ecx, [parametro(2)]	; ptr para o buffer
	macro_syscall 4			; syscall: write (fs/read_write.c)

	pop 	edx
	pop 	ecx
	pop	ebx
	pop	eax
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa


; -----------------------------------------------
; [nome]	printn_z
; [desc]	Imprime uma os primeiros n caracteres de uma string
; [params]	(1) descritor de arquivo para a saida
;		(2) ptr pra a string
;		(3) numer de caracteres a imprimir
; [return]	(eax) numero de bytes escritos
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [30/06/2005 - 22:59]
; Versão 1.0
; Tornou-se necessaria essa função para imprimir o numero dos telefones
; -----------------------------------------------
printn_z:
	ccc_begin 			; Prepara o ambiente
	push	eax
	push	ebx
	push 	ecx
	push 	edx

	; Parametro para syscall
	mov	ebx, [parametro(1)]	; descritor do arquivo
	mov	edx, [parametro(3)]	; numero de bytes a escrever
	mov	ecx, [parametro(2)]	; ptr para o buffer
	macro_syscall 4			; syscall: write (fs/read_write.c)

	pop 	edx
	pop 	ecx
	pop	ebx
	pop	eax
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa


; -----------------------------------------------
; [nome]	strncpy_z
; [desc]	Copia N caracteres do buffer fonte
;		para destino. Se encontrar o fim do buffer
;		origem, para a copia.
; [params]	ptr para fonte			(1)
;		ptr para destino		(2)
;		numero de caracteres a copiar	(3)
; [return]	numero de bytes escritos	(eax)
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [18/06/2005 - 12:23]
; Versão 1.0
; -----------------------------------------------
strncpy_z:
	ccc_begin			; Define o ambiente
	push	eax
	push 	ecx
	pushfd

	cld				; Limpao flag de direção
	
	xor	eax, eax
	mov 	esi, [parametro(1)]	; De
	mov 	edi, [parametro(2)]	; Para
	mov 	ecx, [parametro(3)]	; Bytes


  .loop
	lodsb				; Le
	stosb				; Armazena
	
	dec	ecx

	cmp	ecx, 0x0		; Fim do loop?
	je	.sair

	cmp	al, 0x0			; Fim da string?
	jne	.loop


  .sair

	popfd
	pop 	ecx
	pop	eax
	ccc_end				; Restaura o ambiente
ret					; Retorna o controle ao programa



; -----------------------------------------------
; [nome]	printchar_z
; [desc]	Imprime um caractere em al para o descritor de arquivos em ah
; [params]	(al) caractere a ser impresso
; 		(ah) file descriptor
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [04/07/2005 - 18:43]
; Versão 1.0
; -----------------------------------------------
printchar_z
	ccc_begin		; Define o ambiente
;	push 	eax
	push	ebx
	push 	ecx
	push 	edx
	pushfd			; Armazena os flags

	dec esp
	mov [esp], byte al
;	push byte al		; Caractere a ser impresso

	; Parametro para syscall
	movzx	ebx, ah		; descritor do arquivo (1 stdout)
	mov	edx, 0x1	; numero de bytes a escrever
	mov	ecx, esp	; ptr para o buffer
	macro_syscall 4		; syscall: write (fs/read_write.c)

	inc esp			; Descarta o byte

	popfd			; Restaura os flags
	pop	edx
	pop	ecx
	pop	ebx
;	pop	eax
	ccc_end			; Restaura o ambiente
ret


; -----------------------------------------------
; [nome]	int2ascii
; [desc]	converte um valor inteiro em sua reresentação ascii
; [params]	(eax) numero a ser imrpesso
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [04/07/2005 - 20:16]
; Versão 1.0
; -----------------------------------------------
int2ascii
	ccc_begin
	push eax
	push ebx
	push ecx
	push edx

	xor     ecx, ecx	; contador do numero de caracteres que deverao ser imprimidos
	mov     ebx, 0xA	; Base


  .divide
	xor     edx, edx	; Zera EDX
	div     ebx

	add     edx, '0'	; Converte pra ascii
	dec	esp		; Move a pilha manualmente
	mov 	[esp], byte dl
	inc	ecx

        cmp     eax, 0x0  	; Zerou ?
        jg      .divide

	mov	ax, 0x1		; stdout - parametro para printchar_z


  .imprime
	mov	al, byte [esp]	; Pega o caractere da pilha
	call printchar_z	; Imprime o caracteres
	inc	esp		; Restaura a pilha
	dec	ecx		; e o contador
	jnz	.imprime

	pop edx
	pop ecx
	pop ebx
	pop eax
	ccc_end
ret