#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]){
	printf("The number of arguments is: %d\n",argc);

	DIR *d;
	FILE *f;
	struct dirent *dir;
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
		while((dir = readdir(d)) != NULL) {
			if(dir->d_type == DT_REG){
				printf("Directory name: %s\n",opath);
				char *filepath = strcat(dirpath, dir->d_name);
				printf("File path: %s\n",filepath);
				printf("File name: %s\n",dir->d_name);
				f = fopen(filepath, "r");
				printf("\n");
				while((ch  = getc(f)) != EOF){
					printf("%c",ch);
				}
				
				printf("\n Do you want to delete (X) or save (S) this file (%s): ",dir->d_name);
				scanf("%c",&choice);
				getchar();
				if(toupper(choice) == 'X'){
					printf("\nThe file (%s) is to be deleted", dir->d_name);
				}else if(toupper(choice) == 'S'){
					printf("\nThe file (%s) is to be saved",dir->d_name);
				}else{
					printf("\nPlease give an appropriate response");
				}
				printf("\n");
				fclose(f);	
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
