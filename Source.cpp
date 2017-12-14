#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

template <class DT>
class ArrayBTNode
{
	template <class DT>
	friend ostream& operator<<(ostream& s, ArrayBTNode&);
public:

	DT* _info;
	int _left; //the index position where the left ArrayBTNode will be available
	int _right;//the index position where the right ArrayBTNode will be available

	//constructors
	ArrayBTNode();
	ArrayBTNode(DT info);
	ArrayBTNode(ArrayBTNode<DT>& node);

	//getters and setters
	void setInfo(int info);
	void setLeft(int left);
	void setRight(int right);
	
	DT getInfo();
	int getLeft();
	int getRight();

	//destructor
	virtual ~ArrayBTNode();

	//tested while having trouble with ostream
	void display();

	//= and comparison operators
	ArrayBTNode<DT> operator=(ArrayBTNode<DT>& node);
	bool operator >(ArrayBTNode<DT>& node);
	bool operator <(ArrayBTNode<DT>& node);
	bool operator ==(ArrayBTNode<DT>& node);
	bool operator >=(ArrayBTNode<DT>& node);
	bool operator <=(ArrayBTNode<DT>& node);
	bool operator !=(ArrayBTNode<DT>& node);
};


template <class DT>
ostream & operator<<(ostream & s, ArrayBTNode<DT>& node)
{//prints if info is not "null"
	if (node.(*_info) > 0)
	{
		cout << "Value: " << node.(*_info) << endl << "Left Child Index: " << node._left
			<< endl << "Right Child Index: " << node._right << endl << endl;
	}
	return s;
}

template<class DT>
ArrayBTNode<DT>::ArrayBTNode()
{//sets everything to unused values
	_info = nullptr;
	_left = -1;
	_right = -1;
}

template<class DT>
ArrayBTNode<DT>::ArrayBTNode(DT info)
{//sets the info, but no newly created node will have children
	_info = new DT(info);
	_left = -1;
	_right = -1;
}

template<class DT>
ArrayBTNode<DT>::ArrayBTNode(ArrayBTNode<DT> & node)
{//makes a copy of the node
	_info = node._info;
	_left = node._left;
	_right = node._right;
}

template<class DT>
void ArrayBTNode<DT>::setInfo(int info)
{//sets info
	*_info = info;
}

template<class DT>
void ArrayBTNode<DT>::setLeft(int left)
{//sets left
	_left = left;
}

template<class DT>
void ArrayBTNode<DT>::setRight(int right)
{//sets right
	_right = right;
}

template<class DT>
DT ArrayBTNode<DT>::getInfo()
{//gets info
	return *_info;
}

template<class DT>
int ArrayBTNode<DT>::getLeft()
{//gets left
	return _left;
}

template<class DT>
int ArrayBTNode<DT>::getRight()
{//gets return
	return _right;
}

template<class DT>
ArrayBTNode<DT>::~ArrayBTNode()
{//deletes the node
	if (_info != nullptr)
	{
		delete _info;
	}
}

template<class DT>
void ArrayBTNode<DT>::display()
{//displays if applicable
	if (_info != nullptr)
	{
		cout << "Value: " << (*_info) << endl << "Left Child Index: " << _left
			<< endl << "Right Child Index: " << _right << endl << endl;
	}
}

template<class DT>
ArrayBTNode<DT> ArrayBTNode<DT>::operator=(ArrayBTNode<DT> & node)
{//copies a node and returns it
	ArrayBTNode<DT>* toReturn = new ArrayBTNode<DT>(node);
	return (*toReturn);
}

template<class DT>
bool ArrayBTNode<DT>::operator>(ArrayBTNode<DT> & node)
{//returns if greater 
	return (*_info > node.(*_info));
}

template<class DT>
bool ArrayBTNode<DT>::operator<(ArrayBTNode<DT> & node)
{//returns if less
	return (*_info < node.(*_info));
}

template<class DT>
bool ArrayBTNode<DT>::operator==(ArrayBTNode<DT> & node)
{//returns if equal
	return (*_info == node.(*_info));
}

template<class DT>
bool ArrayBTNode<DT>::operator>=(ArrayBTNode<DT> & node)
{//returns if greater/equal
	return (*_info >= node.(*_info));
}

template<class DT>
bool ArrayBTNode<DT>::operator<=(ArrayBTNode<DT> & node)
{//returns if less/equal
	return (*_info <= node.(*_info));
}

template<class DT>
bool ArrayBTNode<DT>::operator!=(ArrayBTNode<DT> & node)
{//returns if not equal
	return (*_info != node.(*_info));
}

