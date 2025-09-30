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
		printf("\e[1;1H\e[2J");
		printf("%s\n", filepaths[i]);
		printf("\n");
		showcaseFile(filepaths[i]);
		printf("\n");
		printf("\nDo you want to delete (X) or save (S) this file: ");
		scanf("%c",&choice);
		getchar();
		//Maybe a second confirmation before deleting ?
	
		if(toupper(choice) == 'X'){
			printf("\nThe file is to be deleted");
		}else if(toupper(choice) == 'S'){
			printf("\nThe file is to be saved");
		}else{
			printf("\nPlease give an appropriate response");			 }
		
	}

//
//				printf("Debug-------------------------------------------\n");
//				printf("Directory name: %s\n",opath);
//				printf("File format: %d\n",fileformat);
//				printf("File path: %s\n",filepath);
//				printf("File name: %s\n",filename);
//				printf("Debug-------------------------------------------\n");
				

	return 0;
}
