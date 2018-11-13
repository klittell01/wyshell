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
    int in, out, err;
    bool first;
};


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

        char * myPrev;
        myPrev = NULL;
        struct Word *firstWordNode;
        firstWordNode = calloc(1, sizeof(struct Word));
        firstWordNode->command = lexeme;
        firstWordNode->prev = NULL;
        // got to get the first one and then i think the second so we can point
        // backwards easily. 
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

        printf("first node is\n" );

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
