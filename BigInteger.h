#ifndef _BigInteger_h
#define _BigInteger_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 1001

struct node 
{
    int data;
    struct node* next;
};

struct BigInteger 
{
    struct node* l;
    int length;
    int sign;
};

void addatfront(struct node** , int);
struct BigInteger initialize(char*);
void display(struct BigInteger );
struct BigInteger add(struct BigInteger , struct BigInteger );
struct BigInteger sub(struct BigInteger, struct BigInteger );
struct BigInteger mul(struct BigInteger, struct BigInteger );
struct BigInteger div1(struct BigInteger, struct BigInteger);
// struct BigInteger divideBy2(struct BigInteger num);
// struct BigInteger createBigInteger(int length, int* digits);
struct BigInteger rev(struct BigInteger );
struct BigInteger length(struct BigInteger );
struct node* insert(int );
struct BigInteger mod(struct BigInteger, struct BigInteger);
#endif
