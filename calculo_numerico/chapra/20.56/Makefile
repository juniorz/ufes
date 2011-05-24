target = solution
objetos = solution.o diferenca_dividida.o

$(target): $(objetos)
	g++ -o $(target) $(objetos)

run: $(target)
	./$(target)

clean:
	$(RM) $(objetos)

clean-all:	clean
	$(RM) $(target)
