#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

/* integer tree */
typedef int ElementType;

/* Node */
struct TreeNode;
typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;

struct TreeNode
{
	ElementType m_elem;
	SearchTree m_left;
	SearchTree m_right;
};

/* create a tree node, return position */
Position createNode();
/* create a tree, return root node */
SearchTree createTree();
/* empty a tree, return root node */
SearchTree makeTreeEmpty(SearchTree tree);
/* find 'x' in 'tree', return NULL if not found */
Position findNode(ElementType x, SearchTree tree);
/* find smallest node */
Position findTreeMin(SearchTree tree);
/* find largest node */
Position findTreeMax(SearchTree tree);
/* insert a new node, return root node of modified tree */
SearchTree insertNode(ElementType x, SearchTree tree);
/* delete a node, return root node of modified tree */
SearchTree deleteNode(ElementType x, SearchTree tree);
/* get element at 'pos' */
ElementType getNodeElem(Position pos);
/* print a tree as a png using graphviz */
void printTree(char* file_name, SearchTree tree);
/* helper function, add edge recursively (preorder) in output graphviz script */
void printTree_aux(char* file_name, SearchTree tree);
#endif /* SEARCH_TREE_H */
