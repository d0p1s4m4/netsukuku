#ifndef NTKD_NET_INTERFACE_H
# define NTKD_NET_INTERFACE_H 1

typedef struct interface {
	char *name;
	struct interface *next;
} Interface;

extern Interface *interfaces;

int interface_scan(void);
int interface_exist(const char *name);

#endif /* !NTKD_NET_INTERFACE_H */
