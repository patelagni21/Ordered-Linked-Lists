#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct node {
	int data;
	struct node* next;
};

// utility methods
int get_list_size(struct node* head);
void print_list(struct node* head);

// functional methods
struct node* add_num(struct node* head, int input_number);
struct node* del_num(struct node* head, int input_number);
void freeList(struct node* head);

int main(int argc, char *argv[]) {

  struct node* head = NULL;
  int input_number;
  char in_command[20];

  FILE* in_file = fopen(argv[1], "r");				// read only mode
  //FILE* in_file  = fopen("input_file.dat", "r"); 	// Debug mode only

  if (in_file == NULL)  {			//Error reading File
    if (errno == ENOENT) {
	  printf("ERROR\n");
    }
    return 1;
  }

  while ( fscanf(in_file, "%s %d", in_command, &input_number) != EOF ) 
  {
    switch(in_command[0])     //checking 1st char of the in_command
    {
        case 'I':
            head = add_num(head, input_number);
            if (get_list_size(head)==0) {
                printf("EMPTY");
            }else {
            	print_list(head);
			      }
            break;
        case 'D':
            head = del_num(head, input_number);
            break;
        default:
            break;
    }
  }

  freeList(head);
  fclose(in_file);
  return 0;
}

void freeList(struct node* head) {
  struct node* temp;
  while (head != NULL) {
    temp = head;
    head = head -> next;
    free(temp);
   }
}

int get_list_size(struct node* head) {
  int n = 0;
  struct node* curr = head;
  while (curr != NULL) {
    curr = curr -> next;
    n++;
  }
  return n;
}

void print_list(struct node* head) {
  struct node* curr = head;
  if (head != NULL) {
    printf("%d", curr -> data);
    curr = curr -> next;
    while (curr != NULL) {
      printf(" %d", curr -> data);
      curr = curr -> next;
    }
  }
  printf("\n");
}

struct node* add_num(struct node* head, int input_number) {
  struct node* prev = NULL;
  struct node* curr = head;
  struct node* nd = (struct node*) malloc(sizeof(struct node));
  nd -> data = input_number;
  nd -> next = NULL;
  while (curr != NULL) {
    if (input_number < curr -> data) 		//pointer to insert here
      break;
    else if (input_number == curr -> data) 	//this is duplicate, so ignore
      return head;
    prev = curr;
    if (curr != NULL)   // 7/9 put this condition
      curr = curr -> next;
  }
  nd -> next = curr;
  if (prev != NULL)  
    prev -> next = nd; 
  else  
    head = nd;
  
  return head;
}

struct node* del_num(struct node* head, int input_number) {
  struct node* prev = NULL;
  struct node* curr = head;
  while (curr != NULL) 
  {
    if (input_number < curr -> data)  
      return head;
    else if (input_number == curr -> data) 
      break;
    
    prev = curr;
    curr = curr -> next;
  }
  if (curr == NULL) {		// number is NOT THERE
    printf("FAILED\n");
    return head;
  }
  if (prev == NULL) 		// number is there
    head = curr -> next;
  else
    prev -> next = curr -> next;
  
  free(curr);				// deleted number 
  printf("SUCCESS\n");
  return head;
}