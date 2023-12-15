//HW6 by Alexander Segarra
//NETID: asegarra 
// SUID 747437414

//CSE674 HW6  Due: 11:59PM, Dec. 12 Thursday
#include <iostream>
using namespace std;

class node {
public:
	node* parent;
	node* Lchild;
	node* Rchild;
	int value;
	bool color; //true: red, false: black
	bool Is_Lchild;//true if is Lchild of parent; else false	
	node() { parent = Lchild = Rchild = nullptr; Is_Lchild = true; }
	node(int i) { value = i; parent = Lchild = Rchild = nullptr; Is_Lchild = true; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }


	void R_rotate(node* p) {//R-rotate at node pointed by p
		node* newPar = p->Lchild;

		p->Lchild = newPar->Rchild;



		if (newPar->Rchild != nullptr) {   //update parent of Rchild of newPar
			newPar->Rchild->parent = p;
			newPar->Lchild->Is_Lchild = true;
		}

		newPar->parent = p->parent;		//newPar parent is whatever p's parent was

		if (p->parent == nullptr) {
			root = newPar;

		}
		else if (p == p->parent->Rchild) { //if p is the right child of its parent, make newPar right child of parent 
			p->parent->Rchild = newPar;
			newPar->Is_Lchild = false;
		}
		else {
			p->parent->Lchild = newPar; //make newPar left child of parent
			newPar->Is_Lchild = true;
		}

		newPar->Rchild = p; // make p the right child of new root
		p->parent = newPar; //update p's parent



		p->Is_Lchild = false;

		if (p->Lchild != nullptr) {
			p->Lchild->Is_Lchild = true;
		}

		if (p->Rchild != nullptr) {
			p->Rchild->Is_Lchild = false;
		}



	}
















	void L_rotate(node* p) { //L-rotate at node pointed by p 
		//R_rotate and L_rotate will be called by add_node, delete_node, delete_1, delete_2A, delete_2B, and delete_3.

		node* newPar = p->Rchild;

		p->Rchild = newPar->Lchild;

		if (newPar->Lchild != nullptr) {   //update parent of Lchild of newPar
			newPar->Lchild->parent = p;
			newPar->Lchild->Is_Lchild = true;
		}

		newPar->parent = p->parent;		//newPar parent is whatever p's parent was

		if (p->parent == nullptr) {
			root = newPar;
		}
		else if (p == p->parent->Lchild) { //if p is the left child of its parent, make newPar left child of parent 
			p->parent->Lchild = newPar;
			newPar->Is_Lchild = true;
		}
		else {
			p->parent->Rchild = newPar; //make newPar right child of parent
			newPar->Is_Lchild = false;

		}

		newPar->Lchild = p; // make p the left child of new root
		p->parent = newPar; //update p's parent


		
		// Update Is_Lchild for the children of p, if they exist
		p->Is_Lchild = true;
		if (p->Rchild != nullptr) {
			p->Rchild->Is_Lchild = false;
		}
		if (p->Lchild != nullptr) {
			p->Lchild->Is_Lchild = true;
		}


	}













