#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define DIGITS_SIZE 4
#define MAX_VALUE 10000

struct Node
{
	int value;
	struct Node* prev;
	struct Node* next;
};

/*------------------------------------------------
Each number is considered as a Doubly linked list
-------------------------------------------------- */

struct DLL
{
	void* head;
	void* tail;
	int length;
	int negative;
};

/*------------------------------------------------
Custom Functions Used
-------------------------------------------------- */
int Addition(  DLL* ,  DLL * ,  DLL *);
int Comparison ( DLL* ,  DLL * );
int Subtraction (  DLL* ,  DLL * ,  DLL *);
int Multiplication (  DLL* ,  DLL * ,  DLL *);
int Division(  DLL* ,  DLL * ,  DLL *);
int insert( DLL* , int );
int insertFront(DLL* , int );
int removeFront(DLL*);
int remove(DLL*, int );
int string_to_list(DLL*, char*);
int deletelist( DLL*);
int copylist(DLL* , DLL*  );
void print(DLL* );
void* position( DLL* , int );
char* readline(char* , char* );
char* readCharacters(char* , char* , int );


/*------------------------------------------------
Function Definitions
-------------------------------------------------- */


/*-----------------------------------------------------------
Purpose : to insert nodes at the end of a doubly linked list
------------------------------------------------------------- */


int insert(struct DLL* list, int element)
{
	struct Node* newNode = (struct Node*)calloc(sizeof(struct Node), 1);
	newNode->value = element;
	newNode->prev = newNode->next = NULL;

	if(list->head == NULL)
	{
		list->head = list->tail = newNode;
		list->length++;
		return 0;
	}

	struct Node* node = (struct Node*)list->tail;
	node->next = newNode;
	newNode->prev = node;
	list->tail = newNode;
	list->length++;
	return 0;
}

/*-----------------------------------------------------------
Purpose : To insert nodes in front of a doubly linked list
------------------------------------------------------------- */


int insertFront(struct DLL* list, int element)
{
	struct Node* newNode = (struct Node*)calloc(sizeof(struct Node), 1);
	newNode->value = element;
	newNode->prev = newNode->next = NULL;
	struct Node* node = (struct Node*)list->head;
	if(node)
	{
		newNode->next = node;
		node->prev = newNode;
		list->head = newNode;
	}
	else
	{
		list->head = list->tail = newNode;
	}
	list->length++;
	return 0;
}

/*---------------------------------------------------------------
Purpose : To remove nodes from the front of a doubly linked list
----------------------------------------------------------------- */

int removeFront(struct DLL* list)
{
	struct Node* node = (struct Node*)list->head;
	if(node == NULL)
	{
		return -1;
	}
	else if(list->head == list->tail)
	{
		list->head = list->tail = NULL;	
	}
	else
	{
		list->head = node->next;
		node->next->prev = NULL;
	}
	free(node);
	list->length--;
	return 0;
}


/*-------------------------------------------------------------
Purpose : To remove nodes from the end of a doubly linked list
--------------------------------------------------------------- */

int remove(struct DLL* list, int element)
{
	struct Node* node = (struct Node*)list->head;
	while(node && node->value != element)
	{
		node = node->next;
	}

	if(node == NULL)
	{
		return -1;
	}
	else if(node->prev == node->next)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node);
	list->length--;
	return 0;
}

/*-------------------------------------------------------------
Purpose : To print the values of each node of a doubly linked 
list , sequentially from head to tail, separated by commas
--------------------------------------------------------------- */

void print(struct DLL* list)
{
	struct Node* node = (struct Node*)list->head;
	if(list->negative)
	{
		printf("-");
	}
	while(node)
	{
		printf("%d,",node->value);
		node = node->next;
	}
	printf("\n%d\n", list->length);
	return;
}


/*-------------------------------------------------------------
Purpose : To find the position of element in the list from head
to tail . It returns a pointer to the node containing the element
--------------------------------------------------------------- */

void* position(struct DLL* list, int element)
{
	struct Node* node = (struct Node*)list->head;
	while(node && node->value != element)
	{
		node = node->next;
	}
	return node;
}

/*-------------------------------------------------------------
Purpose : To read a line from the text file contaiing the input
--------------------------------------------------------------- */

char* readline(char* input_string, char* output_string)
{
	char* ptr_input_string = input_string;
	while(*input_string != '\n' && *input_string++);
	size_t str_size = input_string - ptr_input_string;
	memcpy(output_string, ptr_input_string, str_size);
	output_string[str_size - 1] = 0;
	return ++input_string;
}


/*-------------------------------------------------------------
Purpose : To read a certain number of characters from the input 
string to the output string
--------------------------------------------------------------- */
char* readCharacters(char* input_string, char* output_string, int count)
{
	char* ptr_input_string = input_string;
	while(count-- && input_string++);
	size_t str_size = input_string - ptr_input_string;
	memcpy(output_string, ptr_input_string, str_size);
	output_string[str_size] = 0;
	return input_string;
}

