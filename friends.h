#ifndef FRIENDS_H
#define FRIENDS_H
#include <stdint.h>
#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

typedef struct prieten {
	char nume[101];
	uint16_t id;
	struct prieten *next;
} prieten;

typedef struct lista {
	char nume_prieten[101];
	int size;
	prieten *head;
} lista;

typedef struct vector {
	int size;
	lista **list;
} vector;

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(char *input, vector *friends);

#endif // FRIENDS_H
