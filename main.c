#include <stdio.h>
#include <stdlib.h>
#include "ilxer.h"
#include "misc.h"

Arena_header ah;
lxer_header lh;

#define TEST_FILE "./example.txt"

int main(){
	StringBuilder* sb;
	sb = read_file(&ah,TEST_FILE);
	lxer_start_lexing(&lh, sb->string);
	printf("Tokenizer content from "TEST_FILE": \n");
	lxer_get_lxer_content(&lh);
	printf("Token in position %zu is %s\n", lh.lxer_tracker, token_table_lh[lxer_get_current_token(&lh)]);
	char** lh_rh = lxer_get_rh_lh(&lh);
	printf("Token left hand is %s, token right hand is %s\n", lh_rh[1], lh_rh[0]);
	printf("Advancing of one token\n");
	lxer_next_token(&lh);
	lh_rh = lxer_get_rh_lh(&lh);
	printf("Current token is [%s], token left hand is %s, token right hand is %s\n", token_table_lh[lxer_get_current_token(&lh)], lh_rh[1], lh_rh[0]);
	printf("Advancing of one token\n");
	lxer_next_token(&lh);
	lh_rh = lxer_get_rh_lh(&lh);
	printf("Current token is [%s], token left hand is %s, token right hand is %s\n", token_table_lh[lxer_get_current_token(&lh)], lh_rh[1], lh_rh[0]);


	arena_free(&lh.lxer_ah);
	arena_free(&ah);
	return 0;
}
