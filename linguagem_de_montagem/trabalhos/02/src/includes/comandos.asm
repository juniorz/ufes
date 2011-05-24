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
cmdEntrar:
	ccc_begin
	push	eax

mov	eax, dword[parametro(1)]
add	eax, 7
push	eax
call procura_telefone
descarta_pilha
dump_regs 888888


	pop	eax
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdSair
; [descr] 	procedimento chamado pelo comando "sair"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
cmdSair:
	ccc_begin
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdChama
; [descr] 	procedimento chamado pelo comando "chama"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
cmdChama:
	ccc_begin
	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdFala
; [descr] 	procedimento chamado pelo comando "fala"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
cmdFala:
	ccc_begin
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
; Versão 0.9. Falta implementar a mensagem de erro caso nao houver mais esaço (???)
; -----------------------------------------------
cmdCadastra:
	ccc_begin
	push eax

	; Reserva a memoria necessaria
	push	TAM_ST_CADASTRO		; (2) quantidade de memoria a solicitar
	push	MAPA_CADASTRO		; (1) Mapa a manipular
	call malloc_z
	descarta_pilha 2

	cmp	eax, 0x0		
	jge	.cadastra		; Alocou memoria

	;
	; Erro ao cadastrar
	;
	nop
	jmp	.fim


  .cadastra

	; Copia o telefone para o cadastro
	push	eax					; Salva eax

	push	dword 0x08				; (3) numero de caracteres a copiar
	push	dword [eax + st_telefone.numero]	; (2) destino
	push	dword [parametro(1)]			; (1) origem
	call strncpy_z					; (eax) retorna o numero de caracteres copiados
	descarta_pilha 3

	pop	eax					; Restaura eax


	push	ebx

	mov	ebx, [eax]
	add	ebx, st_telefone.status
	mov	byte [ebx], ST_TEL_GANCH	; Telefone no gancho

	mov	ebx, [eax]
	add	ebx, st_telefone.chamou
	mov	word [ebx], 0			; 0 ligacoes feitas

	mov	ebx, [eax]
	add	ebx, st_telefone.recebeu
	mov	word [ebx], 0			; 0 ligacoes recebidas

	pop	ebx

%ifdef DEBUG
;Imprime o registro inserido
dump_mem 333333, [eax], 1
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
cmdStatus:
	ccc_begin



	ccc_end
ret


; -----------------------------------------------
; [nome]  	cmdLista
; [descr] 	procedimento chamado pelo comando "listatelefonica"
; [param] 	(1) ptr para string do comando
; -----------------------------------------------
; Changelog
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

	print_str dword [ ecx + st_memoria.endereco_real ]

	print_str tag_telefone_abre
	print_char '/'
	print_char '>'
	_newline


  .proximo_registro
  
	; Avanca para o proximo elemento na tabela
	add	ecx, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	ecx, MapaMemConversa
	jge	.fim_lista

	; Apenas imprime se a memoria estiver ocupada
	cmp	byte [ecx + st_memoria.status], byte ST_MEM_OCUPADA
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
cmdInfo:
	ccc_begin
	ccc_end
ret



; -----------------------------------------------
; [nome]  	procura_telefone
; [descr] 	procedimento chamado pelo comando "fim"
; [param] 	(1) ptr para o numero do telefone
; [return]	(eax) ptr para a celula onde se encontra o teleofne
; -----------------------------------------------
procura_telefone
	ccc_begin
	push	ebx
	push	ecx

	; Armazena o numer ode caracteres a comparar em eax
	push dword [parametro(1)]
	call strlen_z
	descarta_pilha 1

print_str dword [parametro(1)]
	
mov ebx, dword [parametro(1)]
	
dump_regs 123454321

	cld	; limpa o flag de direcao
	mov	ebx, MapaMemCadastro			; mapa de memoria

  .compara_telefone

	; Avanca para o proximo elemento na tabela
	add	ebx, TAM_ST_MEMORIA

	; Chegou ao fim ?
	cmp	ebx, MapaMemConversa
	jge	.erro

	mov	esi, dword [parametro(1)]		; aponta esi para a string a ser processada
	mov 	edi, [ebx]				; aponta edi para o comando atual
	mov	edi, [edi + st_telefone.numero]		; aponta edi para a string do telefone atual

	;
	; Compara enquanto for igual
	;
	mov	ecx, eax				; numero de caracteres a comparar
	repe	cmpsb					; compara enquanto as strings coincidirem E enquanto houver algum caractere a comparar (ecx > 0)
	jne	.compara_telefone			; os comandos coincidem


  .retorna
  
	; Retorna o endereço em eax
	mov	eax, ecx


  .erro	

	; Nao achou
	xor	eax, eax


  .fim

	pop	ecx
	pop	ebx	
	ccc_end
ret