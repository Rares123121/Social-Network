#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"

void create_post(copac *c, char *sir) {
	char copie[600], copie2[600];
	strcpy(copie, sir);
	strcpy(copie2, sir);
	char nume[101], titlu[300], *p;
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);
	int nr_spatii = 0;
	int cnt = 0;
	for (int i = 0; copie2[i] != '\n' && copie2[i] != '\0'; i++) {
		if (copie2[i] == ' ')
			nr_spatii++;
		if (nr_spatii >= 2)
			titlu[cnt++] = copie2[i];
	}
	char titlu2[600];
	int idx = 0;
	for (int i = 2; i < cnt - 1; i++)
		titlu2[idx++] = titlu[i];

	titlu2[idx] = '\0';

	uint16_t id_nume = get_user_id(nume);

	post *nod = malloc(sizeof(*nod));
	nod->id = c->next_id++;
	nod->user_id = id_nume;
	strcpy(nod->titlu, titlu2);
	nod->events = NULL;
	nod->number_posts = 0;
	nod->likes = 0;
	for (int i = 0; i < 1001; i++)
		nod->who_liked[i] = 0;
	c->nr_postari++;
	c->postari = realloc(c->postari, c->nr_postari * sizeof(post *));
	c->postari[c->nr_postari - 1] = nod;

	printf("Created \"%s\" for %s\n", titlu2, nume);
}

post *find_node(post *radacina, int id) {
	if (!radacina)
		return NULL;

	if (radacina->id == id)
		return radacina;

	post *copil = find_node(radacina->repost, id);
	if (copil)
		return copil;

	post *frate = find_node(radacina->events, id);
	if (frate)
		return frate;

	return NULL;
}

void add_repost_la_rep(copac *c, char *nume, int id_post, int id_repo) {
		int idx = 0;
		for (int i = 0; i < c->nr_postari; i++)
			if (c->postari[i]->id == id_post)
				idx = i;

		post *r = find_node(c->postari[idx]->events, id_repo);
		if (!r->repost) {
			r->repost = malloc(sizeof(post));
			r->repost->events = NULL;
			r->repost->repost = NULL;
			r->repost->id = c->next_id;
			r->repost->user_id = get_user_id(nume);
			r->repost->likes = 0;
			for (int i = 0; i < 1001; i++)
				r->repost->who_liked[i] = 0;
		} else {
			if (!r->repost->events) {
				r->repost->events = malloc(sizeof(post));
				r->repost->events->id = c->next_id;
				r->repost->events->user_id = get_user_id(nume);
				r->repost->events->events = NULL;
				r->repost->events->repost = NULL;
				r->repost->events->likes = 0;
				for (int i = 0; i < 1001; i++)
					r->repost->events->who_liked[i] = 0;
			} else {
				post *aux = r->repost->events;
				while (aux->events)
					aux = aux->events;
				aux->events = malloc(sizeof(post));
				aux->events->id = c->next_id;
				aux->events->user_id = get_user_id(nume);
				aux->events->events = NULL;
				aux->events->repost = NULL;
				aux->events->likes = 0;
				for (int i = 0; i < 1001; i++)
					aux->events->who_liked[i] = 0;
			}
		}
		printf("Created repost #%d for %s\n", c->next_id, nume);
		c->next_id++;
		return;
}

