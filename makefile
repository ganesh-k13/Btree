CHECK := $(shell which clang)

ifeq ($(CHECK),)
$(warning no clang found, consider apt-get install clang, using gcc now)
CC = gcc
else
$(info using clang over g)
CC = clang
endif

IDIR=include
ODIR=obj
SRCDIR=src

test:	$(ODIR)/test.o $(ODIR)/Node.o $(ODIR)/Btree.o $(ODIR)/utils.o
		$(CC)  -o test -g $(ODIR)/test.o $(ODIR)/Btree.o $(ODIR)/Node.o $(ODIR)/utils.o

$(ODIR)/test.o:	test.c 
	$(CC)  -w -o $(ODIR)/test.o -c test.c

$(ODIR)/Node.o:	$(SRCDIR)/Node.c $(IDIR)/Node.h
	$(CC)  -w -o $(ODIR)/Node.o -c $(SRCDIR)/Node.c
	
$(ODIR)/Btree.o: $(SRCDIR)/Btree.c $(IDIR)/Btree.h $(ODIR)/Node.o
	$(CC)  -w -o $(ODIR)/Btree.o  -g $(ODIR)/Node.o -c $(SRCDIR)/Btree.c

$(ODIR)/utils.o: $(SRCDIR)/utils.c $(IDIR)/utils.h
	$(CC)  -w -o $(ODIR)/utils.o -c $(SRCDIR)/utils.c

clean:
	rm -f $(ODIR)/*.o
	rm test
