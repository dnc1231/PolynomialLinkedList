#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "Poly.h"

/* Student information for project: These functions aid in creating a linked list containing terms for polynomial functions
 *
 *
 * On my honor, Daniel Canterino, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Daniel Canterino
 * email address: dnc1231@verizon.net
 * UTEID: djc3323
 * Section 5 digit ID: 16115
 * Number of slip days used on this assignment: 0
 */


int getCoeff(const char string[]);
int getExpo(const char string[]);
void condense(Poly one);
void freeZeros(Poly one);

/*This function takes a string polynomial and converts it to the linked list structure created. It assumes there are
 * no negative exponents, the use of 'x' as the variable, all coefficients are non-zero terms, and there are spaces
 * separating the terms from one another. The function works by acquiring one polynomial term at a time until there are
 * none left and passing that term to getCoeff and getExpo to extract the coefficient and exponent to create the node
 * with.
 * Big O Analysis: O(N^2)*/
Poly makePoly(char *string){
    int i = 0; char term[100]; int nodeNumber = 1;
    struct node *cur = malloc(sizeof(struct node));
    struct polyType *first = malloc(sizeof(struct polyType));
    while (*(string+i) != '\0'){
        int j = 0;
        if ((*(string+i) == '-' || *(string+i) == '+') && i != 0){
            term[j] = *(string+i);
            j++; i+=2;//i+2 because we want to skip over the next space that will inevitably follow
        }
        while (*(string+i) != ' ' && *(string+i) != '\0'){
            term[j] = *(string+i);
            j++; i++;
        }
        term[j] = '\0';//null terminates the term array after the term string has been put in it
        int coeff = getCoeff(term);
        int expo = getExpo(term);
        cur->coeff = coeff;
        cur->exp = expo;
        if (*(string+i) == '\0'){
            cur->next = NULL;
            return (first);
        }
        struct node *next = malloc(sizeof(struct node));
        cur->next = next;
        if (nodeNumber == 1){
            first->list = cur;
        }
        cur = next;
        i++; nodeNumber++;
    }
}
/*This function is a helper function to make polynomial designed to acquire the coefficients for each term passed to it
 * Big O Analysis: O(N)*/
int getCoeff(const char string[]){
    int i = 0; char coeff[100]; bool isNeg = false;
    int j = 0;
    if (string[i] == '-' || string[i] == '+'){
        if (string[i] == '-'){
            isNeg = true;
        }
        i++;//skips the plus or minus sign
    }
    while ((string[i] != '\0') && (string[i] != 'x')){
        coeff[j] = string[i];
        i++; j++;
    }
    if (((string[i] == 'x') && (i == 0) || (string[i] == 'x') && (string[i-1] == '+'))){
        coeff[j] = '1';
    }
    if ((string[i-1] =='-') && string[i] == 'x'){
        coeff[j] = '1';
    }
    int value = atoi(coeff);
    if (isNeg){
        return (-value);
    }
    return (value);
}
/*This function is a helper function to make polynomial designed to acquire the exponent for each term passed to it
 * Big O Analysis: O(N)*/
int getExpo(const char string[]){
    int i = 0; char expo[100];
    while (string[i] != '\0' && string[i] != '^'){
        i++;
    }
    if (string[i-1] == 'x' && string[i] != '^'){
        return (1);
    }
    if (string[i] == '\0'){
        return (0);
    }
    else{
        int j = 0; i++;
        while (string[i] != '\0'){
            expo[j] = string[i];
            j++; i++;
        }
        expo[j] = '\0';
        return (atoi(expo));
    }
}
/*This function takes a pointer to a linked list polynomial and creates an exact copy of it stored at a different location
 * in memory
 * Big O Analysis: O(N)*/
Poly polyCopy(Poly first){
    struct node *cur, *copy, *new;
    struct polyType *pointer = malloc(sizeof(struct polyType));
    cur = first->list;
    copy = malloc(sizeof(struct node));
    pointer->list = copy;
    while (cur->next != NULL){
        copy->coeff = cur->coeff;
        copy->exp = cur->exp;
        new = malloc(sizeof(struct node));
        copy->next = new;
        copy = new;
        cur = cur->next;
    }
    copy->coeff = cur->coeff;
    copy->exp = cur->exp;
    copy->next = NULL;
    return (pointer);
}
/*This function takes a number and evaluates it based on the linked list polynomial function passed to it as well
 * Big O Analysis: O(N)*/
