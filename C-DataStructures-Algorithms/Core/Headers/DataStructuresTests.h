/**
 * @file DataStructuresTests.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 18/03/2018
 *
 * @brief Header to Include Structure Test Functions in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int SinglyLinkedListTests(void);
	int DoublyLinkedListTests(void);
	int CircularLinkedListTests(void);
	int SparseMatrixTests(void);

	int StackTests(void);
	int StackArrayTests(void);

	int QueueTests(void);
	int QueueArrayTests(void);
	int DequeTests(void);
	int DequeArrayTests(void);
	int PriorityQueueTests(void);
	int CircularBufferTests(void);

	int BinaryTreeTests(void);
	int BinarySearchTreeTests(void);
	int AVLTreeTests(void);
	int TrieTests(void);

	int ArrayTests(void);
	int DynamicArrayTests(void);

	int VectorTests(void);

	int StructureConversionsTests(void);

	int SStringTests(void);

	int SortingTests(void);

	int HashMapTests(void);
	int HashSetTests(void);

	int ClockTests(void);

#ifdef __cplusplus
}
#endif