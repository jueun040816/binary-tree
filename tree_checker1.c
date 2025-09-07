#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

char input[MAX];
int pos;
int errorFlag = 0;

char nextChar() {
    while (input[pos] && isspace(input[pos])) pos++;
    return input[pos];
}

int parseTree() {
    char c = nextChar();
    if (c == '\0') return 0;

    if (c == '(') {
        pos++;
        c = nextChar();
        if (c == ')') { pos++; return 1; }

        if (!isalpha(c)) { errorFlag = 1; return 0; }
        pos++;

        if (!parseTree()) return 0;
        if (!parseTree()) return 0;

        c = nextChar();
        if (c != ')') { errorFlag = 1; return 0; }
        pos++;
        return 1;
    }

    if (isalpha(c)) { pos++; return 1; }

    errorFlag = 1;
    return 0;
}

int main() {
    if (!fgets(input, MAX, stdin)) {
        printf("ERROR\n");
        return 0;
    }

    pos = 0;
    int result = parseTree();
    char c = nextChar();

    if (errorFlag || c != '\0') printf("ERROR\n");
    else if (result) printf("TRUE\n");
    else printf("FALSE\n");

    return 0;
}