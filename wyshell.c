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
        struct Word *arg_list;
        int in, out, err;
        char *inFile, *outFile, *errFile;
};

void pushToBack(struct Node ** tailRef, char *data){
    struct Node *newNode;
    newNode = calloc(1, sizeof(struct Node));
    newNode->command = data;
    newNode->next = NULL;
    newNode->prev = (*tailRef);
    (*tailRef) = newNode;
}

void printData(struct Node * myNode){
    while(myNode != NULL){
        printf("data for this node is: %s\n", myNode->command);
        myNode = myNode->prev;
    }
}

/// TODO: well my linked list is working but backwards of what i would like
// i can probably just reverse the order of something to straighten it out
// it always assigns the last word to all the commands of each node, except when
// i add them one at time manually


int main (int argc, char * argv[]){
    char buf[256];
    int rtn;
    char *rtpt;
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
        node = calloc(1, sizeof(struct Node));
        //node->prev == NULL;


        while(rtn != EOL){
            printf("command is : %s\n", lexeme);
            pushToBack(&node, lexeme); // this node add method doesnt work
            rtn = parse_line(NULL);
        }
        // these work
        pushToBack(&node, "one");
        pushToBack(&node, "two");
        pushToBack(&node, "three");

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
        printData(node);

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
