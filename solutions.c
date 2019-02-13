#include <stdio.h>
#include "lib/my-functions.h"

int main(){
	int amount, start, end;
	amount = 1;
	start = 2048;
	end = 20480;
	int number1 = random_number_generator(amount, start, end);

	amount = number1;	
	start = 33;
	end = 126;
	int *character = random_number_generator(amount, start, end);

	printf("random number = %d\n", number1);
	printf("random characters (Dec) = %d\n", character);
	printf("random character = %c\n\n\n", character);

	int *characters;
	characters = getCharacters(amount, start, end);
	//printf("characters....\n");
	//for(int i=0; i<amount; ++i){printf("%c", *(characters+i));}

	write_to_page_table(amount, start, end);
	write_to_physical_memory(number1, character, characters);

//	read_from_physical_memory();
//	read_from_page_table();

	return 0;
}
