#include <stdio.h>
#include <stdlib.h>

#include "ilxer.h"
#include "misc.h"


Arena_header ah;
lxer_head lh;

#define SOURCE "./test.json"
#define OBBIES_LIMIT 10

typedef struct{
	char name[256];
	char description[256];
}obbie;

typedef struct{
	char name[256];
	int age;
	obbie obbies[OBBIES_LIMIT];
	int totla_score;
}person_card;

int main(){

	StringBuilder* sb = read_file(&ah,SOURCE);
	lxer_start_lexing(&lh,sb->string);
	//lxer_get_lxer_content(&lh);

	person_card id;
	NOTY("PARSER","Parsing file, searching for all strings inside the example file "SOURCE, NULL);

	char buffer[512];
	bool tag_open = false;
	int token = 0;
	int next_token = 0;
	bool string_open = false;
	char* string_open_ptr;
	int string_len = 0;
	int indent_level = 0;
	bool scope_open = false;
	do{
		token = lxer_get_current_token(&lh);
		next_token = lxer_get_next_token(&lh);
		switch(token){
			case LXR_OPEN_CRL_BRK:
				if(!scope_open){
					scope_open = true;
				}else{
					indent_level += 4;
				}
				break;
			case LXR_CLOSE_CRL_BRK:
				indent_level -= 4;
				if(indent_level == 0){
					scope_open = false;
				}
				break;
			case LXR_OPEN_SQR_BRK: 
				printf("array open\n");
				break;
			case LXR_CLOSE_SQR_BRK:
				break;
			case LXR_DOUBLE_QUOTE: 
				if(!string_open){
					string_open_ptr = lxer_get_current_pointer(&lh);
					string_open = true;
				}else{
					string_len = lxer_get_current_pointer(&lh) - string_open_ptr;
					memcpy(&buffer[0], string_open_ptr, string_len+1);
					buffer[string_len+1] = '\0';
					string_open = false;
					if(!tag_open){
						tag_open = true;
					}else{
						printf("%s\n", buffer);
						tag_open = false;
					}
				}
				break;

			case LXR_DOUBLE_DOTS: 
				if(tag_open){
					for(int i=0;i<indent_level;i++) printf(" ");
					printf("Tag named %s found with content: ", buffer);	
					if(next_token == LXR_OPEN_SQR_BRK){
						tag_open = false;
					}
				}
				break;
			default: break;
		}
		
		//printf("%s\n", token_table_lh[lxer_get_current_token(&lh)]);
	}while(lxer_next_token(&lh));

	arena_free(&lh.lxer_ah);
	arena_free(&ah);
	return 0;
}
