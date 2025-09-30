#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

char* validDirectory(char *dpath){
	int pathlen = strlen(dpath);
	if(dpath[0] != '/' && dpath[0] != '.' && dpath[pathlen - 1] != '/')
	{
		printf("Not a valid directory path");
		exit(1);
	}
	return dpath;
}

char** arrayOfFilePaths(char *dpath, int *num){

	DIR* d;
	struct dirent *entry;
	char* dirpath;
	char* opath;
	

	size_t len = 0;

	dirpath = validDirectory(dpath);
	int pathlen = strlen(dirpath);
	
	opath = malloc(strlen(dirpath) + 1);
	if(opath == NULL){
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(opath, dirpath);
	
		
	if((d = opendir(dirpath)) != NULL){
		while((entry = readdir(d)) != NULL){
			if(entry->d_type == DT_REG){
				len += 1;
			}
		}
	}

	char **filepaths = malloc(len * sizeof(char *));

	*num = len;

	size_t i = 0;
	if((d = opendir(dirpath)) != NULL){
		while((entry = readdir(d)) != NULL){
			if(entry->d_type == DT_REG){
				char *filepath = strcat(dirpath, entry->d_name);
				//printf("%s\n",entry->d_name);
				//printf("%s : %d\n",filepath,strlen(filepath));
				filepaths[i] = malloc((strlen(filepath) + 1) * sizeof(char));	
				strcpy(filepaths[i],filepath);
				i++;
				//Print the list of files
				strcpy(dirpath,opath);

			}
		}
	}else{
		printf("Error opening the directory");
		exit(1);
	}

	return filepaths;
}
