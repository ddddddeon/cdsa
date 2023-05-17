#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    bool is_end;
};

typedef struct Trie Trie;

Trie *trie_new() {
    Trie *p = malloc(sizeof(Trie));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        p->children[i] = NULL;
    }
    p->is_end = false;
    return p;
}

int word_len(const char *word) {
    int len = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        len++;
    }

    return len;
}

void left_pad(int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("└");
        } else {
            printf(" ");
        }
    }
}

void trie_print(Trie *t) {
    int pad = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        left_pad(pad);
        pad = 0;
        if (t->children[i] != NULL) {
            printf("%c", i + 'a');
            trie_print(t->children[i]);

            if (t->is_end) {
                printf("\n");
                pad++;
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

    prev->is_end = true;
}

bool trie_search(Trie *t, const char *word) {
    Trie *curr = t;
    int len = word_len(word);

    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';
        if (curr->children[idx] == NULL) {
            return false;
        }

        if (i == len - 1 && !curr->is_end) {
            return false;
        }

        curr = curr->children[idx];
    }
    return true;
}
