#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <regex.h>

#include "DirReader.h"
#include "FileReader.h"

int main(int argc, char *argv[]){
	printf("The number of arguments is: %d\n",argc);

	if(argc <= 1){
		printf("This should give a help line thingy but not now");
		exit(1);
	}

	FILE *f;
	int files_num;
	int ch;
	char choice;
	char** filepaths;

	
	filepaths = arrayOfFilePaths(argv[1],&files_num);
	
	for(int i = 0; i < files_num; i++){
		printf("%s\n", filepaths[i]);
		showcaseFile(filepaths[i]);
	}

//			printf("\e[1;1H\e[2J");

;
//				enum fformat fileformat = getfformat(filename);
//
//				printf("Debug-------------------------------------------\n");
//				printf("Directory name: %s\n",opath);
//				printf("File format: %d\n",fileformat);
//				printf("File path: %s\n",filepath);
//				printf("File name: %s\n",filename);
//				printf("Debug-------------------------------------------\n");
				
//				if(fileformat == TEXT){
//					f = fopen(filepath, "r");
//					printf("\n");
//				
//					while((ch  = getc(f)) != EOF){
//						printf("%c",ch);
//					}
//
//					fclose(f);
//				}else if(fileformat == IMAGE){
//					printf("This is an image file.\nNo Support for it yet\n");
//				}else{
//					printf("This file format is not supported.\n");
//				}
//				
//				printf("\nDo you want to delete (X) or save (S) this file (%s): ",filename);
//				scanf("%c",&choice);
//				getchar();
//				//Maybe a second confirmation before deleting ?
//				//
//				if(toupper(choice) == 'X'){
//					printf("\nThe file (%s) is to be deleted", filename);
//				}else if(toupper(choice) == 'S'){
//					printf("\nThe file (%s) is to be saved",filename);
//				}else{
//					printf("\nPlease give an appropriate response");
//				}
	return 0;
}
