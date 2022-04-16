#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef ARITH_DLL
#define ARITH_DLL

#define MODE1_SIZE 100
#define MODE2_SIZE 100

/*** Global variables to hole mode 1 and mode 2
front and rear indices ***/
int mode1_front_index = 0;
int mode1_rear_index = -1;
int mode2_front =0 , mode2_rear = -1 , dummy =-1;

/*** Linked list queue node element defined ***/
class QueueNode {
	public:
		QueueNode() {
			next = 0;
		}
		QueueNode(int nodevalue) {
			value = nodevalue;
		}
		int value;
		QueueNode *next;
};

/*** Linked list queue containing a list of QueueNode elements ***/

class CircularList {
	public:
		CircularList() {
			front = rear = 0;
		}
		void Enqueue(int);
		void Dequeue();
		void printQList();
	protected:
		QueueNode *front, *rear;
};

#endif
