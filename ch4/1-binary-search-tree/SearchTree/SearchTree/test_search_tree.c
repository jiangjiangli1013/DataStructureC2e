#include "vld.h"

#include "search_tree.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	/* Declarations */
	SearchTree tree;

	/* create a tree */
	tree=createTree();
	tree->m_elem=6;
	tree=insertNode(2,tree);
	tree=insertNode(8,tree);
	tree=insertNode(1,tree);
	tree=insertNode(4,tree);
	tree=insertNode(3,tree);
	printTree("tree.dot", tree);

	/* test 'insertNode' */
	printf("test 'insertNode'\n");
	tree=insertNode(1,tree);
	tree=insertNode(5,tree);
	printTree("tree_inserted.dot", tree);

	/* test 'deleteNode' */
	printf("test 'deleteNode'\n");
	tree=deleteNode(2,tree);
	printTree("tree_deleted.dot", tree);

	/* test 'findTreeMin' and 'findTreeMax' */
	printf("test 'findTreeMin' and 'findTreeMax'\n");
	printf("the smallest node is: %d\n", findTreeMin(tree)->m_elem);
	printf("the largest node is: %d\n", findTreeMax(tree)->m_elem);
	printf("\n");

	tree=makeTreeEmpty(tree);

	return 0;
}