	void add_node(int i) {//In case of a tie during the BST search, go to the branch with B child; else if both children are B, go to Right branch; else 
		// go to right branch.

		// Step 1: Find the proper BST location and insert a Red node
		node* newNode = new node(i);
		newNode->color = true; // new node is red

		node* y = nullptr;
		node* x = root;

		while (x != nullptr) {
			y = x;
			if (newNode->value < x->value)
				x = x->Lchild;
			else
				x = x->Rchild;
		}

		newNode->parent = y;
		if (y == nullptr) {
			root = newNode;
		}
		else if (newNode->value < y->value) {
			y->Lchild = newNode;
			newNode->Is_Lchild = true;
		}
		else {
			y->Rchild = newNode;
			newNode->Is_Lchild = false;
		}

		// Step 2: If the new node is the root, change it to Black and it is done
		if (newNode->parent == nullptr) {
			newNode->color = false; // root is always black
			newNode->Is_Lchild = false;
			return;
		}

		// Step 3: If the parent of this node is Black, it is done
		if (!newNode->parent->color) {
			return;
		}

		// Step 4: If the parent of this node is Red:
		while (newNode->parent != nullptr && newNode->parent->color) {
			node* grandparent = nullptr;
			node* uncle = nullptr;

			// Find grandparent and uncle of the new node
			if (newNode->parent->parent != nullptr) {
				grandparent = newNode->parent->parent;
				if (newNode->parent->Is_Lchild)
					uncle = grandparent->Rchild;
				else
					uncle = grandparent->Lchild;
			}

			// Case 1: If the uncle node is Black, perform either LL, LR, RR, or RL rotation
			if (uncle == nullptr || !uncle->color) {
				if (newNode->parent->Is_Lchild) {
					// Node is also a left child - LL rotation
					if (newNode->Is_Lchild) {
						R_rotate(grandparent);
						grandparent->color = true;
						newNode->parent->color = false;
						// Additional color changes if needed
					}
					// Node is a right child - LR rotation
					else {
						L_rotate(newNode->parent);
						grandparent->color = true;
						newNode->parent->color = false;


						R_rotate(grandparent);
						newNode->color = false;
						newNode->Rchild->color = true;
						break;
						// Additional color changes if needed
					}
				}
				// Node's parent is the right child of the grandparent
				else {
					// Node is also a right child - RR rotation
					if (!newNode->Is_Lchild) {
						L_rotate(grandparent);
						grandparent->color = true;
						newNode->parent->color = false;

						// Additional color changes if needed
					}
					// Node is a left child - RL rotation
					else {
						R_rotate(newNode->parent);
						grandparent->color = true;
						newNode->parent->color = false;


						L_rotate(grandparent);
						newNode->color = false;
						newNode->Lchild->color = true;
						break;
						// Additional color changes if needed
					}
				}
			}
			// Case 2: If the uncle node is Red, change color of parent, uncle, and grandparent nodes
			else {
				if (grandparent != nullptr) {
					grandparent->color = true;
					newNode->parent->color = false;
					uncle->color = false;

					// Move newNode pointer to grandparent for next iteration
					newNode = grandparent;
				}
			}
		}

		// Ensure the root is always black
		root->color = false;
		root->Is_Lchild = false;
	
	}








	void delete_1(node* p, bool b) {
		//Case 1 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.
		

		node* sibling = (b) ? p->Rchild : p->Lchild; // Get sibling based on boolean b

		if (b) { // Double black node is left child
			if (sibling->Rchild != nullptr && sibling->Rchild->color) { // RR Case
				L_rotate(p); 
				sibling->Rchild->color = sibling->color;
				sibling->color = p->color;
				p->color = false;
				
			}
			else if (sibling->Lchild != nullptr && sibling->Lchild->color) { // RL Case
				
				R_rotate(sibling);
				
				sibling->parent->color = sibling->color;
				sibling->color = sibling->parent->color;
				L_rotate(p);
				 // Original parent becomes red
				p->parent->Rchild->color = p->parent->color;
				p->parent->color = p->color;
				
				p->color = false;
				
				
			}
		}
		else { // Double black node is right child
			if (sibling->Lchild != nullptr && sibling->Lchild->color) { // LL Case
				R_rotate(p);
				sibling->Lchild->color = sibling->color;
				sibling->color = p->color;
				p->color = false;
				
			}
			else if (sibling->Rchild != nullptr && sibling->Rchild->color) { // LR Case
				L_rotate(sibling);

				sibling->parent->color = sibling->color;
				sibling->color = sibling->parent->color;

				R_rotate(p);

				p->parent->Lchild->color = p->parent->color;
				p->parent->color = p->color;

				p->color = false;
			}
		}

		root->color = false;

	}

	void delete_2B(node* p, bool b) {
		//Case 2B of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.
		
		node* sibling = (b) ? p->Rchild : p->Lchild; // find sibling


		// Change sibling to red
		sibling->color = true; 
		p->color = false; 



		root->color = false;

	}

	void delete_3(node* p, bool b) {
		//Case 3 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.
		

		node* sibling = b ? p->Rchild : p->Lchild;
		node* newDB =nullptr;

		if (b) {
			// Double black node is the left child, perform right rotation at parent
			L_rotate(p);
			newDB = p->Lchild;
			newDB->Is_Lchild = true;
		}
		else {
			// Double black node is the right child, perform left rotation at parent
			R_rotate(p);
			newDB = p->Rchild;
			newDB->Is_Lchild = false;
		}

		sibling->color = false; // Former sibling (now parent) is black
		p->color = true; 

		
		node* siblingOfNewDB = (newDB->Is_Lchild) ? newDB->parent->Rchild : newDB->parent->Lchild; // find sibling


		if (siblingOfNewDB->color) {		//sibling is red, case 3
			delete_3(newDB->parent, newDB->Is_Lchild);
		}
		else {								//sibling is black
			if ((siblingOfNewDB->Lchild != nullptr && siblingOfNewDB->Lchild->color) || (siblingOfNewDB->Rchild != nullptr && siblingOfNewDB->Rchild->color)) { // black sibling has a red child
				delete_1(newDB->parent, newDB->Is_Lchild);
			}
			else {				//
				if (newDB->parent->color) { // case 2b
					delete_2B(newDB->parent, newDB->Is_Lchild);
				}
				else {					// case 2a
					delete_2A(newDB->parent, newDB->Is_Lchild);
				}
			}
		}


		root->color = false;

	}



	void delete_2A(node* p, bool b) {
		//Case 2A of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.
		

		node* sibling = (b) ? p->Rchild : p->Lchild; // find sibling

		// Change sibling to red
		sibling->color = true;

		// If parent of sibling is root, it is done 
		if (p == root) {
			p->color = false;

		}
		else {		// start over, checking for new DB (parent) sibling
			node* newDB = p;
			node* siblingOfNewDB = (newDB->Is_Lchild) ? newDB->parent->Rchild : newDB->parent->Lchild;
			

			if (siblingOfNewDB->color) {		//sibling is red, case 3
				delete_3(newDB->parent, newDB->Is_Lchild);
			}
			else {								//sibling is black
				if ((siblingOfNewDB->Lchild != nullptr && siblingOfNewDB->Lchild->color) || (siblingOfNewDB->Rchild != nullptr && siblingOfNewDB->Rchild->color)) { // black sibling has a red child
					delete_1(newDB->parent, newDB->Is_Lchild);
				}
				else {				//
					if (newDB->parent->color) { // case 2b
						delete_2B(newDB->parent, newDB->Is_Lchild);
					}
					else {					// case 2a
						delete_2A(newDB->parent, newDB->Is_Lchild);
					}
				}
			}


		}
	}







	









	void delete_node(int i) {
		/*Delete the find node encountered with value i;
		if the node is in trivial case, porcess it and it is done.
		if not trivial case, replace  it with (1) successor if right child is R; else (2) predecessor if left child is R; else (3) predecessor. */
		

		//Step 1 : Find the node to delete
		node* target = root;
		
		while (target != nullptr && target->value != i) {
			if (i < target->value) {
				target = target->Lchild;
			}
			else {
				target = target->Rchild;
			}
		}


		if (target == nullptr) {
			cout << "Unable to locate node with value: " << i << endl;
			return;
		}

		//Step 2 : IS it a trivial case?
		
		// Trivial case 1: Target is a Red leaf node
		if (target->color && target->Lchild == nullptr && target->Rchild == nullptr) {
			if (target->Is_Lchild) {
				target->parent->Lchild = nullptr;
			}
			else {
				target->parent->Rchild = nullptr;
			}
			delete target;
			return;
		}

		// Trivial case 2: Target has one Red leaf child
		if (target->Lchild != nullptr && target->Lchild->color && target->Rchild == nullptr && target->Lchild->Lchild == nullptr && target->Lchild->Rchild == nullptr) {
			target->Lchild->parent = target->parent;
			if (target->Is_Lchild) {
				target->parent->Lchild = target->Lchild;
			}
			else {
				target->parent->Rchild = target->Lchild;
				target->parent->Rchild->Is_Lchild = false;
			}
			target->Lchild->color = false; // Make it black
			delete target;
			
			return;
		}
		if (target->Rchild != nullptr && target->Rchild->color && target->Lchild == nullptr && target->Rchild->Lchild == nullptr && target->Rchild->Rchild == nullptr) {
			target->Rchild->parent = target->parent;
			if (target->Is_Lchild) {
				target->parent->Lchild = target->Rchild;
			}
			else {
				target->parent->Rchild = target->Rchild;
				target->parent->Rchild->Is_Lchild = false;
			}
			target->Rchild->color = false; // Make  black
			delete target;
			
			return;
		}


		//Step 3 : IF not trivial case REPLACE with PRED or SUCC
		
		// Non trivial-case
		else {
			node* replacement = nullptr;
			bool foundReplacement = false; 
			// Case 1: Successor, right child is red
			
 			if (target->Rchild != nullptr && target->Rchild->color) {				
				replacement = target->Rchild;
				while (replacement->Lchild != nullptr) {
					replacement = replacement->Lchild;
				}
				foundReplacement = true;


			}
			// Case 2: Predecessor, left child is red

			else if (target->Lchild != nullptr && target->Lchild->color) {
				
				replacement = target->Lchild;
				while (replacement->Rchild != nullptr) {
					replacement = replacement->Rchild;
				}
				foundReplacement = true;

			}
			// Case 3: Predecessor, both children are black or leaf
			else {
				if (target->Lchild == nullptr && target->Rchild == nullptr) {																//if target is a leaf and black
					
					node* parent = target->parent;
					node* sibling = (target == parent->Lchild) ? parent->Rchild : parent->Lchild; //find sibling

					if (target == parent->Lchild) {
						target->Is_Lchild = true;
					}

					if (sibling != nullptr && sibling->color) {														//if sibling is red, case III
						
						delete_3(parent, target->Is_Lchild);
					}
					else if (sibling != nullptr && !sibling->color) {											// If sibling is black 
						
						if ((sibling->Lchild != nullptr && sibling->Lchild->color) || (sibling->Rchild != nullptr && sibling->Rchild->color)) { //if black sibling has at least one red child, case I
							
							delete_1(parent, target->Is_Lchild);
						}
						else if (!parent->color) {																	// If black sibling as no children,parent is black, case 2 A
							// Sibling is black, no red children, parent is black
							delete_2A(parent, target->Is_Lchild);
						}
						else {																				// If black sibling as no children,parent is red, case 2B
							// Sibling is black, no red children, parent is red
							delete_2B(parent, target->Is_Lchild);
						}
					}
					else {															//if double blacks sibling is nullptr
						if (!parent->color) {										//if parent is black, case 2a
							delete_2A(parent, target->Is_Lchild);
						}
						else {															//if parent is red, case 2b
							delete_2B(parent, target->Is_Lchild);
						}
					}

					// Remove the double black node
					if (target == parent->Lchild) {
						parent->Lchild = nullptr;
					}
					else {
						parent->Rchild = nullptr;
					}
					delete target;
					return;

				}
				else {						//target is black with 2 black nodes
					replacement = target->Lchild;
					while (replacement != nullptr && replacement->Rchild != nullptr) {
						replacement = replacement->Rchild;

					}
					
					foundReplacement = true;
				}
			}

		//Step 4 : swap replacement with soon to be deleted node, then delete 

			if (foundReplacement) {
				int temp = target->value;
				target->value = replacement->value;
				replacement->value = temp;
			}




		//Step 5: Figuree out what DELETE case it is, then delete replacement 

			if (replacement->Lchild == nullptr && replacement->Rchild == nullptr) {																			// If Replacement node is a leaf
				if (replacement == replacement->parent->Lchild) {
					replacement->Is_Lchild = true;
				}
				if (replacement->Is_Lchild) {
					replacement->parent->Lchild = nullptr;
				}
				else {																		//make the replacement node null 
					replacement->parent->Rchild = nullptr;
				}

				if (!replacement->color) {													// if replacement node is going to be double black
					node* parent = replacement->parent;
					node* sibling = (replacement->Is_Lchild) ? parent->Rchild : parent->Lchild; //find sibling


					if (sibling != nullptr && sibling->color) {		//if doble black nodes sibling is red, case 3
						delete_3(replacement->parent, replacement->Is_Lchild);

					}
					else if (sibling != nullptr && !sibling->color  ){			//if double black nodes sibling is Black
						if ((sibling->Rchild != nullptr && sibling->Rchild->color) || (sibling->Lchild != nullptr && sibling->Lchild->color)) {			//if double black's  sibling has at least one right child, case I 
							delete_1(parent, replacement->Is_Lchild);
						}
						else if(!parent->color){										//if double blakc's black sibling has no R children, parent is black, case 2a
							delete_2A(parent, replacement->Is_Lchild);
						}
						else {															//if double blakc's black sibling has no R children, parent is red, case 2b
							delete_2B(parent, replacement->Is_Lchild);
						}
					}
					else {															//if double blacks sibling is nullptr
						if (!parent->color) {										//if parent is black, case 2a
							delete_2A(parent, replacement->Is_Lchild);
						}
						else {															//if parent is red, case 2b
							delete_2B(parent, replacement->Is_Lchild);
						}
					}

				}
				else {
					
				}
			}





			else {
				// Replacement node has one child

				node* child = replacement->Lchild != nullptr ? replacement->Lchild : replacement->Rchild;

				child->parent = replacement->parent;
				if (replacement->Is_Lchild) {
					replacement->parent->Lchild = child;					//swap replacement with child 
				}
				else {
					replacement->parent->Rchild = child;
				}

				if (!replacement->color) {
					
					if (child->color) {			//if red change to black
						
						child->color = false;
					}
					else {
						node* parent = replacement->parent;
						node* sibling = (replacement->Is_Lchild) ? parent->Rchild : parent->Lchild;


						if (sibling != nullptr && sibling->color) {		//if doble black nodes sibling is red, case 3
							delete_3(replacement->parent, replacement->Is_Lchild);

						}
						else if (sibling != nullptr && !sibling->color) {			//if double black nodes sibling is Black
							if ((sibling->Rchild != nullptr && sibling->Rchild->color) || (sibling->Lchild != nullptr && sibling->Lchild->color)) {			//if double black's black sibling has at least one right child, case I 
								delete_1(parent, parent->Is_Lchild);
							}
							else if (!parent->color) {										//if double blakc's black sibling has no R children, parent is black, case 2a
								delete_2A(parent, parent->Is_Lchild);
							}
							else {															//if double blakc's black sibling has no R children, parent is red, case 2b
								delete_2B(parent, parent->Is_Lchild);
							}
						}
						else {															//if double blacks sibling is nullptr
							if (!parent->color) {										//if parent is black, case 2a
								delete_2A(parent, parent->Is_Lchild);
							}
							else {															//if parent is red, case 2b
								delete_2B(parent, parent->Is_Lchild);
							}
						}
					}
				}
			}
			root->color = false;
			root->Is_Lchild = false;
			delete replacement;


		}


	}




















//For the following, during traveral, print (value, color, Is_Lchild) of each node.
void InorderPrint(node* p) {//Print all nodes of a subtree rooted at node pointed by p; Example: (7 R 1) (12 B 0) (14 R 1) ...
	
	if (p != nullptr) {
		InorderPrint(p->Lchild);
		cout << "(" << p->value << " ";
		if (p->color)
			cout << "R";
		else
			cout << "B";
		cout << " ";
		if (p->Is_Lchild)
			cout << "1";
		else
			cout << "0";
		cout << ") ";
		InorderPrint(p->Rchild);
	}
}
};

int main() {
	tree T1;

	
	T1.add_node(60);
	T1.add_node(30);
	T1.add_node(80);
	T1.add_node(20);
	T1.add_node(40);
	T1.add_node(70);
	T1.add_node(90);
	T1.add_node(10);
	T1.add_node(25);
	T1.add_node(35);
	T1.add_node(45);
	T1.add_node(65);
	T1.add_node(75);
	T1.add_node(85);
	T1.add_node(95);

	T1.delete_node(60);   
	T1.delete_node(20);   
	T1.delete_node(80);   
	T1.delete_node(10);   
	T1.delete_node(95);
	
	T1.InorderPrint(T1.root);


	return 0;
}
