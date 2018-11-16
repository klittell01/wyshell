/*
 * wyshell.c
 * Author: Kevin Littell
 * Date: 11-15-2018
 * COSC 3750, program 8
 * simple shell utility
 */


#include "stdbool.h"
#include "unistd.h"
#include "errno.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "wyscanner.h"

struct Word{
    char *next, *prev;
    char *command;
};

struct Node{
        struct Node *next, *prev;
        char *command;
        int num;
        struct Word *arg_list;
        int in, out, err;
        char *inFile, *outFile, *errFile;
};

struct Node * head;

void pushToBack(struct Node ** headRef, char *data){
    struct Node *newNode;
    newNode = (struct Node*)calloc(1, sizeof(struct Node));
    newNode->command = strdup(data);
    newNode->next = (*headRef);
    (*headRef) = newNode;
}

/*
struct Node *head = NULL;
struct Node *start = NULL;

void insert(char * data, int num) {
   //create a link
   struct Node *link = (struct Node*) malloc(sizeof(struct Node));

   link->command = strdup(data);
   link->num = num;

   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;

   if(start == NULL){
     //  start = link;
     //  printf("start command: %s, link command: %s\n",start->command, link->command );
   }
}
*/

void printData(struct Node *  myNode){
    //struct Node * ptr = head;
    while(myNode != NULL){
        printf("data for this node is: %s\n", myNode->command);
        myNode = myNode->prev;

    }
}

/* Function to reverse the linked list */
static void reverseList(struct Node** headRef)
{
    struct Node* prev   = NULL;
    struct Node* current = *headRef;
    struct Node* next = NULL;
    while (current != NULL)
    {
        // Store next
        next  = current->next;

        // Reverse current node's pointer
        current->next = prev;

        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *headRef = prev;
}


/*
//display the list
void printList() {

   struct Node *ptr = head;

   printf("\n[head] =>");
   //start from the beginning
   while(ptr != NULL) {
      printf(" %s + %d =>",ptr->command, ptr->num);
      ptr = ptr->next;
   }

   printf(" [null]\n");
}
*/
/// TODO: well my linked list is working but backwards of what i would like
// i can probably just reverse the order of something to straighten it out
// it always assigns the last word to all the commands of each node, except when
// i add them one at time manually


/* Function to reverse the linked list */
static void reverse(struct Node** headRef)
{
  struct Node* prev   = NULL;
  struct Node* current = *headRef;
  struct Node* next = NULL;
  while (current != NULL)
  {
      // Store next
      next  = current->next;

      // Reverse current node's pointer
      current->next = prev;

      // Move pointers one position ahead.
      prev = current;
      current = next;
  }
  *headRef = prev;
}

/* Function to push a node */
void push(struct Node** headRef, char * data)
{
  struct Node* newNode =
          (struct Node*) malloc(sizeof(struct Node));
  newNode->command  = strdup(data);
  newNode->next = (*headRef);
  (*headRef)    = newNode;
}

/* Function to print linked list */
void printList(struct Node *head)
{
  struct Node *tmp = head;
  while(tmp != NULL)
  {
      printf(" %s,", tmp->command);
      tmp = tmp->next;
  }
}

int main (int argc, char * argv[]){
    char buf[256];
    int rtn;
    char *rtpt;
    head = calloc(1, sizeof(struct Node));
    while(1){
        printf("$> ");
        rtpt = fgets(buf, 256, stdin);
        if(rtpt == NULL){
            if(feof(stdin)) {
              return 0;
            }
        }
        rtn = parse_line(buf);
        if(rtn == EOL){
            printf("not a valid input\n");
            continue;
        }

        struct Node *node, *head;
        node = NULL;//calloc(1, sizeof(struct Node));

        while(rtn != EOL){
            printf("command is : %s\n", lexeme);
            push(&node, lexeme);
            rtn = parse_line(NULL);
        }
        reverse(&node);
        printList(node);
        // these work
        //pushToBack(&node, "one");
        //pushToBack(&node, "two");
        //pushToBack(&node, "three");

        // got to get the first one and then i think the second so we can point
        // backwards easily.
        /*
        while(rtn != EOL){
            switch (rtn) {
                case WORD:

                    ;
                    struct Word *tmpWord;
                    tmpWord = calloc(1, sizeof(struct Word));
                    tmpWord->command = lexeme;
                    tmpWord->prev = myPrev;

                    rtn = parse_line(NULL);
                    struct Word *nextWord;
                    if(rtn != EOL){
                        nextWord = calloc(1, sizeof(struct Word));
                        tmpWord->next = nextWord;
                    } else {
                        tmpWord->next = NULL;
                    }
                    break;
                default:
                    break;
            }
        }
        */

/*
        while(rtn != EOL){
            switch(rtn){
                case WORD:
                    ;
                    struct Word *tmpWord;
                    tmpWord = calloc(1, sizeof(struct Word));
                    printf("%s\n", lexeme);
                    break;
                case ERROR_CHAR:
                    printf("Error character: %d\n", rtn);
                    break;
                default:
                    printf("Error: %d\n", rtn);
                    break;
            }
            rtn = parse_line(NULL);
        }
        */
    }

    printf("my string is: %s\n", buf);
}
