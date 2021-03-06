#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//returns a random number
//references
//https://stackoverflow.com/questions/1108780/why-do-i-always-get-the-same-sequence-of-random-numbers-with-rand
int random_number_generator(int amount, int start, int end){
	srand(time(NULL));
	int random_number;

	for(int i=0; i<amount; ++i){
		random_number = start + (rand() % (end - start));
		//printf("%d\n", random_number);
	}
	return random_number;
}

//returns random characters
int * getCharacters(int amount, int start, int end){
	srand(time(NULL));
	static int characters[20480];
	
	for(int i=0; i<amount; ++i){
		characters[i] = start + (rand() % (end - start));
	}
	return characters;
}

//allows user to input address then prints the line from physical_memory.txt equal to that address
//references
//https://www.quora.com/How-do-I-read-nth-line-of-a-file-in-C-using-File-handling
void enter_address_show_data(){
	FILE *physical_memory;
	char line[65535];
	physical_memory = fopen("./data/physical_memory.txt", "r");

	int HexAddress = -1;
	int DecAddress;
	printf("Please enter a Hex number between 0 and FFFF (65535)(e.g. of input: 0xa300) or -1 to quit: ");
	scanf("%x", &HexAddress);
	DecAddress = HexAddress;
	if(HexAddress == -1){
		printf("Quitting...\n\n");
	}
	else if(DecAddress < 0 || DecAddress > 65535){
		printf("\nBad number, Please try again.\n");
		enter_address_show_data();
	}
	else{
		printf("You Entered (Hex) : 0x%x\nYou Entered (Dec) : %d\n", HexAddress, DecAddress);
		int i=0;
		while(fgets(line, sizeof(line), physical_memory)){
			i++;
			if(i == (HexAddress + 3)){printf("%s\n", line);}
		}
		enter_address_show_data();
	}
	fclose(physical_memory);
}

//writes to the physical_memory (physical_memory.txt)
//references
//https://ubuntuforums.org/showthread.php?t=1686044
void write_to_physical_memory(int number, int *characters, int firstchar){
	FILE *physical_memory = fopen("./data/physical_memory.txt", "w");
	if(physical_memory == NULL){
		printf("Error with file!\n");
		exit(1);
	}

	int page_size = 256;
	int current_address = 0; //needed an int for current_address and frame because i and j didnt display the tables properly
	int frame = 0;
	_Bool isused = 0;
	//printing the table to the physical memory text file
	fprintf(physical_memory," Address\t| Frame\t| Content | Used?\n");
	fprintf(physical_memory,"----------------|-------|---------|--------\n");
	for(int i=0; i<page_size; ++i){
		for(int j=0; j<page_size; ++j){
			//printing the random characters to the table
			if(current_address >= firstchar && current_address < (firstchar + number)){
				isused = 1;
				fprintf(physical_memory, " 0x%x\t\t| %d\t| %c\t  | %d\n", current_address, frame, *(characters+j), isused);
			}
			else{
				isused = 0;
				fprintf(physical_memory, " 0x%x\t\t| %d\t| ...\t  | %d\n", current_address, frame, isused);
			}
			++current_address;
		}
		++frame;
	}
	fprintf(physical_memory,"----------------------------------------------\n");
	fclose(physical_memory);
}

//references
//https://ubuntuforums.org/showthread.php?t=1686044
//https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.html
//https://www.includehelp.com/c-programs/extract-bytes_from_int.aspx
void write_to_page_table(int *characters, int number1, int firstchar){
	FILE *page_table = fopen("data/page_table.txt", "w");
	if(page_table == NULL){
		printf("Error with file!\n");
		exit(1);
	}
	int page = 0;
	int i = (firstchar/255); //frame
	int j = 0;

	typedef unsigned char BYTE;
	unsigned int virtual_address=firstchar;
	printf("virtual address used for swapping: 0x%x\n", virtual_address);
	BYTE offset,vpn,temp;
	offset=(virtual_address&0xFF);
	vpn=((virtual_address>>8)&0xFF);

	printf("offset: %02X\n", offset);
	printf("VPN: %02X\n", vpn);
	printf("PFN: %d\n\n", vpn);
	
	int sum = offset + vpn;
	//swapping (i know this is not exactly the way you wanted but i was running out of time and couldnt figure out a better way to do it)
	printf("sum of offset and PFN before swap = %d\n", sum);
	temp = offset;
	offset = vpn;
	vpn = temp;
	temp = vpn;
	vpn = offset;
	offset = temp;

	//printing the table to the page table text file
	fprintf(page_table," Page\t | Frame | First Address of Page/Frame\t| swapping...\n");
	fprintf(page_table,"---------|-------|------------------------------|---------------------------------\n");
	for(int frame=i; frame<256; ++frame){
		if(page == 0){
	fprintf(page_table, "%d\t | %d\t | 0x%x\t--\t%d\t| %d\n", page, frame, ((firstchar+page)+j), ((firstchar+page)+j), (offset + frame));
	printf("sum of offset and PFN after swap = %d\n\n", sum);
	
		}
		else{
	fprintf(page_table, "%d\t | %d\t | 0x%x\t--\t%d\n", page, frame, ((firstchar+page)+j), ((firstchar+page)+j));
		}
		
		++page;
		j = j+255;
	}
	fprintf(page_table,"-------------------------------------------------------------------------\n");
	fclose(page_table);
}


//references
//https://www.geeksforgeeks.org/c-program-print-contents-file/
void read_from_page_table(){
	printf("--------------Printing virtual memory (page_table)--------------\n");
	printf("----------------------------------------------------------------\n");
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


