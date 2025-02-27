#include "queue.h"

struct Queue
{
	size_t head;
	size_t tail;
	Vector* vector;
};

Queue* queue_create()
{
	Queue* queue = new Queue;
	queue->head = queue->tail = 0;
	queue->vector = vector_create();
	vector_resize(queue->vector, start_size);
	return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	if ((queue->tail >= vector_size(queue->vector)) && (queue->head != 0))
		queue->tail = 1;
	else if (queue->tail + 1 == queue->head) //ring buffer reload
	{
		Vector* temp = vector_create();
		vector_resize(temp, start_size);
		size_t index = 0;
		for (size_t i = queue->head; i < vector_size(queue->vector); i++)
		{
			vector_set(temp, index, vector_get(queue->vector, i));
			index++;
		}
		for (size_t i = 0; i < queue->tail; i++)
		{
			vector_set(temp, index, vector_get(queue->vector, i));
			index++;
		}
		queue->head = 0;
		queue->tail = vector_size(queue->vector) + 1;
		vector_delete(queue->vector);
		queue->vector = temp;
	}
	else queue->tail++;
	vector_set(queue->vector, queue->tail - 1, data);
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
	if (queue->head + 1 == vector_size(queue->vector))
		queue->head = 0;
	else queue->head++;
}

bool queue_empty(const Queue* queue)
{
	if (queue->tail == queue->head)
		return true;
	else return false;
}