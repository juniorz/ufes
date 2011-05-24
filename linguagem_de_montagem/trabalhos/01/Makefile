#4. make
zero: teste.c
	gcc ./teste.c -o ./zero

#1. make ls
ls:
	@ls -la

#2. make lsR
lsR:
	@ls -Rla

#3. make teste.c
teste.c:
	@echo -e 'main( int argc, char *argv[]){\n' \
	'	printf("Olá mundo %s\\n", argv[1]);\n' \
	'	exit(0);\n' \
	'}' \
	> ./teste.c

#4. make teste
teste: teste.c zero
	./zero testando...

#6. make ola.asm
ola.asm:
	@echo -e -n 'section .text\n' \
	'	global _start\n' \
	'	msg db	"Olá Mundo", 0x0A\n' \
	'	tam equ	$$ - msg\n' \
	'\n_start:\n' \
	'	mov ecx, msg	; ponteiro para string\n' \
	'	mov edx, tam	; tamanho da string\n' \
	'	call imprimir	; chama a funcao imprimir\n' \
	'	mov eax, 1	; sys_exit: encerramento do programa e\n' \
	'			; ao controle do sistema operacional\n' \
	'	int 0x80	; interrupção do linux\n' \
	'\nimprimir:\n' \
	'	push eax	; guarda o conteúdo dos registradores\n' \
	'	push ebx \n\n' \
	'	mov eax, 4	; no de chamada do sistema: sys_write\n' \
	'	mov ebx, 1	; file descriptor: stdout\n' \
	'	int 0x80	; chama a interrupção do linux\n' \
	'	pop ebx\n' \
	'	pop eax		; carrega o valor que estava armazenado na pilha\n' \
	'	ret		; retorno para o corpo do programa' \
	> ./ola.asm

#7. make ola
ola: ola.asm
	@nasm -f elf ola.asm
	@ld -o ola ola.o

#8. make testeola
testeola: ola
	./ola

#9. make all
all: ls lsR teste testeola
