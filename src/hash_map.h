#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct HashMap HashMap;

HashMap *hash_map_new();
void hash_map_set(HashMap *h, const char *key, void *value);
void *hash_map_get(HashMap *h, const char *key);
void hash_map_free(HashMap **h);

#endif /* !HASH_MAP_H */
