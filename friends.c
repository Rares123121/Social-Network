#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"

void adaug_prieten(lista * list, char *nume);

void add(vector *v, char *sir);

void remove_friend(lista *list, char *nume_de_scos);

void scoate(vector *v, char *sir);

void print_names(lista *list, lista *list2);

void suggestion(vector *v, char *sir);

void number_friends(vector *v, char *sir);

void comuni(vector *v, char *sir);

void popular(vector *v, char *sir);

void distante(vector *v, char *sir);

void check_dist(vector *v, char *sir);

void handle_input_friends(char *input, vector *friends)
{
	char commands2[MAX_COMMAND_LEN];
	char *commands = strdup(input);
	strcpy(commands2, input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add"))
		add(friends, commands2);
	else if (!strcmp(cmd, "remove"))
		scoate(friends, commands2);
	else if (!strcmp(cmd, "suggestions"))
		suggestion(friends, commands2);
	else if (!strcmp(cmd, "distance"))
		distante(friends, commands2);
	else if (!strcmp(cmd, "common"))
		comuni(friends, commands2);
	else if (!strcmp(cmd, "friends"))
		number_friends(friends, commands2);
	else if (!strcmp(cmd, "popular"))
		popular(friends, commands2);

	free(commands);
}

void adaug_prieten(lista *list, char *nume) {
	prieten *nod = malloc(sizeof(*nod));

	strcpy(nod->nume, nume);
	nod->id = (int)get_user_id(nume);

	if (list->size == 0) {
		nod->next = NULL;
		list->head = nod;
	} else {
		nod->next = NULL;
		prieten *aux = list->head;
		while (aux->next)
			aux = aux->next;
		aux->next = nod;
	}

	list->size++;
}

void add(vector *v, char *sir) {
	char *p, copie[MAX_COMMAND_LEN];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	char nume1[101], nume2[101];
	p = strtok(NULL, "\n ");
	strcpy(nume1, p);
	p = strtok(NULL, "\n ");
	strcpy(nume2, p);

	if (v->size == 0) {
		strcpy(v->list[0]->nume_prieten, nume1);
		adaug_prieten(v->list[0], nume2);
		strcpy(v->list[1]->nume_prieten, nume2);
		adaug_prieten(v->list[1], nume1);
		v->size += 2;
		printf("Added connection %s - %s\n", nume1, nume2);
	} else {
		int ok1 = 0, ok2 = 0;
		for (int i = 0; i < v->size; i++) {
			if (strcmp(v->list[i]->nume_prieten, nume1) == 0) {
				adaug_prieten(v->list[i], nume2);
				ok1 = 1;
			}
			if (strcmp(v->list[i]->nume_prieten, nume2) == 0) {
				adaug_prieten(v->list[i], nume1);
				ok2 = 1;
			}
		}
		if (ok1 == 0) {
			adaug_prieten(v->list[v->size], nume2);
			strcpy(v->list[v->size]->nume_prieten, nume1);
			v->size++;
		}
		if (ok2 == 0) {
			adaug_prieten(v->list[v->size], nume1);
			strcpy(v->list[v->size]->nume_prieten, nume2);
			v->size++;
		}
		printf("Added connection %s - %s\n", nume1, nume2);
	}
}

void remove_friend(lista *list, char *nume_de_scos) {
	if (list->size == 1) {
		free(list->head);
		list->head = NULL;
		list->size = 0;
		return;
	}

	if (strcmp(nume_de_scos, list->head->nume) == 0) {
		prieten *nod = list->head;
		list->head = list->head->next;
		free(nod);
		list->size--;
		return;
	}

	prieten *nod = list->head;
	prieten *prev = NULL;
	while (nod && strcmp(nod->nume, nume_de_scos) != 0) {
		prev = nod;
		nod = nod->next;
	}

	prev->next = prev->next->next;
	free(nod);
	list->size--;
}

void scoate(vector *v, char *sir) {
	char *p, nume1[101], nume2[101];
	char copie[MAX_COMMAND_LEN];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume1, p);
	p = strtok(NULL, "\n ");
	strcpy(nume2, p);

	for (int i = 0; i < v->size; i++) {
		if (strcmp(v->list[i]->nume_prieten, nume1) == 0)
			remove_friend(v->list[i], nume2);
		if (strcmp(v->list[i]->nume_prieten, nume2) == 0)
			remove_friend(v->list[i], nume1);
	}
	printf("Removed connection %s - %s\n", nume1, nume2);
}

void suggestion(vector *v, char *sir) {
	char copie[101], *p, nume[101];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);

	uint16_t id[MAX_PEOPLE] = {0};
	int friends_index[MAX_PEOPLE] = {0};
	int cnt = 0;
	for (int i = 0; i < v->size; i++) {
		if (strcmp(nume, v->list[i]->nume_prieten) == 0) {
			prieten *nod = v->list[i]->head;
			while (nod) {
				for (int j = 0; j < v->size; j++)
					if (strcmp(nod->nume, v->list[j]->nume_prieten) == 0)
						friends_index[j] = 1;
				nod = nod->next;
			}
		}
	}

for (int i = 0; i < v->size; i++) {
	if (friends_index[i] == 1) {
		prieten *nod = v->list[i]->head;
		while (nod) {
			for (int j = 0; j < v->size; j++) {
				if (strcmp(nod->nume, v->list[j]->nume_prieten) == 0) {
					if (friends_index[j] == 0 && strcmp(nod->nume, nume) != 0) {
						id[cnt++] = get_user_id(nod->nume);
						friends_index[j] = 2;
					}
				}
			}
			nod = nod->next;
		}
	}
}

	for (int i = 0; i < cnt - 1; i++)
		for (int j = i + 1; j < cnt; j++) {
			if (id[i] > id[j]) {
				uint16_t aux = id[i];
				id[i] = id[j];
				id[j] = aux;
			}
		}
	if (cnt) {
		printf("Suggestions for %s:\n", nume);
		for (int i = 0; i < cnt; i++) {
			char *name = get_user_name(id[i]);
			printf("%s\n", name);
		}
	} else {
		printf("There are no suggestions for %s\n", nume);
	}
}

