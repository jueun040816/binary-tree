#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char v;
    struct Node *child, *sibling;
} Node;

char *p;

Node* newNode(char v) {
    Node* n = malloc(sizeof(Node));
    n->v = v;
    n->child = n->sibling = NULL;
    return n;
}

void skip() {
    while (*p == ' ' || *p == '\t') p++;
}

Node* parse() {
    skip();
    if (*p == '(') {
        p++; skip();
        if (*p == ')') { p++; return NULL; }

        Node *root = newNode(*p++), *last = NULL;

        while (1) {
            skip();
            if (*p == '(') {
                Node* c = parse();
                if (c) {
                    if (!root->child) root->child = c;
                    else last->sibling = c;
                    last = c;
                }
            } else if (isalpha(*p)) {
                Node* c = newNode(*p++);
                if (!root->child) root->child = c;
                else last->sibling = c;
                last = c;
            } else if (*p == ')') { p++; break; }
            else break;
        }
        return root;
    }
    return NULL;
}

int countNodes(Node* n) {
    return n ? 1 + countNodes(n->child) + countNodes(n->sibling) : 0;
}

int countLeaves(Node* n) {
    return n ? (!n->child) + countLeaves(n->child) + countLeaves(n->sibling) : 0;
}

int getHeight(Node* n) {
    int max = 0;
    for (Node* c = n ? n->child : NULL; c; c = c->sibling) {
        int h = getHeight(c) + 1;
        if (h > max) max = h;
    }
    return max;
}

int main() {
    char in[1000];
    scanf("%[^\n]", in);
    p = in;
    Node* root = parse();
    printf("%d,%d,%d\n", getHeight(root), countNodes(root), countLeaves(root));
}
