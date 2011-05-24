#
#Variaveis
#
nome_trabalho = trab2
objetos	= std_io.o file_io.o asm_io.o kernel.o pabx.o gc.o $(nome_trabalho).o
objetos_debug = std_io.o file_io.o asm_io.o kernel_debug.o pabx.o gc_debug.o $(nome_trabalho)_debug.o

#gera o trabalho
$(nome_trabalho):	$(objetos)
	gcc $(objetos) -o $(nome_trabalho)


#gera o trabalho em debug mode
debug:	$(objetos_debug)
	gcc $(objetos_debug) -o $(nome_trabalho)


#roda o trabalho
run:	$(nome_trabalho)
	clear
	./$(nome_trabalho) arquivo.txt


#roda o trabalho em debug mode
run-debug:	debug
	clear
	./$(nome_trabalho) arquivo.txt 1> saida.log 2> erro.log


#limpa o executavel
clean:
	rm -f $(nome_trabalho).o
	rm -f $(nome_trabalho)


#limpa tudo que nao precisa
clean-all: clean
	rm -Rf ./includes/*.*~
	rm -Rf *~
	rm -Rf *.*~
	rm -f $(objetos)
	rm -f $(objetos_debug)
	rm -f core.*

#
#Regras
#

#Objetos
$(nome_trabalho).o:	$(nome_trabalho).asm
	nasm -f elf -l ./lst/$*.lst $*.asm

$(nome_trabalho)_debug.o:	$(nome_trabalho).asm
	nasm -d DEBUG -f elf -l ./lst/$*.lst -o ./$*.o $(nome_trabalho).asm

gc_debug.o:	includes/gc.asm
	nasm -d DEBUG -f elf -l ./lst/$*.lst -o ./$*.o includes/gc.asm

gc.o:	includes/gc.asm
	nasm -f elf -l ./lst/$*.lst -o ./$*.o includes/$*.asm
	
kernel_debug.o:	includes/kernel.asm
	nasm -d DEBUG -f elf -l ./lst/$*.lst -o ./$*.o includes/kernel.asm

kernel.o:	includes/kernel.asm
	nasm -f elf -l ./lst/$*.lst -o ./$*.o includes/$*.asm

pabx.o:	includes/pabx.asm
	nasm -f elf -l ./lst/$*.lst -o ./$*.o includes/$*.asm
	
std_io.o:	includes/std_io.asm
	nasm -f elf -l ./lst/$*.lst -o ./$*.o includes/$*.asm
	
file_io.o:	includes/file_io.asm
	nasm -f elf -l ./lst/$*.lst -o ./$*.o includes/$*.asm

asm_io.o:	util/asm_io.asm
	nasm -d ELF_TYPE -f elf -l ./lst/$*.lst -o ./$*.o util/$*.asm