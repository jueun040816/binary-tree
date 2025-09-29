#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000

char tree[MAX];
int left[MAX], right[MAX], cnt=0;

int parse(char *s, int *p){
    while(s[*p]==' ') (*p)++;
    if(!s[*p]||s[*p]==')') return 0;
    char c=s[*p];
    int r=++cnt;
    tree[r]=c;
    left[r]=right[r]=0;
    (*p)++;
    while(s[*p]==' ') (*p)++;
    if(s[*p]=='('){
        (*p)++;
        left[r]=parse(s,p);
        while(s[*p]==' ') (*p)++;
        right[r]=parse(s,p);
        while(s[*p]==' ') (*p)++;
        if(s[*p]==')') (*p)++;
    }
    return r;
}

void preorder(int root){
    int stack[MAX], top=-1;
    stack[++top]=root;
    while(top>=0){
        int n=stack[top--];
        if(!n) continue;
        printf("%c ",tree[n]);
        if(right[n]) stack[++top]=right[n];
        if(left[n]) stack[++top]=left[n];
    }
}

void inorder(int root){
    int stack[MAX], top=-1, cur=root;
    while(cur||top>=0){
        while(cur){ stack[++top]=cur; cur=left[cur]; }
        cur=stack[top--];
        printf("%c ",tree[cur]);
        cur=right[cur];
    }
}

void postorder(int root){
    int s1[MAX], s2[MAX], t1=-1, t2=-1;
    s1[++t1]=root;
    while(t1>=0){
        int n=s1[t1--];
        if(!n) continue;
        s2[++t2]=n;
        if(left[n]) s1[++t1]=left[n];
        if(right[n]) s1[++t1]=right[n];
    }
    while(t2>=0) printf("%c ",tree[s2[t2--]]);
}

int main(){
    char s[MAX]; fgets(s,MAX,stdin);
    int p=0,r=parse(s,&p);
    printf("pre-order: "); preorder(r); printf("\n");
    printf("in-order: "); inorder(r); printf("\n");
    printf("post-order: "); postorder(r); printf("\n");
    return 0;
}
