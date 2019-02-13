#include <stdio.h>
#include "lib/my-functions.h"

int main(){
	write_to_physical_memory();
	read_from_physical_memory();

	write_to_page_table();
	read_from_page_table();

	do_table();
	return 0;
}
