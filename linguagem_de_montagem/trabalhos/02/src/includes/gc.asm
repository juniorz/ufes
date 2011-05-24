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
; Esse arquivo contem funçoes de garbage collection
; -----------------------------------------------


; -----------------------------------------------
;               .:] Changelog [:.
; -----------------------------------------------
; 20/06/2005 11:15
; Criado o arquivo
; -----------------------------------------------

%include "includes/macros.inc"
%define TAM_ST_MEMORIA 7

global malloc_z
global free_z

extern MapaMem
extern NumeroCelulas
extern st_memoria.endereco_real
extern st_memoria.tamanho
extern st_memoria.status

; RETIRAR
%include "util/asm_io.inc"

; [std_io.o]
extern print_z
extern printchar_z


; RETIRAR
;extern getchar
;extern int2ascii

; -----------------------------------------------
; [nome]	malloc_z
; [descr]	reserva uma determinada quantidade de memoria
; [param]	(1) Espaço de memória a ser utilizado
;		(2) Quantidade de memoria a ser reservada
; [return]	(eax) endereco indireto para a memoria alocada ou -1 em caso de erro
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [21/06/2005 - 00:32]
; Versão 0.5
; Falta implementar a parte que fará a mensagem funcionar, que é o redimensionamento das celulas de memoria (e o garbage collection em si)
;
; [24/06/2005 - 19:15]
; Versão 0.7
; Corrigidos problemas de verificação do tamanho da celula. (ao inves de comparar uma word eu comparava uma dword :-D )
;
; [28/06/2005 - 22:25]
; Versão 0.7.1
; Alterada a convenção de retorno e implementado um debug e uma pequena otimização
;
; [14/07/2005 - 19:33]
; Versão 0.9
; Iniciada a implementação do caso em que será preciso efetuar o Garbage Collection.
;
;
; [TODO]
; Implementar o redimensionamento de uma celula caso sobre bytes
; -----------------------------------------------
malloc_z:
	ccc_begin

	push 	ebx
	push	ecx
	pushfd


  .inicio

	;
	; Inicia as variaveis
	;
	mov	eax, dword [parametro(1)]	; parametro(1) possui o elemento da tabela de mapas que sera manipulado (0 - 2)

	mov	ebx, eax			; copia para ebx
	inc	ebx				; ebx possui o mapa seguinte ao mapa que será atualizado
	mov	ebx, dword [MapaMem + 4 * ebx]	; ebx := elemento da tabela de mapas seguinte ao que sera manipulado (1 - 3)
	mov	ecx, ebx			; varlocal(1) possui o limite superior do mapa que está sendo manipulado

	mov	eax, dword [MapaMem + 4 * eax]	; eax := Registro mestre do Mapa de memoria a ser manipulado
	mov	ebx, dword [parametro(2)]	; ebx := bytes a alocar


	;
	; Verifica se há espaço suficiente
	;
	cmp	word [eax + st_memoria.tamanho], bx	; Possui essa quantidade ?
	jge	.procura_espaco				; Procura o espaço

	xor	eax, eax				; Erro
	jmp	.fim


  .procura_espaco

	; Procura um pedaço livre e que tenha o tamanho necessário
	add	eax, TAM_ST_MEMORIA			; Aponta para a proxima celula

%ifdef DEBUG
	_newline
	dump_regs 222001
	dump_mem 222001, eax, 1
	dump_mem 222002, [eax], 1

	; Faz uma pausa :-P
	push eax
	push ebx
	push ecx
	push edx
	call getchar
	pop edx
	pop ecx	
	pop ebx
	pop eax
%endif

								; EBX := Tamanho necessario 
	cmp	bx, word [eax + st_memoria.tamanho]		; Essa célula a possui o tamanho que preciso?
	jnle	.verifica_fim					; Continua procurando ate encontrar uma celula com tamanho maior ou igual ao que preciso

	cmp	byte [eax + st_memoria.status], ST_CELULA_LIVRE	; Verifica se o espaço está ocupado
	je	.retorna					; Retorna o endereço


  .verifica_fim

	cmp	eax, ecx		; Chegou ao fim ?
	jl	.procura_espaco		; Continua procurando

	; Chegou ao fim e nao achou nada nenhuma celula que possua NO MINIMO a quantidade de bytes necessários
	; Então, desfragmenta
	push dword [parametro(1)]	; Mapa a efetuar o CG
	call defrag_mem			; Implementa um garbage collection automatico,
					; caso nao tenha encontrado uma celula livre com o espaço de memoria necessário.
					; A idéia é varrer o mapa de memoria procurando por celulas que possuam a quantidade de bytes necessária,
					; e caso sobre algum byte na celula que sera utilizada , essa quantidade que sobrou será alocada em outra célula - caso exista -
					; (o que diminuiria a probabilidade de se efetuar esse garbage collection mais vezes do que o necessário).
					; Essa alocação ocorre no FINAL desse procedimento.
					; Ver "PABX User Guide" pg 1724 (hehehe)
	descarta_pilha 1


	; Se possuia espaço, mas nao possuia nenhuma celula do tamanho,
	; após o GC haverá um celula do tamanho necessario (ou maior).
	; Então, roda a função de novo
	jmp	.inicio


  .retorna

	mov	byte [eax + st_memoria.status], ST_CELULA_OCUPADA	; Ocupa a celula que será utilizada

	;
	; Atualiza o Registro mestre
	;
	push 	eax

	mov	eax, dword [parametro(1)]	; parametro(1) possui o elemento da tabela de mapas que sera manipulado (0 - 2)
	mov	eax, dword [MapaMem + 4 * eax]	; eax := Registro mestre do Mapa de memoria a ser manipulado

	sub	word [eax + st_memoria.tamanho], bx		; Espaço livre
	jnz	.salta01
	mov	byte [eax + st_memoria.status], ST_CELULA_OCUPADA	; Se acabou o espaço no espaço que o mapa gerencia, marca o espaço como ocupado no registro mestre


    .salta01	

	pop	eax

	; Para aproveitar o espaço, verifica se será utilizado todo o espaço da celula recém-ocupada
	sub	bx, word [eax + st_memoria.tamanho]
	jz	.fim

	; Faz a realocação dos bytes que eventualmente venha ma estar sobrando na celula que será utilizada agora
	; Aloca o espaço que sobrou na primeira célula DISPONIVEL encontrada
	; Se nao encontrar, deixa do tamanho que está :-D
	neg	bx						; BX := numero de bytes que sobraram

	;
	; Aloca os bytes
	;

	; Procura por uma celula disponivel
	push	eax				; Armazena EAX

	push dword [parametro(1)]		; Mapa a efetuar o CG
	call procura_celula_disponivel		; Procura por uma celula disponivel e retornma em EAX
	descarta_pilha 1

	cmp	eax, 0x00	; Possui alguma celula DISPONIVEL?
	mov	ecx, eax	; Armazena a celula. Nao altera os FLAGS
	pop	eax		; Restaura EAX (nao altera os FLAGS)
	je	.fim		; Se nao possui sai assim mesmo

	; ECX := Celula DISPONIVEL
	; EAX := Celula que possui espaço sobrando
	; BX := Numero de bytes que estão sobrando

%ifdef DEBUG
	_newline
	dump_regs 666666
	dump_mem 666666, eax, 1
	dump_mem 666666, ecx, 1
%endif
	
	; Reduz o tamanho da celula que tem espaço sobrando
	sub	word [eax + st_memoria.tamanho], bx

	; Tamanho da nova celula
	mov	word [ecx + st_memoria.tamanho], bx

	; Calcula o endereço do inicio dos bytes restantes
	movzx	ebx, word [eax + st_memoria.tamanho]
	add	ebx, dword [eax + st_memoria.endereco_real]

	; Endereço gerenciado pela nova celula
	mov	dword [ecx + st_memoria.endereco_real], ebx
	
	; Status da nova celula
	mov	byte [ecx + st_memoria.status], ST_CELULA_LIVRE

%ifdef DEBUG
	dump_regs 777777
	dump_mem 777777, eax, 1
	dump_mem 777777, ecx, 1
	_newline
%endif

  .fim

%ifdef DEBUG
	_newline
	dump_mem 222999, eax, 1
%endif

	popfd
	pop	ecx
	pop	ebx
	ccc_end		; Restaura o ambiente
ret

; -----------------------------------------------
; [nome]	free_z
; [descr]	libera uma celula que esteja sendo utilizada
; [param]	(1) ptr para a celula a ser liberada
; [return]	(eax) bytes liberados
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [29/06/2005 - 00:35]
; Versão 1.0
; -----------------------------------------------
free_z
	ccc_begin

	mov	eax, [parametro(1)]					; EAX := ptr para a celula
	cmp	byte [eax + st_memoria.status], ST_CELULA_OCUPADA	; Memoria esta ocupada?
	je	.memoria_ocupada

	; Tentando liberar uma memoria nao ocupada
	mov	eax, -1						; ERRO
	jmp	.fim


  .memoria_ocupada
	; Libera
	mov	byte [eax + st_memoria.status], ST_CELULA_LIVRE	; Memoria agora esta livre
	movzx	eax, word [eax + st_memoria.tamanho]		; Memoria liberada


  .fim
	ccc_end
ret


; -----------------------------------------------
; [nome]	defrag_mem
; [descr]	Manipula a memoria desfragmentando-a
; [param]	(1) mapa a ser manipulado
; [return]	(eax) celula encontrada, ou 0x00 em caso de erro
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [23/07/2005 - 01:33]
; Versão WIP
;
; [25/07/2005 - 18:50]
; Versão 1.0
; -----------------------------------------------
defrag_mem
	ccc_begin 1
	push 	eax
	push	ecx
	push	edx

;dump_regs 98765
	
	; Nesse momento eu sei que há pelo menos 2 celulas LIVRES com menos de "parametro(2)" bytes
	; Minha estrategia é encontrá-las e mesclá-las tornando-as 1 celula de "parametro(2)" bytes e outra com os bytes restantes
	; Como??? Tento mesclar 2 celulas e retorno o controle a outra função que estara em loop enquanto nao conseguir uma celula com pelo menos "parametro(2)" bytes
	; A estrutura esta segura contra um loop infinito pois antes de tudo eu verifico se existe no total esse espaço livre... :P
	; Como performance nao é a questão, a coisa fica mais facil heheh

	;
	; varlocal(1) := endereco que se está procurando atualmente
	;

	; Procura a celula que esteja manipulando o espaço que é o inicio do mapa
	; Essa celula tera como endereco real o mesmo endereço do registro mestre
	mov	eax, dword [parametro(1)]	; parametro(1) possui o elemento da tabela de mapas que sera manipulado (0 - 2)
	mov	eax, dword [MapaMem + 4 * eax]	; EAX := Registro mestre do Mapa de memoria a ser manipulado

	; EAX := registro mestre (uma celula)
	; EDX := Endereco real do resgitro mestre
	mov	edx, dword [eax + st_memoria.endereco_real]
	mov	dword [varlocal(1)], edx


  .procura_celula
	; Procura a celula desse endereco  
	push	dword [varlocal(1)]	; Endereco real da celula que esta sendo procurada
	push	dword [parametro(1)]	; Celula a ser manipulada
	call	procura_celula
	descarta_pilha 2

	; EAX := celula encontrada
	; EDX := endereço real que a celula manipula
	; **** SE EAX = 0, é um erro, é pouco provavel, mas é uma brecha heehhe ****
	cmp	eax, 0x00
	je	near .erro

	; Verifica se a celula esta livre
	cmp	byte [eax + st_memoria.status], ST_CELULA_LIVRE
	je	.memoria_livre


	; Celula oupada
	xor	ecx, ecx
	movzx	ecx, word [eax + st_memoria.tamanho]
;	add	dword [varlocal(1)], ecx		; VARLOCAL(1) := endereço para onde a proxima celula procurada aponta
	add 	ecx, dword [varlocal(1)]
	mov	dword [varlocal(1)], ecx

;dump_regs 100111
;dump_mem 100111, eax, 2
; Faz uma pausa :-P
;push eax
;push ebx
;push ecx
;push edx
;call getchar
;pop edx
;pop ecx	
;pop ebx
;pop eax

	jmp	.procura_celula				; Procura ate encontrar uma celula livre


  .memoria_livre
	; Verifica a proxima celula
	; ****** DEVERIA VERIFICAR ANTES SE NAO CHEGOU AO FIM DO ESPAÇO DE MEMORIA
	mov	edx, eax				; EDX := celula livre
	movzx	ecx, word [eax + st_memoria.tamanho]
	add	dword [varlocal(1)], ecx		; VARLOCAL(1) := endereço para onde a proxima celula procurada aponta

	; Procura a celula desse endereco  
	push	dword [varlocal(1)]	; Endereco real da celula que esta sendo procurada
	push	dword [parametro(1)]	; Celula a ser manipulada
	call	procura_celula
	descarta_pilha 2

;_newline
;dump_regs 100222

	; A proxima celula nao existe.. Ihh.. Ferrouuu...
	cmp	eax, 0x00
	je	near .erro

	; Status da proxima celula
	cmp	byte [eax + st_memoria.status], ST_CELULA_LIVRE
	je	.mescla_celulas

	; Celula desabilitada
;	cmp	byte [eax + st_memoria.status], ST_CELULA_DISPONIVEL
;	je	.mescla_celulas
	
	;
	; EAX := celula de baixo
	; EDX := celula de cima
	;

;dump_mem 1232123, eax, 5
;dump_mem 1232123, edx, 5
		
	; Move a celula ocupada para cima
	cld
;	xor	ecx, ecx
	movzx	ecx, word [eax + st_memoria.tamanho]
	mov	esi, dword [eax + st_memoria.endereco_real]	; Move da celula de baixo
	mov	edi, dword [edx + st_memoria.endereco_real]	; Para a celula de cima

	; Atualiza as celulas
	mov	dword [eax + st_memoria.endereco_real], edi

	; Move os dados
	rep	movsb

	; EDI := Fim da celula de cima
	mov	dword [edx + st_memoria.endereco_real], edi	

	jmp	.memoria_livre


  .mescla_celulas

	; Mescla as duas celulas
	movzx	ecx, word [eax + st_memoria.tamanho]		; ECX := tamanho da celula de BAIXO
	add	word [edx + st_memoria.tamanho], cx		; Aumenta o tamanho da celula de cima

	; Inutiliza a celula de baixo
	mov	dword [eax + st_memoria.endereco_real], 0x0		; Celula que gerencia o conteudo da memoria 0x0
	mov	word [eax + st_memoria.tamanho], 0x0			; Celula com tamanho 0x0
	mov	byte [eax + st_memoria.status], ST_CELULA_DISPONIVEL	; Indica que a celula está disponivel para ser utilizada para gerenciar uma memoria qualquer

;dump_mem 123999, edx, 2
;dump_mem 123998, eax, 2
	
	; A celula de cima agora gerencia a memoria dela MAIS a memoria que pertenciaa celula de baixo.
	; Se sobrar, masi tarde esse espaço será devolvido à essa celula que ficou DISPONIVEL (e com tamanho 0)
	jmp	.fim

  .erro

;dump_mem 99999, 0x00, 1
;_newline

  .fim
	pop	edx
	pop	ecx
	pop	eax
	ccc_end
ret

; -----------------------------------------------
; [nome]	procura_celula
; [descr]	Procura no mapa especificado por uma celula que aponte para o endereco especificado
; [param]	(1) mapa a ser manipulado
;		(2) endereco real da celula em questao
; [return]	(eax) celula encontrada, ou 0x00 em caso de erro
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [22/07/2005 - 21:50]
; Versão 1.0
; -----------------------------------------------
procura_celula
	ccc_begin 1
;	push	eax
	push	ebx
	push	ecx

	mov	eax, dword [parametro(1)]	; parametro(1) possui o elemento da tabela de mapas que sera manipulado (0 - 2)
	mov	ebx, eax			; copia para ebx
	inc	ebx				; ebx possui o mapa seguinte ao mapa que será atualizado
	mov	ebx, dword [MapaMem + 4 * ebx]	; ebx := elemento da tabela de mapas seguinte ao que sera manipulado (1 - 3)
	mov	dword [varlocal(1)], ebx	; varlocal(1) possui o limite superior do mapa que está sendo manipulado

	mov	eax, dword [MapaMem + 4 * eax]	; eax := Registro mestre do Mapa de memoria a ser manipulado


  .procura_endereco

	; Procura um pedaço livre e que tenha o tamanho necessário
	add	eax, TAM_ST_MEMORIA			; Aponta para a proxima celula

	cmp	eax, dword [varlocal(1)]			; Chegou ao fim ?
	jge	.fim_mapa

	mov	ebx, dword [eax + st_memoria.endereco_real]	; Essa célula é a que estou procurando ?
	cmp	dword [parametro(2)], ebx			
	je	.fim

	jmp	.procura_endereco


  .fim_mapa
	; chegou ao fim do mapa sem encontrar
	xor eax, eax				; eax := 0


  .fim

	pop	ecx
	pop	ebx
;	pop	eax
	ccc_end
ret



; -----------------------------------------------
; [nome]	procura_celula_disponivel
; [descr]	Procura no mapa especificado por uma celula que esteja disponivel para manipular algum espaço de memoria
; [param]	(1) mapa a ser manipulado
; [return]	(eax) celula encontrada, ou 0x00 em caso de erro
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [25/07/2005 - ]
; Versão 1.0
; -----------------------------------------------
procura_celula_disponivel
	ccc_begin 1
	push	ebx
	push	ecx

	mov	eax, dword [parametro(1)]	; parametro(1) possui o elemento da tabela de mapas que sera manipulado (0 - 2)
	mov	ebx, eax			; copia para ebx
	inc	ebx				; ebx possui o mapa seguinte ao mapa que será atualizado
	mov	ebx, dword [MapaMem + 4 * ebx]	; ebx := elemento da tabela de mapas seguinte ao que sera manipulado (1 - 3)
	mov	dword [varlocal(1)], ebx	; varlocal(1) possui o limite superior do mapa que está sendo manipulado

	mov	eax, dword [MapaMem + 4 * eax]	; eax := Registro mestre do Mapa de memoria a ser manipulado


  .procura_endereco

	; Procura um pedaço livre e que tenha o tamanho necessário
	add	eax, TAM_ST_MEMORIA					; Aponta para a proxima celula

	cmp	eax, dword [varlocal(1)]				; Chegou ao fim ?
	jge	.fim_mapa

	cmp	byte [eax + st_memoria.status],	ST_CELULA_DISPONIVEL	; Essa célula é a que estou procurando ?
	je	.fim

	jmp	.procura_endereco


  .fim_mapa
	; chegou ao fim do mapa sem encontrar
	xor eax, eax				; eax := 0


  .fim

	pop	ecx
	pop	ebx
;	pop	eax
	ccc_end
ret