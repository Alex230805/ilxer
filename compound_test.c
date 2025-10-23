#include <stdio.h>
#include <stdlib.h>


#include "ilxer.h"



Arena_header ah = {0};
lxer_header lh = {0};
#define SOURCE "./compound_test.txt"

int main(){
	printf("Testing compound expression\n");	
	
	StringBuilder* sb = read_file(&ah,SOURCE);
	lxer_start_lexing(&lh,sb->string);
	lxer_get_lxer_content(&lh);
	
	NOTY("COMPOUND","Compound expressions list", NULL);
	lxer_get_compounds();
	NOTY("COMPOUND","Searching for compound expressions..", NULL);
	
	bool cont = true;
	do{
		printf("Current token under analisys: '%s'\n", lxer_get_string_representation(lxer_get_current_token(&lh)));
		CINDEX c = lxer_expect_compound(&lh); 
		if(c != CINDEX_NOT_FOUND){
			printf("Just found a compound expression which is '%s'\n", lxer_get_compound_lh(c));
			int len = lxer_get_compound_length(c);
			lxer_increase_tracker(&lh, len);		
		}else{
			cont = lxer_next_token(&lh);
		}
	}while(cont);

	arena_free(&ah);
	arena_free(&lh.lxer_ah);
	return 0;
}
