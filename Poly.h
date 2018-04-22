#ifndef _Poly_h
#define _Poly_h 1

#include<stdbool.h>

struct node {
    int coeff;
    int exp;
    struct node *next;
};

struct polyType {
    struct node *list;  // Pointer to first node (for high-order term)
};
typedef struct polyType *Poly;

Poly makePoly(char *string);
Poly polyCopy(Poly first);
double polyEval(Poly first, double val);
Poly polyAdd(Poly one, Poly two);
Poly polyMult(Poly one, Poly two);
void addTerm(Poly one, int coeff, int exponent);
int realRoots(Poly one);
char *stringPoly(Poly one);
bool polyEqual(Poly one, Poly two);
void deletePoly(Poly one);

#endif
