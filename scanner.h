#ifndef SCANNER_H
#define SCANNER_H

struct token_s {  // structure of a single token
	struct source_s *src;  // the string returned by scanner and it's details
	int text_len; // length of the token
	char *text // the token(string)
};

extern struct token_s eof_token; // token returned when error encountered reading token


struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);

#endif
