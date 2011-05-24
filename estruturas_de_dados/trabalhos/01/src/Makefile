nome_trabalho 	= ed20051-trab1

all: $(nome_trabalho)

$(nome_trabalho): main.cpp
	g++ -o $(nome_trabalho) main.cpp

debug: main.cpp
	g++ -D DEBUG=1 -o $(nome_trabalho) main.cpp

run: $(nome_trabalho)
	./$(nome_trabalho)

run-all: $(nome_trabalho)
	./$(nome_trabalho) -l entrada.txt busca.txt 1> list.txt 2> list.log
	./$(nome_trabalho) -sl entrada.txt busca.txt 1> slist.txt 2> slist.log
	./$(nome_trabalho) -s entrada.txt busca.txt 1> stack.txt 2> stack.log
	./$(nome_trabalho) -q entrada.txt busca.txt 1> queue.txt 2> queue.log
	./$(nome_trabalho) -h entrada.txt busca.txt 1> hash.txt 2> hash.log

teste: debug

teste-all: debug run-all

doc:
	@clear	
	doxygen

clean:
	@rm -f $(nome_trabalho)

clean-all: clean
	@rm -Rf ./includes/*.*~
	@rm -Rf *~
	@rm -Rf *.*~
	@rm -f *.o
	@rm -f core.*

release: clean-all doc $(nome_trabalho)