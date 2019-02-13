#include <stdio.h>
#include <stdlib.h>

//returns a random number
int *random_number_generator(amount, start, end){
printf("testing random number generator.....\n");	
	int random_number;
	for(int i=0; i<amount; ++i){
		random_number = rand() % end + start;
		printf("%d\n", random_number);
	}


	//int random_number = 3000;
	return random_number;
}

//returns a random character
//references
//https://www.linuxquestions.org/questions/programming-9/c-returning-char-array-pointer-4175490314/
char* random_character_generator(number){
	printf("testing random character generator......\n");

	char *mymessage;
	mymessage = malloc (sizeof (char) * number);
	strcpy(mymessage, "Hello World");
	return mymessage;

	//char random_character = 'a';
	//return random_character;
}


//-------------------------PHYSICAL MEMORY-------------------------
//writes to the physical_memory (physical_memory.txt)
//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_physical_memory(int number, char character){
	printf("num: %d\n", number);
	printf("char: %d\n", character);
	printf("char: %c\n\n\n", character);


	FILE *physical_memory = fopen("./data/physical_memory.txt", "w");
	if(physical_memory == NULL){
		printf("Error with file!\n");
		exit(1);
	}

//	int address_space	= 16;
	int page_size		= 256; //(256)
//	int array_length	= page_size * page_size; //(65536)
	int current_address	= 0;
	int frame		= 0;

	fprintf(physical_memory," Address\t| Frame\t| Content\n");
	fprintf(physical_memory,"----------------|-------|------------\n");
	for(int i=0; i<page_size; ++i){
		for(int j=0; j<page_size; ++j){
			if(current_address == number){
				fprintf(physical_memory, " 0x%d\t\t| %d\t| %d\n", current_address, frame, character);
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







//-------------------------PAGE TABLE-------------------------
//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_page_table(){
	FILE *page_table = fopen("./data/page_table.txt", "w");

	if(page_table == NULL){
		printf("Error!\n");
		exit(1);
	}
//	int address_space = 16;
	int page_size = 256; //256
//	int array_length = page_size * page_size; //65536
	int current_address = 0;
	int frame = 0;

	fprintf(page_table," Page\t\t| Page Table Entry\n");
	fprintf(page_table,"-----------------|-------------------\n");
	for(int i=0; i<page_size; ++i){
		for(int j=0; j<page_size; ++j){
			fprintf(page_table," 0x%d\t\t| Frame: %d\n", current_address, frame);
			++current_address;
		}
		++frame;
	}
	fprintf(page_table,"--------------------------------------\n");
	fclose(page_table);
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