template <class DT>
class ArrayBT
{//the generic class/methods
public:
	vector<DT>* myBinaryTree; //HAD TO CHANGE TO DT DUE TO CONSTANT ERRORS
	int _root; //index position of the root the binary tree in the vector
	int _noNodes; //the number of nodes in the binary tree
	int _size; //the maximum size of the vector
	stack<int> freeLocations; //STL stack

	//constructors, unnecessary?
	ArrayBT();
	ArrayBT(int size);
	ArrayBT(ArrayBT& copy);

	//generic methods to be used also by BST
	int height(int index);

	void inOrder(DT toShow);
	void preOrder(DT toShow);

	//destructor
	virtual ~ArrayBT();
};

template<class DT>
ArrayBT<DT>::ArrayBT()
{//empty constructor, shouldn't be used, sets some arbitrary values
	myBinaryTree = new DT();
	freeLocations = NULL;
	_size = 0;
	_noNodes = 0;
	_root = 0;
}

template<class DT>
ArrayBT<DT>::ArrayBT(int size)
{//initializes the stack and vector based on size
	myBinaryTree = new vector<DT>(size);
	
	for (int i = size - 1; i > -1; i--)
	{
		freeLocations.push(i);
	}
	_size = size;
	_noNodes = 0;
	_root = 0;
}

template<class DT>
ArrayBT<DT>::ArrayBT(ArrayBT & copy)
{//creates a careful/ deep copy of an arrayBT
	_size = copy._size;
	_noNodes = copy._noNodes;
	vector<DT>* temp;
	for (int i = 0; i < copy.myBinaryTree->size(); i++)
	{
		temp[i] = copy.myBinaryTree[i];
		myBinaryTree[i] = temp[i];
	}
	freeLocations = copy.freeLocations;
}

template<class DT>
int ArrayBT<DT>::height(int index)
{//returns the height of the total tree (must start at 0)?
	int left = 0;
	if (myBinaryTree->at(index)->getLeft() != -1)
	{//if left exists go down it
		left = height(myBinaryTree->at(index)->getLeft());
	}
	int right = 0;
	if (myBinaryTree->at(index)->getRight() != -1)
	{//if right exists go down it
		right = height(myBinaryTree->at(index)->getRight());
	}

	if (left > right)
	{
		return (1 + left);
	}
	else
	{//return the greater of the two
		return (1 + right);
	}
}

template<class DT>
void ArrayBT<DT>::inOrder(DT toShow)
{//prints things in order
	if (toShow != nullptr && toShow->getInfo() != 0)
	{//essentially, if the node is a valid node
		if (toShow->getLeft() != -1)
		{//keep going left if you can
			inOrder(myBinaryTree->at(toShow->getLeft()));
		}
		//print it
		cout << toShow->getInfo() << endl;
		if (toShow->getRight() != -1)
		{//go right if you can
			inOrder(myBinaryTree->at(toShow->getRight()));
		}
	}
}

template<class DT>
void ArrayBT<DT>::preOrder(DT toShow)
{//prints preorder traversal
	if (toShow != nullptr && toShow->getInfo() != 0)
	{//if valid node
		if (toShow->getLeft() != -1)
		{//go left
			preOrder(myBinaryTree->at(toShow->getLeft()));
		}		
		if (toShow->getRight() != -1)
		{//go right
			preOrder(myBinaryTree->at(toShow->getRight()));
		}
		//print
		cout << toShow->getInfo() << endl;
	}
}

template<class DT>
ArrayBT<DT>::~ArrayBT()
{//destructor
	if (myBinaryTree != nullptr)
	{//delete if needed
		delete myBinaryTree;
	}
}

template <class DT>
class ArrayBST : virtual public ArrayBT<DT>
{//the sorted version of BT
	template <class DT>
	friend ostream& operator<<(ostream& s, ArrayBST<DT>& copy);
public:
	//constructors
	ArrayBST();
	ArrayBST(int size);
	ArrayBST(ArrayBST& copy);

	//unique methods for a BST (I started with addfirst so kept it)
	void addFirst(DT toAdd);
	void insert(DT toFind, int index);
	void remove(int data);
	int find(int toFind, int index);
	void displayRaw();

	//destructor
	virtual ~ArrayBST();
};

template<class DT>
ostream & operator<<(ostream & s, ArrayBST<DT>& copy)
{//prints preorder and inorder things
	cout << "Preorder:" << endl;
	copy.preOrder(copy.myBinaryTree->at(copy._root));

	cout << endl << "Inorder:" << endl;
	copy.inOrder(copy.myBinaryTree->at(copy._root));

	return s;
}

template<class DT>
ArrayBST<DT>::ArrayBST() : ArrayBT<DT>()
{//empty constructor uses BT
}

template<class DT>
ArrayBST<DT>::ArrayBST(int size) : ArrayBT<DT>(size)
{//same with the normal constructor
}

template<class DT>
ArrayBST<DT>::ArrayBST(ArrayBST & copy) : ArrayBT(copy)
{//and same with copy constructor
}

template<class DT>
void ArrayBST<DT>::addFirst(DT toAdd)
{//only acts when the root is not used
	myBinaryTree->at(freeLocations.top()) = toAdd;
	freeLocations.pop();
	_noNodes++;
}

template<class DT>
void ArrayBST<DT>::insert(DT toFind, int index)
{//inserts (recursively?)
	if (myBinaryTree->at(index)->getInfo() == toFind->getInfo())
	{//base case if already exists
		cout << "That data is already in the tree " << endl << endl;
	}
	else if (toFind->getInfo() < myBinaryTree->at(index)->getInfo())
	{//if value less
		if (myBinaryTree->at(index)->getLeft() == -1)
		{//if spot is open, put it there at next empty index
			myBinaryTree->at(index)->setLeft(freeLocations.top());
			this->myBinaryTree->at(freeLocations.top()) = toFind;
			freeLocations.pop();
		}
		else
		{//keep going on that left child
			this->insert(toFind, myBinaryTree->at(index)->getLeft());
		}
	}
	else
	{//must be greater
		if (myBinaryTree->at(index)->getRight() == -1)
		{//if spot open, put at next empty index
			this->myBinaryTree->at(index)->setRight(freeLocations.top());
			this->myBinaryTree->at(freeLocations.top()) = toFind;
			freeLocations.pop();
		}
		else
		{//keep checking on right child index
			this->insert(toFind, myBinaryTree->at(index)->getRight());
		}
	}
}

template<class DT>
void ArrayBST<DT>::remove(int data)
{//removes things based on a value
	int x = find(data, 0);
	if (x == -1)
	{//if number's not there no need to keep going
		cout << "Data not in the list " << endl << endl;
	}
	else
	{//it's in there somewhere
		int i = _root; //start at root
		while (i != -1)
		{//technically a worthless check since each path breaks but needs loop
			if (data == myBinaryTree->at(i)->getInfo())
			{//once value is found, 3 cases for removal
				if (myBinaryTree->at(i)->getLeft() == -1 &&
					myBinaryTree->at(i)->getRight() == -1)
				{//no children, set info to 0, readd the index to freeLoc, finish
					myBinaryTree->at(i)->setInfo(0);

					freeLocations.push(i);
					break;
				}
				else if (myBinaryTree->at(i)->getLeft() == -1)
				{//right child is only child
					//give freeLoc back the index of right
					freeLocations.push(myBinaryTree->at(i)->getRight());

					//the spot that's being removed actually takes the information from its child,
					//left/right index and all, in order to "remove" that child by setting it to 0
					myBinaryTree->at(i)->setInfo(
						myBinaryTree->at(myBinaryTree->at(i)->getRight())->getInfo());
					int tempLeft = myBinaryTree->at(myBinaryTree->at(i)->getRight())->getLeft();
					int tempRight = myBinaryTree->at(myBinaryTree->at(i)->getRight())->getRight();
					myBinaryTree->at(myBinaryTree->at(i)->getRight())->setLeft(-1);
					myBinaryTree->at(myBinaryTree->at(i)->getRight())->setRight(-1);
					myBinaryTree->at(myBinaryTree->at(i)->getRight())->setInfo(0);
					myBinaryTree->at(i)->setLeft(tempLeft);
					myBinaryTree->at(i)->setRight(tempRight);

					break; //be sure to end loop
				}
				else if (myBinaryTree->at(i)->getRight() == -1)
				{// same thing as above with different direction
					freeLocations.push(myBinaryTree->at(i)->getLeft());

					myBinaryTree->at(i)->setInfo(
						myBinaryTree->at(myBinaryTree->at(i)->getLeft())->getInfo());
					int tempLeft = myBinaryTree->at(myBinaryTree->at(i)->getLeft())->getLeft();
					int tempRight = myBinaryTree->at(myBinaryTree->at(i)->getLeft())->getRight();
					myBinaryTree->at(myBinaryTree->at(i)->getLeft())->setLeft(-1);
					myBinaryTree->at(myBinaryTree->at(i)->getLeft())->setRight(-1);
					myBinaryTree->at(i)->setLeft(tempLeft);
					myBinaryTree->at(i)->setRight(tempRight);

					break;
				}
				else
				{//both children are taken. 4 temps
					//one to obtain the smallest val index in right tree
					//one the actual value there
					//one to get the parent of that small (so it can set its left to -1)
					//and one to make the while loop go effectively
					int j = myBinaryTree->at(i)->getRight();
					int val = 0;
					int k, x;
					k = 0;
					while (j != -1)
					{//condition keeps going left after initially going right
						//x and k store parent and value index, respectively
						x = k;
						k = j;
						val = myBinaryTree->at(j)->getInfo();
						j = myBinaryTree->at(j)->getLeft();
					}
					//the last value to be obtained should have been the minimum
					myBinaryTree->at(i)->setInfo(val);
					//make the parent obtain the right index, if it had any
					myBinaryTree->at(x)->setLeft(myBinaryTree->at(k)->getRight());
					//the child is now "deleted" and its index is pushed back onto freeLoc
					myBinaryTree->at(k)->setInfo(0);
					freeLocations.push(k);
					break; // end
				}	
			}
			else if (data < myBinaryTree->at(i)->getInfo())
			{//make index go left
				i = myBinaryTree->at(i)->getLeft();
			}
			else
			{//make index go right
				i = myBinaryTree->at(i)->getRight();
			}
		}
	}
}

