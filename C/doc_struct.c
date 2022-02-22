#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

typedef struct document Document;
typedef struct paragraph Paragraph;
typedef struct sentence Sentence;
typedef struct word Word;

int count_chars(char* text, const char c){
    int char_counter = 0;
    while(*text){
        if(*text == c){
            char_counter++;
        }
		text++;
    }
    return char_counter;
}

struct document get_document(char* text) {
	char *p_ptr, *sp_ptr;
	char *s_ptr, *ss_ptr;
	char *w_ptr, *sw_ptr;
    
	size_t paragraph_count = count_chars(text, '\n');
	size_t p_idx = 0;
	Paragraph *paragraphs = (Paragraph*) malloc(paragraph_count * sizeof(Paragraph));
	p_ptr = strtok_r(text, "\n", &sp_ptr);

	while(p_ptr){
		char p_cpy[strlen(p_ptr) + 1];
		strcpy(p_cpy, p_ptr);
		size_t sentence_count = count_chars(p_cpy, '.') + 1;
		size_t s_idx = 0;
		Sentence *sentences = (Sentence*) malloc(sentence_count * sizeof(Sentence));
		s_ptr = strtok_r(p_cpy, ".", &ss_ptr);
		while(s_ptr){
			char s_cpy[strlen(s_ptr)+1];
			strcpy(s_cpy, s_ptr);
			size_t word_count = count_chars(s_cpy, ' ') + 1, w_idx = 0;
			Word *words = (Word*) malloc(word_count * sizeof(Word));
			w_ptr = strtok_r(s_cpy, " ", &sw_ptr);
			while(w_ptr){
				words[w_idx].data = strdup(w_ptr);
				w_idx++;
				w_ptr = strtok_r(NULL, " ", &sw_ptr);
			}
			sentences[s_idx].data = words;
			sentences[s_idx].word_count = word_count;
			s_idx++;
			s_ptr = strtok_r(NULL, ".", &ss_ptr);
		}
		paragraphs[p_idx].data = sentences;
		paragraphs[p_idx].sentence_count = sentence_count;
		p_idx++;
		p_ptr = strtok_r(NULL, "\n", &sp_ptr);
	}
		
	Document doc = { .data = paragraphs, .paragraph_count = paragraph_count };

	return doc; 
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
	return Doc.data[m-1].data[n-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
	return Doc.data[k-1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
	Document Doc = get_document(text);
	int q;
	scanf("%d", &q);
	

	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3){
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
			print_word(w);
		}

		else if (type == 2) {
			int k, m;
			scanf("%d %d", &k, &m);
			struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
			print_sentence(sen);
		}

		else{
			int k;
			scanf("%d", &k);
			struct paragraph para = kth_paragraph(Doc, k);
			print_paragraph(para);
		}
		printf("\n");
	}     
	for(int p = 0; p < Doc.paragraph_count; p++){
		for(int s = 0; s < Doc.data[p].sentence_count; s++){
			for(int w = 0; w < Doc.data[p].data[s].word_count; w++){
				free(Doc.data[p].data[s].data[w].data);
			}
			free(Doc.data[p].data[s].data);
		}
		free(Doc.data[p].data);
	}
	free(Doc.data);
	free(text);
}
