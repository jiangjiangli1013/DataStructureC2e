#include "polynomial.h"
#include "fatal.h"

#include <stdlib.h>

/* Create a node, return position */
Position createNode()
{
	Position pos;
	pos=(struct Node* ) malloc(sizeof(struct Node));

	return pos;
}

/* Create a zero polynomial, that is 0*x^0, return header */
Polynomial createPolynomial()
{
	/* the result polynomial */
	Polynomial poly;
	/* iterator for L */
	Position pos;
	/* tmp Node for insertion */
	Position tmp_cell;

	poly=createNode();
	pos=poly;
	tmp_cell=createNode();
	tmp_cell->m_coefficient=0;
	tmp_cell->m_exponent=0;
	poly->m_next=tmp_cell;
	tmp_cell->m_next=NULL;
	return poly;
}

/* Create a polynomial from array */
/* Array format: Coefficient_1, Exponent_1, Coefficient_2, Exponent_2, ..., also note that the array size is even */
/* Example: 1+5*x^14+10*x^1000 is represented in array as 1,0,5,14,10,1000 */
Polynomial createPolynomialFromArray(ElementType array[], int length)
{
	/* the result polynomial */
	Polynomial poly;
	/* iterator for 'poly' */
	Position pos;
	/* tmp node for insertion */
	Position tmp_cell;
	/* iterator for array */
	int i;

	poly=createNode();
	pos=poly;
	for(i=0;i<length/2;i++)
	{
		tmp_cell=createNode();
		tmp_cell->m_coefficient=array[2*i];
		tmp_cell->m_exponent=array[2*i+1];
		pos->m_next=tmp_cell;
		pos=tmp_cell;
	}
	pos->m_next=NULL;
	
	return poly;
}

/* Clone a polynomial, return the new polynomial */
Polynomial clonePolynomial(Polynomial poly1)
{
	/* the result polynomial */
	Polynomial poly;
	/* iterator for 'poly' */
	Position pos;
	/* iterator for 'poly1' */
	Position pos1;
	/* tmp node for insertion */
	Position tmp_cell;

	/* create header for new polynomial */
	poly=createNode();
	/* point to the header of new polynomial */
	pos=poly;
	/* point to the first element of original polynomial */
	pos1=poly1->m_next;
	while(pos1!=NULL)
	{
		/* copy 'm_coefficient' and 'm_exponent' from 'poly1' */
		tmp_cell=createNode();
		tmp_cell->m_coefficient=pos1->m_coefficient;
		tmp_cell->m_exponent=pos1->m_exponent;
		/* append 'tmp_cell' */
		pos->m_next=tmp_cell;
		/* increment iterators */
		pos1=advanceNode(pos1);
		pos=advanceNode(pos);
	}
	/* add last 'NULL' node */
	tmp_cell->m_next=NULL;

	return poly;
}

/* Delete all terms of a polynomial */
void deletePolynomial(Polynomial poly)
{
	Position pos, tmp_cell;

	pos=poly->m_next; /* header assumed */
	poly->m_next=NULL;
	while(pos!=NULL)
	{
		tmp_cell=pos->m_next;
		free(pos);
		pos=tmp_cell;
	}
}

/* Destroy a polynomial */
void destroyPolynomial(Polynomial poly)
{
	deletePolynomial(poly);
	free(poly);
}

/* Swap Field 'm_coefficient' and Field 'm_exponent' in two Positions */
void swapNode(Position pos1, Position pos2, Polynomial poly)
{
	ElementType tmp;

	tmp=pos1->m_coefficient;
	pos1->m_coefficient=pos2->m_coefficient;
	pos2->m_coefficient=tmp;
	tmp=pos1->m_exponent;
	pos1->m_exponent=pos2->m_exponent;
	pos2->m_exponent=tmp;
}

/* Bubble sort on a polynomial, ascending in Field 'm_exponent' */
void bubbleSortPolynomial(Polynomial poly)
{
	/* iterators for L */
	Position pos1, pos2;
	/* tmp node for deletion */
	Position tmp_cell;
	/* counter */
	int pass;

	/* the last pass is not needed, so the last node is omitted (when pos1->Next==NULpoly) */
	/* after every pass, a large value is bubbled to the last part of the array */ 
	pos1=poly->m_next;
	pass=0;
	while(pos1->m_next!=NULL)
	{
		pos2=poly->m_next;
		/* some last elements are already sorted, so we sort elements up to Position of index 'getPolynomialLength(poly)-pass' */
		/* 'pos2, pos2->m_next', so we operate 'pos2' on Position of index '1' to Position of index 'getPolynomialLength(poly)-pass' */
		tmp_cell=poly->m_next;
		while(getNodeIndex(tmp_cell,poly)!=getPolynomialLength(poly)-pass)
		{
			tmp_cell=advanceNode(tmp_cell);
		}
		while(pos2!=tmp_cell)
		{
			if(pos2->m_exponent>pos2->m_next->m_exponent)
			{
				swapNode(pos2, pos2->m_next, poly);
			}
			pos2=advanceNode(pos2);
		}
		pos1=advanceNode(pos1);
		pass++;
	}
}

