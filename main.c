#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

char* validDirectory(char *dirpath){
	if(dirpath[0] != '/' && dirpath[0] != '.'){
		printf("Not a valid directory path");
		exit(1);
	}	
	return dirpath;
}

int main(int argc, char *argv[]){
	printf("The number of arguments is: %d\n",argc);

	DIR *d;
	FILE *f;
	struct dirent *dir;
	int count = 0;
	char *dirpath;
	char *opath;

	dirpath = validDirectory(argv[1]);
	
	opath = malloc(sizeof(dirpath));
	strcpy(opath, dirpath);
	printf("The directory path is: %s\n", dirpath);
	if((d = opendir(dirpath)) != NULL){
		while((dir = readdir(d)) != NULL) {
			if(dir->d_type == DT_REG){
				printf("Directory name: %s\n",opath);
				printf("File path: %s\n",strcat(strcat(dirpath, "/"), dir->d_name));
				printf("File name: %s\n",dir->d_name);
				strcpy(dirpath,opath);
			}
		
			printf("\n");
			count += 1;
		}	
		count -= 2;	
	}else{
		printf("Error in opening the directory");
		exit(1);
	}
	return 0;
}
