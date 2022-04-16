#include <iostream>
#include <string>
#include "queue_implementations.h"

using namespace std;

/*** A regular array based queue ***/
int mode1_queue[MODE1_SIZE];

/*** A circular array with dummy element queue ***/
int circular_array[MODE2_SIZE];

/*** A Linked List Queue ***/
CircularList MyQueue;

/*********
Enqueue API for linked list queue implementation
*********/
void CircularList::Enqueue(int nvalue) {
	QueueNode* newnode = (struct QueueNode*)malloc(sizeof(struct QueueNode)); 
	newnode->value = nvalue;
	if (rear != 0 && front != 0)
	{
		rear->next = newnode;
		newnode->next = front;
		rear = newnode;
	}
	if (front == 0)
		front = rear = newnode;
}

/*********
Dequeue API for linked list queue implementation
*********/
void CircularList::Dequeue() {
	if ((front == 0) && (rear == 0))
		cout << "Empty List\n" <<endl;
	if (front == rear)
	{	
		front = 0; 
		rear = 0;
	}	
	if ((front != 0) && (front != rear))
	{
		front = front->next;
		rear->next = front;
	}
}

/*********
Print API for linked list queue implementation
to print all current array elements
*********/
void CircularList::printQList() {
	if ((front == 0) && (rear == 0))
	{
		cout << "Empty List\n" <<endl;
		return;
	}
	cout << "Printing Queue Items\n" <<endl;
	QueueNode* tmp;
	tmp = front;
	while(tmp != 0 && tmp != rear)
	{
		cout<<tmp->value<<endl;
		tmp = tmp->next;
	}
	if(rear != 0)
		cout<<rear->value<<endl;
}

/* Initializing the array
------------------------------------------------------------------------------
Note :  All elements are initialized as -1.
        So -1 is considered the default element and a node value cannot be -1

------------------------------------------------------------------------------*/
void InitializeArray(int arr [] )
{
     for (int i =0 ; i < MODE2_SIZE ; i++)
     {
         arr[i]= -1;
     }
}

/* Checking if the array is empty
------------------------------------------------------------------------------
Note :  if front and rear !=0 and they are equal , the array is empty.
------------------------------------------------------------------------------*/
int IsArrayEmpty()
{
    if ((mode2_front-1) == mode2_rear)
    return 1;
    else
    return 0;
}

/* Checking if the array is full
------------------------------------------------------------------------------
Note :  The array is full if it has ARRAY_SIZE number of elements
------------------------------------------------------------------------------*/
int IsArrayFull()
{
    if ( ( dummy ==-1) && (mode2_rear == (MODE2_SIZE - 2)))
    return 1;
    else if( mode2_rear == (mode2_front - 2))
    return 1;
    else
    return 0;
}

/*********
Print all queue elements in current queue based on mode.
*********/
int PrintQueue(int mode, int *queue)
{
	int i = 0;
	switch(mode)
	{
	case 1:
		queue = (int *)queue;
		cout << "Listing queue elements" <<endl;
		for (i = mode1_front_index; i< mode1_rear_index+1; i++)
			cout <<queue[i]<<" "<<endl;
		break;
	case 2:
		if(!IsArrayEmpty())
		{
			cout << "Listing queue elements" <<endl;
			if(mode2_front <= mode2_rear)
			{
				for(  int i = mode2_front; i <= mode2_rear ; i++)
					cout<< circular_array[i] <<endl;
			}
			else
			{
				for(int i = mode2_front; i < MODE2_SIZE ; i++)
					cout<< circular_array[i] <<endl;

				for (int i = 0; i <= mode2_rear; i++)
					cout<< circular_array[i] <<endl;
			}
		}
		else
		{
			cout << " The array is empty " << endl;
		}
		break;
	case 3:
		MyQueue.printQList();
		break;
	default:
		break;
	}
	return 0;
}

