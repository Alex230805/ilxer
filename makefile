FLAGS:= 
COMP:=clang 
INC:= -I./src

null: 
	# no target selected 
	#

main: ./main.c misc.o ilxer.o
	$(COMP) $(FLAGS) $(INC) $< ./src/ilxer.o ./src/misc.o -o ./$@

misc.o: ./src/misc.c ./src/misc.h
	$(COMP) -c $(FLAGS) $(INC) $< -o ./src/$@
	
ilxer.o: ./src/ilxer.c ./src/ilxer.h
	$(COMP) -c $(FLAGS) $(INC) $< -o ./src/$@ 
