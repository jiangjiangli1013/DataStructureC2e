#include "search_tree.h"
#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

/* create a tree node, return position */
Position createNode()
{
	Position pos;

	pos=(struct TreeNode* ) malloc(sizeof(struct TreeNode));

	return pos;
}

/* create a tree, return root node */
SearchTree createTree()
{
	SearchTree tree;

	tree=createNode();
	if(tree==NULL)
	{
		reportFatalError("Out of space");
	}
	else
	{
		tree->m_left=NULL;
		tree->m_right=NULL;
	}

	return tree;
}

/* empty a tree, return root node */
SearchTree makeTreeEmpty(SearchTree tree)
{
	if(tree!=NULL)
	{
		makeTreeEmpty(tree->m_left);
		makeTreeEmpty(tree->m_right);
		free(tree);
	}

	return NULL;
}

/* find 'x' in 'tree', return NULL if not found */
Position findNode(ElementType x, SearchTree tree)
{
	if(tree==NULL)
	{
		return NULL;
	}
	if(x<tree->m_elem)
	{
		return findNode(x,tree->m_left);
	}
	else
	{
		if(x>tree->m_elem)
		{
			return findNode(x,tree->m_right);
		}
		else
		{
			return tree;
		}
	}
}

/* find smallest node */
Position findTreeMin(SearchTree tree)
{
	if(tree==NULL)
	{
		return NULL;
	}
	else
	{
		if(tree->m_left==NULL)
		{
			return tree;
		}
		else
		{
			return findTreeMin(tree->m_left);
		}
	}
}

/* find largest node */
Position findTreeMax(SearchTree tree)
{
	if(tree==NULL)
	{
		return NULL;
	}
	else
	{
		if(tree->m_right==NULL)
		{
			return tree;
		}
		else
		{
			return findTreeMax(tree->m_right);
		}
	}
}

/* insert a new node, return root node of modified tree */
SearchTree insertNode(ElementType x, SearchTree tree)
{
	if(tree==NULL)
	{
		/* create and return a one-node tree */
		tree=createTree();
		tree->m_elem=x;
	}
	else
	{

		if(x<tree->m_elem)
		{
			tree->m_left=insertNode(x,tree->m_left);
		}
		else
		{
			if(x>tree->m_elem)
			{
				tree->m_right=insertNode(x,tree->m_right);
			}
			/* else 'x' is in the tree already, we'll do nothing */
		}
	}

	return tree;
}

/* delete a node, return root node of modified tree */
SearchTree deleteNode(ElementType x, SearchTree tree)
{
	Position tmp_cell;

	if(tree==NULL)
	{
		reportError("Element not found");
	}
	else
	{
		if(x<tree->m_elem) /* go left */
		{
			tree->m_left=deleteNode(x, tree->m_left);
		}
		else
		{
			if(x>tree->m_elem) /* go right */
			{
				tree->m_right=deleteNode(x, tree->m_right);
			}
			else /* found element to be deleted */
			{
				if(tree->m_left && tree->m_right) /* two children */
				{
					/* replace with smallest in right tree */
					tmp_cell=findTreeMin(tree->m_right);
					tree->m_elem=tmp_cell->m_elem;
					tree->m_right=deleteNode(tree->m_elem, tree->m_right);
				}
				else /* one or zeo children */
				{
					tmp_cell=tree;
					if(tree->m_left==NULL) /* also handles 0 children */
					{
						tree=tree->m_right;
					}
					else
					{
						if(tree->m_right==NULL)
						{
							tree=tree->m_left;
						}
					}
					free(tmp_cell);
				}
			}
		}
	}

	return tree;
}

/* get element at 'pos' */
ElementType getNodeElem(Position pos)
{
	return pos->m_elem;
}

/* print a tree as a png using graphviz */
void printTree(char* file_name, SearchTree tree)
{
	/* file pointer */
	FILE* fp;

	/* file size */
	int size;

	/* open a file for reading and appending */
	fp=fopen(file_name, "a+");

	if(!fp)
	{
		fprintf(stderr, "unable to open file!\n");
		exit(1);
	}

	/* get file size */
	fseek(fp, 0, SEEK_END);
	size=ftell(fp);

	/* append file header when file is empty */
	if(!size)
	{
		fprintf(fp, "digraph G {\n");
		fprintf(fp, "graph [dpi=300] [ordering=\"out\"];\n");
		fprintf(fp, "margin=0.1;\n");
		fprintf(fp, "node [shape=circle];\n");
		fprintf(fp, "edge [arrowsize=0.8];\n");
	}

	/* close file */
	fclose(fp);

	/* add edge */
	printTree_aux(file_name, tree);

	/* open a file for reading and appending */
	fp=fopen(file_name, "a+");

	/* closing } */
	fprintf(fp, "}");

	/* close file */
	fclose(fp);
}

/* helper function, add edge recursively (preorder) in output graphviz script */
void printTree_aux(char* file_name, SearchTree tree)
{
	/* file pointer */
	FILE* fp;

	/* open a file for reading and appending */
	fp=fopen(file_name, "a+");

	if(!fp)
	{
		fprintf(stderr, "unable to open file!\n");
		exit(1);
	}

	/* transversal the tree */
	if(tree->m_left!=NULL && tree->m_right!=NULL)
	{
		fprintf(fp, "%d -> %d;\n", tree->m_elem, tree->m_left->m_elem);
		printTree_aux(file_name, tree->m_left);
		fprintf(fp, "%d -> %d;\n", tree->m_elem, tree->m_right->m_elem);
		printTree_aux(file_name, tree->m_right);
		fprintf(fp, "{rank=same; %d %d}\n", tree->m_left->m_elem, tree->m_right->m_elem);
	}
	
	if(tree->m_left!=NULL && tree->m_right==NULL)
	{
		fprintf(fp, "%d -> %d;\n", tree->m_elem, tree->m_left->m_elem);
		fprintf(fp, "%d -> NULL [style=invis];\n", tree->m_elem);
		fprintf(fp, "NULL [style=invis];\n");
		fprintf(fp, "{rank=same; %d NULL}\n", tree->m_left->m_elem);
	}

	if(tree->m_left==NULL && tree->m_right!=NULL)
	{
		fprintf(fp, "%d -> NULL [style=invis];\n", tree->m_elem);
		fprintf(fp, "%d -> %d;\n", tree->m_elem, tree->m_right->m_elem);
		fprintf(fp, "NULL [style=invis];\n");
		fprintf(fp, "{rank=same; NULL %d}\n", tree->m_right->m_elem);
	}

	/* close file */
	fclose(fp);
}