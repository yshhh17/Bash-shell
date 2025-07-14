#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "node.h"

int do_exec_cmd(int argc, char **argv);
int do_simple_command(struct node_s *node);

#endif
