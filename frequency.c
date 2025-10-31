#include <stdio.h>
#include "ilxer.h"
#include "misc.h"

#define SOURCE "./dante_inferno_canto_8_9_10_11_12_13_14.txt"

Arena_header ah;
lxer_header lh;

typedef struct{
	char* token_name;
	size_t token_hash;
	size_t count;
}freq_header;


size_t get_hash(char* word){
	size_t hash = 5381;
	int c;

	for(size_t i=0;i<strlen(word);i++){
		c = tolower(word[i]);
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

int main(){
	NOTY("WORD TEST", "Testing general word tokenizer with some Dante's inferno paragraphs", NULL);
	StringBuilder* sb = read_file(&ah, SOURCE);
	lxer_start_lexing(&lh,sb->string);
	bool cont = true;
	LXR_TOKENS token;
	List_header list = {0};
	while(cont){
		token = lxer_get_current_token(&lh);
		if(token == LXR_WORD){
			char* word = lxer_get_word(&lh);
			if(strchr(word, ' ') == NULL){
				arena_list_push(&ah, &list, word);
			}
		}
		cont = lxer_next_token(&lh);
	}
	List_header freq_list = {0};

	for(size_t i=0;i<list.count;i++){
		size_t hash = get_hash(list_get_at(&list,i));
		bool found = false;
		for(size_t j=0;j<freq_list.count && !found;j++){
			freq_header* fh = list_get_at(&freq_list, j);
			if(fh->token_hash == hash){
				fh->count += 1;
				found = true;
			}
		}
		if(!found){
			freq_header *new_freq = (freq_header*)arena_alloc(&ah, sizeof(freq_header));
			new_freq->count = 1;
			new_freq->token_name = list_get_at(&list, i);
			new_freq->token_hash = hash;
			arena_list_push(&ah, &freq_list, new_freq);
		}
	}

	freq_header *max_freq = list_get_at(&freq_list, 0);
	for(size_t i=0;i<freq_list.count;i++){
		freq_header *new_freq = list_get_at(&freq_list, i);
		if(new_freq->count > max_freq->count) max_freq = new_freq;
	}
		
	printf("List of the tokens occurred more than 50 times, names are case sensitive but the hashing was done in case insensitive mode: \n");
	for(size_t i=0;i<freq_list.count;i++){
		freq_header *new_freq = list_get_at(&freq_list, i);
		if(new_freq->count > 50){
			printf("Common token '%s' occurred %zu times\n",new_freq->token_name, new_freq->count);
		}
	}
	printf("The most occurred token is '%s' for a total of %zu times\n",max_freq->token_name, max_freq->count);
	arena_free(&lh.lxer_ah);
	arena_free(&ah);	
	return 0;
}