double polyEval(Poly first, double val){
    double sum = 0; int i; double expo;
    struct node *cur = first->list;
    while (cur->next != NULL){
        expo = 1; i = 0;
        while (i < cur->exp){
            expo = expo * val;
            i++;
        }
        sum += expo * cur->coeff;
        cur = cur->next;
    }
    expo = 1; i = 0;
    while (i < cur->exp){
        expo = expo * val;
        i++;
    }
    sum += expo * cur->coeff;
    return (sum);
}
/*This function takes two polynomial linked lists and adds them together and returns that new polynomial as a new linked
 * list. It does this by first creating a copy of the first polynomial passed to it, and then adding in each term of the
 * second polynomial with the add term function. This result is then condensed to combine all like terms and remove any
 * zero coefficient terms.
 * Big O Analysis: O(N^2)*/
Poly polyAdd(Poly one, Poly two){
    Poly add;
    struct node *cur = two->list;
    add = polyCopy(one);
    while (cur != NULL){
        addTerm(add, cur->coeff, cur->exp);
        cur = cur->next;
    }
    condense(add);
    return (add);
}
/*This function takes two polynomial linked lists and multiplies them together and reutrns that new polynomial as a new
 * linked list. It does this by iterating through each term in each polynomial and multiplying them and putting that
 * new term in the new linked list. This list is then condensed to remove any zero coefficients and combine any
 * created like exponentials.
 * Big O Analysis: O(N^2)*/
Poly polyMult(Poly one, Poly two){
    struct node *cur1, *cur2, *new;
    Poly mult = malloc(sizeof(Poly));
    cur1 = one->list;
    cur2 = two->list;
    new = malloc(sizeof(struct node));
    mult->list = new;
    while (cur1 != NULL){
        while (cur2 != NULL){
            new->exp = cur1->exp + cur2->exp;
            new->coeff = cur1->coeff * cur2->coeff;
            if ((cur1->next == NULL) && (cur2->next == NULL)){
                new->next = NULL;
                break;
            }
            new->next = malloc(sizeof(struct node));
            new = new->next;
            cur2 = cur2->next;
        }
        cur1 = cur1->next;
        cur2 = two->list;
    }
    condense(mult);
    return (mult);
}
/*This is a helper function created to take a linked list polynomial and combine any like terms or free/get rid of
 * any nodes with a zero coefficient
 * Big O Analysis: O(N^2)*/
void condense(Poly one){
    struct node *cur, *comp, *copy;
    cur = one->list;
    comp = one->list;
    while (cur != NULL){
        while (comp != NULL){
            if ((cur->exp == comp->exp) && (cur != comp)){
                cur->coeff = cur->coeff + comp->coeff;
                copy = comp;
                cur->next = comp->next;
                comp = comp->next;
                free(copy);
            }
            comp = comp->next;
        }
        comp = one->list;
        cur = cur->next;
    }
    freeZeros(one);
}
/*This is a helper function created to free any nodes that have zero as a coefficient in a linked list polynomial
 * Big O Analysis: O(N)*/
void freeZeros(Poly one){
    struct node *copy, *prev;
    struct node *cur = one->list;
    while (cur != NULL){
        if (cur->coeff == 0){
            copy = cur;
            prev->next = cur->next;
            free(copy);
            cur = prev->next;
        }
        prev = cur;
        cur = cur->next;
    }
}
/*This function takes a passed coefficient and exponential term and adds it to a linked list polynomial.
 * Big O Analysis: O(N)*/
void addTerm(Poly one, int coeff, int exponent){
    struct node *cur, *prev;
    cur = one->list;
    prev = one->list;
    while (cur->exp > exponent){//this loop looks for the location to which to add the node to
        prev = cur;
        cur = cur->next;
        if (cur == NULL){//case where the node needs to be added at the end of the list
            struct node *new = malloc(sizeof(struct node));
            new->coeff = coeff;
            new->exp = exponent;
            prev->next = new;
            new->next = NULL;
            return;
        }
    }
    if (cur->exp == exponent){//case where the exponent of the term already exists within the linked list
        cur->coeff = cur->coeff + coeff;
        freeZeros(one);
        return;
    }
    if (cur->exp < exponent && cur != one->list){//case where the new term needs to be added to the beginning of the list
        struct node *new = malloc(sizeof(struct node));
        new->coeff = coeff;
        new->exp = exponent;
        prev->next = new;
        new->next = cur;
        return;
    }
    else{//case where the node needs to be added between two existing nodes of the linked list
        struct node *new = malloc(sizeof(struct node));
        new->coeff = coeff;
        new->exp = exponent;
        new->next = cur;
        one->list = new;
    }
}
/*This function returns the number of real distinct roots in a polynomial linked list function that is of degree 2 or less
 * by passing it's a,b,and c coefficients into the quadratic formula to determine if the roots are real and distinct.
 * Big O Analysis: O(N)*/
