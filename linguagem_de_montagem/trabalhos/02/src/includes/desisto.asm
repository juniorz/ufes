; -----------------------------------------------
; [nome]	intval_z
; [desc]	Converte uma sequencia de caracteres ascii
;		para o seu valor numerico
; [params]	ptr para string	(1)
; [return]	valor inteiro	(eax)
; -----------------------------------------------
; Changelog
; -----------------------------------------------
; [24/06/2005 - 19:20]
; Versão 1.0
; -----------------------------------------------
intval_z:
	ccc_begin 1
	push	ebx
	push	ecx
	push	edx
	pushfd


	; Tamanho da string
	push	dword [parametro(1)]
	call strlen_z
	descarta_pilha 1


	mov	edx, dword [parametro(1)]	; Aponta edx para o final da string
	add	edx, eax
	

	; Verifica se eh um numero hexadecimal
	mov	ebx, dword [parametro(1)]
	movzx	ecx, word [ebx]

	xor	ebx, ebx	; Zera ebx

	cmp	cx, 0x7830	; 0x
	je	.modo_hexa

	cmp	cx, 0x5830	;0X
	je	.modo_hexa

	mov	ecx, 10		; ecx := base do numero armazenado na string (10)
	
	; verifica o tamanho maximo para o numero
	cmp	eax, 10
	jg	.fim
	
	cmp	
	
	jmp 	.loop


  .modo_hexa

	; O numero eh um hexa decimal
	mov	ecx, 0xF	; ecx := base do numero armazenado na string (F)


  .proximo_caractere

	; Apos o primeiro loop ebx recebe 1 e começa o jogo
	cmp	ebx, 0
	jne	.loop
	inc	ebx		; ebx := 1


  .loop


	; Varre byte a byte
	dec	eax
	

	cmp	eax, dword [parametro(1)]	; Chegou ao fim
	jl	.fim

	push	byte [ebx]			; Move o byte lido pra ecx


    .hexa

	; Caractere HEXA
	cmp	byte [ebx], 'x'		; 0x para hexa, ignora
	je	.fim
	cmp	byte [ebx], 'X'		; 0X para hexa, ignora
	je 	.fim
	cmp	byte [ebx], 'h'		; 0xAh para hexa, fim
	je	.loop
	cmp	byte [ebx], 'H'		; 0xAH para hexa, fim
	je 	.loop

	cmp	byte [ebx], 'f'		; De 'f'
	jnle	.loop
	cmp	byte [ebx], 'a'		; a 'a'
	jnge	.maiuscula
	
	; hexa minsculo
	sub 	ecx, 'a' - 10
	add	eax, ecx
;_newline
;dump_regs 5555
	jmp	.proximo_caractere


    .maiuscula
	cmp	byte [ebx], 'F'		; F
	jnle	.loop
	cmp	byte [ebx], 'A'		; F
	jnge	.decimal
	
	; hexa maiusculo
	sub 	ecx, 'A' - 10
	add	eax, ecx
;_newline
;dump_regs 6666
	jmp	.loop


    .decimal	

	; Numericos
	cmp	byte [ebx], '0'		; 0
	jnge	.loop

	; decimal
	sub 	ecx, '0'
	add	eax, ecx
;_newline
;dump_regs 7777
	jmp	.loop


  .fim

	cmp	byte [parametro(1)], '-'; - (negativo)
	jne	.desempilha
	neg	eax
  
  


  .desempilha
dump_regs 4321
  
	popfd
	pop	ecx
	pop	ebx			; Restarua ecx
	ccc_end
ret