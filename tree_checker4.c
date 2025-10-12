#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* insert(Node* root, int v) {
    if (!root) {
        Node* n = malloc(sizeof(Node));
        n->data = v; n->left = n->right = NULL;
        return n;
    }
    if (v < root->data) root->left = insert(root->left, v);
    else root->right = insert(root->right, v);
    return root;
}

int search_bst(Node* root, int key, int* c) {
    (*c)++;
    if (!root) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search_bst(root->left, key, c);
    else return search_bst(root->right, key, c);
}

int linear_search(int arr[], int n, int key, int* c) {
    for (int i = 0; i < n; i++) {
        (*c)++;
        if (arr[i] == key) return i;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    int arr[100];
    for (int i = 0; i < 100; i++) arr[i] = rand() % 1001;

    Node* root = NULL;
    for (int i = 0; i < 100; i++) root = insert(root, arr[i]);

    int target = arr[rand() % 100];
    printf("찾을 숫자: %d\n", target);

    int c1 = 0, c2 = 0;
    clock_t s, e;

    s = clock();
    linear_search(arr, 100, target, &c1);
    e = clock();
    double t1 = (double)(e - s) / CLOCKS_PER_SEC;

    s = clock();
    search_bst(root, target, &c2);
    e = clock();
    double t2 = (double)(e - s) / CLOCKS_PER_SEC;

    printf("[선형탐색] 횟수:%d  시간:%f초\n", c1, t1);
    printf("[BST탐색]  횟수:%d  시간:%f초\n", c2, t2);

    return 0;
}
