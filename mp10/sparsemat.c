#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

//partners: ufacio2, ehaynes2
//introduction: * This program takes an input file in a specified format to create a sparse matrix using a singly linked list. The first line
// of the file contains the total rows and columns of the matrix. Each line following will be in the format "row col value".
// load_tuples will create the head initial structure and place the first node in the sparse matrix. Then it will iterate through
// all the lines in the file and place the nodes ordered in the matrix. The completed sparse matrix is iterated through
// at the end and all the nodes are counted.
// gv_tuples will take a sparse matrix and return the value at a specified row and col.
// set_tuples will take a row, col, value, and place a row ordered in a sparse matrix. If the value is 0, then it will delete that node if it exists.
// save_tuples will write all nodes in a sparse matrix to a file.
// add_tuples will take two sparse matrices, adds them, and outputs the computed sum matrix.


sp_tuples * load_tuples(char* input_file)
{
	int row_f, col_f;								//declared variables
	double value_f;

	FILE* file = fopen(input_file, "r");						//open given file
	sp_tuples* tuples_ptr = (sp_tuples*) malloc(sizeof(sp_tuples));			//create space for the struct sp_tuples
	sp_tuples_node* head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));	//create space for the head node
	tuples_ptr->tuples_head = head;							//assign ptr to tuples_head
	fscanf(file, "%d %d", &(tuples_ptr->m), &(tuples_ptr->n));		//set the rows and cols of the matrix to sp_tuples
	tuples_ptr->nz = 0;							//initialize non-zero count to 0

	int num;								//declare variable
	do{									//get a head node with a value from file if possible. If the program can read in the row, col and value, it'll return 3 if it read in those values
	num = fscanf(file, "%d %d %lf ", &(head->row), &(head->col), &(head->value));
	} while (head->value == 0 && num == 3);					//if the file gives a node with a value of 0, it will not read it in and create a node with it
	head->next = NULL;							//set the head pointer to point to null
	do {
		num = fscanf(file, "%d %d %lf ", &row_f, &col_f, &value_f);	//continue to read in a row, col and value from the given file
		if (num == 3)							//only valid inputs (two integers and one double) will allow this to continue scanning
		{
			set_tuples(tuples_ptr, row_f, col_f, value_f);		//using the function from set_tuples to sort the nodes while making the linked list
		}
	} while (num == 3);							//continue reading and setting up the linked list until the file does not have anymore information
	sp_tuples_node* count = tuples_ptr->tuples_head;			//make a ptr to the head node to count
	while (count != NULL)							//loop through the newly made linked list 
	{
		tuples_ptr->nz += 1;						//increment number of non zero values for each node in the linked list
		count = count->next;						//update counter to go to the next node
	}

	fclose(file);								//close the file
	return tuples_ptr;							//ptr returned
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
	sp_tuples_node* node = mat_t->tuples_head;			//get pointer to the node we are checking
	while (node != NULL && node->row <= row)			//check through the linked list until the row we are 
									//checking goes past the given row
	{
		if (row == node->row && col == node->col)		//see if node has the same coordinate as the one we are 
		{							//looking for
			return node->value;				//found coordinates, so we should return the value
		}
		else	
			node = node->next;				//this node does not match the coordinates. Check next node
	}
	return 0;								//coordinates not found in linked list
}

sp_tuples_node* create_tuple(int row, int col, double value)	//makes a space in heap for 1 node with the given values
{
	sp_tuples_node* newHead = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));	//create new ptr to a new node
											//with the given parameters
	newHead->row = row;								//given row set to new node
	newHead->col = col;								//given col set to new node
	newHead->value = value;								//given value set to new node
	return newHead;	
}

