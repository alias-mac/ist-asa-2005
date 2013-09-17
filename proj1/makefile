
CFLAGS += -g
CFLAGS += -Wall -ansi -pedantic
CFLAGS += $(DEFINES)
# Compilador a usar
CC = gcc

PROG = proj1
SRCS = proj1.c
OBJS = proj1.o
TESTFILE = test.out
TESTS = p1test01.in p1test02.in p1test03.in p1test05.in p1test07.in p1test09.in
TEST = $(addprefix p1gt/, $(TESTS))

.PHONY: all
all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: rebuild
# Recriar tudo
rebuild: clean all

.PHONY: clean
# Limpar antes de recompilar
clean:
	rm -f $(PROG) $(OBJS)
#	rm -f *.core */*.core *.bak */*.bak *~ */*~

.PHONY: check
# Corre os testes todos
check: all $(TESTFILE) $(TEST) checkclean

$(TESTFILE):
	touch $(TESTFILE)

.PHONY: checkclean
# Limpar o ficheiro de teste usado
checkclean:
	rm -f $(TESTFILE)

# Não esquecer que os .out têm de ter data posterior aos .in
%.in: %.out
	./$(PROG) < $@ > $(TESTFILE)
	@cat $(TESTFILE)
	@cat $<
	diff -w $(TESTFILE) $<

# Criar lista de dependencias na Makefile
# Basta correr uma vez em cada sistema operativo
depend: $(SRCS)
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRCS)

# Ajuda
.DEFAULT:
	@echo "Utilizacao:"
	@echo "make               - recompilar."
	@echo "make all           - recompilar."
	@echo "make rebuild       - recriar tudo."
	@echo "make depend        - recriar lista de dependencias na makefile. Basta uma vez."
	@echo "make clean         - limpar executaveis, ficheiros objecto, core e bak."
	@echo "make check         - corre os testes e verifica se estão correctos."

# DO NOT DELETE THIS LINE -- make depend depends on it.
