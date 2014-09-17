typedef int* Polynomial;

#include "vld.h"

#include <iostream>
using namespace std;

Polynomial polyInit(int* arr, int order)
{
	Polynomial poly = new int[order+1];
	for(int i=0;i<order+1;i++)
	{
		poly[i]=arr[i];
	}

	return poly;
}

void polyDestroy(Polynomial poly)
{
	delete(poly);
}

int polyEval(Polynomial poly, int order, int val)
{
	int output = poly[0];

	for(int i=1;i<order+1;i++)
	{
		output=val*output+poly[i];
	}

	return output;
}

int main(int argc, char* argv[])
{
	int arr[] = {1,-4,7,-5,0,-2};
	Polynomial poly = polyInit(arr,5);
	int output = polyEval(poly,5,3);
	cout<<"result is: "<<output<<endl;
	polyDestroy(poly);

	return 0;
}