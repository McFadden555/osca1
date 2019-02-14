#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

int random_number_generator(int, int, int);
int *getCharacters(int, int, int);

void write_to_physical_memory(int, int *, int);
void write_to_page_table(int *, int, int);

void enter_address_show_data();

void read_from_page_table();

#endif
