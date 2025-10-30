#include <stdio.h>
#include "ilxer.h"
#include "misc.h"

#define SOURCE "./word_test.json"

Arena_header ah;
lxer_header lh;

int main(){
	NOTY("WORD TEST", "Testing general word tokenizer", NULL);
	StringBuilder* sb = read_file(&ah,SOURCE);
	lxer_start_lexing(&lh,sb->string);
	lxer_get_lxer_content(&lh);
	LXR_TOKENS token, next_token;
	bool cont = true;
	while(cont){
		token = lxer_get_current_token(&lh);
		next_token = lxer_get_next_token(&lh);
		if(token == LXR_WORD && next_token == LXR_ASSIGNMENT){
			char* city_name = lxer_get_word(&lh);
			lxer_next_token(&lh);
			if(lxer_get_next_token(&lh) == LXR_OPEN_SQR_BRK){
				printf("\n\nCity '%s' found:", city_name);
				token = lxer_get_current_token(&lh);
				next_token = lxer_get_next_token(&lh);
			}else{
				lxer_increase_tracker(&lh, -1);
			}
		}
		
		if(token == LXR_OPEN_CRL_BRK){
			printf("\n");
		}
		if(token == LXR_DOUBLE_QUOTE && next_token == LXR_WORD){
			lxer_next_token(&lh);
			char* tag_word = lxer_get_word(&lh);
			lxer_next_token(&lh);
			next_token = lxer_get_next_token(&lh);
			if(next_token == LXR_DOUBLE_DOTS){
				if(strcmp(tag_word, "name") == 0){
					printf("House owner ");	
				}else if(strcmp(tag_word, "address") == 0){
					printf("located at ");		
				}
			}else if(next_token == LXR_COMMA || next_token == LXR_CLOSE_CRL_BRK){
				printf("%s ", tag_word);
			}
		}
		cont = lxer_next_token(&lh);
	}
	printf("\n");
	arena_free(&lh.lxer_ah);
	arena_free(&ah);	
	return 0;
}
