// Shim to publicly export Git symbols. These must be renamed so that the
// original symbols can be hidden. Renaming these with a "libgit_" prefix also
// avoid conflicts with other libraries such as libgit2.

#include "git-compat-util.h"
#include "contrib/cgit-rs/cgit-sys/public_symbol_export.h"
#include "common-init.h"
#include "config.h"
#include "setup.h"
#include "version.h"

extern struct repository *the_repository;

#pragma GCC visibility push(default)

const char *libgit_setup_git_directory(void)
{
	return setup_git_directory();
}

int libgit_config_get_int(const char *key, int *dest)
{
	return repo_config_get_int(the_repository, key, dest);
}

void libgit_init_git(const char **argv)
{
	init_git(argv);
}

int libgit_parse_maybe_bool(const char *val)
{
	return git_parse_maybe_bool(val);
}

struct config_set *libgit_configset_alloc(void)
{
	return git_configset_alloc();
}

void libgit_configset_clear_and_free(struct config_set *cs)
{
	git_configset_clear_and_free(cs);
}

void libgit_configset_init(struct config_set *cs)
{
	git_configset_init(cs);
}

int libgit_configset_add_file(struct config_set *cs, const char *filename)
{
	return git_configset_add_file(cs, filename);
}

int libgit_configset_get_int(struct config_set *cs, const char *key, int *dest)
{
	return git_configset_get_int(cs, key, dest);
}

int libgit_configset_get_string(struct config_set *cs, const char *key, char **dest)
{
	return git_configset_get_string(cs, key, dest);
}

const char *libgit_user_agent(void)
{
	return git_user_agent();
}

const char *libgit_user_agent_sanitized(void)
{
	return git_user_agent_sanitized();
}

#pragma GCC visibility pop
