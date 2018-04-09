/**
 * @file C-Data-Structures.c
 *
 * @author Leonardo Vencovsky
 * @date 04/04/2018
 *
 * @brief Entry point for project. In this file all tests are called.
 *
 * What is C-Data-Structures ?
 *
 * C-Data-Structures is a project for implementing data structures purely in C.
 *
 */

#include "Core\Tests.h"

int main()
{

	srand();

	ArrayTests();
	DynamicArrayTests();
	DoublyLinkedListTests();
	SinglyLinkedListTests();
	CircularLinkedListTests();
	StackTests();
	ConversionTests();
	VectorTests();

	printf("\n");
    return 0;
}
