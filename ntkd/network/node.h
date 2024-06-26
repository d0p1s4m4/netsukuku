#ifndef NETSUKUKU_NODE_H
# define NETSUKUKU_NODE_H 1

# include <stdint.h>
# include <sodium.h>

struct node {
	uint8_t id[crypto_core_ed25519_BYTES];
};

#endif /* NETSUKUKU_NODE_H */