template<class DT>
int ArrayBST<DT>::find(int toFind, int index)
{//finds a given number (needs index because it's somewhat recursive (lazy)
	if (toFind == myBinaryTree->at(index)->getInfo())
	{//if you've found that number give back the position
		return index;
	}
	else if (toFind < myBinaryTree->at(index)->getInfo())
	{//if smaller
		if (myBinaryTree->at(index)->getLeft() != -1)
		{//go left if can
			find(toFind, myBinaryTree->at(index)->getLeft());
		}
		else
		{//it's not there
			return -1;
		}
	}
	else if (toFind > myBinaryTree->at(index)->getInfo())
	{//if greater
		if (myBinaryTree->at(index)->getRight() != -1)
		{//go right
			find(toFind, myBinaryTree->at(index)->getRight());
		}
		else
		{//it ain't there
			return -1;
		}
	}
}

template<class DT>
void ArrayBST<DT>::displayRaw()
{//prints each index and info if it has something in it
	for (int i = 0; i < _size; i++)
	{
		if (myBinaryTree->at(i) != nullptr && myBinaryTree->at(i)->getInfo() != 0)
		{//two cases where i don't want to print
			cout << "Index " << i << endl;
			myBinaryTree->at(i)->display();
		}
	}
	stack<int> s;
	cout << "Contents of stack:" << endl;
	while (!freeLocations.empty())
	{
		cout << freeLocations.top() << endl;
		s.push(freeLocations.top());
		freeLocations.pop();
	}
	cout << endl;
	//very cleverly duplicates the stack, despite inefficient
	while (!s.empty())
	{
		freeLocations.push(s.top());
		s.pop();
	}
}

template<class DT>
ArrayBST<DT>::~ArrayBST()
{//destructor
	if (myBinaryTree != nullptr)
	{//destructor
		delete myBinaryTree;
	}
}


int main()
{
	//input variables and a flag needed
	int size, data;
	char c;
	bool firstAdded = false;

	//only reads size in at beginning
	cin >> size;
	ArrayBST<ArrayBTNode<int>*>* arr2 = new ArrayBST<ArrayBTNode<int>*>(size);

	while (!cin.eof())
	{//reads whole input
		if (!cin.eof())
		{//some weird condition
			//always reads character
			cin >> c;
			if (c == 'O')
			{//uses ostream
				cout << "Outputting:" << endl << *arr2 << endl;
			}
			else if (c == 'R')
			{//removes data given
				cout << "Removing: " << endl << endl;
				cin >> data;
				arr2->remove(data);

			}
			else if (c == 'F')
			{//gives an index if applicable when found
				cout << "Searching: " << endl << endl;
				cin >> data;
				int x = arr2->find(data, 0);

				if (x == -1)
				{
					cout << "Number not found " << endl << endl;
				}
				else
				{
					cout << "Data found at index " << x << endl << endl;
				}
			}
			else if (c == 'A')
			{//uses the other display
				cout << "Displaying:" << endl << endl;
				arr2->displayRaw();
			}
			else if (c == 'I')
			{//inserts given data if stack nonempty
				cin >> data;
				if (!arr2->freeLocations.empty())
				{//stack keeps track of initial size which overrides the vector
					ArrayBTNode<int>* toAdd = new ArrayBTNode<int>(data);
					if (firstAdded)
					{//i had a weird way of doing the first insert so here's the check
						arr2->insert(new ArrayBTNode<int>(data), 0);
					}
					else
					{//uses first insert then hopefully never again
						arr2->addFirst(new ArrayBTNode<int>(data));
						firstAdded = true;
					}
				}
				else
				{//something to avoid the stack throwing errors since the file size is so huge
					cout << "Even though this is a vector, the size specified has reached its max and will not add" << endl;
				}
			}
		}
	}
	return 0;
}