/* Sort (ascending in exponent) and simplify a polynomial */
void simplifyPolynomial(Polynomial poly)
{
	/* iterators for 'poly' */
	Position pos1, pos2;
	/* tmp node for deletion */
	Position tmp_cell;

	/* sort it first */
	bubbleSortPolynomial(poly);

	/* first 'pos1' is set to the first node, 'pos2' the second */
	pos1=poly->m_next;
	pos2=pos1->m_next;
	/* note that comparing NULL is nonsense */
	while(pos1!=NULL)
	{
		/* comparing Exponent of 'pos1' and 'pos2', */
		/* as long as 'pos1' and 'pos2' have same exponent, merge their coefficients, and delete 'pos2', */
		/* also note that comparing NULL is nonsense */  
		while(pos2!=NULL && getNodeExponent(pos1)==getNodeExponent(pos2))
		{
			pos1->m_coefficient=pos1->m_coefficient+pos2->m_coefficient;
			/* delete pos2 */
			tmp_cell=pos1->m_next;
			pos1->m_next=tmp_cell->m_next; /* Bypass deleted cell */
			free(tmp_cell);
			/* for debugging */ 
			/* Print(poly); */
			/* set 'pos2' as the next Node of 'pos1' */
			pos2=pos1->m_next;
		}
		pos1=advanceNode(pos1);
		/* set 'pos2' as the next Node of 'pos1', also beware of when 'pos1' is NULL */
		if(pos1!=NULL)
		{
			pos2=pos1->m_next;
		}
	} 

	/* discard the leading '0' if exists */
	if(poly->m_next->m_coefficient==0)
	{
		tmp_cell=poly->m_next;
		poly->m_next=tmp_cell->m_next;
		free(tmp_cell);
	}
}

/* 'poly=poly1+poly2' */
/* Connect 'poly1' and 'poly2' to 'poly' */
void addPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2)
{
	/* the last node of 'poly', 
	   the first node of 'poly1',
	   The last node of 'poly1',
	   the first node of 'poly2' 
	*/
	Position poly_last, poly1_first, poly1_last, poly2_first;

	/* the last node of 'poly' */
	poly_last=getLastNode(poly);

	/* the first node of poly1 */
	poly1_first=getFirstNode(poly1);

	/* the last node of 'poly1' */
	poly1_last=getLastNode(poly1);

	/* the first node of 'poly2' */
	poly2_first=getFirstNode(poly2);

	/* connect them together */
	poly_last->m_next=poly1_first;
	poly1_last->m_next=poly2_first;

	/* delete the bypassed dummy headers, 'poly1' and 'poly2' */
	free(poly1);
	free(poly2);

	/* simplify the connected polynomial */
	simplifyPolynomial(poly);
}

/* 'poly=poly+poly1' */
void addPolynomialInPlace(Polynomial poly, Polynomial poly1)
{
	/* the last node of 'poly', 
	   the first node of 'poly1',
	   The last node of 'poly1',
	*/
	Position poly_last, poly1_first, poly1_last;

	/* the last node of 'poly' */
	poly_last=getLastNode(poly);

	/* the first node of 'poly1' */
	poly1_first=getFirstNode(poly1);

	/* the last node of 'poly1' */
	poly1_last=getLastNode(poly1);

	/* connect them together */
	poly_last->m_next=poly1_first;

	/* delete the bypassed dummy header, poly1 */
	free(poly1);

	/* simplify the connected polynomial */
	simplifyPolynomial(poly);
}

/* 'poly1=-poly1' */
/* Modify 'poly1' in-place */
void minusPolynomial(Polynomial poly1)
{
	multiplyKPolynomial(poly1, -1);
}

/* 'poly=poly1-poly2' */
void subtractPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2)
{
	minusPolynomial(poly2);
	addPolynomial(poly, poly1, poly2);
}

/* 'poly=poly-poly1' */
void subtractPolynomialInPlace(Polynomial poly, Polynomial poly1)
{
	minusPolynomial(poly1);
	addPolynomialInPlace(poly, poly1);
}

/* 'poly1=k*poly1' */
/* Modify 'poly1' in-place */
void multiplyKPolynomial(Polynomial poly1, ElementType k)
{
	/* iterator for 'poly1' */
	Position pos1;

	/* transverse the polynomial and multiply 'k' to every coefficient */
	pos1=poly1->m_next;
	while(pos1!=NULL)
	{
		pos1->m_coefficient*=k;
		pos1=advanceNode(pos1);
	}
}