/*-------------------------------------------------------------
Purpose : To split and insert the values of a string into a doubly
linked list with each node having DISGITS_SIZE number of numbers
--------------------------------------------------------------- */

int string_to_list(struct DLL* list, char* operand)
{	
	int length = strlen(operand);
	int node_digit_count = length % DIGITS_SIZE ? length % DIGITS_SIZE : DIGITS_SIZE;
	char digit[DIGITS_SIZE + 1];
	while(*operand){
		operand = readCharacters(operand, digit, node_digit_count);
		int value = atoi(digit);
		insert(list, value);
		node_digit_count = DIGITS_SIZE;
	}
	return 0;
}

/*-------------------------------------------------------------
Purpose : To delete a list at the end of processing for freeing 
up space
--------------------------------------------------------------- */


int deletelist(struct DLL* list)
{
	struct Node* node = (struct Node*)list->head;
	struct Node* tempNode = NULL;
	while(node)
	{
		tempNode = node;
		node = node->next;
		free(tempNode);
		list->length--;
	}
	list->head = list->tail = NULL;
	list->negative = 0;
	return 0;
}

/*-------------------------------------------------------------
Purpose : To add 2 numbers of any dimension. Overflow handled
--------------------------------------------------------------- */

int Addition(struct DLL* operand1, struct DLL* operand2, struct DLL* result)
{
	struct Node* operand1_node = (struct Node*)operand1->tail;
	struct Node* operand2_node = (struct Node*)operand2->tail;
	int overflow = 0, value1 = 0, value2 = 0, output = 0;

	while(operand1_node && operand2_node)
	{
		value1 = operand1_node->value;
		value2 = operand2_node->value;
		output = value1 + value2 + overflow;
		insertFront(result, output % MAX_VALUE);
		overflow = output / MAX_VALUE;
		operand1_node = operand1_node->prev;
		operand2_node = operand2_node->prev;
	}

	while(operand1_node)
	{
		value1 = operand1_node->value;
		output = value1 + overflow;
		insertFront(result, output % MAX_VALUE);
		overflow = output / MAX_VALUE;
		operand1_node = operand1_node->prev;
	}

	while(operand2_node)
	{
		value2 = operand2_node->value;
		output =  value2 + overflow;
		insertFront(result, output % MAX_VALUE);
		overflow = output / MAX_VALUE;
		operand2_node = operand2_node->prev;
	}
	insertFront(result, overflow);
	return 0;
}

/*-------------------------------------------------------------
Purpose : To subtract 2 numbers of any dimension. Underflow handled
--------------------------------------------------------------- */

int Subtraction(struct DLL* operand1, struct DLL* operand2, struct DLL* result)
{
	struct Node* operand1_node = (struct Node*)operand1->tail;
	struct Node* operand2_node = (struct Node*)operand2->tail;
	int underflow = 0, value1 = 0, value2 = 0, output = 0;
	
	if(operand1->length < operand2->length ||
	(operand1->length == operand2->length &&
	((struct Node*)operand1->head)->value < ((struct Node*)operand2->head)->value))
	{
		operand1_node = (struct Node*)operand2->tail;
		operand2_node = (struct Node*)operand1->tail;
		result->negative = 1;
	}	
	
	// Complement of subtrahend
	while(operand2_node)
	{
		value2 = operand2_node->value;
		output = MAX_VALUE - value2;
		insertFront(result, output);
		operand2_node = operand2_node->prev;
	}

	// Addition of minuend and complement of subtrahend
	struct Node* result_node = (struct Node*)result->tail;
	while(operand1_node && result_node)
	{
		value1 = operand1_node->value;
		value2 = result_node->value;
		output = value1 + value2 - underflow;
		result_node->value = output % MAX_VALUE;
		underflow = (int)!(output / MAX_VALUE);
		operand1_node = operand1_node->prev;
		result_node = result_node->prev;
	}
	
	if(underflow && operand1_node)
	{
		operand1_node->value -= 1;
	}

	while(operand1_node)
	{
		insertFront(result, operand1_node->value);
		operand1_node = operand1_node->prev;
	}

	return 0;
}

/*-------------------------------------------------------------
Purpose : To multiply 2 numbers of any dimension. Overflow handled
--------------------------------------------------------------- */

