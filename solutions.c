#include <stdio.h>
#include "lib/my-functions.h"

int main(){
	int amount, start, end;
	amount = 1;
	start = 2048;
	end = 20480;
	int random_number = random_number_generator(amount, start, end);

	amount = random_number;
	start = 32;
	end = 125;
	int *array_of_numbers = random_number_generator(amount, start, end);

	char *character = random_character_generator(random_number);	
	printf("random number = %d\n", random_number);
	printf("random character = %c\n\n\n", character);

	write_to_physical_memory(random_number, character);
	free(character);
//	read_from_physical_memory();

//	write_to_page_table();
//	read_from_page_table();

	return 0;
}
