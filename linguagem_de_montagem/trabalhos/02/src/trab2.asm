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
; Versão 0.8
; -----------------------------------------------
; Descrição
; Esse arquivo possui o procedimento principal do trabalho
; e os dados
; -----------------------------------------------


; -----------------------------------------------
;               .:] Changelog [:.
; -----------------------------------------------
; 14/06/2005
; Inicio da escrita da documentação oo trabalho
; Adotado o método de "Dividir para conquistar"
; -----------------------------------------------


; -----------------------------------------------
; Inicio
; Declarações e includes
; -----------------------------------------------
global main

; Utilizadas por kernel.o
global s_comando.ptComando
global s_comando.ptFuncao
global fimComandos

; Utilizadas por gc.o
global st_memoria.endereco_real
global st_memoria.tamanho
global st_memoria.status

global MapaMem
global MapaMemCadastro
global MapaMemConversa
global MapaMemMensagem
global FimMapaMem

; Utilizadas por pabx.o
global st_telefone.numero
global st_telefone.status
global st_conversa.tel_1
global st_conversa.tel_2
global st_mensagem.status
global st_mensagem.id_conversa

; [std_io.asm]
extern strlen_z
extern print_z
extern printn_z
extern strncpy_z
extern intval_z
extern getparametro_z
extern printchar_z
extern int2ascii

; [file_io.asm]
extern abre_arquivo
extern fecha_arquivo

; [kernel.asm]
extern processa_arquivo
extern processa_comando

; [gc.asm]
extern malloc_z
extern free_z

; [pabx.asm]
extern procura_telefone_cadastrado
extern procura_conversa_telefone
extern libera_mensagens
extern status_mensagens

; Includes
%include "includes/macros.inc"
%include "util/asm_io.inc"

; -----------------------------------------------
;         .:] Dados nao inicializados [:.
; -----------------------------------------------
section .bss

	;
	; Estruturas de armazenamento de dados e garbage colection
	; 7 bytes
	;%define TAM_ST_MEMORIA 7
	struc st_memoria
	  .endereco_real:	resd	1
	  .tamanho:		resw	1
	  .status:		resb	1
	endstruc


	;
	; Estrutura de um registro de telefone
	; 13 bytes
	;%define TAM_ST_CADASTRO 13
	struc st_telefone
	  .numero:	resq	1	; 3344-1724
	  .status:	resb	1
	  .chamou:	resw	1
	  .recebeu:	resw	1
	endstruc


	;
	; Estrutura de uma conversação
	; 9 bytes
	;%define TAM_ST_CONVERSA 12
	struc st_conversa
	  .id:		resw	1	; Identificacao da conversa
	  .tel_1:	resd	1	; Telefone 1
	  .msg_1:	resb	1	; Numero de mensagens enviadas por 1
	  .tel_2:	resd	1	; Telefone 2
	  .msg_2:	resb	1	; Numero de mensagens enviadas por 2
	endstruc


	;
	; Estrutura que define uma mensagem (minimo)
	; 11 bytes
	; %define TAM_ST_MENSAGEM 12
	struc st_mensagem
	  .id_conversa	resw	1	; Identificacao da conversa a qual essa mensagem pertence
	  .de		resd	1	; Quem enviou a mensagem
	  .para		resd	1	; Quem recebera a mensagem
	  .status	resb	1	; Status da mensagem
	  .texto	resb	1	; Onde inicia o texto
	endstruc
	

	;
	; Estrutura utilizada no manipulador de comandos	
	;
	struc s_comando
	  .ptComando:
		resd	1	;ptr para um string q contem o texto dd comando
	  .ptFuncao:
		resd	1	;ptr para o procedimento q trata esse comando
	endstruc


	;
	; Área de memória utiilizada para o armazenamento dos dados
	; 16K = 16 * 1024 = 8 * 2048
	; %define NUM_CADASTROS 200
	; %define NUM_CONVERSAS 100
	EspMem:
	EspCadastro:
		times NUM_CADASTROS resb TAM_ST_CADASTRO		; 2600 bytes - 200 numeros cadastrados
		TamMemCadastro	equ $ - EspCadastro

	EspConversa:
		times NUM_CONVERSAS resb TAM_ST_CONVERSA		; 1200 bytes - 100 conversas
		TamMemConversa equ $ - EspConversa

	EspMensagem
		times 16 * 1024 - $ + EspMem resb 1	; Reserva o restante para Mensagens
		TamMemMensagem equ $ - EspMensagem


; -----------------------------------------------
;          .:] Dados inicializados [:.
; -----------------------------------------------
section .data

	;
	; Garbage Collection
	;

	; Inicio do mapa Geral, indica onde esta cada mapa
	MapaMem:
		dd	MapaMemCadastro
		dd	MapaMemConversa
		dd 	MapaMemMensagem
		dd 	FimMapaMem

	; Mapa para Geral de Cadastro
	; Registro inicial, indica o estado da àrea de cadastro como um todo
	MapaMemCadastro:
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspCadastro
		at st_memoria.tamanho,  	dw TamMemCadastro
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend

	; A tabela em si
	%assign i 0
	%rep NUM_CADASTROS
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspCadastro + i
		at st_memoria.tamanho,  	dw TAM_ST_CADASTRO
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend

	  %assign i i + TAM_ST_CADASTRO
	%endrep

	; Mapa para Geral de Conversa
	; Registro inicial, indica o estado da àrea de conversa como um todo
	MapaMemConversa:
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspConversa
		at st_memoria.tamanho,  	dw TamMemConversa
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend	

	; A tabela em si
	%assign i 0
	%rep NUM_CONVERSAS
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspConversa + i
		at st_memoria.tamanho,  	dw TAM_ST_CONVERSA
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend

	  %assign i i + TAM_ST_CONVERSA
	%endrep

	; Mapa para Geral de Mensagem
	; Registro inicial, indica o estado da àrea de mensagem como um todo
	MapaMemMensagem:
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspMensagem
 		at st_memoria.tamanho,  	dw TamMemMensagem
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend

	; Restante do mapa
	; Sobra 12584 bytes = 8 * 1573 = 11 * 1144 = 22 * 572
	;%define TAM_ST_MENSAGEM 22	| 572 (atualmente)
	%define NUM_MENSAGENS (16 * 1024 - NUM_CADASTROS * TAM_ST_CADASTRO - NUM_CONVERSAS * TAM_ST_CONVERSA) / TAM_ST_MENSAGEM		; 1144 (atualmente, é o maximo pois no minimo uma mensagem tem 11 bytes - 1 caractere)
	%assign i 0
	%rep NUM_MENSAGENS
	  istruc st_memoria
		at st_memoria.endereco_real,	dd EspMensagem + i
		at st_memoria.tamanho,  	dw TAM_ST_MENSAGEM
		at st_memoria.status, 		db ST_CELULA_LIVRE
	  iend

	  %assign i i + TAM_ST_MENSAGEM
	%endrep

	; Fim do mapa de memoria
	FimMapaMem equ $-0

	;
	; Comandos
	;

	; Tabela de comandos
	tabelaComandos
		dd stc_Fim
		dd stc_Entrar
		dd stc_Sair
		dd stc_Chama
		dd stc_Fala
		dd stc_Cadastra
		dd stc_Status
		dd stc_Lista
	fimComandos equ $
		dd stc_Info


	; Nomes
	str_cmdFim	db "fim", 0x0
	str_cmdEntrar	db "entrar", 0x0
	str_cmdSair	db "sair", 0x0
	str_cmdChama	db "chama", 0x0
	str_cmdFala	db "fala", 0x0
	str_cmdCadastra	db "cadastra", 0x0
	str_cmdStatus	db "status", 0x0
	str_cmdLista	db "listatelefonica", 0x0
	str_cmdInfo	db "info", 0x0


	; Estruturas
	stc_Fim:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdFim
		at s_comando.ptFuncao,  dd cmdFim
	  iend

	stc_Entrar:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdEntrar
		at s_comando.ptFuncao,  dd cmdEntrar
	  iend

	stc_Sair:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdSair
		at s_comando.ptFuncao,  dd cmdSair
	  iend

	stc_Chama:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdChama
		at s_comando.ptFuncao,  dd cmdChama
	  iend

	stc_Fala:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdFala
		at s_comando.ptFuncao,  dd cmdFala
	  iend

	stc_Cadastra:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdCadastra
		at s_comando.ptFuncao,  dd cmdCadastra
	  iend

	stc_Status:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdStatus
		at s_comando.ptFuncao,  dd cmdStatus
	  iend

	stc_Lista:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdLista
		at s_comando.ptFuncao,  dd cmdLista
	  iend

	stc_Info:
	  istruc s_comando
		at s_comando.ptComando, dd str_cmdInfo
		at s_comando.ptFuncao,  dd cmdInfo
	  iend


	;
	; Chave primaria das conversas
	;
	conversa_pk	dw	0x0000
	
	;
	; Strings de marcação dos comandos
	;
	str_identa 		db "  ", 0x00
	str_fecha_tag		db ">", 0x0A, 0x00

	tag_telefone_abre	db "<telefone", 0x00
	tag_telefone_fecha	db "</telefone", 0x00
	
	tag_num_abre		db "<num>", 0x00
	tag_num_fecha		db "</num>", 0x00
	
	tag_status_abre		db "<status>", 0x00
	tag_status_fecha	db "</status>", 0x00
	
	tag_msg_abre		db "<msg>", 0x00
	tag_msg_fecha		db "</msg>", 0x00

	tag_nfeitas_abre	db "<nfeitas>", 0x00
	tag_nfeitas_fecha	db "</nfeitas>", 0x00

	tag_nrecebidas_abre	db "<nrecebidas>", 0x00
	tag_nrecebidas_fecha	db "</nrecebidas>", 0x00

	tag_ID_abre		db "<ID id=", 0x00
	tag_ID_fecha		db "</ID>", 0x00
	
	tag_usuario_abre	db "<usuario", 0x00
	tag_usuario_fecha	db "</usuario", 0x00
	
	tag_tel_abre		db "<tel>", 0x00
	tag_tel_fecha		db "</tel>", 0x00
	
	tag_nmsg_abre		db "<nmsg>", 0x00
	tag_nmsg_fecha		db "</nmsg>", 0x00


	;
	; Mensagens
	;
	str_erroArquivo		db "Arquivo de entrada nao informado ou nao foi possivel abri-lo", 0x0A, 0x00

	str_commonNumero 	db "o numero ", 0x00
	str_commonLinha 	db "a linha ", 0x00
	str_commonMotivo	db ". Motivo:", 0x00
	str_commonID		db "ID: ", 0x00

	str_commonLivre		db "Livre", 0x00
	str_commonOcupado	db "Ocupado", 0x00
	str_commonNaoCadastrado db "Nao Cadastrado", 0x00
	str_commonMsgDe		db "msg de ", 0x00

	str_erroNaoCadastrado		db " item nao cadastrado.", 0x0A, 0x00
	str_erroNumeroOcupado 		db " telefone ocupado.", 0x07, 0x0A, 0x00
	str_erroLinhaDisponivel		db " nao ha linha disponivel. Tente novamente mais tarde.", 0x0A, 0x00
	str_erroNumeroDisponivel	db " nao ha espaco disponivel. Tente novamente mais tarde.", 0x0A, 0x00
	str_erroMemoriaDisponivel	db " nao ha memoria disponivel. Tente novamente mais tarde.", 0x0A, 0x00
	str_erroNumeroGancho		db " telefone no gancho.", 0x0A, 0x00
	str_erroSemLinha		db " telefone sem linha.", 0x0A, 0x00
	str_erroLinhaDiferentes		db " os numeros nao estao na mesma linha.", 0x0A, 0x00

	str_erroCadastra		db "Nao foi possivel cadastrar ", 0x00
	str_erroEntrar			db "Nao foi possivel solicitar uma linha para ", 0x00
	str_erroChamar			db "Nao foi possivel chamar ", 0x00
	str_erroFalar			db "Nao foi possivel enviar uma mensagem", 0x00
	str_erroSair			db "Nao foi possivel colocar no gancho ", 0x00
	str_erroStatus			db "Nao foi possivel exibir o status da comunicacao por causa d", 0x00
	str_erroStatusComunicacao	db "Nao foi possivel exibir o status da comunicacao", 0x00
	str_erroID			db "ID: -1", 0x0A, 0x00

; -----------------------------------------------
;                .:] Codigo [:.
; -----------------------------------------------  	
section .text 
main:


	; No inicio do programa temos na pilha
	; | ..... |
	; | *argn |
	; | *.... |
	; | *arg1 |	
	; |  argc |	
	; |  ret  |	ESP

	
	;Verifica se foi passado o nome do arquivo
	mov	eax, [esp + 4]		;numero de parametros
	cmp	eax, 1
	jnz	.arquivo_informado	; Arquivo foi informado? tenta abri-lo


.erro_arquivo_acoes

	; Mensagem de erro no parametro
	print_str dword str_erroArquivo, 2
	jmp 	_sair			; termina o prorama

; -----------------------------------------------
; O arquivo foi informado corretamente
; -----------------------------------------------
.arquivo_informado
	mov eax, [esp + 8]		; Isso é a posição da pilha dos parametros

 	push	ebp			; Armazeana EBP

	mov 	ebp, eax		; EBP aponta para os parametros

	; Tenta abrir o arquivo
	push	dword [ebp + 4]		; parametro 1
	call	abre_arquivo
	descarta_pilha 1

	cmp	eax, 0			; Erro ao abrir ?
	jng	.erro_arquivo_acoes


	; Processa o arquivo
	push	tabelaComandos		; Param 2 para a funcao abaixo	(3)
	push	processa_comando	; Funcao q processa a linha	(2)
	push	eax			; Descrito do arquivo 		(1)
	call	processa_arquivo
	pop	eax			; Rearmazena o descritor de arquivo
	descarta_pilha 2		; Descarta os parametros
	
	push eax			; Descritor do arquivo
	call fecha_arquivo		; Fecha o arquivo
	descarta_pilha 1		; Descarta os parâmetros


	pop	ebp			; Restaura ebp
	
  _sair:

;_newline
;dump_mem 100900, MapaMem, 2
;dump_mem 100910, MapaMemCadastro, 5
;dump_mem 100915, EspCadastro, 10
;dump_mem 100920, MapaMemConversa, 5
;dump_mem 100925, EspConversa, 10
dump_mem 100930, MapaMemMensagem, 10
dump_mem 100935, EspMensagem, 20

	termina_programa 0







;--------------------------------------------
; COMANDOS
;--------------------------------------------
;%include "includes/comandos.asm"

; -----------------------------------------------
;          .:] Comandos do programa [:.
; -----------------------------------------------

; -----------------------------------------------
; [nome]  	cmdFim
; [descr] 	procedimento chamado pelo comando "fim"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
cmdFim:
	ccc_begin
	termina_programa 0
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdEntrar
; [descr] 	procedimento chamado pelo comando "entrar"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [28/06/2005 - 23:44]
; Versão 0.8
; Finalizada a versão WIP (work in progress), ainda falta verificar e manipular o status do telefone.
; Mensagens de erro caso nao haja linha foi adicionada.
;
; [29/06/2005 - 00:15]
; Versão 1.0
; Adicionada verificação e manipulação do status do telefone.
; Adicionadas mensagens de erro informando problemas com o status (tentando entrar 2)
;
; [13/07/2005 - 23:22]
; Versão 1.1
; Adicionada a possibilidade de um telefone estar no gancho mas ainda estar com uma comunicação
; Essa é a maneira como funciona um telefone de verdade. Quando o telefone que foi chamado é
; colocado no gancho, ele continua na comunicação até que o telefone que fez a chamada seja colocado no gancho.
; -----------------------------------------------
cmdEntrar:
	ccc_begin
	push	eax
	push	ebx
	push	ecx

	; Procura pelo telefone se esta cadastrado no sistema
	push	dword [parametro(1)]
	call procura_telefone_cadastrado
	descarta_pilha 1

	cmp	eax, 0x00		; Encontrou ?
	jne	.telefone_cadastrado

	; Erro
	print_str str_erroEntrar, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNaoCadastrado, 2	; nao cadastrado
	jmp	.fim


  .telefone_cadastrado
	; O numero existe
	mov	ebx, eax				; EBX := telefone que solicitou a linha
	mov	ecx, [ebx + st_memoria.endereco_real]	; ECX := endereco real
	xor	eax, eax				; EAX := 0 (compatibilidade com .solicita_linha)

	; Verifica se o telefone pode fazer ligações (se ele está no gancho e SEM comunicação)
	cmp	byte [ecx + st_telefone.status], MSK_TEL_LIVRE
	je	near .solicita_linha

	; O telefone nao está no GANCHO
	; Verifica se ele foi chamado e foi colocado no gancho em seguida
	cmp	byte [ecx + st_telefone.status], MSK_TEL_TEM_LINHA
	jne	.telefone_ocupado

	; Possui o status correto, verifica a comunicação (seguranca)
	push	ebx
	call procura_conversa_telefone
	descarta_pilha 1

	cmp	eax, 0x00			; Se não possui
	jne	.solicita_linha


  .telefone_ocupado

	; Erro
	print_str str_erroEntrar, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroOcupado, 2	; ocupado
	jmp	.fim


  .solicita_linha
	; Telefone foi tirado do gancho
	or	byte [ecx + st_telefone.status], MSK_TEL_FORA_GANCHO
	cmp	eax, 0x00			; EAX := possui o endereco da celula da conversa atual do numero (caso exista)
	jne	near .fim				; Se já possui uma conversa ], entao SAI

	; Solicita uma linha
	push	TAM_ST_CONVERSA		; (2) quantidade de memoria a solicitar
	push	MAPA_CONVERSA		; (1) Mapa a manipular
	call malloc_z
	descarta_pilha 2

	cmp	eax, 0x0		; Alocou memoria ?
	jne	.alocou_memoria

	; Erro
	print_str str_erroEntrar, 2		; mensagem
	print_str str_commonNumero,  2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroLinhaDisponivel, 2	; falta espaco
	jmp	.fim


  .alocou_memoria
