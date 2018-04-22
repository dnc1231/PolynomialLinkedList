#include<stdio.h>
#include<string.h>
#include "Poly.h"


int main() {

    // test 1, makePoly and stringPoly
    double test;
    int roots;
    char *string;
    Poly p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    bool equal;

    p1 = makePoly("-x^2 - x - 1");
    string = stringPoly(p1);
    p2 = makePoly("-2x + 6");
    p3 = polyCopy(p1);
    test = polyEval(p1, 2);
    printf("%f", test);
    p5 = makePoly("-2x + 1");
    p6 = makePoly("2x + 1");
    p4 = polyMult(p5, p6);
    p7 = makePoly("-3x^3 - 2x + 1");
    addTerm(p7, 7, 5);
    roots = realRoots(p1);
    string = stringPoly(p7);
    p8 = polyAdd(p1, p2);
    p9 = makePoly("3x^2 + 3x + 1");
    p10 = makePoly("3x^2 + 2x + 1");
    equal = polyEqual(p9, p10);
    deletePoly(p2);
    deletePoly(p1);
    deletePoly(p3);
    deletePoly(p4);
    deletePoly(p5);
    deletePoly(p6);
    deletePoly(p7);
    deletePoly(p8);
    deletePoly(p9);
    deletePoly(p10);

/*
    if(strcmp(stringPoly(p1), "3x^2 + 5x + 2") == 0 && strcmp(stringPoly(p2), "-2x + 6") == 0) {
        printf("Test 1 makePoly and stringPoly: passed\n");
    }
    else{
        printf("Test1 makePoly and stringPoly: failed\n");
    }


    // test 2, polyMult
    Poly ans = polyMult(p1, p2);
    if(strcmp(stringPoly(ans), "-6x^3 + 8x^2 + 26x + 12") == 0) {
        printf("Test2 polyMult: passed\n");
    }
    else{
        printf("Test 2 polyMult: failed\n");
    }*/

}




