/**
 * @file CircularLinkedList.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 05/04/2018
 *
 * @brief Header file for @c CircularLinkedList implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"

	/**
	 * A @c CircularLinkedNode is what a @c CircularLinkedList is composed of.
	 * They are exactly the same as @c DoublyLinkedNode. The differentiation of
	 * both was made so that no structure depends on another.
	 */
	typedef struct CircularLinkedNode
	{
		int data;						 /*!< Pointer to node's content */
		struct CircularLinkedNode *next; /*!< Pointer to the next node on the list */
		struct CircularLinkedNode *prev; /*!< Pointer to the previous node on the list */
	} CircularLinkedNode;

	/**
	 * A @c CircularLinkedList is a structure much like a @c DoublyLinkedList
	 * except that the nodes wrap around making it a circular structure. This
	 * way only one pointer is necessarry as you won't have any problems like
	 * pointing the @c *head pointer to the next node making the node before it
	 * inaccessible. But in a circular list you must be careful to not fall
	 * into an infinite loop as the list won't have a node pointing to @c NULL
	 * as if it was the end of it.
	 *
	 * @b Advantages over @c DoublyLinkedList
	 * - Can be used to many problems where a circular structure is needed
	 * - No need for a tail pointer as the list wraps around itself
	 *
	 * @b Drawbacks
	 * - The end of the list is relative and may change
	 *
	 * @b Functions
	 *
	 * @c CircularLinkedList.c
	 *
	 */
	typedef struct CircularLinkedList
	{
		size_t length;                   /*!< List length */
		struct CircularLinkedNode *curr; /*!< Pointer to current node. Functions operate relative to this node */
	} CircularLinkedList;

	Status cll_init_list(CircularLinkedList **cli);
	Status cll_init_node(CircularLinkedNode **cln);

	Status cll_make_node(CircularLinkedNode **cln, int value);

	Status cll_insert_after(CircularLinkedList *cll, int value);
	Status cll_insert_before(CircularLinkedList *cll, int value);

	//Status cll_push_after(CircularLinkedList *cll, CircularLinkedNode *node);
	//Status cll_push_before(CircularLinkedList *cll, CircularLinkedNode *node);

	Status cll_remove_after(CircularLinkedList *cll, int *result);
	Status cll_remove_current(CircularLinkedList *cll, int *result);
	Status cll_remove_before(CircularLinkedList *cll, int *result);

	//Status cll_pop_after(CircularLinkedList *cll, CircularLinkedNode **result);
	//Status cll_pop_current(CircularLinkedList *cll, CircularLinkedNode **result);
	//Status cll_pop_before(CircularLinkedList *cll, CircularLinkedNode **result);

	Status cll_iter_next(CircularLinkedList *cll, size_t positions);
	Status cll_iter_prev(CircularLinkedList *cll, size_t positions);

	Status cll_display(CircularLinkedList *cll);
	Status cll_display_raw(CircularLinkedList *cll);

	Status cll_delete_node(CircularLinkedNode **cln);
	Status cll_delete_list(CircularLinkedList **cll);
	Status cll_erase(CircularLinkedList **cll);

	size_t cll_length(CircularLinkedList *cll);

	//Status cll_frequency(CircularLinkedList *cll, int key, size_t *frequency);

	//Status cll_contains(CircularLinkedList *cll, int key, bool *result);
	//bool cll_exists(CircularLinkedList *cll, int key);

	bool cll_is_empty(CircularLinkedList *cll);

	Status cll_find_max(CircularLinkedList *cll, int *result);
	Status cll_find_min(CircularLinkedList *cll, int *result);

	Status cll_josephus(size_t n, size_t k, size_t *result);

#ifdef __cplusplus
}
#endif