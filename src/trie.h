#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct Trie Trie;

Trie *trie_new();
void trie_print(Trie *t);
void trie_insert(Trie *t, const char *word);
bool trie_search(Trie *t, const char *word);

#endif /* !TRIE_H */
