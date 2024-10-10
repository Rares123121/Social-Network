/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

vector *create(void) {
	vector *aux = malloc(sizeof(*aux));
	aux->size = 0;
	aux->list = malloc(MAX_PEOPLE * sizeof(lista *));
	for (int i = 0; i < MAX_PEOPLE; i++) {
		aux->list[i] = malloc(sizeof(lista));
		aux->list[i]->head = NULL;
		aux->list[i]->size = 0;
	}
	return aux;
}

copac *creez(void) {
	copac *aux = malloc(sizeof(copac));
	aux->postari = (post **)malloc(sizeof(post *));
	aux->next_id = 1;
	aux->nr_postari = 0;
	return aux;
}

void free_post(post *p) {
	if (!p)
		return;
	// Recursively free the children nodes
	free_post(p->repost);
	free_post(p->events);
	// Free the current node
	free(p);
}

void free_tree(post *r) {
	if (!r)
		return;
	// Free the subtree rooted at r->repost
	free_post(r->repost);
	// Free the subtree rooted at r->events
	free_post(r->events);
}

/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	init_users();

	init_tasks();

	vector *friends = create();
	copac *retea = creez();

	char *input = (char *)malloc(MAX_COMMAND_LEN);
	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!command)
			break;

		#ifdef TASK_1
		handle_input_friends(input, friends);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, retea);
		#endif

		#ifdef TASK_3
		handle_input_feed(input, friends, retea);
		#endif
	}

	for (int i = 0; i < MAX_PEOPLE; i++) {
		prieten *nod = friends->list[i]->head;
		while (nod) {
			prieten *aux = nod;
			nod = nod->next;
			free(aux);
		}
		free(friends->list[i]);
	}
	free(friends->list);
	free(friends);

	for (int i = 0; i < retea->nr_postari; i++) {
		free_tree(retea->postari[i]->events);
		free(retea->postari[i]->events);
		free(retea->postari[i]);
	}
	free(retea->postari);
	free(retea);

	free_users();
	free(input);

	return 0;
}