void add_repost(copac *c, char *nume, int id_post) {
	int index = 0;
	int user_id = get_user_id(nume);// aici trb get_user_id

	for (int i = 0; i < c->nr_postari; i++) {
		if (c->postari[i]->id == id_post)
			index = i;
	}

	if (!c->postari[index]->events) {
		c->postari[index]->events = malloc(sizeof(post));
		c->postari[index]->events->events = NULL;
		c->postari[index]->events->repost = NULL;
		c->postari[index]->events->id = c->next_id;
		c->postari[index]->events->user_id = user_id;
		c->postari[index]->events->likes = 0;
		for (int i = 0; i < 1001; i++)
			c->postari[index]->events->who_liked[i] = 0;
	} else {
		post *aux = c->postari[index]->events;
		while (aux->events)
			aux = aux->events;

		aux->events = malloc(sizeof(post));
		aux->events->id = c->next_id;
		aux->events->user_id = user_id;
		aux->events->events = NULL;
		aux->events->repost = NULL;
		aux->events->likes = 0;
		for (int i = 0; i < 1001; i++)
			aux->events->who_liked[i] = 0;
	}
	printf("Created repost #%d for %s\n", c->next_id, nume);
	c->next_id++;
}

void split_text_repo(copac *c, char *sir) {
	char copie[600], *p, nume[1001];
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);
	int id_post, id_repo;
	p = strtok(NULL, "\n ");
	id_post = atoi(p);
	p = strtok(NULL, "\n ");
	if (p) {
		id_repo = atoi(p);
		add_repost_la_rep(c, nume, id_post, id_repo);
		return;
	}
	add_repost(c, nume, id_post);
}

void print_copac(post *radacina, int lvl) {
	if (!radacina)
		return;

	char *nume = get_user_name(radacina->user_id);

	printf("Repost #%d by %s\n", radacina->id, nume);

	if (radacina->repost)
		print_copac(radacina->repost, lvl + 1);

	if (radacina->events)
		print_copac(radacina->events, lvl);
}

void get_rep(copac *c, char *sir) {
	char copie[700];
	strcpy(copie, sir);
	char *p;
	int id;
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	id = atoi(p);
	p = strtok(NULL, "\n ");
	int id_repo;
	if (p) {
		id_repo = atoi(p);
		int idx = 0;
		for (int i = 0; i < c->nr_postari; i++)
			if (c->postari[i]->id == id)
				idx = i;

		post *r = find_node(c->postari[idx]->events, id_repo);
		char *nume1 = get_user_name(r->user_id);
		printf("Repost #%d by %s\n", r->id, nume1);
		if (r->repost)
			print_copac(r->repost, 0);
		return;
	}

	int ix = 0;
	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == id)
			ix = i;

	char *nume = get_user_name(c->postari[ix]->user_id);
	printf("\"%s\" - Post by %s\n", c->postari[ix]->titlu, nume);
	print_copac(c->postari[ix]->events, 0);
}

int find_path(post *radacina, post *target, post **path, int *len) {
	if (!radacina)
		return 0;

	path[(*len)++] = radacina;
	if (radacina == target)
		return 1;

	if (radacina->repost && find_path(radacina->repost, target, path, len))
		return 1;

	(*len)--;
	if (radacina->events && find_path(radacina->events, target, path, len))
		return 1;

	return 0;
}

void caut(copac *c, char *sir) {
	int id1, id2, idx;
	char copie[600];
	strcpy(copie, sir);
	char *p;
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	idx = atoi(p);
	p = strtok(NULL, "\n ");
	id1 = atoi(p);
	p = strtok(NULL, "\n ");
	id2 = atoi(p);

	int index = 0;
	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == idx)
			index = i;

	post *n1, *n2;
	n1 = find_node(c->postari[index]->events, id1);
	n2 = find_node(c->postari[index]->events, id2);
	post *p1[1001], *p2[1001];
	p1[0] = c->postari[index];
	p2[0] = c->postari[index];
	int p1_len = 1, p2_len = 1;
	if (!find_path(c->postari[index]->events, n1, p1, &p1_len) ||
		!find_path(c->postari[index]->events, n2, p2, &p2_len))
		return;

	int i;
	for (i = 0; i < p1_len && i < p2_len; i++)
		if (p1[i]->id != p2[i]->id)
			break;

	printf("The first common repost of %d and %d is %d\n", id1, id2,
		   p1[i - 1]->id);
}

