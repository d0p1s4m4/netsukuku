#ifndef NTKD_MAP_H
# define NTKD_MAP_H 1

# include <stddef.h>
# include <stdint.h>

# define MAP_NODE_MAX 256

/* Internal map */
typedef struct {

} Map;

# define GNODE_MAX_CHILD 256
# define NODE_MAX_LEVEL 4

typedef struct node {
	uint8_t level; /* level 0 == node else gnode */

	struct node *child;
	size_t child_count;
} Node;


#endif /* !NTKD_MAP_H */
