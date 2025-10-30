FLAGS:= -O3 
COMP:=clang 
INC:= -I./src

null: 
	# no target selected, chose one of those: 
	#
	# main: general testing for the library
	# parser: parser implemented with this library to elaborate the content from a json
	# compound: testing compound expression
	# word: make a test file for the precise tokenizer mode 

main: ./main.c misc.o ilxer.o
	$(COMP) $(FLAGS) $(INC) $< ./src/ilxer.o ./src/misc.o -o ./$@

parser: ./parser_test.c misc.o ilxer.o
	$(COMP) $(FLAGS) $(INC) $< ./src/ilxer.o ./src/misc.o -o ./$@

compound: ./compound_test.c misc.o ilxer.o
	$(COMP) $(FLAGS) $(INC) $< ./src/ilxer.o ./src/misc.o -o ./$@

word: ./word_example.c misc.o ilxer_pr.o
	$(COMP) $(FLAGS) $(INC) $< ./src/ilxer_pr.o ./src/misc.o -o ./$@

misc.o: ./src/misc.c ./src/misc.h
	$(COMP) -c $(FLAGS) $(INC) $< -o ./src/$@
	
ilxer.o: ./src/ilxer.c ./src/ilxer.h
	$(COMP) -c $(FLAGS) $(INC) $< -o ./src/$@ 

ilxer_pr.o: ./src/ilxer.c ./src/ilxer.h
	$(COMP) -DILXER_PRECISE_MODE -c $(FLAGS) $(INC) $< -o ./src/$@ 