;	; Telefone possui linha
;	or	byte [ecx + st_telefone.status], MSK_TEL_TEM_LINHA
; [01/07/2005 - 01:14]
; Da minha concepção, o fato de um telefone ter conseguido linha nao quer dizerque ele está já em comunicação
; Isso me facilitará mais lá na frente

%ifdef DEBUG
;eax := endereco para o registro da conversa
;ebx := endereco para o telefone que solicitou a linha
	_newline
	dump_regs 888000 + TAM_ST_CONVERSA
%endif

	; Cadastra a conversa
	; Aponta eax para oa endereco real (nao ha problema em fazer isso aqui pois nao há programação concorrente)
	; Entoa nao ha risco de ser executado um garbage collection o cadastro de cada elemento do "objeto" conversa
	; (e mesmo que fosse possivel, é virtualmente impossivel que isso ocorra entre um MOV e outro :-P )
	mov	eax, [eax + st_memoria.endereco_real]
	mov	word [eax + st_conversa.id], 0xFFFF		; ID (linha reservada, mas nao utilizada ainda)
	mov	dword [eax + st_conversa.tel_1], ebx		; Armazena o telefone que solicitou a linha
	mov	byte [eax + st_conversa.msg_1], 0x00		; Mensagens enviadas pelo telefone que solicitou a linha