int realRoots(Poly one){
    struct node *cur = one->list;
    int arr[3] = {0, 0, 0};//array for a,b,c for quadratic formula
    if (cur->exp >= 3){
        return (-1);
    }
    if (cur->exp == 2){
        while (cur != NULL){
            arr[cur->exp] = cur->coeff;
            cur = cur->next;
        }
        int quad = (arr[1] * arr[1]) - 4*(arr[0] * arr[2]);//quadratic formual discriminant determining number of roots
        if (quad == 0){
            return (1);
        }
        if (quad > 0){
            return (2);
        }
        if (quad < 0){
            return (0);
        }
    }
    if (cur->exp == 1){
        return (1);
    }
    if (cur->exp == 0){
        return (0);
    }
}
/*This function returns a pointer to a string of the passed polynomial linked list function returned in the same format
 * as the polynomial was initially passed by.
 * Big O Analysis: O(N)*/
char *stringPoly(Poly one){
    char *string = malloc(100 * sizeof(char));
    char term[100];
    struct node *cur = one->list;
    int i = 0;
    while (cur != NULL){
        if (cur->coeff > 0 && (i != 0)) {//adds the plus sign between terms since it is not explicitly distinguished in a positive integer string
            string[i] = '+';
            string[i+1] = ' ';
            i += 2;
        }
        sprintf(term,"%d", cur->coeff);
        int j = 0;
        while (term[j] != '\0'){//loop puts the coefficient in the string
            if ((term[j] == '-') && (i != 0)){//puts the negative sign in as a minus
                string[i] = term[j];
                string[i+1] = ' ';
                i+=2;
                j++;
            }
            if ((cur->coeff == -1) && (cur->exp != 0) && (term[j] != '1') && (string[i-2] != '-')){//accounts for case if first coeff is -1 (doesn't put any other number/coefficient
                string[i] = '-';
                i++;
                break;
            }
            if ((cur->coeff == 1)&& (cur->exp != 0)){//accounts for case where coeff = 1
                break;
            }
            if ((cur->coeff == -1) && (cur->exp != 0) && (term[j] == '1') && (string[i-2] == '-')){//accounts for cases where coeff is -1 not in first term
                break;
            }
            string[i] = term[j];//puts the term coefficient into the allocated string
            i++;
            j++;
        }
        if (cur->exp >= 1){//puts 'x' into the string if the exponent is not 0
            string[i] = 'x';
            i++;
            }
        if (cur->exp >= 2){//puts the exponential term into the string if the exponent is 2 or more
            string[i] = '^';
            i++;
            sprintf(term, "%d", cur->exp);
            j = 0;
            while (term[j] != '\0') {
                string[i] = term[j];
                i++;
                j++;
            }
        }
        string[i] = ' ';//separates the terms by spaces
        i++;
        cur = cur->next;
    }
    string[i-1] = '\0'; //corrects for extra space at end
    return (string);
}
/*This function returns the logic if 2 passed linked list polynomials are equal to one another comparing each term
 * in each polynomial to the other returning false if any are different.
 * Big O Analysis: O(N)*/
bool polyEqual(Poly one, Poly two){
    struct node *cur1, *cur2;
    bool areEqual = false;
    cur1 = one->list;
    cur2 = two->list;
    while ((cur1 != NULL) && (cur2 != NULL)){
        if ((cur1->coeff != cur2->coeff) || (cur1->exp != cur2 ->exp)){
            return(areEqual);
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if ((cur1 != NULL) || (cur2 !=NULL)){
        return(areEqual);
    }
    areEqual = true;
    return(areEqual);
}
/*This function deletes a linked list polynomial. It frees all its nodes from their allocated space in memory.
 * Big O Analysis: O(N)*/
void deletePoly(Poly one){
    struct node *cur, *copy;
    cur = one->list;
    while (cur != NULL){
        copy = cur->next;
        free(cur);
        cur = copy;
    }
    free(one);
    one = NULL;
}