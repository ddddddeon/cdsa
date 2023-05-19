#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "queue.h"

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    const char *word;
};

typedef struct Trie Trie;

Trie *trie_new() {
    Trie *p = malloc(sizeof(Trie));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        p->children[i] = NULL;
    }
    p->word = NULL;
    return p;
}

int word_len(const char *word) {
    int len = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        len++;
    }

    return len;
}

void trie_print(Trie *t) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (t->children[i] != NULL) {
            trie_print(t->children[i]);

            if (t->word != NULL) {
                printf("%s\n", t->word);
            }
        }
    }
}

void trie_insert(Trie *t, const char *word) {
    ABORT_IF_NULL(t);

    Trie *curr = t;
    Trie *prev = NULL;
    int len = word_len(word);

    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';

        if (curr->children[idx] == NULL) {
            Trie *new = trie_new();
            *(curr->children + idx) = new;
        }
        prev = curr;
        curr = curr->children[idx];
    }

    prev->word = word;
}

void trie_delete(Trie *t, const char *word) {
    ABORT_IF_NULL(t);

    Trie *curr = t;
    Trie *prev = NULL;
    int len = word_len(word);

    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';

        if (curr->children[idx] == NULL) {
            return;
        }

        prev = curr;
        curr = curr->children[idx];
    }

    prev->word = NULL;
}

bool trie_search(Trie *t, const char *word) {
    ABORT_IF_NULL(t);
    Trie *curr = t;
    int len = word_len(word);

    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';
        if (curr->children[idx] == NULL) {
            return false;
        }

        if (i == len - 1 && curr->word == NULL) {
            return false;
        }

        curr = curr->children[idx];
    }
    return true;
}

Trie *seek(Trie *t, const char *word) {
    ABORT_IF_NULL(t);
    Trie *curr = t;
    int len = word_len(word);

    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';
        if (curr->children[idx] == NULL) {
            return curr;
        }
        curr = curr->children[idx];
    }
    return curr;
}

void autocomplete(Trie *t, Queue *q) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (t->children[i] != NULL) {
            autocomplete(t->children[i], q);

            if (t->word != NULL) {
                queue_enqueue(q, (void *)t->word);
            }
        }
    }
}

Queue *trie_autocomplete(Trie *t, const char *word) {
    Queue *q = queue_new();
    Trie *curr = seek(t, word);
    autocomplete(curr, q);
    return q;
}

void trie_free(Trie **t) {
    ABORT_IF_NULL(*t);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((*t)->children[i] != NULL) {
            trie_free(&(*t)->children[i]);
        }
    }
    free(*t);
    *t = NULL;
}
