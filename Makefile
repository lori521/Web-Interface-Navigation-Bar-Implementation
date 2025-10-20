build:
	gcc -o tema2 main.c tasks.c alocari_distr.c fct_suplimentare.c
run:
	./tema2 $(ARGS)
clean:
	rm -f tema2