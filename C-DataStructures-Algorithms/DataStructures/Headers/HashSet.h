/**
 * @file HashSet.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 10/06/2018
 *
 * @brief Header file for @c HashSet implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Core.h"

	typedef struct HashSetEntry {
		char *value;
		size_t hash;
	} HashSetEntry;

	typedef struct HashSet {
		struct HashSetEntry **buckets;
		size_t size;
		size_t max_size;
		Status(*hash_function) (char *, size_t *);
		Status(*rehash_function) (size_t *);
	} HashSet;

	Status set_init_table(HashSet **set, size_t max_size,
		Status(*hash_function) (char *, size_t *),
		Status(*rehash_function) (size_t *));

	Status set_init_entry(HashSetEntry **entry, char *value);

	Status set_make_entry(HashSetEntry **entry, char *key, size_t hash);

	Status set_insert(HashSet *set, char *value);

	//Status set_remove(HashSet *set, char *value);

	Status set_display_entry(HashSetEntry *entry);
	Status set_display_entry_raw(HashSetEntry *entry);
	Status set_display_table(HashSet *set);
	Status set_display_table_raw(HashSet *set);

	Status set_delete_table(HashSet **set);
	Status set_erase_table(HashSet **set);

	bool set_is_full(HashSet *set);

	Status set_contains(HashSet *set, char *value, bool *result);
	bool set_exists(HashSet *set, char *value);

	Status set_count_elements(HashSet *set, size_t *result);
	Status set_count_empty(HashSet *set, size_t *result);

	//Status set_union(HashSet *set1, HashSet *set2, HashSet **result);
	//Status set_intersection(HashSet *set1, HashSet *set2, HashSet **result);
	//Status set_difference(HashSet *set1, HashSet *set2, HashSet **result);
	//Status set_complement(HashSet *set1, HashSet *set2, HashSet **result);
	//Status set_sym_diff(HashSet *set1, HashSet *set2, HashSet **result);

	Status set_hash_string_djb2(char *key, size_t *hash);
	Status set_hash_string_sdbm(char *key, size_t *hash);
	Status set_hash_string_fnv(char *key, size_t *hash);

	Status set_rehash_rj(size_t *hash);
	Status set_rehash_prime(size_t *hash);
	
#ifdef __cplusplus
}
#endif