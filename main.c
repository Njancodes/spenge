#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <regex.h>

enum fformat {
	TEXT,
	IMAGE,
	ERREXT
};

char* validDirectory(char *dirpath){
	if(dirpath[0] != '/' && dirpath[0] != '.'){
		printf("Not a valid directory path");
		exit(1);
	}
	int pathlen = strlen(dirpath);
	if(dirpath[pathlen - 1] != '/'){
		dirpath = strcat(dirpath, "/");
	}
	return dirpath;
}

enum fformat getfformat(const char *filename){
	char *ext = strrchr(filename, '.');
	enum fformat ff = ERREXT;
	
	regex_t textregex;
	regex_t imageregex;

	int text_reg_errval = regcomp(&textregex,".txt|.c|.py|.java|.rs",REG_EXTENDED);
	int img_reg_errval = regcomp(&imageregex,".png|.jpg",REG_EXTENDED);

	int text_file_check = regexec(&textregex,ext,0,NULL,0);
	int image_file_check = regexec(&imageregex,ext,0,NULL,0);

	if(text_file_check != REG_NOMATCH){
		ff = TEXT;
	}
	if(image_file_check != REG_NOMATCH){
		ff = IMAGE;
	}

	return ff;
}

int main(int argc, char *argv[]){
	printf("The number of arguments is: %d\n",argc);

	DIR *d;
	FILE *f;
	struct dirent *dirent;
	int count = 0;
	int ch;
	char *dirpath;
	char *opath;
	char choice;

	dirpath = validDirectory(argv[1]);
	int pathlen = strlen(dirpath);
	opath = malloc(sizeof(dirpath));
	strcpy(opath, dirpath);
	printf("The directory path is: %s\n", dirpath);

	if((d = opendir(dirpath)) != NULL){
		while((dirent = readdir(d)) != NULL) {
			if(dirent->d_type == DT_REG){
				const char *filepath = strcat(dirpath, dirent->d_name);
				const char *filename = dirent->d_name;
				enum fformat fileformat = getfformat(filename);

				printf("Debug-------------------------------------------");
				printf("Directory name: %s\n",opath);
				printf("File format: %d\n",fileformat);
				printf("File path: %s\n",filepath);
				printf("File name: %s\n",filename);
				printf("Debug-------------------------------------------");
				
				if(fileformat == TEXT){
					f = fopen(filepath, "r");
					printf("\n");
				
					while((ch  = getc(f)) != EOF){
						printf("%c",ch);
					}

					fclose(f);
				}else if(fileformat == IMAGE){
					printf("\nThis is an image file.\nNo Support for it yet\n");
				}
				
				printf("\n Do you want to delete (X) or save (S) this file (%s): ",filename);
				scanf("%c",&choice);
				getchar();
				if(toupper(choice) == 'X'){
					printf("\nThe file (%s) is to be deleted", filename);
				}else if(toupper(choice) == 'S'){
					printf("\nThe file (%s) is to be saved",filename);
				}else{
					printf("\nPlease give an appropriate response");
				}
				printf("\n");
				
				
				strcpy(dirpath,opath);
			}
			count += 1;
		}	
		count -= 2;	
	}else{
		printf("Error in opening the directory");
		exit(1);
	}
	return 0;
}
