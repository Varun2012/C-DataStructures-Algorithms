/**
 * @file HashTable.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 05/06/2018
 *
 * @brief Source file for @c HashTable implementations in C
 *
 */

#include "HashTable.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status hst_init_table(HashTable **hst, size_t size, Status(*function) (char *, size_t *))
{
	if (size == 0)
		return DS_ERR_INVALID_SIZE;

	*hst = malloc(sizeof(HashTable));

	if (!(*hst))
		return DS_ERR_ALLOC;

	(*hst)->buckets = malloc(sizeof(HashTableEntry *) * size);

	if (!((*hst)->buckets))
		return DS_ERR_ALLOC;

	size_t i;
	for (i = 0; i < size; i++) {

		((*hst)->buckets)[i] = malloc(sizeof(HashTableEntry));

		if (!(((*hst)->buckets)[i]))
			return DS_ERR_ALLOC;

		((*hst)->buckets)[i] = NULL;
	}

	(*hst)->size = size;

	(*hst)->hash_function = function;

	return DS_OK;
}

Status hst_init_entry(HashTableEntry **entry, int value)
{
	*entry = malloc(sizeof(HashTableEntry));

	(*entry)->data = value;
	(*entry)->hash = 0;

	(*entry)->next = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Getters                                              |
// +-------------------------------------------------------------------------------------------------+

Status hst_make_entry(HashTableEntry **entry, int value, size_t hash)
{
	*entry = malloc(sizeof(HashTableEntry));

	(*entry)->data = value;
	(*entry)->hash = hash;

	(*entry)->next = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status hst_insert(HashTable *hst, char * key, int value)
{
	if (hst == NULL)
		return DS_ERR_NULL_POINTER;

	size_t hash;

	Status st = hst->hash_function(key, &hash);

	if (st != DS_OK)
		return st;

	size_t pos = hash % hst->size;

	if ((hst->buckets)[pos] == NULL) {

		st = hst_make_entry(&((hst->buckets)[pos]), value, hash);

		if (st != DS_OK)
			return st;
	}
	else if (((hst->buckets)[pos])->hash == hash) {

		return DS_OK;
	}
	else {

		HashTableEntry *scan = (hst->buckets)[pos];

		while (scan->next != NULL)
		{
			if (scan->hash == hash)
				return DS_OK;

			scan = scan->next;
		}

		if (scan->hash == hash)
			return DS_OK;

		HashTableEntry *entry;

		st = hst_make_entry(&entry, value, hash);

		if (st != DS_OK)
			return st;

		scan->next = entry;

	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status hst_display_entry(HashTableEntry *entry)
{
	if (entry == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n|%21zu|\t|%10d|", entry->hash, entry->data);

	return DS_OK;
}

Status hst_display_entry_raw(HashTableEntry *entry)
{
	if (entry == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n%21zu\t%d", entry->hash, entry->data);

	return DS_OK;
}

Status hst_display_table(HashTable *hst)
{
	if (hst == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n+---------------------+\t+----------+");
	printf("\n|    Hash Table       |\t|          |");

	Status st;

	size_t i;
	for (i = 0; i < hst->size; i++) {

		printf("\n+---------------------+\t+----------+");

		if ((hst->buckets)[i] == NULL)
			printf("\n|        NULL         |\t|   NULL   |");
		else {

			if ((hst->buckets)[i]->next != NULL) {

				HashTableEntry *scan = (hst->buckets)[i];

				while (scan != NULL)
				{
					st = hst_display_entry(scan);

					if (st != DS_OK)
						return st;

					scan = scan->next;
				}

			}
			else {

				st = hst_display_entry((hst->buckets)[i]);

				if (st != DS_OK)
					return st;
			}
		}
	}

	printf("\n+---------------------+\t+----------+");

	printf("\n");

	return DS_OK;
}


Status hst_display_table_raw(HashTable *hst)
{
	if (hst == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	size_t i;
	for (i = 0; i < hst->size; i++) {

		if ((hst->buckets)[i] == NULL)
			printf("\n");
		else {

			if ((hst->buckets)[i]->next != NULL) {

				HashTableEntry *scan = (hst->buckets)[i];

				while (scan != NULL)
				{
					st = hst_display_entry_raw(scan);

					if (st != DS_OK)
						return st;

					scan = scan->next;
				}

			}
			else {

				st = hst_display_entry_raw((hst->buckets)[i]);

				if (st != DS_OK)
					return st;
			}
		}
	}

	printf("\n");

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status hst_delete_table(HashTable **hst)
{
	if ((*hst) == NULL)
		return DS_ERR_NULL_POINTER;

	size_t i;
	for (i = 0; i < (*hst)->size; i++)
		free(((*hst)->buckets)[i]);

	free((*hst)->buckets);
	free(*hst);

	*hst = NULL;

	return DS_OK;
}

Status hst_erase_table(HashTable **hst)
{
	if ((*hst) == NULL)
		return DS_ERR_NULL_POINTER;

	size_t size = (*hst)->size;
	Status(*function) (char *, size_t *) = (*hst)->hash_function;

	Status st = hst_delete_table(hst);

	if (st != DS_OK)
		return st;

	st = hst_init_table(hst, size, function);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status hst_search(HashTable *hst, char *key, int *value)
{
	*value = 0;

	if (hst == NULL)
		return DS_ERR_NULL_POINTER;

	size_t hash;

	hst->hash_function(key, &hash);

	size_t pos = hash % hst->size;

	if ((hst->buckets)[pos] == NULL)
		return DS_ERR_NOT_FOUND;

	if (((hst->buckets)[pos])->next == NULL && ((hst->buckets)[pos])->hash == hash)
		*value = ((hst->buckets)[pos])->data;
	else {

		HashTableEntry *scan = (hst->buckets)[pos];

		bool found = false;

		while (scan != NULL)
		{
			if (scan->hash == hash) {

				*value = scan->data;

				found = true;

				break;
			}

			scan = scan->next;
		}

		if (!found)
			return DS_ERR_NOT_FOUND;

	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Hash                                                |
// +-------------------------------------------------------------------------------------------------+

Status hash_string_java(char * key, size_t *hash)
{
	size_t len = strlen(key);

	*hash = 0;

	if (len == 0)
		return DS_OK;

	size_t i;
	for (i = 0; i < len; i++)
		(*hash) += (size_t)pow((key[i] * 31), len - i);

	return DS_OK;
}

Status hash_string_djb2(char * key, size_t *hash)
{
	*hash = 5381;

	int c;

	while (c = *key++)
		(*hash) = (((*hash) << 5) + (*hash)) + c;

	return DS_OK;
}

Status hash_string_sdbm(char * key, size_t *hash)
{
	*hash = 0;

	int c;

	while (c = *key++)
		(*hash) = c + (((*hash) << 6) + ((*hash) << 16)) - (*hash);

	return DS_OK;
}