%ifdef DEBUG
;registro inserido
	dump_mem 888000 + TAM_ST_CONVERSA, eax, 1
	_newline
%endif


  .fim
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdSair
; [descr] 	procedimento chamado pelo comando "sair"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [29/06/2005 - 00:15]
; Versão WIP
;
; [30/06/2005 - 23:53]
; Versão WIP
; Altera o status do telefone E da conversa da qual ele saiu (caso ele tenha estado em alguma)
;
; [01/07/2005 - 00:30]
; Versão WIP.
; O segredo é disponibilizar código "funcional" o mais rapido possivel e acertar tudo depois.
;
; [08/07/2005 - 11:15]
; Versão 1.0
; Finalmente acertei a funcao :-P
; -----------------------------------------------
cmdSair:
	ccc_begin
	push	eax
	push	ebx
	push	ecx
	push	edx

	; Procura pelo telefone se esta cadastrado no sistema
	push	dword [parametro(1)]
	call procura_telefone_cadastrado
	descarta_pilha 1

	cmp	eax, 0x00			; Encontrou?
	jne	.verifica_status_telefone

	; Erro
	print_str str_erroSair, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNaoCadastrado, 2	; nao cadastrado
	jmp	.fim


  .verifica_status_telefone

	; Altera o status do telefone
	mov	ebx, [eax + st_memoria.endereco_real]		; Aponta para o telefone | EAX := celula | EBX := resgistro do telefone
	cmp	byte [ebx + st_telefone.status], MSK_TEL_LIVRE	; Telefone jah esta livre? (tá zuando comigo né?)

	jne	.procura_conversas

	; Erro
	print_str str_erroSair, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroGancho, 2	; no gancho
	jmp	.fim


  .procura_conversas

	push	eax			; Celula do telefone
	call procura_conversa_telefone	; Procura a comunicacao
	mov	ebx, eax		; Celula da conversa (ou 0 em caso de erro)
	pop	eax			; Restaura a celula do telefone

	cmp	ebx, 0x00		; Encontrou uma conversa?
	je	.telefone_livre		; 

	; EAX := celula do telefone
	; EBX := celula da conversa

	mov	edx, dword [ebx + st_memoria.endereco_real]	; Aponta para a conversa
	cmp	dword [edx + st_conversa.tel_1], eax
	jne	.segundo_telefone

	;
	; Primeiro Telefone
	; Se ele sair, a comunicação termina
	;

	; Libera a conversa
	mov	byte [ebx + st_memoria.status], ST_CELULA_LIVRE	; Libera a memoria

	; Libera a comunicação do segundo telefone
	mov 	edx, dword [edx + st_conversa.tel_2]			; EDX := celula do telefone 2
	mov	edx, [edx + st_memoria.endereco_real]			; EDX := endereço do telefone 2
	xor	byte [edx + st_telefone.status], MSK_TEL_TEM_LINHA	; Sem comunicação

	; Poe o telefone no gancho
	mov	edx, [eax + st_memoria.endereco_real]		; Aponta para o telefone
	and	byte [edx + st_telefone.status], MSK_TEL_LIVRE	; Libera o telefone (poe no gancho e tira da comunicação)
	jmp 	.fim


  .segundo_telefone

	;
	; Segundo Telefone
	; Apenas coloca-o no gancho
	;

	mov	edx, [eax + st_memoria.endereco_real]			; Aponta para o telefone
	xor	byte [edx + st_telefone.status], MSK_TEL_FORA_GANCHO	; Poe no gancho e mantém o status da comunicação
	jmp	.fim


  .telefone_livre

	; O telefone nao possui nenhuma comunicacao.
	; Provavelmente:
	; [*] ele foi tirado do gancho e nao conseguiu linha
	; [*] o telefone que iniciou a conversa desligou (o famoso túuuuuuuuuuu...)
	mov	eax, [eax + st_memoria.endereco_real]		; Aponta para o telefone
	and	byte [eax + st_telefone.status], MSK_TEL_LIVRE	; Telefone esta livre


  .fim
	pop 	edx
	pop 	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdChama
; [descr] 	procedimento chamado pelo comando "chama"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [05/07/2005 - 00:18]
; Versão 1.0
; -----------------------------------------------
cmdChama:
	ccc_begin 2				; 2 variaveis locais, 1 para o ptr para a celula de cada telefone
	push	eax
	push	ebx
	push	ecx
	push	edx

	jmp	.inicio
	
	; Movi os erros aqui pra cima pois no "pula pula" de um passo pro outro
	; estava tendo problemas com a distância (estava passando do permitido para um short jump)

  .erro01
	; Erro 01
	print_str str_erroChamar, 2		; mensagem
	print_char ch				; caractere que completa a mensagem
	print_str str_commonNumero, 2		; item
	printn_str edx, 8, 2			; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNaoCadastrado, 2	; nao cadastrado
	print_str str_erroID			; ID -1
	jmp	.fim

	
  .erro02
	; Erro 02
	print_str str_erroChamar, 2		; mensagem
	print_char ch				; caractere que completa a mensagem
	print_str str_commonNumero, 2		; item
	printn_str edx, 8, 2			; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroGancho, 2	; no gancho
	print_str str_erroID			; ID -1	
	jmp	.fim


  .erro03
	; Erro 03
	print_str str_erroChamar, 2		; mensagem
	print_char ch				; caractere que completa a mensagem
	print_str str_commonNumero, 2		; item
	printn_str edx, 8, 2			; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroOcupado, 2	; telefone esta ocupado
	print_str str_erroID			; ID -1	
	jmp	.fim	


  .inicio		
	
	; O parametro vira no formato <telefone>{espaco}<telefone>
	; tenho que substituir esse espaco por 0x00 primeiro
	mov	edx, dword [parametro(1)]
	push	edx
	call getparametro_z
				; Nao descarta pois sera parametro da proxima funcao

	; ECX := EAX := numero de caracteres
	xor	ecx, ecx
	mov	ch, 'd'		; caractere que vai completar a mensagem
	mov	cl, al		; numero de caracteres no telefone 1


  .verifica_cadastro

	; Procura pelo telefone se esta cadastrado no sistema
	call procura_telefone_cadastrado
	descarta_pilha 1

	cmp	eax, 0x00		; Nao encontrou o telefone
	je	.erro01


  .telefone_cadastrado

	; Altera o status do telefone
	mov	ebx, [eax + st_memoria.endereco_real]		; Aponta para o telefone | EAX := celula | EBX := resgistro do teleofne

	cmp	byte [ebx + st_telefone.status], MSK_TEL_LIVRE	; Telefone no gancho ?
	jne	.telefone_ocupado

	cmp	ch, 0x0				; Se o telefone está sendo chamado, ele PODE estar no gancho
	je	.verifica_conversa		; O telefone esta sendo chamado, nao exige que ele esteja fora do gancho

	jmp	.erro02


  .telefone_ocupado
	
	; Telefone nao esta no gancho
	cmp	ch, 0x0				; Se o telefone está sendo chamado, ele DEVE estar no gancho
	je	.erro03				; Por isso nao pode chegar aqui, se chegar é porque ele está ocupado :-D e ele nao pode estar

	cmp	byte [ebx + st_telefone.status], MSK_TEL_FORA_GANCHO	; Telefone nao esta em comunicacao?
	jne	.erro03							; Exige que o telefone que esta chamando esteja apenas fora do gancho (isso indica que ele solicitou uma linha)
									; Mais na frente verificará se ele realmente está em alguma comunicação, por isso nao precisa de um novo status


  .proximo_numero

	; ch := caractere que completa as mensagens
	; cl := numero de caracteres do ultimo telefone manipulado

	cmp	ch, 0x0
	je	.verifica_conversa

	xor	ch, ch				; Retira o caractere que completa a mensagem

	mov	dword [varlocal(1)], eax	; Amazena a celula do primeiro telefone