void set_tuples(sp_tuples* mat_t, int row, int col, double value)
{	
	sp_tuples_node* node1 = mat_t->tuples_head;				//act as a previous node
	sp_tuples_node* node2 = mat_t->tuples_head->next;			//act as the current node
	//first check if this is 0 or not so we can remove memory (nz count decrements)
	if (value == 0)
	{
		//if the coordinate is at the head
		if (row == node1->row && col == node1->col)			//check to see if we are replacing the head node with 0
		{
			mat_t->tuples_head = node2;				//reroute head ptr to the node following the head
			free(node1);						//old head node is freed
			return;							//finished
		}
		else								//set coordinate is after the head
		{		//loop until we hit the end of the linked list (no node needs to be replaced or if we passed the 
				//location (meaning there will no longer be any chance that a node afterwards has the given coords
	
			while (node2 != NULL && node2->row <= row)		//check to see if there are any nodes with the same
			{							//coordinates and have the value of 0 (after head node)
										//it will not check for any locations after the given row because the linked list is ordered (there is no need to look further on)
										//Concept for node2->row <= row is adapted from LECTURE 20
				if (node2->row == row && node2->col == col)	//check if node2 has the same coordinates as the new 
				{						//zero value
					node1->next = node2->next;		//reroute ptr to next node on node1 to point to the
										//node after node2
					free(node2);				//delete node2
					return;					//finished
				}	//if node2 does not equal the coordinates given
				node1 = node2;					//node1 will now point to node2
				node2 = node2->next;				//node2 will point to the node after itself
			}
		}
	}	
	else	//not setting a value to 0
	{
		//check if the node needs to be set directly on the head
		if (node1->row == row && node1->col == col)			//check if the head has matching coordinates 
		{
			node1->value = value;					//update value at coordinate to given value
			return;
		} 
		else if ((row < node1->row) || ((row == node1->row) && (col < node1->col)))	//check to see if we need to insert node 
		{										//before the head
			mat_t->tuples_head = create_tuple(row, col, value);			//ptr to head changes to new node
			mat_t->tuples_head->next = node1;					//new node points to old head ptr
			return;
		}
		else		//inserted node is not at the head, check on other nodes
		{
		while (node2 != NULL && node2->row <= row)			//make sure we are in the right range for checking
			{
				if (row == node2->row && col == node2->col)	//found a node with the same coordinates as the given
				{						//parameters
					node2->value = value;			//set new value to the coordinate
					return;
				}	
				else if (row == node2->row && col < node2->col)		//check to see if we are before the node in terms
				{							//of its col placement
					node1->next = create_tuple(row, col, value);	//node1 will now point to the newly made node
					node1->next->next = node2;			//new node points to node2
					return;
				}
				node1 = node2;						//update the node1 and node2 to check next node
				node2 = node2->next;
			}
			node1->next = create_tuple(row, col, value);			//current node has a higher row value than the 
											//node we want to insert. Put new node before this
											//node (node2)
			node1->next->next = node2;					//update the pointer values
		}	
		return;
	}

}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE* file = fopen(file_name, "w");						//open the given file and enable it to be written
	if (file == NULL)								//check to make sure a valid file was given
		return;
	sp_tuples_node* node = mat_t->tuples_head;					//create a ptr to the head node
	fprintf(file, "%d %d", mat_t->m, mat_t->n);					//print out the dimensions of the matrix
	
	while (node != NULL)								//loop through every node in the matrix
	{	fputs("\n", file);							//print a new line for every new node we are going to print out
		fprintf(file, "%d %d %lf", node->row, node->col, node->value);		//print out node information
		node = node->next;							//go to next node
	}
	fputs("\n", file);								//print out one last \n for formatting
	fclose(file);									//close the file
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	sp_tuples_node* A = matA->tuples_head;				//create ptr to head node in matA
	sp_tuples_node* B = matB->tuples_head;				//ptr to head node in matB
	sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));	//create ptr to matC
	matC->m = matA->m;						//initiate matrix C with m,n and nz values
	matC->n = matA->n;
	matC->nz = 0;
	matC->tuples_head = NULL;				//make the head pointer point to null first
	sp_tuples_node* C_previous = matC->tuples_head;		//get the ptr to the head of matC into a variable dubbed 
									//C_previous
	while (A != NULL)				//loop through all the nodes in matA
	{	
		sp_tuples_node* newC;			//create a ptr to a node
		newC = create_tuple(A->row, A->col, A->value);	//create a space and address for the new node (with values)
		if (C_previous == NULL)			//for initializing the head
		{
			matC->tuples_head = newC;	//matC has its head node ptr initialized
			C_previous = matC->tuples_head;	//update variable C_previous
		}
		else					//for nodes other than head node
		{
			C_previous->next = newC;	//init the next node to the newly made node
			newC->next = NULL;		//newly made node will point to NULL
			C_previous = C_previous->next;	//advance C_previous node
		}
		A = A->next;				//advance node in matA
	}
			
	while (B != NULL)				//loop through matB
	{	double found_coord = gv_tuples(matC, B->row, B->col);		//determine if there is a shared coordinate with the nodes in matC and matB
		if (found_coord != 0)						//found a shared coordinate
		{
			set_tuples(matC, B->row, B->col, found_coord + B->value);	//set the new value in matC to be the sum of itself and matB's values
		}
		else
		{
			set_tuples(matC, B->row, B->col, B->value);		//if they are not sharing coordinates, fill in the "blank" spots in the matrix
		}
		B = B->next;					//go to the next node in B
	}
	C_previous = matC->tuples_head;		//reuse C-previous ptr to count non zero values (set to head node)
	while (C_previous != NULL)		//loop through matC and count the nodes
	{
		matC->nz += 1;
		C_previous = C_previous->next;
	}
	return matC; 
//	return 0;	//for testing purposes
}


/*
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;

}*/


	
void destroy_tuples(sp_tuples * mat_t){

	sp_tuples_node* current = mat_t->tuples_head;		//set our head tuple to "current"
	sp_tuples_node* next_t = current->next;			//set the tuple that follows the current tuple as "next"

	do							//continue going down the linked list until we are at the 
	{							//last node
		free(current);					//free up location of our current node
		current = next_t;				//current pointer now points to the destroyed nodes's 
								//subsequent node
		next_t = current->next;				//get node after the subsequent node's pointer
	} while (next_t !=NULL);
	free(current);						//free the last node
	free(mat_t);						//free up the ptr to our matrix
	return;
}  






