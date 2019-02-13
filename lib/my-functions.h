#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

int *random_number_generator();
int *getCharacters();

void write_to_physical_memory(int *, char *, int *);
void write_to_page_table(int, int, int);

//void read_from_physical_memory();
//void read_from_page_table();
#endif