;dump_regs 44444

	; Verifica os status do Telefone 2
	mov	edx, dword [parametro(1)]
	add	edx, ecx
;	add	ecx, dword [parametro(1)]
;	mov	edx, ecx
	inc	edx				; Aponta para o endereços correto
	push	edx				; Sera utilizado em .verifica_cadastro
;	xor	ch, ch				; Zera

;dump_mem 22222, edx, 1

	jmp	.verifica_cadastro


  .verifica_conversa

	; EDX := ptr para a string do 2nd telefone
	; ECX := numero de caracteres do 1st telefone

	mov	dword [varlocal(2)], eax	; Amazena a celula do segundo telefone

;
;_newline	
;dump_regs 11111

	push	dword [varlocal(1)]		; Celula onde se encontra o telefone
	call procura_conversa_telefone
	descarta_pilha 1

;
;dump_regs 99999
;_newline

	cmp	eax, 0x0			; Encontrou?
	jne	.inicia_conversa

	; Erro
; 	print_str str_erroChamar, 2		; mensagem
; 	print_char ch				; caractere que completa a mensagem
; 	print_str str_commonNumero, 2		; item
; 	printn_str edx, 8, 2			; referencia
; 	print_str str_commonMotivo, 2		; "motivo"
; 	print_str str_erroNaoCadastrado, 2	; nao cadastrado

