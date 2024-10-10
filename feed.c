#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "users.h"

void feed(copac *c, vector *f, char *sir) {
	char nume[1001], *p;
	int feed_size;
	char copie[1001];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);
	p = strtok(NULL, "\n ");
	feed_size = atoi(p);

	for (int i = 0; i < f->size; i++)
		if (strcmp(nume, f->list[i]->nume_prieten) == 0) {
			if (feed_size > c->nr_postari)
				feed_size = 0;
			if (feed_size == c->nr_postari)
				feed_size = 0;
			for (int j = c->nr_postari - 1; j >= feed_size; j--) {
				prieten *nod = f->list[i]->head;
				int ok = 0;
				char *s = get_user_name(c->postari[j]->user_id);
				while (nod) {
					if (strcmp(nod->nume, s) == 0)
						ok = 1;
					nod = nod->next;
				}
				if (strcmp(nume, s) == 0)
					ok = 1;
				if (ok == 1)
					printf("%s: \"%s\"\n", s, c->postari[j]->titlu);
			}
		}
}

void view_repost(post *r, int user_id, char *titlu) {
	if (!r)
		return;

	if (r->user_id == user_id)
		printf("Reposted: \"%s\"\n", titlu);

	view_repost(r->repost, user_id, titlu);
	view_repost(r->events, user_id, titlu);
}

void view_profile(copac *c, char *sir) {
	char copie[1001], nume[1001], *p;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);

	int user_id = get_user_id(nume);
	for (int i = 0; i < c->nr_postari; i++) {
		if (c->postari[i]->user_id == user_id)
			printf("Posted: \"%s\"\n", c->postari[i]->titlu);
		view_repost(c->postari[i]->events, user_id, c->postari[i]->titlu);
	}
}

void friend_repost(copac *c, vector *v, char *sir) {
	char nume[1001], copie[1001], *p;
	int post_id;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);
	p = strtok(NULL, "\n ");
	post_id = atoi(p);

	int index = 0;
	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == post_id)
			index = i;

	for (int i = 0; i < v->size; i++)
		if (strcmp(v->list[i]->nume_prieten, nume) == 0) {
			prieten *nod = v->list[i]->head;
			while (nod) {
				post *rep = c->postari[index]->events;
				while (rep) {
					if (rep->user_id == nod->id)
						printf("%s\n", nod->nume);
					rep = rep->events;
				}
				nod = nod->next;
			}
		}
}

void handle_input_feed(char *input, vector *prieteni, copac *retea)
{
	char com2[1001];
	strcpy(com2, input);
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "feed"))
		feed(retea, prieteni, com2);
	else if (!strcmp(cmd, "view-profile"))
		view_profile(retea, com2);
	else if (!strcmp(cmd, "friends-repost"))
		friend_repost(retea, prieteni, com2);
	else if (!strcmp(cmd, "common-groups"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}
