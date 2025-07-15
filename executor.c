#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include "shell.h"
#include "node.h"
#include "executor.h"

int do_exec_cmd(int argc, char **argv) {
	printf("running command: \n");
	for (int i = 0; argv[i]; i++) {
		printf(" argv[%d] = '%s'\n", i, argv[i]);
	}

	execvp(argv[0], argv);
	
	perror("error: failed to execute command");
	if (errno == ENOEXEC) {
		exit(126);
	} else if (errno == ENOENT) {
		exit(127);
	} else {
		exit(EXIT_FAILURE);
	}
}

static inline void free_argv(int argc, char **argv) {
	if (!argc) {
		return;
	}

	while (argc--) {
		free(argv[argc]);
	}
}

int do_simple_command(struct node_s *node) {
	if (!node) {
		return 0;
	}

	struct node_s *child = node->first_child;
	if(!child) {
		return 0;
	}

	int argc = 0;
	long max_args = 255;
	char *argv[max_args+1];
	char *str;

	while(child) {
		str = child->val.str;
		if (!str) {
			fprintf(stderr, "Null string in command node\n");
			free_argv(argc, argv);
			return 0;
		}
		argv[argc] = malloc(strlen(str)+1);

		if(!argv[argc]) {
			free_argv(argc, argv);
			return 0;
		}

		strcpy(argv[argc], str);
		if (++argc >= max_args) {
			break;
		}
		child = child->next_sibling;
	}
	argv[argc] = NULL;

	int child_pid = 0;
	if ((child_pid = fork()) == 0) {
		do_exec_cmd(argc, argv);
		fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
		if(errno == ENOEXEC) {
			exit(126);
		}
		else if(errno == ENOENT) {
			exit(127);
		} else {
			exit(EXIT_FAILURE);
		}
	} else if (child_pid < 0) {
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		return 0;
	}

	int status = 0;
	waitpid(child_pid, &status, 0);
	free_argv(argc, argv);

	return 1;
}