void like_post(copac *c, char *sir) {
	char nume[1001], *p, copie[10001];
	int id_post, id_repost;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	strcpy(nume, p);
	p = strtok(NULL, "\n ");
	id_post = atoi(p);
	p = strtok(NULL, "\n ");
	if (p) {
		id_repost = atoi(p);
		int idx = 0;
		int userid = get_user_id(nume);
		for (int i = 0; i < c->nr_postari; i++)
			if (c->postari[i]->id == id_post)
				idx = i;
		post *nod = find_node(c->postari[idx]->events, id_repost);
		if (nod->who_liked[userid] == 0) {
			nod->who_liked[userid] = 1;
			nod->likes++;
			printf("User %s liked repost \"%s\"\n", nume,
				   c->postari[idx]->titlu);
			return;
		}
		if (nod->who_liked[userid] == 1) {
			nod->who_liked[userid] = 0;
			nod->likes--;
			printf("User %s unliked repost \"%s\"\n", nume,
				   c->postari[idx]->titlu);
			return;
		}
	}

	int index = 0;
	int user_id = get_user_id(nume);
	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == id_post)
			index = i;

	if (c->postari[index]->who_liked[user_id] == 0) {
		c->postari[index]->who_liked[user_id] = 1;
		c->postari[index]->likes++;
		printf("User %s liked post \"%s\"\n", nume, c->postari[index]->titlu);
		return;
	}
	if (c->postari[index]->who_liked[user_id] == 1) {
		c->postari[index]->who_liked[user_id] = 0;
		c->postari[index]->likes--;
		printf("User %s unliked post \"%s\"\n", nume, c->postari[index]->titlu);
		return;
	}
}

void get_likes(copac *c, char *sir) {
	char copie[1001], *p;
	int id_p, id_rep;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	id_p = atoi(p);
	p = strtok(NULL, "\n ");
	if (p) {
		id_rep = atoi(p);
		int index = 0;
		for (int i = 0; i < c->nr_postari; i++)
			if (c->postari[i]->id == id_p)
				index = i;

		post *nod = find_node(c->postari[index]->events, id_rep);
		printf("Repost #%d has %d likes\n", nod->id, nod->likes);
		return;
	}

	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == id_p) {
			printf("Post \"%s\" has %d likes\n", c->postari[i]->titlu,
				   c->postari[i]->likes);
			return;
		}
}

void get_likes_max(post *root, post **nod) {
	if (!root)
		return;

	if (!(*nod) || root->likes > (*nod)->likes)
		*nod = root;

	get_likes_max(root->events, nod);
	get_likes_max(root->repost, nod);
}

void ratio(copac *c, char *sir) {
	char copie[1001], *p;
	int id_post;
	strcpy(copie, sir);
	p = strtok(copie, "\n ");
	p = strtok(NULL, "\n ");
	id_post = atoi(p);
	int index = 0;

	for (int i = 0; i < c->nr_postari; i++)
		if (c->postari[i]->id == id_post)
			index = i;

	post *max = NULL;
	get_likes_max(c->postari[index]->events, &max);
	if (!max || c->postari[index]->likes >= max->likes)
		printf("The original post is the highest rated\n");
	else
		printf("Post %d got ratio'd by repost %d\n", id_post, max->id);
}

void handle_input_posts(char *input, copac *ret)
{
	char com2[600];
	strcpy(com2, input);
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		create_post(ret, com2);
	else if (!strcmp(cmd, "repost"))
		split_text_repo(ret, com2);
	else if (!strcmp(cmd, "common-repost"))
		caut(ret, com2);
	else if (!strcmp(cmd, "like"))
		like_post(ret, com2);
	else if (!strcmp(cmd, "ratio"))
		ratio(ret, com2);
	else if (!strcmp(cmd, "delete"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		get_likes(ret, com2);
	else if (!strcmp(cmd, "get-reposts"))
		get_rep(ret, com2);

	free(commands);
}

