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

char *tokens[]={ "QUOTE_ERROR", "ERROR_CHAR", "SYSTEM_ERROR",
               "EOL", "REDIR_OUT", "REDIR_IN", "APPEND_OUT",
               "REDIR_ERR", "APPEND_ERR", "REDIR_ERR_OUT", "SEMICOLON",
               "PIPE", "AMP", "WORD" };


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
  printf("\n");
}

int main (int argc, char * argv[]){
    char buf[256];
    int rtn;
    char *rtpt;
    bool dirOut = false;
    bool dirIn = false;
    bool dirErr = false;
    bool appErr = false;
    bool appOut = false;
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

        struct Node *node;
        node = NULL;

        bool rdOut = false;
        bool rdIn = false;
        bool rdErr = false;
        bool rdDefined = false;

        bool background = false;
        bool myError = false;
        bool beginningOfCommand = true;

        while(rtn != EOL){
            switch(rtn){
                case WORD:
                    if(beginningOfCommand == true){
                        printf(":--: %s\n", lexeme);
                        beginningOfCommand = false;
                        rdIn = false;
                        rdOut = false;
                        rdErr = false;
                    } else {
                        printf(" --: %s\n", lexeme);
                        rdDefined = true;
                    }
                    break;
                case ERROR_CHAR:
                    break;
                default:
                    if (strcmp(tokens[rtn %96], "PIPE") == 0){
                        if(beginningOfCommand == true){
                            break;
                            myError = true;
                        }
                        printf(" |\n");
                        beginningOfCommand = true;
                        rdIn = false;
                        rdOut = false;
                        rdErr = false;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "SEMICOLON") == 0){
                        printf(" ;\n");
                        beginningOfCommand = true;
                        rdIn = false;
                        rdOut = false;
                        rdErr = false;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "REDIR_OUT") == 0){
                        if(beginningOfCommand == true){
                            myError = true;
                            printf("Ambiguous redirection\n");
                            break;
                        }
                        if(rdOut == true){
                            printf("Ambiguous redirection\n");
                            myError = true;
                            break;
                        }
                        printf(" >\n");
                        dirOut = true;
                        rdOut = true;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "REDIR_IN") == 0){
                        if(beginningOfCommand == true){
                            myError = true;
                            printf("Ambiguous redirection\n");
                            break;
                        }
                        if(rdIn == true){
                            printf("Ambiguous redirection\n");
                            myError = true;
                            break;
                        }
                        printf(" <\n");
                        dirIn = true;
                        rdIn = true;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "REDIR_ERR") == 0){
                        if(beginningOfCommand == true){
                            myError = true;
                            printf("Ambiguous redirection\n");
                            break;
                        }
                        if(rdErr == true){
                            printf("Ambiguous redirection\n");
                            myError = true;
                            break;
                        }
                        printf(" 2>\n");
                        dirErr = true;
                        rdErr = true;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "APPEND_OUT") == 0){
                        if(beginningOfCommand == true){
                            myError = true;
                            printf("Ambiguous redirection\n");
                            break;
                        }
                        if(rdOut == true){
                            printf("Ambiguous redirection\n");
                            myError = true;
                            break;
                        }
                        printf(" >>\n");
                        dirOut = true;
                        rdOut = true;
                        rdDefined = false;
                    } else if(strcmp(tokens[rtn %96], "APPEND_ERR") == 0){
                        if(beginningOfCommand == true){
                            myError = true;
                            printf("Ambiguous redirection\n");
                            break;
                        }
                        if(rdErr == true){
                            printf("Ambiguous redirection\n");
                            myError = true;
                            break;
                        }
                        printf(" 2>>\n");
                        dirErr = true;
                        rdErr = true;
                        rdDefined = false;
                    } else if (strcmp(tokens[rtn %96], "QUOTE_ERROR") == 0){
                        myError = true;
                        break;
                    } else if (strcmp(tokens[rtn %96], "AMP") == 0){
                        background = true;
                    }
                    //printf("%d: %s\n", rtn, tokens[rtn%96]);
            }
            if(myError == true){
                break;
            }
            push(&node, lexeme);
            rtn = parse_line(NULL);
            if(rtn == EOL){
                if(rdDefined == false){
                    printf("No file defined for redirection\n");
                    myError = true;
                    break;
                }
            }
        }
        if(myError == false){
            printf(" --: EOL\n");
        }
        //reverse(&node);
        //printList(node);

    }

    printf("my string is: %s\n", buf);
}
