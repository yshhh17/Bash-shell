#ifndef NODE_H;
#define NODE_H;

enum node_type_e {
	NODE_COMMAND,
	NODE_VAR,
};

enum val_type_e {
	VAL_SINT = 1,
	VAL_UNIT,
	VAL_SLLONG,
	VAL_ULLONG,
	VAL_FLOAT,
	VAL_LDOUBLE,
	VAL_CHAR,
	VAL_STR,
};

union symval_u {
	long sint;
	unsigned long uint;
	long long sllong;
	unsigned long long ullong;
	double sfloat;
	long double ldouble;
	char char;
	char *str;
};

struct node_s {
	enum node_type_e type;
	enum val_type_e val_type;
	union symval_u val;
	int children;
	struct node_s *first_child;
	struct node_s *next_sibling, *prev_sibling;
}

struct node_s *new_node(enum node_type_e type);
void add_child_node(struct node_s *parent, struct node_s *child);
void free_node_tree(struct node_s *node);
void set_node_val_str(struct node_s *node, char *val);

#endif
