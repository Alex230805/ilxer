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
	lxer_get_lxer_content(&lh);

	person_card id;
	printf("Parsing file, searching for all strings inside the example file "SOURCE"\n");

	char buffer[512];
	bool tag_open = false;
	while(lxer_next_token(&lh)){
		if(lxer_get_current_token(&lh) == LXR_DOUBLE_QUOTE){
			char*string_start = lxer_get_current_pointer(&lh);
			bool status = true;
			lxer_next_token(&lh);
			while(lxer_get_current_token(&lh) != LXR_DOUBLE_QUOTE && status) status = lxer_next_token(&lh);
			if(!status){
				printf("ERROR: string started and never finished, char pointer %zu\n",string_start-sb->string);
				return 1;
			}
			int string_len = lxer_get_current_pointer(&lh) - string_start;
			memcpy(&buffer[0],string_start,string_len+1);
			buffer[string_len+1] = '\0';
			printf("%s\n", buffer);
		}
	}
	arena_free(&lh.lxer_ah);
	arena_free(&ah);
	return 0;
}
