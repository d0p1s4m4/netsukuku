#ifndef NETSUKUKU_CFG_H
# define NETSUKUKU_CFG_H 1

# define CFG_FILE "ntkd.conf"

const char *cfg_default_path(void);
int cfg_load_from(const char *file);

#endif /* NETSUKUKU_CFG_H */