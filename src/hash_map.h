#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct HashMap HashMap;

HashMap *hash_map_new();
int hash_map_size(HashMap *h);
int hash_map_cap(HashMap *h);
void hash_map_set(HashMap *h, const char *key, void *value);
void *hash_map_get(HashMap *h, const char *key);
void hash_map_free(HashMap **h);

#endif /* !HASH_MAP_H */
