#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 50
#define MAX_CHARS 2000

typedef struct {
    char array[MAX_LINES][MAX_CHARS];
    int size;
} Strings;

//Function to determine the format of the output based on first line giving 0 or 1 combination
int format(char lines[][MAX_CHARS]) {

    //Setting variables to tokenize by comma
    int fmt;
    char delimiter[] = ",";
    char format[2];
    char *token = strtok(lines[0], delimiter);

    //putting integer values into own array spots
    format[0] = atoi(token);
    token = strtok(NULL, delimiter);
    format[1] = atoi(token);

    //Finding format
    if (format[0] == 0 && format[1] == 0) {
        return 1;
    } else if (format[0] == 1 && format[1] == 0) {
        return 2;
    } else if (format[0] == 0 && format[1] == 1) {
        return 3;
    } else if (format[0] == 1 && format[1] == 1) {
        return 4;
    }
}

//Function to tokenize any line into 2D array using specified delimeter
Strings tokenize(char *line, char delimeter[]) {
    Strings tokenized;
    tokenized.size = 0;
    char* token;
    int j = 0;

    token = strtok(line, delimeter);
    while (token != NULL) {
        while (*token == ' ') token++;
        strcpy(tokenized.array[tokenized.size], token);
        token = strtok(NULL, delimeter);
        tokenized.size++;
    }

    return tokenized;
}

void proportions(Strings responses, Strings questions, Strings options, int proportions[questions.size][options.size]) {

    char answers[MAX_LINES][MAX_CHARS];
    int numAnswers;

    //Filling prop with 0's
    for (int i = 0; i < questions.size; i++) {
        for (int j = 0; j < options.size; j++) {
            proportions[i][j] = 0;
        }
    }

    for (int j = 0; j < responses.size; j++) { //Outer loops through lines
        Strings ops = tokenize(responses.array[j], ",");

        for (int k = 0; k < ops.size; k++) { //Inner loops through answers in line j
            for (int i = 0; i < options.size; i++) {
                if (strcmp(ops.array[k], options.array[i]) == 0) {
                    proportions[k][i] += 1;
                }
            }
        }
    }
}


int main() {

    char buffer[1000];
    char lines[30][1000];
    int i = 0;

    //Takes input line by line, checks for comments, and adds to array
    while (fgets(buffer, 1000, stdin) != NULL) {
        if (buffer[0] != '#') {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(lines[i], buffer);
            i += 1;

        }
    }

    Strings questions = tokenize(lines[1], ";");
    Strings options = tokenize(lines[2], ",");

    Strings responses;
    responses.size = 0;

    for (int i = 3; i < 13; i++) {
        strcpy(responses.array[responses.size++], lines[i]);
    }

    int props[questions.size][options.size];
    proportions(responses, questions, options, props);

    for (int q = 0; q < questions.size; q++) {
        printf("Q%d: %s\n", q + 1, questions.array[q]);
        for (int o = 0; o < options.size; o++) {
            printf("   %s = %d\n", options.array[o], props[q][o]);
        }
    }

    return 0;

}
