#include <stdio.h>
#include <stdlib.h> // For exit() function

// initialize my variables
int count = 0;
int stateArr[250];
int inputArr[250];
int nextArr[250];
int curState = 0;
int nextState = 0;

// initialize my functions
void makeArrs(FILE*file);
void nextMachine(FILE* file);
int inputChars(FILE* file);
int numLines(FILE* file);


int main(int argc, char**argv) {
    FILE *file1 = fopen(argv[1], "r");      // open the fsm file
    FILE *file2 = fopen(argv[2], "r");      // open the input file
    if (file1 == NULL || file2 == NULL) {                    // check the file exists
        printf("Error! This file could not be opened\n");       // error message
        exit(1);
    }

    printf("processing FSM definition file test1.fsm\n");
    makeArrs(file1);                // rewinds the input file
    rewind(file1);
    printf("FSM has %d transitions\n", numLines(file1));            // prints the number of transitions
    printf("processing FSM input file test1.inputs\n");
    inputChars(file2);      // making sure the inputs are right

    rewind(file1);                  // rewinds the fsm file
    rewind(file2);
    nextMachine(file2);      // calls nextMachine function
    rewind(file2);                  // rewinds the inputs file
    // finishes and sums up the steps and current state
    printf("after %d steps, state machine finished successfully at state %d\n",inputChars(file2), curState);
    fclose(file1);      //close the files
    fclose(file2);
}

int inputChars(FILE* file) {  // this reads and counts all the inputs and ensures right format.
    char line[3];
    int step = 0;
    while (((fgets(line, 3, file)) != NULL)) {                                              // gets each line of the text file
        if (line[0] < 'A' || (line[0] > 'Z' && line[0] < 'a') || line[0] > 'z') {           // makes sure its a letter
            printf("----There is an error in the format of your inputs!----");          // error message
            exit(1);                                                                       // error output
        }
        step += 1;              // increments the number of steps
    }
    return step;
}

void nextMachine(FILE* file){        // this function switches the states based on the input
    char letter;
    int steps = 0;
    while(fscanf(file, "%c\n", &letter) != EOF) {           // reads in the input
        printf("\tat step %d, %c", steps, letter);          // prints the current step and the input
        for (int a = 0; a < count; a++) {                           // goes through a loop of the number of inputs
            if (letter == inputArr[a] && curState == stateArr[a]) {         // if the input is the same and the current state is the same
                printf(" transitions from state %d ",curState);          // print this and the current state
                nextState = nextArr[a];                                 // update the next state to be the determined next state
                curState = nextState;                               // update the current state to be the next state
                break;
            }
        }
        printf("to state %d\n", nextState);                 // print out the next state
        steps++;                                            // increment the number of steps
    }
}

void makeArrs(FILE* file) {     // this function makes the fsm file into arrays.
    // intialize my vaiables
    int state;
    int next;
    char input;
    int i=0;
    while(fscanf(file, "%d:%c>%d\n", &state, &input, &next) != EOF) {       // read in the lines and set them to variables
        if (state < 0 || next < 0) {
            printf("----One of your states is negative!----");
            exit(1);
        }
        stateArr[i] = state;                 // array of current states
        inputArr[i] = input;                // array of input
        nextArr[i] = next;                      // array of next state
        i ++;
    }
}

int numLines(FILE* file) {  // this function counts the number of lines in the fsm file
    char format[7];
    while ((fgets(format, 7, file)) != NULL) {      // gets each line
        count += 1;             // increments count
    }
    return count;
}





