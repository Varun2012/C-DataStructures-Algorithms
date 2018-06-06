/**
 * @file HashTable.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 05/06/2018
 *
 * @brief Header file for @c HashTable implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Core.h"

	typedef struct HashTableEntry {
		int data;
		size_t hash;
		struct HashTableEntry *next;
	} HashTableEntry;

	typedef struct HashTable {
		struct HashTableEntry **buckets;
		size_t size;
		Status(*hash_function) (char *, size_t *);
	} HashTable;

	Status hst_init_table(HashTable **hst, size_t size, Status(*function) (char *, size_t *));
	Status hst_init_entry(HashTableEntry **entry, int value);

	Status hst_insert(HashTable *hst, char * key, int value);

	Status hst_display_entry(HashTableEntry *entry);
	Status hst_display_table(HashTable *hst);
	Status hst_display_table_raw(HashTable *hst);

	Status hst_delete_table(HashTable **hst);
	Status hst_erase_table(HashTable **hst);

	Status hst_search(HashTable *hst, char *key, int *value);

	Status hash_string_java(char * key, size_t *hash);
	Status hash_string_djb2(char * key, size_t *hash);
	Status hash_string_sdbm(char * key, size_t *hash);
	
	
#ifdef __cplusplus
}
#endif