;
;_newline
;dump_mem 99999, dword [varlocal(1)], 2
;_newline
	jmp	.fim


  .inicia_conversa

	mov	eax, [eax + st_memoria.endereco_real]	; Aponta para o endereco
	
	; Incrementa a chave primaria
	xor	ebx, ebx
	mov	bx, word [conversa_pk]
	inc	bx
	mov	word [conversa_pk], bx
	
	; Atualizaa os dados da conversa
	mov	word [eax + st_conversa.id], bx		; ID

	; Imprime o ID da comunicação
	print_str str_commonID
	push	eax
	movzx	eax, bx
	call	int2ascii
	pop	eax
	_newline

	mov	ebx, dword [varlocal(2)]		; Célula do segundo telefone
	mov	dword [eax + st_conversa.tel_2], ebx

	mov	byte [eax + st_conversa.msg_2], 0x00	; Num de mensagens de tel 2

	; Atualiza o status dos telefones
	mov	ebx, [ebx + st_memoria.endereco_real]	; Telefone 2
	or	byte [ebx + st_telefone.status], MSK_TEL_TEM_LINHA | MSK_TEL_FORA_GANCHO
	inc	word [ebx + st_telefone.recebeu]	; Recebeu mais uma ligação

	mov 	ebx, dword [eax + st_conversa.tel_1]	; Telefone 1
	mov	ebx, [ebx + st_memoria.endereco_real]
	or	byte [ebx + st_telefone.status], MSK_TEL_TEM_LINHA	; Esse telefone ja esta fora do gancho :-D
	inc	word [ebx + st_telefone.chamou]		; Fez mais uam ligação


  .fim

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdFala
; [descr] 	procedimento chamado pelo comando "fala"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
cmdFala:
	ccc_begin	3	; 1 variavel local
	push	eax
	push	ebx
	push	ecx
	push	edx

	; varlocal(1) := CONVERSA
	; varlocal(2) := telefone 1
	; varlocal(3) := telefone 2

	;
	; Apagar as mensagens que com o status maior que 2
	;
	push	dword 2			; (1) Status minimo a se manter
	call libera_mensagens
	descarta_pilha 1

	; Zera
	mov	dword [varlocal(1)], 0x00
	xor	ecx, ecx

	; O parametro vira no formato <telefone>{espaco}<telefone>{espaco}<mensagem>
	; tenho que substituir esses espacos por 0x00
	mov	edx, dword [parametro(1)]
	push	edx


  .inicio

	call getparametro_z	; Nao descarta pois sera parametro da proxima funcao

	; CL := AL := numero de caracteres
	mov	cl, al

	; Procura pelo telefone se esta cadastrado no sistema
	call procura_telefone_cadastrado
	descarta_pilha 1

	cmp	eax, 0x00			; Nao encontrou o telefone
	jne	.armazena_telefone_1

	; Erro
	print_str str_erroFalar, 2		; mensagem
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNaoCadastrado, 2	; nao cadastrado
	jmp	.fim


  .armazena_telefone_1
	; Armazena o endereco dos telefones
	mov	dword [varlocal(3)], eax	; telefone 2 (primeiro vai receber o valor do tel 1 e depois sera sobrescrito pel ovalor do tel 2
						; No problems - apenas fiz isso pra aproveita a estrutura (coisas de assembly)

	cmp	ch, 0x00			; Se nao for segundo numero, nao sobreescreve o primeiro
	jne	.verifica_linha
	mov	dword [varlocal(2)], eax	; telefone 1


  .verifica_linha

	push	eax				; Celula onde se encontra o telefone
	call procura_conversa_telefone
	descarta_pilha 1

	cmp	eax, 0x00			; Nao encontrou o telefone
	jne	.proximo_numero

	; Erro
	print_str str_erroFalar, 2		; mensagem
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroSemLinha, 2		; nao cadastrado
	jmp	.fim


  .proximo_numero

	cmp	ch, 0x00			; Ja verificou o segundo numero?
	jne	.verifica_conversa

	mov	dword [varlocal(1)], eax	; varlocal(1) := conversa do telefone 1

	add	edx, ecx			; EDX := Proximo texto a ser verificado (ptr para o numero do segundo telefone)
	inc	edx				; Pula o 0x00

	mov	ch, 0x01			; Asinala que ja esta verificando o segundo telefone
	push	edx
	jmp	.inicio


	; Erro
	print_str str_erroFalar, 2		; mensagem
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroDisponivel, 2	; ocupado
	jmp	.fim


  .verifica_conversa

	cmp	dword [varlocal(1)], eax	; Verifica se eles sao da mesma conversa
	je	.reserva_memoria

	; Erro
	print_str str_erroFalar, 2		; mensagem
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroLinhaDiferentes, 2	; linhas diferentes
	jmp	.fim


  .reserva_memoria

	xor	ch, ch		; Zera o indicador que ja leu o segundo numero
	add	edx, ecx	; EDX := ptr para mensagem
	inc	edx

	; Calcula quantos bytes devera armazenar
	push	edx
	call strlen_z
	descarta_pilha 1

	; ECX := Numero de bytes necessarios para a mensagem
	mov	ecx, eax
	inc	ecx

	; EAX := numero de bytes necessarios
	add	eax, TAM_ST_MENSAGEM + 1	; Numero de bytes = numero de caracteres da mensagem + bytes para a estrutura de mensagem
	
	; Reserva a memoria
	push	eax		; (2) Quant de memoria
	push	MAPA_MENSAGEM	; (1) Mapa a manipular
	call malloc_z
	descarta_pilha 2

	; Possui memoria suficiente ?
	cmp	eax, 0x00
	jne	.grava_mensagem

	; Erro
	print_str str_erroFalar, 2		; mensagem
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroMemoriaDisponivel, 2	; nao ha memoria disponivel. Alguem(ns) tem uma mensagem MUITO GRANDE que ainda nao foi descartada (pois deve ser a ultima mensagem)
	jmp	.fim


  .grava_mensagem
	; Move a mensagem
	cld
	mov	esi, edx
	mov	edi, dword [eax + st_memoria.endereco_real]	; EDI := Enderço do inicio do registro da mensagem
	add	edi, st_mensagem.texto				; Aponta para o lugar correto
	rep 	movsb

	; EDX := endereço da conversa
	mov	edx, [eax + st_memoria.endereco_real]

	; Insere os outros dados da mensagem
	mov	ecx, dword [varlocal(1)]			; ID da CONVERSA
	mov	ecx, [ecx + st_memoria.endereco_real]
	push	ecx						; Armazena o endereco da conversa
	mov	cx, word [ecx + st_conversa.id]

	mov	word [edx + st_mensagem.id_conversa], cx

	mov	ecx, dword [varlocal(3)]			; Destinatario
	mov	dword [edx + st_mensagem.para], ecx

	mov	ecx, dword [varlocal(2)]			; Remetente
	mov	dword [edx + st_mensagem.de], ecx
	pop	eax						; Recupera o endereco da memoria

	;
	; EAX := Endereco da Conversa
	;

	; Atualiza o status das mensagens (para manter apenas a ultiam mensagem)
	push	dword eax
	call	status_mensagens
	descarta_pilha 1

	;
	; Incrementa o numero de mensagens enviadas do Remetente

	
	cmp	dword [eax + st_conversa.tel_1], ecx	; Verifica se o remetente é o primeiro ou o segundo telefone
	jne	.segundo_telefone

	; Atualiza os dados do Primeiro telefone	
	inc	byte [eax + st_conversa.msg_1]		; Atualiza o numero de mensagens enviadas pelo primeiro telefone
	jmp	.imprime_mensagem


  .segundo_telefone
	inc	byte [eax + st_conversa.msg_2]		; Atualiza o numero de mensagens enviadas pelo segundo telefone

  
  .imprime_mensagem
	; Imprime a mensagem
	mov	ecx, dword [ecx + st_memoria.endereco_real]	; Aponta ECX para o texto do telefone
	add	edx, st_mensagem.texto				; Aponta EDX para o inicio do texto da mensagem
	
	print_str str_commonMsgDe
	printn_str ecx, 8
	print_char ':'
	print_char ' '
	print_str edx
	_newline

dump_mem 100930, MapaMemMensagem, 10
dump_mem 100935, EspMensagem, 20
	

  .fim

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdCadastra
; [descr] 	procedimento chamado pelo comando "cadastra"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [24/06/2005 - 21:55]
; Versão 0.9. Falta implementar a mensagem de erro caso nao houver mais espaço
;
; [28/06/2005 - 22:19]
; Versão 1.0. Implementada as mensagens de erro e alteradas algumas convenções de chamada
; -----------------------------------------------
cmdCadastra:
	ccc_begin
	push eax

	; Reserva a memoria necessaria
	push	TAM_ST_CADASTRO		; (2) quantidade de memoria a solicitar
	push	MAPA_CADASTRO		; (1) Mapa a manipular
	call malloc_z
	descarta_pilha 2

	cmp	eax, 0x00
	jne	.cadastra		; Alocou memoria

	; Erro
	print_str str_erroCadastra, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str dword [parametro(1)], 8, 2	; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNumeroDisponivel, 2	; ocupado
	jmp	.fim


  .cadastra

	; Copia o telefone para o cadastro
	push	eax					; Salva eax

	push	dword 0x08				; (3) numero de caracteres a copiar
	push	dword [eax + st_telefone.numero]	; (2) destino
	push	dword [parametro(1)]			; (1) origem
	call strncpy_z					; (eax) retorna o numero de caracteres copiados
	descarta_pilha 3

; ********************************************************
; EAX := numero de caracteres copiados
; **TODO** ADICIONAR ZEROS NOS ESPAÇOS QUE SOBRARAM - EVITA BUGs
; ********************************************************
	
	pop	eax					; Restaura eax


	mov	eax, [eax + st_memoria.endereco_real]		; Aponta eax para o endereco real
	mov	byte [eax + st_telefone.status], MSK_TEL_LIVRE	; Telefone no gancho e SEM comunicacao
	mov	word [eax + st_telefone.chamou], 0x00		; 0 ligacoes feitas
	mov	word [eax + st_telefone.recebeu], 0x00		; 0 ligacoes recebidas

%ifdef DEBUG
; EAX := endereco para o registro de cadastro
; Imprime o registro inserido
dump_mem 333333, eax, 1
_newline
%endif


  .fim

	pop eax
	ccc_end		; Restaura o ambiente
ret


; -----------------------------------------------
; [nome]  	cmdStatus
; [descr] 	procedimento chamado pelo comando "status"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [13/07/2005 - 22:51]
; Versão 1.0
; Falta ainda implementar a <MSG> da conversa. O que colocar???
; -----------------------------------------------
cmdStatus:
	ccc_begin 1				; 1 variavel local
	push	eax
	push	ebx
	push	ecx
	push	edx

	; O parametro vira no formato <telefone>{espaco}<telefone>
	; tenho que substituir esse espaco por 0x00 primeiro
	mov	edx, dword [parametro(1)]
	push	edx
	call getparametro_z	; Nao descarta pois sera parametro da proxima funcao

	; ECX := EAX := numero de caracteres
	mov	ecx, eax


  .verifica_cadastro


	; Procura pelo telefone se esta cadastrado no sistema
	call procura_telefone_cadastrado
	descarta_pilha 1

	cmp	eax, 0x00			; Nao encontrou o telefone
	jne	.verifica_linha

	; Erro
	print_str str_erroStatus, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str edx, 8, 2			; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroNaoCadastrado, 2	; nao cadastrado
	jmp	.fim


  .verifica_linha

	push	eax				; Celula onde se encontra o telefone
	call procura_conversa_telefone
	descarta_pilha 1

	cmp	eax, 0x00			; Nao encontrou o telefone
	jne	.proximo_numero

	; Erro
	print_str str_erroStatus, 2		; mensagem
	print_str str_commonNumero, 2		; item
	printn_str edx, 8, 2			; referencia
	print_str str_commonMotivo, 2		; "motivo"
	print_str str_erroSemLinha, 2		; nao cadastrado
	jmp	.fim


  .proximo_numero

	; CL := numero de caracteres do ultimo telefone manipulado

	cmp	edx, dword [parametro(1)]
	jne	.verifica_conversa

	mov	dword [varlocal(1)], eax	; Amazena a celula da linha do primeiro telefone

	; Verifica os status do segundo telefone
	mov	edx, dword [parametro(1)]
	add	edx, ecx
	inc	edx				; Aponta para o endereços correto
	push	edx				; Sera utilizado em .verifica_cadastro

	jmp	.verifica_cadastro


  .verifica_conversa

  	; Verifica se os telefones são da mesma linha
	cmp	eax, dword [varlocal(1)]
	je	.exibe_dados

	; Erro
	print_str str_erroStatusComunicacao, 2	; mensagem
	print_str str_commonMotivo, 2
	print_str str_erroLinhaDiferentes, 2
	jmp	.fim


  .exibe_dados

	; Exibe os dados
	mov	ebx, [eax + st_memoria.endereco_real]	; EBX := Endereco da conversa
	xor	eax, eax				; EAX := ID da conversa
	mov	ax, word [ebx + st_conversa.id]


	; Inicia a marcação XML
	print_str tag_ID_abre
	call	int2ascii
	print_str str_fecha_tag


	; Mensagem de Status ???
	print_str str_identa
	print_str tag_msg_abre
	print_str tag_msg_fecha
	_newline


	; Usuarios [ ABRE ]
	print_str str_identa
	print_str tag_usuario_abre
	print_char 's'
	print_str str_fecha_tag


	; Prepara a impressão do usuario 1
	xor	eax, eax
	mov	edx, dword [ebx + st_conversa.tel_1]	; EDX := celula onde esta o telefone
	mov	al, byte [ebx + st_conversa.msg_1]	; EAX := Numero de mensagens enviadas pelo telefone


  .imprime_usuario
	
	; USUARIO [ ABRE ]
	print_str str_identa
	print_str str_identa
	print_str tag_usuario_abre
	print_str str_fecha_tag

	; Numero do telefone
	print_str str_identa
	print_str str_identa
	print_str str_identa
	print_str tag_tel_abre

	; EDX := celula onde esta o telefone 1
	; [EDX] := Endereço da estrutura para o telefone 1
	; [EDX] + st_telefone.numero := Endereço da string do telefone (nao precisa pois deveria somar 0)
	printn_str dword [edx], 8

	print_str tag_tel_fecha
	_newline

	; Enviadas
	print_str str_identa
	print_str str_identa
	print_str str_identa
	print_str tag_nmsg_abre
	call	int2ascii		;
	print_str tag_nmsg_fecha
	_newline

	; USUARIO [ FECHA ]
	print_str str_identa
	print_str str_identa
	print_str tag_usuario_fecha
	print_str str_fecha_tag	


	; Imprime o segundo
	cmp	edx, dword [ebx + st_conversa.tel_1]
	jne	.fecha_usuarios
	mov	edx, dword [ebx + st_conversa.tel_2]	; EDX := celula onde esta o telefone
	mov	al, byte [ebx + st_conversa.msg_2]	; EAX := Numero de mensagens enviadas pelo telefone
	jmp	.imprime_usuario


  .fecha_usuarios

	; usuarios [FECHA]
	print_str str_identa
	print_str tag_usuario_fecha
	print_char 's'
	print_str str_fecha_tag

	; Finaliza a marcação XML
	print_str tag_ID_fecha
	_newline


  .fim

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdLista
; [descr] 	procedimento chamado pelo comando "listatelefonica"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [24/06/2005 - 21:54]
; Versão Final
; -----------------------------------------------
cmdLista:
	ccc_begin
	push eax
	push ebx
	push ecx

	; Inicio do node xml
	print_str tag_telefone_abre
	print_char 's'
	print_char '>'
	_newline

	; Cria um node para cada telefone cadastrado
	mov	ecx, MapaMemCadastro
	jmp	.proximo_registro


  .imprime

	; Imprime
	print_str str_identa
	print_str tag_telefone_abre
	print_char '>'

	printn_str dword [ ecx + st_memoria.endereco_real ], 8

	print_str tag_telefone_fecha
	print_str str_fecha_tag


  .proximo_registro
  
	; Avanca para o proximo elemento na tabela
	add	ecx, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	ecx, MapaMemConversa
	jge	.fim_lista

	; Apenas imprime se a memoria estiver ocupada
	cmp	byte [ecx + st_memoria.status], byte ST_CELULA_OCUPADA
	je	.imprime
	jmp	.proximo_registro


  .fim_lista

	; Fim do node xml
	print_str tag_telefone_fecha
	print_char 's'
	print_char '>'
	_newline
	
	pop ecx
	pop ebx
	pop eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdInfo
; [descr] 	procedimento chamado pelo comando "info"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; CHANGELOG
; -----------------------------------------------
; [08/07/2005 - 12:29]
; Versão Final
; -----------------------------------------------
cmdInfo:
	ccc_begin 1	; 1 variavel local
	push	eax
	push	ebx	; Vai armazenar numero de ligacoes feitas
	push	ecx	; Vai armazenar o numero de recebidas
	push	edx	; Mensagem de status

	; Zera os contadores
	xor	ebx, ebx
	xor	ecx, ecx

	; Abre a marcação XML
	print_str tag_telefone_abre
	print_char '>'
	_newline


	; Imprime o numero
	print_str str_identa
	print_str tag_num_abre
	printn_str dword [parametro(1)], 8
	print_str tag_num_fecha
	_newline


	; Imprime o status
	print_str str_identa
	print_str tag_status_abre

	; Verifica o Status
	push	dword [parametro(1)]
	call	procura_telefone_cadastrado	; Verifica se o telefone esta cadastrado
	descarta_pilha 1

	cmp	eax, 0x00			; Esta cadastrado?
	jne	.telefone_cadastrado

	;Nao cadastrado
	print_char '-'
	print_char '1'

	mov	edx, str_commonNaoCadastrado
	jmp	.continua_impressao


  .telefone_cadastrado

	; O telefone esta cadastrado, entao verifica seu status
	mov	dword [varlocal(1)], eax		; celula do telefone
	mov	eax, [eax + st_memoria.endereco_real]
	mov	bx, word [eax + st_telefone.chamou]
	mov	cx, word [eax + st_telefone.recebeu]

	; Verifica o status
	cmp	byte [eax + st_telefone.status], MSK_TEL_LIVRE
	jne	.verifica_comunicacao

	push	eax
	print_char '0'
	mov	edx, str_commonLivre
	pop	eax
	jmp	.continua_impressao


  .verifica_comunicacao

	; Todos os outros status correspondem ao telefone oupado
	mov	edx, str_commonOcupado

	cmp	byte [eax + st_telefone.status], MSK_TEL_TEM_LINHA | MSK_TEL_FORA_GANCHO
	jne	.procura_linha

	push	eax
	print_char '3'
	pop	eax
	jmp	.continua_impressao


  .procura_linha

	;O telefone nao está livre, verifica se ele possui alguam comunicação (linha)
	push	dword [varlocal(1)]		; Celula onde se encontra o telefone
	call procura_conversa_telefone
	descarta_pilha 1
	cmp	eax, 0x00			; Encontrou?
	jne	.com_linha

	; Telefone nao possui linha e nao esta livre
	push	eax
	print_char '1'
	pop	eax
	jmp	.continua_impressao


  .com_linha
	; Se ele estiver fora do gancho o status é 2
	; Caso contrario é 4 (o telefone foi chamado e foi colocado no gancho, mas a linha continua ativa até que quem chamou desligue - assim que funciona no mundo real)
	mov	eax, dword [varlocal(1)]		; celula do telefone
	mov	eax, [eax + st_memoria.endereco_real]	; endereço real

	cmp	byte [eax + st_telefone.status], MSK_TEL_FORA_GANCHO	; Fora do gancho
	jne	.outro_status

	push	eax
	print_char '2'
	pop	eax
	jmp	.continua_impressao


  .outro_status

	; Qualquer outro status
	push	eax
	print_char '4'
	pop	eax
	jmp	.continua_impressao


  .continua_impressao

	; Continua imprimindo

	print_str tag_status_fecha
	_newline


	; Imprime a mensagem do status
	print_str str_identa
	print_str tag_msg_abre
	print_str edx
	print_str tag_msg_fecha
	_newline


	; Imprime o numero de ligacoes feitas
	print_str str_identa
	print_str tag_nfeitas_abre
	mov	eax, ebx
	call	int2ascii
	print_str tag_nfeitas_fecha
	_newline


	; Imprime o numero de ligacoes recebidas
	print_str str_identa
	print_str tag_nrecebidas_abre
	mov	eax, ecx
	call	int2ascii
	print_str tag_nrecebidas_fecha
	_newline
	
	; Abre a marcação XML
	print_str tag_telefone_fecha
	print_char '>'
	_newline

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	ccc_end
ret