int Multiplication(struct DLL* operand1, struct DLL* operand2, struct DLL* result)
{
	struct Node* operand1_node = NULL;
	struct Node* operand2_node = (struct Node*)operand2->tail;
	int overflow = 0, value1 = 0, value2 = 0, output = 0;
	insert(result, output);
	struct Node* result_node = (struct Node*)result->tail;
	struct Node* iteration_node = (struct Node*)result->tail;

	while(operand2_node)
	{
		value2 = operand2_node->value;
		operand1_node = (struct Node*)operand1->tail;
		while(operand1_node)
		{
			value1 = operand1_node->value;
			output = value1 * value2 + overflow;
			overflow = output / MAX_VALUE;
			output = output % MAX_VALUE;
			if(result_node == NULL)
			{
				insertFront(result, output);
				result_node = (struct Node*)result->head;
			}
			result_node->value = output;
			operand1_node = operand1_node->prev;
			result_node = result_node->prev;
			if(result_node)
			{
				overflow += result_node->value;
			}
		}
		if(overflow)
		{
			insertFront(result, overflow);
		}
		result_node = iteration_node = iteration_node->prev;
		overflow = result_node->value;
		operand2_node = operand2_node->prev;
	}
	return 0;
}

/*-------------------------------------------------------------
Purpose : To copy DLL operand1 to DLL operand2  
--------------------------------------------------------------- */

int copylist(struct DLL* operand1, struct DLL* operand2 )
{  
	struct Node* node1 = (struct Node*)operand1->head;
   	struct Node* node2 = (struct Node*)operand2->head;
	while(node1)
	{
		node2->value = node1->value;
		node2 = node2->next; 
		node1 = node1->next;
	}
	return 0;
}

/*-------------------------------------------------------------
Purpose : To divide 2 numbers of comparable dimension. This implements
division as repeated subtraction. Quotient and remainder are displayed
--------------------------------------------------------------- */

int Division(struct DLL* operand1, struct DLL* operand2, struct DLL* result)
{
	int counter =0;	
	printf("\noperand1 length =%d",operand1->length );
	printf("\noperand2 length =%d",operand2->length );
	if(operand1->length - operand2->length >=1 )
	{
		printf("\nIncompatible dimensions of inputs, please enter numbers of similar dimensions");
		return 0;
	}
	while(Comparison(operand1, operand2))
	{
		Subtraction(operand1, operand2 , result);
		copylist(result, operand1);
		memset(result,0,sizeof(result));
		print(operand1);
		counter++;
	}
	
	printf("\nQuotient =");
	printf("%d",counter);
	printf("\nRemainder::");
	print(operand1);


	return 0;
	
}

/*-------------------------------------------------------------
Purpose : To compare 2 large numbers and return 1 if operand1 is 
greater than operand2 , 0 otherwise.
--------------------------------------------------------------- */

int Comparison(struct DLL* operand1, struct DLL* operand2)
{
	struct Node* operand1_node = (struct Node*)operand1->head;
	struct Node* operand2_node = (struct Node*)operand2->head;
	int check = 0; 
	while( operand1_node && operand2_node && (operand1_node->value >= operand2_node->value))
	{	
		operand1_node = operand1_node->next;
		operand2_node = operand2_node->next;
	}
	if(operand1_node && operand2_node)
	{
	
		check = 0;
	}
	else
	{
		check = 1;

	}

	return check;
}

/*-------------------------------------------------------------
Purpose : 2 large numbers are read from the text file. Operation 
of user's choice is performed on them and the result is displayed
--------------------------------------------------------------- */

int main()
{
	int fd = open("input.txt", O_RDONLY);
	if(fd == -1)
	{
		printf("Cannot access inputfile\n");
		return -1;
	}

	char buffer[BUFFER_SIZE];
	char* ptr_buffer = buffer;
	ssize_t length = read(fd, &buffer, BUFFER_SIZE - 1);
	buffer[length] = 0;
	char line[BUFFER_SIZE];
	int choice = -1;
	struct DLL* operand1 = (struct DLL*)calloc(sizeof(struct DLL), 1);
	struct DLL* operand2 = (struct DLL*)calloc(sizeof(struct DLL), 1);
	struct DLL* result = (struct DLL*)calloc(sizeof(struct DLL), 1);
	printf("%s",buffer);
	ptr_buffer = readline(ptr_buffer, line);
	string_to_list(operand1, line);
	ptr_buffer = readline(ptr_buffer, line);
	string_to_list(operand2, line);
	printf("\noperand 1 ::");
	print(operand1);
	printf("\noperand 2 ::");
	print(operand2);
	printf("Enter choice : \n1. Addition \n2. Subtraction \n3. Multiplication \n4. Division\n");
	scanf("%d", &choice);
	switch(choice)
		{
			case 1: 
				Addition(operand1, operand2, result);
				printf("\nAdding operand1 + operand2\n");
				print(result);
				break;
			
			case 2:
				Subtraction(operand1, operand2, result);
				printf("\nSubtracting operand1 - operand2\n");
				print(result);
				break;
				
			case 3:
				Multiplication(operand1, operand2, result);
				printf("\nMultiplying operand1 * operand2\n");
				print(result);
				break;
				
			case 4:
				printf("\nDividing operand1 / operand2\n");
				Division(operand1, operand2, result);
				break;
			
			default:
				printf("\n Incorrect Option");
				
				
		}
		
	
	
	deletelist(operand1);
	deletelist(operand2);
	deletelist(result);

	return 0;
}