/******
Dequeue operation on the queue.
Element is removed from front of queue if queue is not empty
based on mode of operation.
******/
int Dequeue(int mode, int *queue)
{
	switch(mode)
	/*** Mode 1 : regular array dequeue ***/
	{
	case 1:
		if((mode1_front_index <= mode1_rear_index) &&
			(mode1_front_index <= MODE1_SIZE - 1))
			mode1_front_index = mode1_front_index + 1;
		else
			cout << "array indexes exhausted, array empty\n" <<endl;
		break;
	/*** Mode 2 : circular array with dummy index dequeue ***/
	case 2:
		if(!IsArrayEmpty())
		{

			 dummy=(dummy+1) % MODE2_SIZE;
			 mode2_front = (mode2_front+1) % MODE2_SIZE;
		}
		else
			cout << "array empty\n" <<endl;
		break;
	/*** Mode 3 : linked list dequeue implementation of queue ***/
	case 3:
		MyQueue.Dequeue();
		break;
	default:
		break;
	}
	return 0;
}

/******
Enqueue operation on the queue.
Element is added to rear of queue if array size permits
based on mode of operation.
******/
int Enqueue(int mode, int *queue, int elem)
{
	switch(mode)
	{
	/*** Mode 1 : regular array enqueue ***/
	case 1:
		if(mode1_rear_index < MODE1_SIZE - 1) {
			mode1_rear_index = mode1_rear_index + 1;
			queue[mode1_rear_index] = elem;
		} else {
			cout << "array indexes exhausted\n" <<endl;
		}
		break;
	/*** Mode 2 : circular array with dummy index enqueue ***/
	case 2:
		if(!IsArrayFull())
		{
			mode2_rear=(mode2_rear+1) % MODE2_SIZE;
			circular_array[mode2_rear] = elem;
		}
		else
			cout<<" The array is full " << endl;
		break;
	/*** Mode 3 : linked list enqueue implementation of queue ***/
	case 3:
		MyQueue.Enqueue(elem);
		break;
	default:
		break;
	}
	return 0;
}

/******
Survivor value and index for mode 1 current queue is returned.
******/
int Josephus(int size_arr)
{
	if (size_arr == 1) 
    		return 1; 
	else
	    	return ((Josephus(size_arr - 1)+1) % size_arr) + 1; 
}

static void usage() {
	cout << "This executable implements Queues as a Data Structure in 333ifferent modes:" <<endl;
	cout << "mode1: regular array" <<endl;
	cout << "mode2: circular array index counted circularly with empty cell" <<endl;
	cout << "mode3: circular list \n" <<endl;
}

int main()
{
	int mode;
	int operation;
	int enQelem;
	int* Queue;
	int size_arr;
	int survivor_idx;
	InitializeArray(circular_array);

	usage();
	/*** mode and operation is taken as input for every operation to be performed***/
	/*** Thus, three different queues can be maintained and operated on simultaneously ***/
	while (1) {
		cout << "\n\nEnter queue mode number" <<endl;
		cin >> mode;
		if (mode == 1)
			Queue = mode1_queue;
		else if (mode == 4)
			Queue = NULL;
		cout << "Enter operation number to execute" <<endl;
		cout << "1: Enqueue" <<endl;
		cout << "2: Dequeue" <<endl;
		cout << "3: PrintQueue "<<endl;
		cout << "4: Joesephus survivor" <<endl;
		cin >> operation;
		if (operation == 1)
		{
			cout << "Enter element to enqueue" <<endl;
			cin >> enQelem;
		}
		switch (operation)
		{
		case 1:
			Enqueue(mode, Queue, enQelem);
			break;
		case 2:
			Dequeue(mode, Queue);
			break;
		case 3:
			PrintQueue(mode, Queue);
			break;
		case 4:
			if (mode != 1)
			{
				cout << "Josephus Problem is implemented in mode1, exiting" <<endl;
				break;
			}
			size_arr = mode1_rear_index - mode1_front_index + 1;
			PrintQueue(mode, Queue);
			survivor_idx = mode1_front_index - 1 + Josephus(size_arr);
			cout << "Josephus survivor for above list is: " << mode1_queue[survivor_idx]<< "at idx: "<< survivor_idx <<endl;
			break;
		default:
			break;
		}
	}
	return 0;
}
