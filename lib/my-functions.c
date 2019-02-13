#include <stdio.h>
#include <stdlib.h>

//-------------------------PHYSICAL MEMORY-------------------------
//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_physical_memory(){
	FILE *physical_memory = fopen("./data/physical_memory.txt", "w");
	if(physical_memory == NULL){
		printf("Error!\n");
		exit(1);
	}

//	int address_space		= 16;
	int page_size				= 256; //(256)
//	int last_num				= page_size * page_size; //(65536)
	int current_address = 0;
	int frame						= 0;

	fprintf(physical_memory," Address\t| Frame\t| Content\n");
	fprintf(physical_memory,"----------------|-------|------------\n");

	for(int i=0; i<page_size; ++i){
		for(int j=0; j<page_size; ++j){
			fprintf(physical_memory, " 0x%d\t\t| %d\t| .......\n", current_address, frame);
			++current_address;
		}
		++frame;
	}

	fprintf(physical_memory,"-----------------------------------------\n");
	fclose(physical_memory);
}
//references
//https://www.geeksforgeeks.org/c-program-print-contents-file/
void read_from_physical_memory(){
	FILE *physical_memory;
	char table[255], c;
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
	int last_num = page_size * page_size; //65536
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

	char table[255], c;
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









void do_table(){
//	char *array_table[3][10] = {"Address", "Frame", "Content"};

//	for(int i=0; i<3; i++){
//		printf("%s | %s | %s | [some additional data to indicate used addresses]\n", array_table + i);
//	}

	printf("Address | Frame | Content | [some additional data to indicate used addresses\n");
	printf("--------|-------|---------\n");
	printf("  0x0   |   0   |   A\n");
	printf("  0x1   |   0   |   B\n");

//	for(int i=0; i<3; i++){
//		printf("%u | %u | %u\n", array_table + i);
//	}
}
