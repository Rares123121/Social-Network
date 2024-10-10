Task 1: Friends

I use the 'create' function defined in social_media.c to allocate memory for the
variable that will hold the friend lists.

In the 'add_friends' function, I copy the name and user_id into the current
node. If the friend is not already in the list, I add the node at the
beginning. Otherwise, I traverse the list to the end and set it as the
last node. Finally, I update the size of the list.

In the 'add' function, I check the size of the list array. If it is 0, I add
the two names to the first two positions and update the array's size.
Otherwise, if the size is not 0, I check if the names already exist in the
array. If they do, I add a new friend to the friend list at the found
position. If they do not exist, I add two more lists with the two friends
at the end of the array.

In the 'remove' function, I remove from a given list a node that contains
the name provided as a parameter.

In the 'remove_friend' function, I check if the name exists in the list array,
and if it does, I remove the friend’s name from the current list using the
'remove' function.

In the 'suggestion' function, I declare two arrays: one for the id and one
for the index of a visited friend. Then, I search for the friend list of the
friend for whom I want to make suggestions, marking the friends I’ve visited
with a 1 in the friends_index array. To generate suggestions, I search
through friends that are marked with 1 in the visited friend array. If a
friend of a friend hasn’t been visited, I mark it with 2 (to avoid adding it
multiple times) and place their id in the id array. Then, I sort the id array
in ascending order and print all found names.

The 'number_friends' function returns the size of the list for the given name.

In the 'common_friends' function, I first store the indexes of the two
friends in the list array. Then, I sort the friend list for the first name
by id. I check if there’s at least one common name between the two friends.
If not, I display a message indicating no common friends, otherwise, I print
the common friends.

In the 'popular_friend' function, I store the index of the name for which
I want to find the most popular friend. I then sort the friend list for this
name by id. After sorting, I calculate the maximum number of friends for one
friend. If this max is larger than the size of the current name’s list, I
display the respective friend’s name. Otherwise, I display the name provided
as a parameter.

In the 'distance' function, I declare two arrays: 'visited' and 'distance',
initially filled with 0. I search for the indexes of the two names for
which I want to calculate the distance, and if the initial values don’t
change, I display the appropriate message and exit the function. Otherwise,
I perform a BFS, calculating the distance using the array. In the end, I
print the value at the second name's index from the distance array.

Task 2: Posts

I use the 'create' function to allocate memory for the tree array in
social_media.c.

In the 'create_post' function, I first separate the name and title for the
posts. Then, I increment the post count in this tree array, where each
root is stored in the first field of the tree structure. For each new post,
I reallocate memory for the tree array.

In the 'find_node' function, I recursively search a tree for a node with
the given id.

In the 'split_text_repo' function, I check if I need to add a repost to a
repost or to a post. If it’s a repost to a post, I call the 'add_repost'
function, where, if the root has no children, I create a node that the
'events' field points to, representing the first "sibling". If there are
already children added to the root, I add the repost at the end. If it’s
a repost to a repost, I call the 'add_repost_to_rep' function, where if the
node has no children, I add it as the first child. Otherwise, I check if it
has siblings. If not, I add it at the beginning, else I add it at the end.

In the 'print_tree' function, I print all the nodes of a tree, starting from
the first node under the root, recursively.

In the 'get_rep' function, if I need to print all reposts of a tree, I call
the 'print_tree' function from the root. If I need to print reposts starting
from a repost, I call the 'print_tree' function from the respective node.

In the 'search' function, I identify the nodes for which I want to find
the LCA. Then I use the 'find_path' function to generate path arrays that
contain the nodes traversed to reach the desired node.

In the 'like_post' function, I check if the user has already liked the post,
in which case I decrease the like count and remove the user from the list
of people who liked the post.

In the 'get_likes' function, I display the number of likes a post has.

In the 'ratio' function, I store in the 'max' node the node with the most
likes in a tree. To find it, I use the 'get_likes_max' function, which
recursively searches for this node.

Task 3: Feed

In the 'feed' function, I search the friend list for the name for which I
want to generate the feed. If my feed_size is greater than or equal to the
number of posts, feed_size becomes 0, meaning I need to display all posts.

In the 'view_profile' function, I print all posts and reposts made by a
user, using the 'view_repost' function, which searches recursively.

In the 'friend_repost' function, I search the list array for the given
name, and then for each of their friends, I check if they reposted the
given post id.