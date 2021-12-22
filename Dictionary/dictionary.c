#define SIZE 7

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char key;
    int val;
    struct node *next;
} node;

node *newNode(char key, int val);
void append(node *hashtable[], char key, int val);
node *find(node *hashtable[], char key);
node *makeDict();
int romanToInt(char *s);

node *newNode(char key, int val) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    n->key = key;
    n->val = val;
    n->next = NULL;
    return n;
}

void append(node *hashtable[], char key, int val) {
    node *n = newNode(key, val);
    int i = 0;
    for (node *head = hashtable[0]; head; head = head->next) {
        if (head->key == key) {
            break;
        }
        i++;
    }
    hashtable[i] = n;
}

node *find(node *hashtable[], char key) {
    for (node *head = hashtable[0]; head; head = head->next) {
        if (head->key == key) {
            return head;
        }
    }
    return NULL;
}

node *makeDict(node *dict[]) {
    int val = 1;
    char symbols[SIZE] = "IVXLCDM";
    for (int i = 0; i < SIZE; i++) {
        append(dict, symbols[i], val);
        if (i % 2 == 1) {
            val *= 2;
        } else {
            val *= 5;
        }
    }
    return *dict;
}

int romanToInt(char *s){
    node *dict;
    node *hashtable[SIZE];
    dict = makeDict(hashtable);
    return 0;
}

int main(int argc, char *argv[]) {
    node *dict[SIZE];
    for (int i = 0; i < SIZE; i++) {
        dict[i] = NULL;
    }
    dict[0] = makeDict(dict);
    return 0;
}