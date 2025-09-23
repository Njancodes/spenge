#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <regex.h>
#include <MagickWand/MagickWand.h>

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
	if(!ext) return ERREXT;
	enum fformat ff = ERREXT;
	
	regex_t textregex;
	regex_t imageregex;

	int text_reg_errval = regcomp(&textregex,"\\.txt|\\.c|\\.py|\\.java|\\.rs",REG_EXTENDED);
	int img_reg_errval = regcomp(&imageregex,"\\.png|\\.jpg",REG_EXTENDED);

	int text_file_check = regexec(&textregex,ext,0,NULL,0);
	int image_file_check = regexec(&imageregex,ext,0,NULL,0);

	if(text_file_check != REG_NOMATCH){
		ff = TEXT;
	}
	if(image_file_check != REG_NOMATCH){
		ff = IMAGE;
	}


	regfree(&textregex);
	regfree(&imageregex);
	return ff;
}

int main(int argc, char *argv[]){
	printf("The number of arguments is: %d\n",argc);

	#define ThrowWandException(wand) \
	{ \
		char \
		  *description; \
		\
		 ExceptionType \
		  severity; \
		\
		 description=MagickGetException(wand,&severity); \
		 (void) fprintf(stderr, "%s %s %lu %s\n",GetMagickModule(), description); \
		 description = (char *) MagickRelinquishMemory(description); \
		 exit(-1); \
	}

	if(argc <= 1){
		printf("This should give a help line thingy but not now");
		exit(1);
	}

	DIR *d;
	FILE *f;
	struct dirent *entry;
	int count = 0;
	int ch;
	char *dirpath;
	char *opath;
	char choice;

	//Image properties
	size_t y;
	size_t x;
	size_t width;
	size_t depth;

	//Image Magick Definitions
	MagickBooleanType status;
	MagickWand *magick_wand;
	PixelIterator *iterator;
	PixelWand **row_of_pixels; //Each Pixel here is called a Pixel Wand (Because they are wrappers so to speak around each pixel)
	PixelInfo pixel;

	//Magick Wand Genesis
	MagickWandGenesis();
	magick_wand = NewMagickWand();

	dirpath = validDirectory(argv[1]);
	int pathlen = strlen(dirpath);
	opath = malloc(strlen(dirpath)+1);
	if(!opath){
		printf("malloc failed");
	}
	strcpy(opath, dirpath);
	printf("The directory path is: %s\n", dirpath);

	if((d = opendir(dirpath)) != NULL){
		while((entry = readdir(d)) != NULL) {
			printf("\033[2J\033[H");
			if(entry->d_type == DT_REG){
				const char *filepath = strcat(dirpath, entry->d_name);
				const char *filename = entry->d_name;
				enum fformat fileformat = getfformat(filename);

				printf("Debug-------------------------------------------\n");
				printf("Directory name: %s\n",opath);
				printf("File format: %d\n",fileformat);
				printf("File path: %s\n",filepath);
				printf("File name: %s\n",filename);
				printf("Debug-------------------------------------------\n");
				
				if(fileformat == TEXT){
					f = fopen(filepath, "r");
					printf("\n");
				
					while((ch  = getc(f)) != EOF){
						printf("%c",ch);
					}

					fclose(f);
				}else if(fileformat == IMAGE){
					ClearMagickWand(magick_wand);
					status = MagickReadImage(magick_wand, filepath);
					if(status==MagickFalse){
						ThrowWandException(magick_wand);
					}
					width = MagickGetImageWidth(magick_wand);
					iterator = NewPixelIterator(magick_wand);
					printf("\nPixel Data of the Image\n");
					printf("The QuantumDepth is %s\n", MagickGetQuantumDepth(&depth));
					for(y = 0; y < MagickGetImageHeight(magick_wand); y++){
						row_of_pixels = PixelGetNextIteratorRow(iterator, &width);
						for(x=0;x<width; x++){
							PixelGetMagickColor(row_of_pixels[x],&pixel);
							printf("Red: %f, Green: %f, Blue: %f\n", pixel.red, pixel.green, pixel.blue);
							
						}
					}
					printf("\n");


					
				}else{
					printf("This file format is not supported.\n");
				}
				
				printf("\nDo you want to delete (X) or save (S) this file (%s): ",filename);
				scanf("%c",&choice);
				getchar();
				//Maybe a second confirmation before deleting ?
				//
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
