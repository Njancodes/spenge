#include <regex.h>
#include <string.h>
#include <stdio.h>


enum fformat {
	TEXT,
	IMAGE,
	ERREXT
};


void readTextFile(char *filepath){
	FILE *f = fopen(filepath, "r");
	int ch;	
	printf("\n");

	while((ch = getc(f)) != EOF){
		printf("%c",ch);
	}

	fclose(f);
}

void readImageFile(char *filepath){
	printf("This is an image file.\n No Support yet");
}


enum fformat getfformat(const char *filename){
	char *ext = strchr(filename, '.');
	enum fformat ff = ERREXT;

	regex_t textregex;
	regex_t imageregex;

	int text_reg_errval = regcomp(&textregex, ".txt|.c|.py|.java|.rs",REG_EXTENDED);
	int img_reg_errval = regcomp(&imageregex, ".png|.jpg", REG_EXTENDED);

	int text_file_check = regexec(&textregex, ext, 0, NULL, 0);
	int image_file_check = regexec(&imageregex, ext, 0, NULL, 0);

	if(text_file_check != REG_NOMATCH){
		ff = TEXT;
	}else if(image_file_check != REG_NOMATCH){
		ff = IMAGE;
	}

	return ff;
}

void showcaseFile(char *filepath){
	const enum fformat ff = getfformat(filepath);
	
	if(ff == TEXT){
		readTextFile(filepath);
	}else if(ff == IMAGE){
		readImageFile(filepath);
	}else{
		printf("Unknown File.\n");
	}
}

