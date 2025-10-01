#include <regex.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define WIDTH 10
#define HEIGHT 10

enum fformat {
	TEXT,
	IMAGE,
	ERREXT
};


void readTextFile(const char *filepath){
	FILE *f = fopen(filepath, "r");
	int ch;	

	while((ch = getc(f)) != EOF){
		printf("%c",ch);
	}

	fclose(f);
}

void draw_pixel(int x, int y, int r, int g, int b){
	printf("\x1b_Ga=%d,b=%d,c=%d;P0e[0m",r,g,b);
	printf("\x1b_[0;0He[0;%dHe[Je[u]",y,x);
}

void readImageFile(char *filepath){
	char *base_command = "viu ";
	char command[strlen(base_command) + strlen(filepath) + 2];

	strcat(command, base_command);
	strcat(command, filepath);
	printf("%s", command);
	system(command);
}


enum fformat getfformat(const char *filename){
	char *ext = strchr(filename, '.');
	if(!ext) return ERREXT;
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

