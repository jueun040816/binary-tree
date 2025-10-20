#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

Node* insert(Node* root, int key) {
    if (!root) return newNode(key);
    if (key < root->key) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

int searchArray(int arr[], int key) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        cnt++;
        if (arr[i] == key) break;
    }
    return cnt;
}

int searchBST(Node* root, int key) {
    int cnt = 0;
    while (root) {
        cnt++;
        if (key == root->key) break;
        root = (key < root->key) ? root->left : root->right;
    }
    return cnt;
}

void makeData(int arr[], int type) {
    if (type == 1) { // 무작위
        int pool[10001];
        for (int i = 0; i <= 10000; i++) pool[i] = i;
        for (int i = 0; i < N; i++) {
            int r = rand() % (10001 - i);
            arr[i] = pool[r];
            pool[r] = pool[10000 - i];
        }
    } else if (type == 2) { // 오름차순
        for (int i = 0; i < N; i++) arr[i] = i;
    } else if (type == 3) { // 내림차순
        for (int i = 0; i < N; i++) arr[i] = 999 - i;
    } else { // 공식형
        for (int i = 0; i < N; i++) arr[i] = i * (i % 2 + 2);
    }
}

int main() {
    srand(time(NULL));
    int data[N], query[N];
    for (int t = 1; t <= 4; t++) {
        makeData(data, t);
        Node* bst = NULL;
        for (int i = 0; i < N; i++) bst = insert(bst, data[i]);
        for (int i = 0; i < N; i++) query[i] = rand() % 10001;

        double arrSum = 0, bstSum = 0;
        for (int i = 0; i < N; i++) {
            arrSum += searchArray(data, query[i]);
            bstSum += searchBST(bst, query[i]);
        }

        printf("데이터 (%d): Array %.2f회, BST %.2f회\n",
               t, arrSum / N, bstSum / N);
    }
    return 0;
}