void number_friends(vector *v, char *sir) {
	char copie[MAX_COMMAND_LEN], *p, nume[101];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);

	for (int i = 0; i < v->size; i++)
		if (strcmp(nume, v->list[i]->nume_prieten) == 0)
			printf("%s has %d friends\n", nume, v->list[i]->size);
}

void comuni(vector *v, char *sir) {
	char copie[MAX_COMMAND_LEN], nume1[101], nume2[101], *p;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume1, p);
	p = strtok(NULL, "\n ");
	strcpy(nume2, p);

	int index_nume1 = 0, index_nume2 = 0;
	for (int i = 0; i < v->size; i++) {
		if (strcmp(nume1, v->list[i]->nume_prieten) == 0)
			index_nume1 = i;
		if (strcmp(nume2, v->list[i]->nume_prieten) == 0)
			index_nume2 = i;
	}

	int gata;
	do {
		gata = 0;
		prieten *sort = v->list[index_nume1]->head;
		while (sort->next) {
			if (sort->id > sort->next->id) {
				uint16_t aux = sort->id;
				sort->id = sort->next->id;
				sort->next->id = aux;
				char v[1001];
				strcpy(v, sort->nume);
				strcpy(sort->nume, sort->next->nume);
				strcpy(sort->next->nume, v);
				gata = 1;
			}
			sort = sort->next;
		}
	} while (gata == 1);
	prieten *nod = v->list[index_nume1]->head;
	int exista = 0;
	while (nod) {
		char aux[101];
		strcpy(aux, nod->nume);
		prieten *nod2 = v->list[index_nume2]->head;
		while (nod2) {
			if (strcmp(nod2->nume, aux) == 0) {
				exista = 1;
				break;
			}
			nod2 = nod2->next;
		}
		nod = nod->next;
	}

	if (exista == 0) {
		printf("No common friends for %s and %s\n", nume1, nume2);
	} else {
		printf("The common friends between %s and %s are:\n", nume1, nume2);
		prieten *nod = v->list[index_nume1]->head;
		while (nod) {
			char aux[101];
			strcpy(aux, nod->nume);
			prieten *nod2 = v->list[index_nume2]->head;
			while (nod2) {
				if (strcmp(nod2->nume, aux) == 0)
					printf("%s\n", aux);
				nod2 = nod2->next;
			}
			nod = nod->next;
		}
	}
}

void popular(vector *v, char *sir) {
	char copie[MAX_COMMAND_LEN], nume[101], *p;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);

	char nume_popular[101];
	int maxim = -1;
	int index = 0;
	for (int i = 0; i < v->size; i++)
		if (strcmp(nume, v->list[i]->nume_prieten) == 0)
			index = i;

	int gata;
	do {
		gata = 0;
		prieten *sort = v->list[index]->head;
		while (sort->next) {
			if (sort->id > sort->next->id) {
				uint16_t aux = sort->id;
				sort->id = sort->next->id;
				sort->next->id = aux;
				char v[1001];
				strcpy(v, sort->nume);
				strcpy(sort->nume, sort->next->nume);
				strcpy(sort->next->nume, v);
				gata = 1;
			}
			sort = sort->next;
		}
	} while (gata == 1);

	prieten *nod = v->list[index]->head;
	while (nod) {
		char aux[101];
		strcpy(aux, nod->nume);
		int index2;
		for (int i = 0; i < v->size; i++)
			if (strcmp(aux, v->list[i]->nume_prieten) == 0)
				index2 = i;

		if (maxim < v->list[index2]->size) {
			maxim = v->list[index2]->size;
			strcpy(nume_popular, aux);
		}
		nod = nod->next;
	}
	if (v->list[index]->size >= maxim)
		printf("%s is the most popular\n", nume);
	else
		printf("%s is the most popular friend of %s\n", nume_popular, nume);
}

void distante(vector *v, char *sir) {
	char copie[MAX_COMMAND_LEN], nume1[101], nume2[101], *p;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume1, p);
	p = strtok(NULL, "\n ");
	strcpy(nume2, p);

	int vizitat[MAX_PEOPLE] = {0};
	int distanta[MAX_PEOPLE] = {0};

	int index1 = -1, index2 = -1;

	for (int i = 0; i < v->size; i++) {
		if (strcmp(nume1, v->list[i]->nume_prieten) == 0)
			index1 = i;
		if (strcmp(nume2, v->list[i]->nume_prieten) == 0)
			index2 = i;
	}

	if (index1 == -1 || index2 == -1) {
		printf("There is no way to get from %s to %s\n", nume1, nume2);
		return;
	}

	int queue[MAX_PEOPLE];
	int front = 0, rear = 0;
	queue[rear++] = index1;
	vizitat[index1] = 1;

	while (front < rear) {
		int current = queue[front++];
		prieten *nod = v->list[current]->head;
		while (nod) {
			for (int i = 0; i < v->size; i++) {
				if (strcmp(nod->nume, v->list[i]->nume_prieten) == 0 &&
					vizitat[i] == 0) {
					distanta[i] = distanta[current] + 1;
					vizitat[i] = 1;
					queue[rear++] = i;
				}
			}
			nod = nod->next;
		}
	}

	if (vizitat[index2] == 0)
		printf("There is no way to get from %s to %s\n", nume1, nume2);
	else
		printf("The distance between %s - %s is %d\n", nume1, nume2,
			   distanta[index2]);
}
