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
; Criado em: 08/07/2005
; Versão 1.0
; -----------------------------------------------
; Descrição:
; Esse arquivo contém as funções que auxiliam
; na inteligencia do pabx em si.
; -----------------------------------------------

%include "includes/macros.inc"

extern MapaMemCadastro
extern MapaMemConversa
extern MapaMemMensagem
extern FimMapaMem

extern st_memoria.endereco_real
extern st_memoria.tamanho
extern st_memoria.status

extern st_telefone.numero
extern st_telefone.status
extern st_conversa.tel_1
extern st_conversa.tel_2
extern st_mensagem.id_conversa
extern st_mensagem.status
extern strlen_z

global procura_telefone_cadastrado
global procura_conversa_telefone
global libera_mensagens
global status_mensagens

%include "util/asm_io.inc"

; -----------------------------------------------
; [nome]  	procura_telefone_cadastrado
; [descr] 	procura por um telefone cadastrado no sistema
; [param] 	(1) ptr para o numero do telefone
; [return]	(eax) ptr para a celula onde se encontra o telefone
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [28/06/2005 - 20:10]
; Finalizada a versão 1.0
; -----------------------------------------------
procura_telefone_cadastrado
	ccc_begin
	push	ebx
	push	ecx

	cld	; limpa o flag de direcao
	mov	ebx, MapaMemCadastro			; mapa de memoria


  .compara_telefone

	; Avanca para o proximo elemento na tabela
	add	ebx, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	ebx, MapaMemConversa
	jge	.erro

	; Apenas pesquisa por numeros que estão ocupados
	cmp	byte [ebx + st_memoria.status], ST_CELULA_OCUPADA
	jne	.compara_telefone

	mov	esi, dword [parametro(1)]		; aponta esi para a string a ser processada
	mov 	edi, [ebx + st_telefone.numero]		; aponta edi para o telefone atual
							; isso nao eh o correto, mas como eu coloquei o que importa no offset 0 a partir do endereço, isso funciona e econimoza alguns comandos (q seriam somar 0 algumas vezes)

	; Armazena o numero de caracteres a comparar em eax
	push dword [parametro(1)]
	call strlen_z
	descarta_pilha 1
	mov	ecx, eax				; numero de caracteres a comparar


	;
	; Compara enquanto for igual
	;
	repe	cmpsb					; compara enquanto as strings coincidirem E enquanto houver algum caractere a comparar (ecx > 0)
	jne	.compara_telefone			; os comandos coincidem

	; Retorna o endereço em eax
	mov	eax, ebx
	jmp	.fim


  .erro	

	; Nao achou
	xor	eax, eax


  .fim
	; Termina a funcao
	pop	ecx
	pop	ebx	
	ccc_end
ret



; -----------------------------------------------
; [nome]  	procura_conversa_telefone
; [descr] 	procura uma conversa associada ao telefone especificado
; [param] 	(1) ptr para a celula onde se encontra o telefone
; [return]	(eax) ptr para a celula onde se encontra a conversa
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [04/07/2005 - 23:11]
; Versão WIP
; -----------------------------------------------
procura_conversa_telefone
	ccc_begin
	push	ebx
	push	ecx

	mov	eax, MapaMemConversa			; mapa de memoria
	mov	ecx, dword [parametro(1)]		; telefone a ser buscado


  .compara_telefone

	; Avanca para o proximo elemento na tabela
	add	eax, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	eax, MapaMemMensagem
	jge	.erro

	; Apenas pesquisa por numeros que estão ocupados
	cmp	byte [eax + st_memoria.status], ST_CELULA_OCUPADA
	jne	.compara_telefone

	mov	ebx, [eax + st_memoria.endereco_real]	; Aponta para a conversa

	cmp	dword [ebx + st_conversa.tel_1], ecx	; procura pelo telefone
	je	.fim

	cmp	dword [ebx + st_conversa.tel_2], ecx	; procura pelo telefone
	jne	.compara_telefone

	jmp	.fim


  .erro	

	; Nao achou
	xor	eax, eax


  .fim
	; Termina a funcao
	pop	ecx
	pop	ebx	
	ccc_end
ret



	push	dword 2			; (2) Status minimo a se manter
	push	dword MAPA_MENSAGEM	; (1) Mapa a manipular
	call libera_mensagens
	descarta_pilha 2

; -----------------------------------------------
; [nome]	libera_mensagens
; [descr]	Libera as mensagens com o status maior que o status minimo informado
; [param]	(1) status minimo
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [25/07/2005 - 20:20]
; Versão 1.0
; -----------------------------------------------
libera_mensagens
	ccc_begin
	push	eax
	push	ebx
	push	ecx
	push	edx

	mov	eax, MapaMemMensagem			; mapa de memoria
	mov	edx, eax				; EDX := registro mestre
	mov	ecx, dword [parametro(1)]		; status


  .compara_mensagem

	; Avanca para o proximo elemento na tabela
	add	eax, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	eax, FimMapaMem
	jge	.fim

	; Apenas pesquisa por numeros que estão ocupados
	cmp	byte [eax + st_memoria.status], ST_CELULA_OCUPADA
	jne	.compara_mensagem

	mov	ebx, [eax + st_memoria.endereco_real]	; Aponta para a conversa

	cmp	byte [ebx + st_mensagem.status], cl	; Status
	jl	.compara_mensagem

	; Libera a memoria
	mov	byte [eax + st_memoria.status], ST_CELULA_LIVRE

	push	ecx
	movzx	ecx, word [eax + st_memoria.tamanho]
	add	word [edx + st_memoria.tamanho], cx
	pop	ecx

dump_mem 1111, [eax], 1
	
	jmp	.compara_mensagem

  .fim
	; Termina a funcao
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]	libera_mensagens
; [descr]	Libera as mensagens com o status maior que o status minimo informado
; [param]	(1) conversa
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [25/07/2005 - 19:50]
; Versão 1.0
; -----------------------------------------------
status_mensagens
	ccc_begin
	push	eax
	push	ebx
	push	ecx

	mov	eax, MapaMemMensagem				; mapa de memoria
	mov	ecx, dword [parametro(1)]			; endereco da conversa
	mov	cx, word [ecx + st_mensagem.id_conversa]	; Numero identificador da conversa


  .compara_mensagem

	; Avanca para o proximo elemento na tabela
	add	eax, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	eax, FimMapaMem
	jge	.fim

	; Apenas pesquisa por numeros que estão ocupados
	cmp	byte [eax + st_memoria.status], ST_CELULA_OCUPADA
	jne	.compara_mensagem

	mov	ebx, [eax + st_memoria.endereco_real]	; Aponta para a conversa

	cmp	word [ebx], cx				; A mensagem possui o ID da conversa especificada?
	jne	.compara_mensagem

	; Marca a memoria como já passada
	inc 	byte [ebx + st_mensagem.status]
	jmp	.compara_mensagem

  .fim

	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret