#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/*
Defines structure for node of bst (int)
Contains - Value of node
	 - Pointer to left subtree
	 - Pointer to right subtree
*/
typedef struct _Node {
	int value;
	Node * leftChild;
	Node * rightChild;
} Node;

/*
Task 1 - Inserts a new leaf into the bst (int)
       - Also used to create root when root = NULL
       - Returns pointer to the new leaf if added successfully
       - Returns NULL if a duplicate node is found
*/
Node * insertNode(Node * root, int value) {
	//Stores pointer to current root node
	Node * currentRoot = root;
	//Stores pointer to newly added leaf
	Node * newLeaf = NULL;
	int inserted = 0;

	//If argument root is NULL
	if (currentRoot == NULL) {
		//Create root node
		newLeaf = (Node *)malloc(sizeof(Node));
		if (newLeaf == NULL) {
			exit(-1);
		}
		newLeaf -> value = value;
		newLeaf -> leftChild = NULL;
		newLeaf -> rightChild = NULL;
	} else {
		while (inserted == 0) {
			if (currentRoot -> value == value) { //If current root = value
				inserted = 1;
				return NULL;

			} else if (currentRoot -> value > value) { //If current root > value
				if (currentRoot -> leftChild != NULL) {
					currentRoot = currentRoot -> leftChild;
				} else {
 					newLeaf = (Node *)malloc(sizeof(Node));
					if (newLeaf == NULL) {
						exit(-1);
					}
					newLeaf -> value = value;
					newLeaf -> leftChild = NULL;
					newLeaf -> rightChild = NULL;

					currentRoot -> leftChild = newLeaf;
					inserted = 1;
				}

			} else if (currentRoot -> value < value) { //If current root < value
				if (currentRoot -> rightChild != NULL) {
					currentRoot = currentRoot -> rightChild;
				} else {
					newLeaf = (Node *)malloc(sizeof(Node));
					if (newLeaf == NULL) {
						exit(-1);
					}
					newLeaf -> value = value;
					newLeaf -> leftChild = NULL;
					newLeaf -> rightChild = NULL;

					currentRoot -> rightChild = newLeaf;
					inserted = 1;
				}
			}
		}
	}
	return newLeaf;
}

/*
Task 2 - Deletes a node from the bst
       - Returns pointer to the new root of the entire tree, after successful deletion of a node
       - Returns NULL if node to be deleted could not be found in the tree, or if root of entire tree was deleted
*/
Node * deleteNode(Node * root, int value) {
	//Stores pointer to current root node (sometimes node to be deleted)
	Node * currentRoot = root;
	//Stores pointer to parent of current node
	Node * previousNode = NULL;
	//Stores node to replace deleted node
	Node * newRoot = NULL;
	//Stores previous node when searching for leftmost node
	Node * previousLeftmost = NULL;

	int deleted = 0;
	int deleteRoot = 0;
	//Stores whether the current node is the left child (1) or right child (2)
	//of its parent - also stores if current node is the only node in the tree (0)
	int whichChild = 0;

	if (root -> value == value) {
		deleteRoot = 1;
	}

	while (deleted == 0) { //While node has not been deleted...

		if (currentRoot == NULL) { //**If reached end of tree**
			deleted = 1;
			return NULL;

		} else {	
			if (currentRoot -> value == value) { //**If current node is to be deleted**

				if (currentRoot -> rightChild != NULL) { //If has a rightChild

					//If rightChild of node to be deleted is the leftmost node of the right subtree
					if (currentRoot -> rightChild -> leftChild == NULL) { 
						newRoot = currentRoot -> rightChild;
						newRoot -> leftChild = currentRoot -> leftChild;

						free(currentRoot);
						currentRoot = NULL;
					} else {
						previousLeftmost = currentRoot;
						newRoot = currentRoot -> rightChild;

						//Locates leftmost node of right subtree
						while (newRoot -> leftChild != NULL) {
							previousLeftmost = newRoot;
							newRoot = newRoot -> leftChild;
						}
					
						//Add any right children that the replacement for the deleted node had
						//to the left branch of the node before it
						previousLeftmost -> leftChild = newRoot -> rightChild;
					
						newRoot -> leftChild = currentRoot -> leftChild;
						newRoot -> rightChild = currentRoot -> rightChild;

						free(currentRoot);
						currentRoot = NULL;
					}
					if (previousNode != NULL && whichChild == 1) { //If deleted node was a left child
						previousNode -> leftChild = newRoot;
					} else if (previousNode != NULL && whichChild == 2) { //If deleted node was a right child
						previousNode -> rightChild = newRoot;
					}
	
					deleted = 1;

				} else if (currentRoot -> leftChild != NULL) { //If has a leftChild, but no rightChild
					newRoot = currentRoot -> leftChild;
	
					free(currentRoot);
					currentRoot = NULL;

					if (previousNode != NULL && whichChild == 1) { //If deleted node was a left child
						previousNode -> leftChild = newRoot;
					} else if (previousNode != NULL && whichChild == 2) { //If deleted node was a right child
						previousNode -> rightChild = newRoot;
					}

					deleted = 1;

				} else { //If has no children
					free(currentRoot);
					currentRoot = NULL;

					if (previousNode != NULL && whichChild == 1) { //If deleted node was a left child
						previousNode -> leftChild = NULL;
					} else if (previousNode != NULL && whichChild == 2) { //If deleted node was a right child
						previousNode -> rightChild = NULL;
					}
					deleted = 1;
				}

			} else if (currentRoot -> value > value) { //**If node to be deleted should be in left subtree**
				previousNode = currentRoot;
				currentRoot = currentRoot -> leftChild;
				whichChild = 1;

			} else if (currentRoot -> value < value) { //**If node to be deleted should be in right subtree**
				previousNode = currentRoot;
				currentRoot = currentRoot -> rightChild;
				whichChild = 2;
			}
		}
	}

	if (deleteRoot == 0) { //If root of entire tree was not deleted
		return root;
	} else {
		return newRoot;
	}
}

/*
Task 3 - Prints all values of subtree from a root node
*/
void printSubtree(Node * N) {
	if (N != NULL) {
		//Prints all values in left subtree
		if (N -> leftChild != NULL) {
			printSubtree(N -> leftChild);
		}

		//Prints value of root
		printf("%d", N -> value);
		printf("\n");

		//Prints all values in right subtree
		if (N -> rightChild != NULL) {
			printSubtree(N -> rightChild);
		}
	}
}

/*
Task 4 - Returns the number of leaves in subtree, with root N
       - A root with no children has one leaf
*/
int countLeaves(Node * N) {
	if (N == NULL) { //If node doesnt exist
		return 0;
	} else {
		if (N -> leftChild == NULL && N -> rightChild == NULL) { //If node has no children (is a leaf)
			return 1;
		} else {
			//Counts leaves in left and right subtrees
			return countLeaves(N -> leftChild) + countLeaves(N -> rightChild);
		}
	}
}

/*
Task 5 - Deletes subtree rooted at root
       - Returns root of entire tree if value != root
       - Returns NULL if value = root
*/
Node* deleteSubtree(Node * root, int value) {
	//Stores current node in search/next node to be deleted during deletion of subtree
	Node * currentNode = root;
	Node * returnNode = NULL;
	Node * newRoot = NULL;
	int found = 0;

	//Search for root of subtree to be deleted
	while (found == 0) {
		if (currentNode == NULL) { //If root is not present in the tree
			found = 1;
			return NULL;
		} else if (currentNode -> value == value) { //If root has been found
			found = 1;
		} else if (currentNode -> value > value) { //If root should be in left subtree
			currentNode = currentNode -> leftChild;
		} else if (currentNode -> value < value) { //If root should be in right subtree
			currentNode = currentNode -> rightChild;
		}
	}

	//Delete every node in subtree
	if (currentNode -> leftChild != NULL) {
		returnNode = deleteSubtree(root, currentNode -> leftChild -> value);
	}
	if (currentNode -> rightChild != NULL) {
		returnNode = deleteSubtree(root, currentNode -> rightChild -> value);
	}
	newRoot = deleteNode(root, currentNode -> value);

	return newRoot;
}

/*
Task 6 - Returns the depth of node N in the tree rooted at root
       - Returns 0 if the root of the tree = node
       - Returns -1 if the node does not belong to the tree rooted at root
*/
int depth(Node * R, Node * N) {
	//Stores current node in search
	Node * currentNode = R;
	int depth = 0;
	int found = 0;
	
	while (found == 0) { //While node has not been found
		if (currentNode == NULL) { //If node cannot be found in tree
			depth = -1;
			found = 1;
		} else if (currentNode -> value == N -> value) { //If node has been found
			found = 1;
		} else if (N -> value < currentNode -> value) { //If node should be in left subtree
			depth = depth + 1;
			currentNode = currentNode -> leftChild;
		} else if (N -> value > currentNode -> value) { //If node should be in right subtree
			depth = depth + 1;
			currentNode = currentNode -> rightChild;
		}
	}

	return depth;
}