/* 'poly1=poly1*term' */
/* Modify 'poly1' in-place */
void multiplyTermPolynomial(Polynomial poly1, Position term)
{
	/* iterator for 'poly1' */
	Position pos1;

	/* transverse the polynomial and multiply every term with 'term' */
	pos1=poly1->m_next;
	while(pos1!=NULL)
	{
		pos1->m_coefficient*=term->m_coefficient;
		pos1->m_exponent+=term->m_exponent;
		pos1=advanceNode(pos1);
	}
}

/* 'poly=poly1*poly2' */
void multiplyPolynomial(Polynomial poly, Polynomial poly1, Polynomial poly2)
{
	/* tmp term */
	Polynomial tmp_term;
	/* iterator for poly2 */
	Position pos2;


	/* simplify polynomials first */
	simplifyPolynomial(poly1);
	simplifyPolynomial(poly2);

	pos2=poly2->m_next;
	while(pos2!=NULL)
	{
		tmp_term=clonePolynomial(poly1);
		multiplyTermPolynomial(tmp_term, pos2);

		addPolynomialInPlace(poly, tmp_term);

		pos2=advanceNode(pos2);
	}
}

/* Return header of a polynomial */
Position getHeaderNode(Polynomial poly)
{
	return poly;
}

/* Return Position of first Node */
Position getFirstNode(Polynomial poly)
{
	return poly->m_next;
}

/* Return Position of last Node */
Position getLastNode(Polynomial poly)
{
	Position poly_last;

	/* find the last node of 'poly' */
	poly_last=poly->m_next;
	while(poly_last->m_next!=NULL)
	{
		poly_last=advanceNode(poly_last);
	}

	return poly_last;
}

/* Return Position after 'pos' */
Position advanceNode(Position pos)
{
	return pos->m_next;
}

/* Retrieve Element at 'pos' */
ElementType getNodeExponent(Position pos)
{
	return pos->m_exponent;
}

/* Retrieve Coefficient at 'pos' */
ElementType getNodeCoefficient(Position pos)
{
	return pos->m_coefficient;
}

/* get order of 'poly' */
int getPolynomialOrder(Polynomial poly)
{
	Position pos;
	int order=0;

	/* 'pos' point to the first Node */
	pos=poly->m_next;
	while(pos!=NULL)
	{
		if(pos->m_coefficient!=0 && pos->m_exponent>order)
		{
			order=pos->m_exponent;
		}
		pos=advanceNode(pos);
	}

	return order;
}

/* get coefficient array of 'poly', descending in Field 'm_exponent' */
void getPolynomialCoeffArray(ElementType coeff_array[], Polynomial poly, int order)
{
	Position pos;
	int i;
	simplifyPolynomial(poly);

	for(i=0;i<order+1;i++)
	{
		coeff_array[i]=0;
	}

	pos=poly->m_next;
	while(pos!=NULL)
	{
		coeff_array[order-pos->m_exponent]=pos->m_coefficient;
		pos=advanceNode(pos);
	}
}

/* Return length of a polynomial, header not counted */
int getPolynomialLength(Polynomial poly)
{
	int count=0;
	Position pos_count;

	/* 'pos_count' point to the first Element */
	pos_count=poly->m_next;
	while(pos_count!=NULL)
	{
		pos_count=advanceNode(pos_count);
		count++;
	}

	return count;
}

/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, Polynomial poly)
{
	/* check whether 'pos' exists */
	if(pos!=NULL)
	{
		int count=0;
		Position pos_count;

		/* 'pos_count' point to the Node header */
		pos_count=poly;
		while(pos_count!=NULL && pos_count!=pos)
		{
			pos_count=advanceNode(pos_count);
			count++;
		}
		return count;
	}
	else
	{
		/* 'pos' is not in list */
		return -1;
	}
}

/* Print a polynomial */
void printPolynomial(Polynomial poly)
{
	Position pos;

	pos=poly->m_next;
	while(pos!=NULL)
	{
		if(pos!=poly->m_next)
		{
			if(pos->m_coefficient>=0)
			{
				printf("+");
			}
		}
		printf("%d*x^%d", pos->m_coefficient, pos->m_exponent);
		pos=advanceNode(pos);
	}
	printf("\n");
}

/* Evaluate a polynomial at value 'Val' */
ElementType evalPolynomial(Polynomial poly, int order, ElementType val)
{
	ElementType result;
	int i;

	ElementType* coeff_array=(ElementType* ) malloc(sizeof(ElementType)*(order+1));
	getPolynomialCoeffArray(coeff_array, poly, order);

	printf("Coefficient array: \n");
	for(i=0;i<order+1;i++)
	{
		printf("%d ", coeff_array[i]);
	}
	printf("\n");

	result=coeff_array[0];

	for(i=1;i<order+1;i++)
	{
		result=val*result+coeff_array[i];
	}

	free(coeff_array);
	
	return result;
}
