#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#include "../src/queue.h"

typedef struct Trie Trie;

Trie *trie_new();
void trie_print(Trie *t);
void trie_insert(Trie *t, const char *word);
void trie_delete(Trie *t, const char *word);
bool trie_search(Trie *t, const char *word);
Queue *trie_autocomplete(Trie *t, const char *word);
void trie_free(Trie **t);

#endif /* !TRIE_H */
