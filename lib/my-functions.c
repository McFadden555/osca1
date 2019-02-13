#include <stdio.h>
#include <stdlib.h>

//returns a random number
//references
//https://stackoverflow.com/questions/1108780/why-do-i-always-get-the-same-sequence-of-random-numbers-with-rand
int *random_number_generator(amount, start, end){
	srand(time(NULL));
	int random_number;

	for(int i=0; i<amount; ++i){
		random_number = start + (rand() % (end - start));
		//printf("%d\n", random_number);
	}
	return random_number;
}

int * getCharacters(amount, start, end){
	static int characters[20480];
	int i;
	srand(time(NULL));
	for(i=0; i<amount; ++i){
		characters[i] = start + (rand() % (end - start));
	}
	return characters;
}


//-------------------------PHYSICAL MEMORY-------------------------
//writes to the physical_memory (physical_memory.txt)
//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_physical_memory(int number, char character, int *characters){
	printf("num: %d\n", number);
	printf("char (Dec): %d\n", character);
	printf("char: %c\n\n\n", character);

	FILE *physical_memory = fopen("./data/physical_memory.txt", "w");
	if(physical_memory == NULL){
		printf("Error with file!\n");
		exit(1);
	}

	int page_size		= 256;
	int current_address	= 0;
	int frame		= 0;

	fprintf(physical_memory," Address\t| Frame\t| Content\n");
	fprintf(physical_memory,"----------------|-------|------------\n");

	for(int i=0; i<page_size; ++i){
		for(int j=0; j<page_size; ++j){
			if(current_address >= 512 && current_address < (512 + number)){
				fprintf(physical_memory, " 0x%d\t\t| %d\t| %c\n", current_address, frame, *(characters+j));
			}
			else{
				fprintf(physical_memory, " 0x%d\t\t| %d\t| ...\n", current_address, frame);
			}
			++current_address;
		}
		++frame;
	}
	fprintf(physical_memory,"-----------------------------------------\n");
	fclose(physical_memory);
}

//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_page_table(amount, start, end){
	FILE *page_table = fopen("data/page_table.txt", "w");
	if(page_table == NULL){
		printf("Error with file!\n");
		exit(1);
	}

	int *characters;
	int i;
	characters = getCharacters(amount, start, end);
	fprintf(page_table," Page\t | Page Table Entry\n");
	fprintf(page_table,"---------|-------------------\n");
	for(i=0; i<amount; ++i){
		fprintf(page_table, "[%d]\t | %c\n", (i+512), *(characters+i));
	}
	fprintf(page_table,"--------------------------------------\n");
	fclose(page_table);
}

//reads from the physical memory (physical_memory.txt)
//references
//https://www.geeksforgeeks.org/c-program-print-contents-file/
void read_from_physical_memory(){
	FILE *physical_memory;
	char c;
	physical_memory = fopen("./data/physical_memory.txt", "r");
	if(physical_memory == NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	c = fgetc(physical_memory);
	while(c != EOF){
		printf("%c", c);
		c = fgetc(physical_memory);
	}
	fclose(physical_memory);
}

//references
//https://www.geeksforgeeks.org/c-program-print-contents-file/
void read_from_page_table(){
	FILE *page_table;

	char c;
	page_table = fopen("./data/page_table.txt", "r");
	if(page_table == NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	c = fgetc(page_table);
	while(c != EOF){
		printf("%c", c);
		c = fgetc(page_table);
	}
	fclose(page_table);
}
