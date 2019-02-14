#include <stdio.h>
#include "lib/my-functions.h"

int main(){
	int amount, start, end;
	amount = 1;
	start = 2048;
	end = 20480;
	int number1 = random_number_generator(amount, start, end);
	printf("random number of characters: %d\n\n", number1);

	amount = number1;	
	start = 33;
	end = 126;
	int *characters = getCharacters(amount, start, end);

	amount = 1;
	start = 2;
	end = 255 - (number1 / 255);
	int firstchar = random_number_generator(amount, start, end);
	printf("      Frame characters start at: %d\n", firstchar);
	firstchar = firstchar * 256;
	printf("Hex address characters start at: 0x%x\nDec address characters start at: %d\n\n", firstchar, firstchar);

	write_to_page_table(characters, number1, firstchar);
	write_to_physical_memory(number1, characters, firstchar);

	enter_address_show_data();

	//read_from_page_table();
	return 0;
}
