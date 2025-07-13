#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
#include "source.h"

void unget_char(struct source_s *src) {  //will be used in further files
	if (src->curpos < 0) {
		return;
	}

	src->curpos--;
}

char next_char(struct source_s *src) { // returns the next character of the token
	if (!src || !src->buffer) {
		errno = ENODATA;
		return ERRCHAR;
	}

	char c1 = 0;
	if(src->curpos == INIT_SRC_POS) {
		src->curpos = -1;
	} else {
		c1 = src->buffer[src->curpos];
	}
	if(++src->curpos >= src->buffsize) {
		src->curpos = src->buffsize;
		return EOF;
	} 
	return src->buffer[src->curpos];
}

char peek_char(struct source_s *src) { // typical use is to detect whitespaces for removal
	if(!src || !src->buffer) {
		errno = ENODATA;
		return ERRCHAR;
	}
	long pos = src->curpos;

	if (pos == INIT_SRC_POS) {
		pos++
	}
	pos++;

	if(pos >= src->bufsize) {
		return EOF;
	}
	return src->buffer[pos];
}

void skip_white_spaces(struct source_s *src) { // removes the white spaces from the string we recieved
	char c;
	if (!src || !src->buffer) {
		return;
	}

	while((c = peek_char(src) !=EOF) && (c == ' ' || c == '\t')) {
		next_char(src);
	}
}
