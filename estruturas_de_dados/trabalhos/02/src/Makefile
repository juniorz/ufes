nome_executavel = run-rbtree
objetos = $(nome_executavel).o TRBTree.o

all: runs 
    
$(nome_executavel):	$(objetos)
	g++ $(objetos) -o $(nome_executavel)

run:	$(nome_executavel)
	./$(nome_executavel)

runs: 	$(nome_executavel)
	./$(nome_executavel) -s input.txt

dot:
	dot -Tgif $(nome_executavel).dot > $(nome_executavel).gif

#Limpa
clean:
	rm -f $(objetos)

#compila qualquer arquivo cpp        
.cpp.o:
	g++ -g -c $*.cpp
