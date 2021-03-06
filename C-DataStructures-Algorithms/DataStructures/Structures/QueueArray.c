/**
* @file QueueArray.c
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @date 04/08/2018
*
* @brief Source file for @c QueueArrary implementations in C
*
*/

#include "QueueArray.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status qua_init(QueueArray **qua)
{
	(*qua) = malloc(sizeof(QueueArray));

	if (!(*qua))
		return DS_ERR_ALLOC;

	(*qua)->buffer = malloc(sizeof(int) * QUEUE_ARRAY_INIT_SIZE);

	if (!((*qua)->buffer))
		return DS_ERR_ALLOC;

	(*qua)->capacity = QUEUE_ARRAY_INIT_SIZE;
	(*qua)->growth_rate = QUEUE_ARRAY_GROW_RATE;

	(*qua)->length = 0;

	(*qua)->front = 0;
	(*qua)->rear = 0;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Getters                                              |
// +-------------------------------------------------------------------------------------------------+

Status qua_get_length(QueueArray *qua, size_t *result)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	*result = qua->length;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status qua_enqueue(QueueArray *qua, int value)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_full(qua))
	{
		Status st = qua_realloc(qua);

		if (st != DS_OK)
			return st;
	}
	else if (qua->rear == qua->capacity)
	{
		// Shift
		size_t i, j;
		for (i = 0, j = qua->front; j < qua->rear; i++, j++)
		{
			qua->buffer[i] = qua->buffer[j];
		}

		qua->front = 0;
		qua->rear = qua->length;
	}

	qua->buffer[qua->rear] = value;

	(qua->rear)++;

	(qua->length)++;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status qua_dequeue(QueueArray *qua, int *value)
{
	*value = 0;

	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
		return DS_ERR_INVALID_OPERATION;

	*value = qua->buffer[qua->front];

	(qua->front)++;

	(qua->length)--;

	if (qua_is_empty(qua))
	{
		qua->front = 0;

		qua->rear = 0;
	}

	return DS_OK;
}

Status qua_pop(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
		return DS_ERR_INVALID_OPERATION;

	(qua->front)++;

	(qua->length)--;

	if (qua_is_empty(qua))
	{
		qua->front = 0;

		qua->rear = 0;
	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status qua_display(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
	{

		printf("\nQueueArray\n[ empty ]\n");

		return DS_OK;
	}

	printf("\nQueueArray\nfront <-");

	size_t i;
	for (i = qua->front; i < qua->rear; i++)
		printf(" %d <-", qua->buffer[i]);

	printf(" rear\n");

	return DS_OK;
}

Status qua_display_raw(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (qua_is_empty(qua))
		return DS_OK;

	int i;
	for (i = qua->front; i < qua->rear; i++)
		printf("%d ", qua->buffer[i]);

	printf("\n");

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status qua_delete(QueueArray **qua)
{
	if ((*qua) == NULL)
		return DS_ERR_NULL_POINTER;

	free((*qua)->buffer);

	free(*qua);

	*qua = NULL;

	return DS_OK;
}

Status qua_erase(QueueArray **qua)
{
	if ((*qua) == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = qua_delete(qua);

	if (st != DS_OK)
		return st;

	st = qua_init(qua);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status qua_peek_front(QueueArray *qua, int *result)
{
	*result = 0;

	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
		return DS_ERR_INVALID_OPERATION;

	*result = qua->buffer[qua->front];

	return DS_OK;
}

Status qua_peek_rear(QueueArray *qua, int *result)
{
	*result = 0;

	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
		return DS_ERR_INVALID_OPERATION;

	*result = qua->buffer[qua->rear - 1];

	return DS_OK;
}

size_t qua_length(QueueArray *qua)
{
	if (qua == NULL)
		return 0;

	return qua->length;
}

size_t qua_capacity(QueueArray *qua)
{
	if (qua == NULL)
		return 0;

	return qua->capacity;
}

bool qua_is_empty(QueueArray *qua)
{
	return qua->length == 0;
}

bool qua_is_full(QueueArray *qua)
{
	return qua->length == qua->capacity;
}

bool qua_fits(QueueArray *qua, size_t size)
{
	return (qua->length + size) <= qua->capacity;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Copy                                                |
// +-------------------------------------------------------------------------------------------------+

Status qua_copy(QueueArray *qua, QueueArray **result)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = qua_init(result);

	if (st != DS_OK)
		return st;

	if (qua_is_empty(qua))
		return DS_OK;

	while (!qua_fits(*result, qua->length))
	{
		st = qua_realloc(*result);

		if (st != DS_OK)
			return st;
	}

	size_t i, j;
	for (i = 0, j = qua->front; j < qua->rear; i++, j++)
	{
		(*result)->buffer[i] = qua->buffer[j];
	}

	(*result)->rear = qua->length;

	(*result)->length = qua->length;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Buffer                                               |
// +-------------------------------------------------------------------------------------------------+

Status qua_realloc(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	qua->capacity *= qua->growth_rate;

	int *new_buffer = realloc(qua->buffer, sizeof(int) * qua->capacity);

	if (!new_buffer)
	{
		qua->capacity /= qua->growth_rate;

		return DS_ERR_ALLOC;
	}

	qua->buffer = new_buffer;

	return DS_OK;
}