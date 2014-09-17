#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

/* integer polynomial using list */
typedef int ElementType;

/*** Declarations ***/

/* Node */
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Polynomial;
typedef PtrToNode Position;

struct Node
{
	ElementType m_coefficient;
	ElementType m_exponent;
	Position m_next;
};

/*** Declarations ***/

/*** Create ***/

/* Create a node, return position */
Position createNode();
/* Create a zero polynomial, that is 0*x^0, return header */
Polynomial createPolynomial();
/* Create a polynomial from array */
/* Array format: Coefficient_1, Exponent_1, Coefficient_2, Exponent_2, ..., also note that the array size is even */
/* Example: 1+5*x^14+10*x^1000 is represented in array as 1,0,5,14,10,1000 */
Polynomial createPolynomialFromArray(ElementType array[], int length);
/* Clone a polynomial, return the new polynomial */
Polynomial clonePolynomial(Polynomial poly1);
/* Delete all terms of a polynomial */
void deletePolynomial(Polynomial poly);
/* Destroy a polynomial */
void destroyPolynomial(Polynomial poly);

/*** Create ***/

/*** Sort ***/

/* Swap Field 'm_coefficient' and Field 'm_exponent' in two Positions */
void swapNode(Position pos1, Position pos2, Polynomial poly);
/* Bubble sort on a polynomial, ascending in Field 'm_exponent' */
void bubbleSortPolynomial(Polynomial poly);

/*** Sort ***/

/*** Arithmetic ***/

/* Sort (ascending in exponent) and simplify a polynomial */
void simplifyPolynomial(Polynomial poly);
/* 'poly=poly1+poly2' */
void addPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2);
/* 'poly=poly+poly1' */
void addPolynomialInPlace(Polynomial poly, Polynomial poly1);
/* 'poly1=-poly1' */
void minusPolynomial(Polynomial poly1);
/* 'poly=poly1-poly2' */
void subtractPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2);
/* 'poly=poly-poly1' */
void subtractPolynomialInPlace(Polynomial poly, Polynomial poly1);
/* 'poly1=k*poly1' */
void multiplyKPolynomial(Polynomial poly1, ElementType k);
/* 'poly1=poly1*term' */
void multiplyTermPolynomial(Polynomial poly1, Position term);
/* 'poly=poly1*poly2' */
void multiplyPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2);

/*** Arithmetic ***/

/*** Utility ***/

/* Return header of a polynomial */
Position getHeaderNode(Polynomial poly);
/* Return Position of first Node */
Position getFirstNode(Polynomial poly);
/* Return Position of last Node */
Position getLastNode(Polynomial poly);
/* Return Position after 'pos' */
Position advanceNode(Position pos);
/* get Exponent at 'pos' */
ElementType getNodeExponent(Position pos);
/* get Coefficient at 'pos' */
ElementType getNodeCoefficient(Position pos);
/* get order of 'poly' */
int getPolynomialOrder(Polynomial poly);
/* get coefficient array of 'poly', descending in Field 'm_exponent' */
void getPolynomialCoeffArray(ElementType coeff_array[], Polynomial poly, int order);
/* Return length of a polynomial, header not counted */
int getPolynomialLength(Polynomial poly);
/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, Polynomial poly);
/* Print a polynomial */
void printPolynomial(Polynomial poly);
/* Evaluate a polynomial at value 'val' */
ElementType evalPolynomial(Polynomial poly, int order, ElementType val);

/*** Utility ***/

#endif /* POLYNOMIAL_H */
