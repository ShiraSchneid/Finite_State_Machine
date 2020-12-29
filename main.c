#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <ctype.h>

// initialize my variables
int count = 0;
int stateArr[250];
int inputArr[250];
int nextArr[250];
int curState = 0;
int nextState = 0;

// initialize my functions
int makeArrs(FILE*file);
int nextMachine(FILE* file);
int inputChars(FILE* file);
int numLines(FILE* file);
int numStates();
void negNumTest(FILE* file);
void nonLetterTest(FILE* file);
void stateSizeTest(FILE* file);


int main(int argc, char**argv) {
    FILE *file1 = fopen(argv[1], "r");      // open the fsm file
    FILE *file2 = fopen(argv[2], "r");      // open the input file
    if (file1 == NULL || file2 == NULL) {                    // check the file exists
        printf("----Error! This file could not be opened----\n");       // error message
        exit(1);
    }

    printf("processing FSM definition file test1.fsm\n");
    makeArrs(file1);                //checks that the states can't be negative
    rewind(file1);                      //rewinds the fsm file
    printf("FSM has %d transitions\n", numLines(file1));            // prints the number of transitions
    printf("processing FSM input file test1.inputs\n");
    inputChars(file2);      // making sure the inputs are letters

    rewind(file1);                  // rewinds the fsm file
    rewind(file2);                      //rewinds the input file
    nextMachine(file2);      // calls nextMachine function
    rewind(file2);                  // rewinds the inputs file
    // finishes and sums up the steps and current state
    printf("after %d steps, state machine finished successfully at state %d\n",inputChars(file2), curState);
    printf("This is the unique states %d\n", numStates());
    negNumTest(file1);
    nonLetterTest(file2);
    stateSizeTest(file1);


    fclose(file1);      //close the files
    fclose(file2);
}

int inputChars(FILE* file) {  // this reads and counts all the inputs and ensures right format.
    char line[3];
    char letter;
    int step = 0;
    while(fscanf(file, "%c\n", &letter) != EOF) {           // reads in the input                                            // gets each line of the text file
        if (isalpha(letter)==0) {           // makes sure its a letter
            printf("----Error! There is an error in the format of your inputs.----\n");          // error message
            exit(1);                                                                     // error output
        }
        step += 1;              // increments the number of steps
    }
    return step;
}

int nextMachine(FILE* file){        // this function switches the states based on the input
    char letter;
    int steps = 0;
    while(fscanf(file, "%c\n", &letter) != EOF) {           // reads in the input
        printf("\tat step %d, %c", steps, letter);          // prints the current step and the input
        for (int a = 0; a < count; a++) {                           // goes through a loop of the number of inputs
            char lower = tolower(letter);                       // allows the input to be upper or lower case
            if ((letter == inputArr[a] || lower == inputArr[a]) && curState == stateArr[a]) {    // if the input is the same and the current state is the same
                printf(" transitions from state %d ",curState);          // print this and the current state
                nextState = nextArr[a];                                 // update the next state to be the determined next state
                curState = nextState;                               // update the current state to be the next state
                break;
            }
        }
        printf("to state %d\n", nextState);                 // print out the next state
        steps++;                                            // increment the number of steps
    }
    return 0;
}

int makeArrs(FILE* file) {     // this function makes the fsm file into arrays.
    // intialize my vaiables
    int state;
    int next;
    char input;
    int i=0;
    while(fscanf(file, "%d:%c>%d\n", &state, &input, &next) != EOF) {       // read in the lines and set them to variables
        if (state < 0 || next < 0) {                                        // makes sure no states are negative
            printf("----Error! One of your states is negative.----\n");
            exit(1);
        }
        stateArr[i] = state;                 // array of current states
        inputArr[i] = input;                // array of input
        nextArr[i] = next;                      // array of next state
        i ++;
    }
    return 0;
}

int numStates() {                       // this function counts the number of distinct states
    int res = 0;
    for (int i = 0; i < count; i++) {
        int j = 0;
        for (j = 0; j<i; j++){
            if (stateArr[i] == stateArr[j]){
                break;
            }
        }
        if (i == j +1){
            res +=1;
        }
    }
    if (res > 50){                  // if there are more than 50 distinct states, rasie an error.
        printf("----Error! You have too many different states.----");
        exit(1);
    }
    return res;                 // return the number of distinct states
}

int numLines(FILE* file) {  // this function counts the number of lines in the fsm file
    char format[7];
    while ((fgets(format, 7, file)) != NULL) {      // gets each line
        count += 1;             // increments count
    }
    return count;
}



// testing functions
void negNumTest(FILE* file) {
    int actual = makeArrs(file);
    int expected = 0;
    printf("Testing with correct state input: %s\n", (expected == actual ? "PASSED": "FAILED"));
    FILE* fsm2 = fopen("test2.fsm", "r");
    actual = makeArrs(fsm2);
    expected = -1;
    printf("Testing with incorrect state input: %s\n", (expected == actual ? "PASSED": "FAILED"));
}
void nonLetterTest(FILE* file) {
    int actual = inputChars(file);
    int expected = 0;
    printf("Testing with correct fsm input: %s\n", (expected == actual ? "PASSED": "FAILED"));
    FILE* input2 = fopen("test2.inputs", "r");
    actual = inputChars(input2);
    expected = -1;
    printf("Testing with incorrect fsm input: %s\n", (expected == actual ? "PASSED": "FAILED"));
}

void stateSizeTest(FILE* file) {
    int actual = numStates(file);
    int expected = 4;
    printf("Testing with valid number of states: %s\n", (expected == actual ? "PASSED": "FAILED"));
    FILE* fsm3 = fopen("test3.fsm", "r");
    actual = numStates(fsm3);
    expected = -1;
    printf("Testing with invalid fsm size: %s\n", (expected == actual ? "PASSED": "FAILED"));
        }








