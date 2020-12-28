#include <stdio.h>
#include <stdlib.h> // For exit() function

int count;
int stateArr[250];
int inputArr[250];
int nextArr[250];
int curState = 0;
int nextState = 0;


void makeArrs(FILE*file);
void nextMachine(FILE* file, int count);
int inputChars(FILE* file);
int numLines(FILE* file);

int main(int argc, char**argv) {
    FILE *file1 = fopen(argv[1], "r");      // open the fsm file
    FILE *file2 = fopen(argv[2], "r");      // open the input file
    if (file1 == NULL || file2 == NULL) {                    // check the file exists
        printf("Error! This file could not be opened\n");
        exit(-1);
    }

    printf("processing FSM definition file test1.fsm\n");
    printf("FSM has %d transitions\n", numLines(file1));
    printf("processing FSM input file test1.inputs\n");

    rewind(file1);
    makeArrs(file1);
    nextMachine(file2, count);
    rewind(file2);
    printf("after %d steps, state machine finished successfully at state %d\n",inputChars(file2), curState);
}

int inputChars(FILE* file) {  // this reads and counts all the inputs and ensures right format.
    char line[3];
    int step = 0;
    while (((fgets(line, 3, file)) != NULL)) {
        if (line[0] < 'A' || (line[0] > 'Z' && line[0] < 'a') || line[0] > 'z') {
            printf("There is an error in the format of your code at this point!");
            exit(-1);
        }
        step += 1;
    }
    return step;
}

void nextMachine(FILE* file, count){
    char letter;
    int steps = 0;
    while(fscanf(file, "%c\n", &letter) != EOF) {
        printf("\tat %d step, %c", steps, letter);
        for (int a = 0; a < count; a++) {
            if (letter == inputArr[a] && curState == stateArr[a]) {
                printf(" transition from state %d ",curState);
                nextState = nextArr[a];
                curState = nextState;
                break;
            }
        }
        printf("to state %d\n", nextState);
        steps++;
    }
}

void makeArrs(FILE* file) {     // this function makes the fsm file into arrays.
    int state;
    int next;
    char input;
    int i=0;
    while(fscanf(file, "%d:%c>%d\n", &state, &input, &next) != EOF) {
        stateArr[i] = state;
        inputArr[i] = input;
        nextArr[i] = next;
        i ++;
    }
}

int numLines(FILE* file) {  // this function counts the number of lines in the fsm file
    char format[7];
    while ((fgets(format, 7, file)) != NULL) {
        count += 1;
    }
    return count;
}



