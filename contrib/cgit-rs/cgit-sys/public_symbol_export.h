#ifndef PUBLIC_SYMBOL_EXPORT_H
#define PUBLIC_SYMBOL_EXPORT_H

const char *libgit_setup_git_directory(void);

int libgit_config_get_int(const char *key, int *dest);

void libgit_init_git(const char **argv);

int libgit_parse_maybe_bool(const char *val);

struct config_set *libgit_configset_alloc(void);

void libgit_configset_clear_and_free(struct config_set *cs);

void libgit_configset_init(struct config_set *cs);

int libgit_configset_add_file(struct config_set *cs, const char *filename);

int libgit_configset_get_int(struct config_set *cs, const char *key, int *dest);

int libgit_configset_get_string(struct config_set *cs, const char *key, char **dest);

const char *libgit_user_agent(void);

const char *libgit_user_agent_sanitized(void);

#endif /* PUBLIC_SYMBOL_EXPORT_H */
