#include "vld.h"

#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	/* Declarations */
	/* Test 'create' and 'clone' */
	Polynomial poly, poly_clone;
	/* Test 'add', 'minus', 'subtract' */
	Polynomial poly_1, poly_2;
	/* Test 'multiply' */
	Polynomial poly_3;
	/* Test 'eval' */
	Polynomial poly_4;
	ElementType poly_arr[]={-1,0,5,14,-10,1000};
	ElementType poly_1_arr[]={3,2,4,4,5,2};
	ElementType poly_2_arr[]={7,2,5,4};
	ElementType poly_4_arr[]={1,5,-4,4,7,3,-5,2,-2,0};
	int order;
	int val;
	ElementType result;

	printf("Create a zero polynomial:\n");
	poly=createPolynomial();
	printPolynomial(poly);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly);

	printf("Create polynomial from array:\n");
	poly=createPolynomialFromArray(poly_arr, 6);
	printPolynomial(poly);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly);

	printf("Clone a polynomial:\n");
	poly=createPolynomialFromArray(poly_arr, 6);
	printf("Original polynomial:\n");
	printPolynomial(poly);
	poly_clone=clonePolynomial(poly);
	printf("New polynomial:\n");
	printPolynomial(poly_clone);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly);
	destroyPolynomial(poly_clone);

	printf("Apply bubble sort on a polynomial:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	printf("Before bubble sort:\n");
	printPolynomial(poly_1);
	bubbleSortPolynomial(poly_1);
	printf("After bubble sort:\n");
	printPolynomial(poly_1);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_1);

	printf("Simplify a polynomial:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	printf("Before simplify:\n");
	printPolynomial(poly_1);
	simplifyPolynomial(poly_1);
	printf("After simplify:\n");
	printPolynomial(poly_1);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_1);

	printf("Add polynomials:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	poly_2=createPolynomialFromArray(poly_2_arr, 4);
	printf("Polynomial 1:\n");
	printPolynomial(poly_1);
	printf("Polynomial 2:\n");
	printPolynomial(poly_2);
	poly_3=createPolynomial();
	addPolynomial(poly_3, poly_1, poly_2);
	printf("Addition result:\n");
	printPolynomial(poly_3);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_3);

	printf("Minus a polynomial:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	printf("Before minus:\n");
	printPolynomial(poly_1);
	minusPolynomial(poly_1);
	printf("After minus:\n");
	printPolynomial(poly_1);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_1);

	printf("Subtract polynomials:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	poly_2=createPolynomialFromArray(poly_2_arr, 4);
	printf("Polynomial 1:\n");
	printPolynomial(poly_1);
	printf("Polynomial 2:\n");
	printPolynomial(poly_2);
	poly_3=createPolynomial();
	subtractPolynomial(poly_3, poly_1, poly_2);
	printf("Subtraction result:\n");
	printPolynomial(poly_3);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_3);

	printf("Multiply polynomials:\n");
	poly_1=createPolynomialFromArray(poly_1_arr, 6);
	poly_2=createPolynomialFromArray(poly_2_arr, 4);
	printf("Polynomial 1:\n");
	printPolynomial(poly_1);
	printf("Polynomial 2:\n");
	printPolynomial(poly_2);
	poly_3 = createPolynomial();
	multiplyPolynomial(poly_3, poly_1, poly_2);
	printf("Multiplication result:\n");
	printPolynomial(poly_3);
	printf("\n");
	/* Cleanup memory */
	destroyPolynomial(poly_1);
	destroyPolynomial(poly_2);
	destroyPolynomial(poly_3);

	printf("Evaluate a polynomial: \n");
	poly_4=createPolynomialFromArray(poly_4_arr, 10);
	printf("Polynomial: \n");
	printPolynomial(poly_4);
	order=getPolynomialOrder(poly_4);
	printf("Order: %d\n", order);
	val=3;
	printf("Evaluation at value %d: \n", val);
	result=evalPolynomial(poly_4, order, val);
	printf("Result: %d\n", result);
	/* Cleanup memory */
	destroyPolynomial(poly_4);

	return 0;
}
