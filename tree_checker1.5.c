#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000
char s[MAX]; int i,l;

void sp(){while(i<l&&isspace(s[i]))i++;}

int node(){
    sp(); if(i>=l||s[i]!='(')return 0; i++;
    sp(); if(i>=l||!isalpha(s[i]))return 0; i++;
    int c=0;
    while(1){
        sp();
        if(i<l&&s[i]=='('){if(++c>2||!node())return 0;}
        else if(i<l&&isalpha(s[i])){if(++c>2)return 0; i++;}
        else break;
    }
    sp(); if(i>=l||s[i]!=')')return 0; i++;
    return 1;
}

int main(){
    if(!fgets(s,MAX,stdin))return 0;
    l=strlen(s); i=0;
    int r=node(); sp();
    printf((r&&i==l)?"TRUE\n":"FALSE\n");
    return 0;
}