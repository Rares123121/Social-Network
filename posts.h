#ifndef POSTS_H
#define POSTS_H

typedef struct post {
	int id;
	char titlu[300];
	uint16_t user_id;
	struct post *events;
	struct post *repost;
	int number_posts;
	int likes;
	int who_liked[1001];
} post;

typedef struct copac {
	post **postari;
	int next_id;
	int nr_postari;
} copac;
/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_posts(char *input, copac *random);

#endif // POSTS_H
