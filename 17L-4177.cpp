#include <iostream>
#include <conio.h>
#include <list>
#include <fstream>
using namespace std;

class heap;
template<class T>
class bstnode;

struct dat
{
	char key;
	int freq;

	dat(char c = '\0', int f = 0)
	{
		key = c;
		freq = f;
	}

	void print()
	{
		cout << key << "   ";
		cout << freq;
		cout << "\n";

	}
	void printfreq()
	{
		cout << freq;
	}

	void printkey()
	{
		cout << key;
	}

	char getkey()
	{
		return key;
	}
	/*void storefrequency()
	{
		a[ind] = freq;
		ind++;
	}*/

	friend ostream &operator <<(ostream& out, const dat& d)
	{
		out << d.key << " ";
		cout << d.freq << "\n";
		return out;
	}
};

template<class T>
class Treenode
{
	Treenode<T> * left;
	Treenode<T>* right;
	dat data;
	int height;

	friend class heap;
	friend class bstnode<T>;

public:
	Treenode()
	{
		left = nullptr;
		right = nullptr;
		height = 0;

	}
	Treenode(T d, Treenode<T>* l = nullptr, Treenode<T>* r = nullptr)
	{
		left = l;
		right = r;
		data = d;
		height = 0;
	}

	bool checkleft()
	{
		if (left == nullptr)
			return false;
		return true;
	}

	void printbstnode()
	{
		data.print();

	}

	bool checkright()
	{
		if (right == nullptr)
			return false;
		return true;
	}

	~Treenode()
	{
		if (right != nullptr)
		{
			delete right;
			right = nullptr;
		}
		if (left != nullptr)
		{
			delete left;
			left = nullptr;
		}
	}
};

template<class T>
class bstnode
{
	friend class heap;
	Treenode<T>* root;
public:
	bstnode()
	{
		root = nullptr;
	}

	bstnode(T d)
	{
		if (d != nullptr)
		{
			root = new Treenode<T>(d);
		}
	}

	Treenode<T>* getroot()
	{
		return root;
	}

	~bstnode()
	{
		if (root != nullptr)
		{
			delete root;
			root = nullptr;
		}
	}

	void printbstnode()
	{
		print(root);
	}

	void print(Treenode<T>* root)
	{
		if (root != nullptr)
		{
			root->printbstnode();
			print(root->left);
			print(root->right);
		}
	}

};

class heap
{
	list<Treenode<dat>*>* _heap;
public:
	heap()
	{
		_heap = new list<Treenode<dat>*>;
	}

	void addNew(Treenode<dat>* k)
	{
		if (k != nullptr)
		{
			list<Treenode<dat>*>::iterator it = _heap->begin();
			for (; it != _heap->end() && k->data.freq > (*it)->data.freq; ++it);
			if (it != _heap->end())
				_heap->insert(it, k);
			else
				_heap->push_back(k);
		}
	}

	bstnode<dat>* HuffTree()
	{
		bstnode<dat>* t = new bstnode<dat>;
		t->root = huffTree();
		return t;
	}

	Treenode<dat>* huffTree()
	{
		if (_heap->size() > 1)
		{
			Treenode<dat>* temp = new Treenode<dat>;
			temp->data.freq = temp->data.freq + _heap->front()->data.freq;
			temp->left = _heap->front();
			_heap->pop_front();
			temp->data.freq = temp->data.freq + _heap->front()->data.freq;
			temp->right = _heap->front();
			temp->data.key = '\0';
			_heap->pop_front();
			addNew(temp);
			huffTree();
		}
		return _heap->front();
	}

	void printHeap()
	{
		list<Treenode<dat>*>::iterator it = _heap->begin();
		for (; it != _heap->end(); ++it)
		{
			(*it)->printbstnode();
		}
	}


	void deleteheap(heap* & h)
	{
		if (h != nullptr)
			delete h;
	}

	~heap()
	{
		delete _heap;
	}
};
class HashTable
{
	list<dat> *table[32] = { nullptr };
public:
	HashTable()
	{
		for (int i = 0; i < 32; i++)
		{
			table[i] = new list<dat>;
		}
	}
	void search(char k)
	{
		int i = k;
		i = i % 32;
		typename list<dat>::iterator it;
		it = table[i]->begin();
		bool flag = false;
		for (;it != table[i]->end();++it)
		{
			if (k == it->key)
			{
				it->freq++;
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			dat temp(k, 1);
			table[i]->push_back(temp);
		}
	}
	void print()
	{
		for (int i = 0; i < 32; i++)
		{
			if (table[i] != nullptr)
			{
				for (list<dat>::iterator it = table[i]->begin(); it != table[i]->end(); ++it)
				{
					cout << *it;
				}
			}
			//cout << "\n\n\n";
		}
		cout << "\n\n\n";
	}
	heap* consHeap()
	{
		heap* Heap = new heap;
		for (int i = 0; i < 32; i++)
		{
			for (list<dat>::iterator it = table[i]->begin(); it != table[i]->end(); ++it)
			{
				Treenode<dat>* temp = new Treenode<dat>(*it);
				Heap->addNew(temp);
			}
		}
		return Heap;
	}
	~HashTable()
	{
		for (int i = 0; i < 32; i++)
		{
			if (table[i] != nullptr)
			{
				table[i]->~list();
				table[i] = nullptr;
			}
		}
	}
	void deletehashtable(HashTable*& h)
	{
		if (h != nullptr)
			delete h;
	}
};



struct MinHeapNode
{

	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap
{

	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->size = 0;
	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}
void minHeapify(struct MinHeap* minHeap, int idx)

{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;
	if (smallest != idx)
	{
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	for (int i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i];

	cout << "\n";
}

int isLeaf(struct MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
	struct MinHeap* minHeap = createMinHeap(size);
	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
	while (!isSizeOne(minHeap))
	{

		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top)
{
	if (root->left)
	{

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	if (root->right)
	{

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	if (isLeaf(root))
	{

		cout << root->data << ": ";
		printArr(arr, top);
	}
}

void huffmanENCODING(char data[], int freq[], int size)

{
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
	int arr[100], top = 0;
	printCodes(root, arr, top);
}






class avltree;
class dnode;
class tnode;
template<class T>
class dlist;
template<class T>
class stack;
template<class T>
class bst;

template<class T>
class Lnode
{
	T data;
	Lnode<T> * next;
	Lnode<T> * prev;
public:
	Lnode()
	{
		next = NULL;
		prev = NULL;
	}
	Lnode(T d, Lnode* n = NULL)
	{
		data = d;
		next = n;
	}
	friend class dlist<T>;

};

template <class T>
class dlist
{
private:
	Lnode<T> head; // dummy head

				   //Nested class starts from here.
	class dlistiterator
	{
		Lnode<T> * curr;
	public:
		friend class dlist;
		dlistiterator(Lnode<T>* n = NULL)
		{
			curr = n;
		}
		Lnode<T>* getNext()
		{
			if (curr->next != NULL)
			{
				return (curr->next);
			}
			else
				return NULL;
		}
		dlistiterator & operator++()
		{
			if (curr != NULL)
			{
				curr = curr->next;
			}
			return *this;
		}
		dlistiterator & operator--()
		{
			if (curr != NULL)
			{
				curr = curr->prev;
			}
			return *this;
		}
		bool operator!= (dlistiterator &it) const
		{
			if (curr != it.curr)
			{
				return true;
			}
			else
				return false;
		}
		T& operator*()
		{
			return curr->data;
		}
		T& getdata()
		{
			return curr->next->data;
		}
	};
public:
	typedef dlistiterator diterator;
	dlist()
	{
		head.next = NULL;
	}

	void insertatstart(T d)
	{
		Lnode <T> *node = new Lnode <T>(d);
		node->next = head.next;
		node->prev = NULL;
		if (head.next != NULL)
		{
			head.next->prev = node;
		}
		head.next = node;
	}
	void insertafter(dlistiterator it, T d)
	{

		Lnode<T>* node = new Lnode<T>(d);
		node->next = it.curr->next;
		if (node->next != NULL)
		{
			node->next->prev = node;
		}
		node->prev = it.curr;
		it.curr->next = node;

	}

	bool IsEmpty()
	{
		bool flag = false;
		if (head.next == NULL)
		{
			flag = true;
		}
		if (flag == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Remove(dlistiterator it)
	{
		Lnode<T>* temp = head.next;
		if (it.curr->next != NULL)
		{
			while (temp != it.curr->next)
			{
			}
			it.curr->next = temp->next;
			delete temp;
		}




	}
	void insertSorted(T d)
	{
		Lnode<T>* node = new Lnode<T>(d);

		Lnode<T>* temp = head.next;
		while (temp->next != 0 && temp->data < d) //Traversing to the required node.
		{
			temp = temp->next;
		}
		node->next = temp; //storing value.
		if (temp == head.next)
		{
			head.next = node;
		}
		else
		{
			temp->prev->next = node;
		}

	}
	void Remove(T d)
	{

		Lnode<T>* temp;
		if (head->data == d)
		{
			//First node to be deleted
			temp = head.next;
			head = head->next;
			delete temp;
		}
		else
		{
			temp = head.next;
			while (temp->next != 0 && temp->next->data < d)
			{
				temp = temp->next;
			}

			if (temp->next != 0 && temp->next->data == d)
			{
				if (temp->next == head.next)
				{
					head.next = temp->next;
				}
				else
				{
					temp->prev->next = temp->next;
				}
				delete temp;
			}
		}
	}
	dlistiterator begin()
	{
		dlistiterator obj(head.next);
		return obj;
	}
	dlistiterator end()
	{
		dlistiterator obj;
		return obj; //which will be NULL.
	}

	void RemoveAll()
	{
		Lnode <T> * node = head.next;
		Lnode <T> * temp = node->next;
		while (node != NULL)
		{
			delete node;
			node = temp;
		}
	}

	~dlist()
	{
		RemoveAll();
	}

	void printlist()
	{
		diterator temp = head.next;
		while (temp != end())
		{
			cout << *temp << "\t";
			++temp;
		}
		cout << endl;
	}
};

void stringcopy(char* str1, char* str2)
{
	int i = 0;
	for (i = 0; str2[i] != '\0'; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

class Helper
{
public:
	static char* GetStringFromBuffer(char* str);
	static int stringlength(char* str);
	static bool stringcompare(char* str1, char* str2);
};
int Helper::stringlength(char* str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}
bool Helper::stringcompare(char* str1, char* str2)
{
	bool flag = true;
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}
char* Helper::GetStringFromBuffer(char* str)
{
	char* buffer = new char[strlen(str) + 1];
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		buffer[i] = str[i];
	}
	buffer[i] = '\0';
	return buffer;
}




template<class T>
class stack
{
private:
	T * s;
	int maxsize;
	int stackptr;
public:
	stack(int _size = 10)
	{
		s = new T[_size];
		maxsize = _size;
		stackptr = 0;
	}
	~stack()
	{
		if (s != nullptr)
		{
			delete[]s;
			s = nullptr;
		}
	}
	int getstackptr()
	{
		return stackptr;
	}

	bool isempty()
	{
		if (stackptr < 0)
			return true;
		return false;
	}
	bool isfull()
	{
		if (stackptr == maxsize)
			return true;
		return false;
	}

	T* getS()
	{
		return s;
	}
	bool push(T data)
	{
		if (!isfull())
		{
			s[stackptr] = data;
			stackptr++;
			return true;
		}
		return false;
	}
	bool pop(T &data)
	{
		if (isempty())
		{
			cout << "\nList is empty.\n";
			return false;
		}
		else
		{
			stackptr--;
			data = s[stackptr];
			return true;
		}
	}
	bool top(T &data)
	{
		if (isempty())
		{
			cout << "\nList is empty.\n";
			return false;
		}
		data = s[stackptr - 1];
		return true;
	}
	void printlist()
	{
		cout << "\n\t";
		for (int i = stackptr - 1; i >= 0; i--)
			cout << s[i] << "\n\t";
	}
};

bool search(int* arr, int key, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (key == arr[i])
			return true;
	}
	return false;
}

template<class T>
bool found(T* obj, int key, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (obj[i] == key)
			return true;

	}
	return false;
}

class tnode
{
	friend class avltree;
	int data;
	int _height;
	tnode * next;
	tnode * prev;
	tnode * left;
	tnode *right;


public:
	tnode()
	{
		next = nullptr;
		prev = nullptr;
		left = nullptr;
		right = nullptr;

	}
	~tnode()
	{
		delete next;
		delete prev;
		delete left;
		delete right;
	}
	tnode(int d)
	{
		data = d;
	}
};

class avltree
{
	tnode* root;
	friend class tnode;

public:
	avltree()
	{
		root = nullptr;
	}
	/*~avltree()
	{
	if (issn != nullptr)
	delete[] issn;
	if (references != nullptr)
	delete[] references;
	if (issuable != nullptr)
	delete[] issuable;
	if (authornames != '\0')
	delete[] authornames;
	if (title != '\0')
	delete[]title;
	}*/

	/*void rotateright(tnode* &y)
	{
	tnode *x = y->left;
	tnode *z = x->right;
	x->right = y;
	y->left = z;
	y->_height = max(height(y->left), height(y->right)) + 1;
	x->_height = max(height(x->left), height(x->right)) + 1;
	}
	void rotateleft(tnode* &x)
	{
	tnode *y = x->right;
	tnode *z = y->left;
	y->left = x;
	x->right = z;
	x->_height = max(height(x->left), height(x->right)) + 1;
	y->_height = max(height(y->left), height(y->right)) + 1;

	}*/
	void rotateright(tnode* &x)
	{
		tnode *y = x->left;
		x->left = y->right;
		y->right = x;
		x = y;
	}
	void rotateleft(tnode* &x)
	{
		tnode *y = x->right;
		x->right = y->left;
		y->left = x;
		x = y;
	}
	void doublerotateright(tnode* &x)
	{
		rotateleft(x->left);
		rotateright(x);
	}
	void doublerotateleft(tnode* &x)
	{
		rotateright(x->right);
		rotateleft(x);
	}
	int height(tnode *&N)
	{
		if (N == nullptr)
			return -1;
		return N->_height;
	}
	void balance(tnode*& ptr)
	{
		if (ptr == nullptr)
			return;
		else if (height(ptr->left) - height(ptr->right) > 1)
		{
			if (height(ptr->left->left) >= height(ptr->left->right))
				rotateright(ptr);
			else
				doublerotateright(ptr);
		}
		else if (height(ptr->right) - height(ptr->left) > 1)
		{
			if (height(ptr->right->right) >= height(ptr->right->left))
				rotateleft(ptr);
			else
				doublerotateleft(ptr);

			ptr->_height = max(height(ptr->left), height(ptr->right)) + 1;
		}
	}
	int max(int a, int b)
	{
		if (a < b)
			return b;
		return a;
	}
	int findmax(tnode* ptr)
	{
		while (ptr->right != nullptr)
		{
			ptr = ptr->right;
		}
		return ptr->data;
	}
	void insert(tnode* &r, int d)
	{
		if (r == nullptr)
		{
			r = new tnode(d);
			return;
		}
		if (r->data > d)
		{
			insert(r->left, d);
			if (height(r->left) - height(r->right) == 2)
			{
				if (d < r->left->data)
				{
					rotateright(r);
				}
				else
				{
					doublerotateright(r);
				}
			}
		}
		else if (d > r->data)
		{
			insert(r->right, d);
			if (height(r->left) - height(r->right) == 2)
			{
				if (d < r->right->data)
				{
					rotateleft(r);
				}
				else
				{
					doublerotateleft(r);
				}
			}
		}
		r->_height = 1 + max(height(r->left), height(r->right));
	}
	void deletenode(tnode* & ptr, int d)
	{
		if (ptr == nullptr)
			return;

		if (ptr->data == d)
		{
			if (ptr->left == nullptr)
			{
				tnode* temp = ptr;
				ptr = ptr->right;
				delete temp;
				return;
			}
			else if (ptr->right == nullptr)
			{
				tnode* temp = ptr;
				ptr = ptr->left;
				delete temp;
				return;
			}
			else if (ptr->left != 0 && ptr->right != 0)
			{
				ptr->data = findmax(ptr->left);
				deletenode(ptr->left, ptr->data);
			}
		}
		if (d > ptr->data) {
			deletenode(ptr->right, d);
		}
		if (d < ptr->data) {
			deletenode(ptr->left, d);
		}
		balance(ptr);
	}

	void deletenode(int d)
	{
		return deletenode(root, d);
	}
	void print()
	{
		printavl(root);
	}
	void printavl(tnode *_root)
	{
		if (_root != nullptr)
		{
			cout << _root->data << " ";
			printavl(_root->left);
			printavl(_root->right);
		}
	}
	void recursivedelete(tnode* r)
	{
		if (r != nullptr)
		{
			recursivedelete(r->left);
			recursivedelete(r->right);
			delete r;

		}
	}
	tnode* search(tnode* r, int d)
	{
		if (r == nullptr)
			return r;
		if (r->data == d)
			return r;
		if (r->data < d)
			return search(r->right, d);
		else
			return search(r->left, d);
	}
	tnode* _search(tnode*r, int d)
	{
		return search(r, d);
	}
	~avltree()
	{
		recursivedelete(root);
	}

};

template <class T>
class node
{
	T data;
	node* right;
	node* left;
public:

	node()
	{
		right = nullptr;
		left = nullptr;
	}
	node(T d, node*r, node*l)
	{
		data = d;
		left = l;
		right = r;
	}
	~node()
	{
		if (right != nullptr)
		{
			delete[]right;
			right = nullptr;
		}
		if (left != nullptr)
		{
			delete[]left;
			left = nullptr;
		}
	}

};


template<class T>
class bst
{
	node* root;
public:
	bst()
	{
		root = nullptr;
	}
	void removeall(node * _node)
	{
		if (_node != nullptr)
		{
			removeall(_node->left);
			removeall(_node->right);
			delete _node;
		}
	}
	~bst()
	{
		removeall(root);
	}
	tnode* search(node* r, int d)
	{
		if (r == nullptr)
			return r;
		if (r->data == d)
			return r;
		if (r->data < d)
			return search(r->right, d);
		else
			return search(l->left, d);
	}
	void insert(node*&r, int d)
	{
		if (r == nullptr)
			r = new node(d);
		if (r->data > d)
			insert(r->left, d);
		else
			insert(r->right, d);
	}
	tnode* search(T d)
	{
		return search(root, d);
	}
	void insert(T d)
	{
		_insert(root, d);
	}
	void _insert(node*&r, int d)
	{
		if (r == nullptr)
			r = new node(d);
		if (r->data > d)
			_insert(r->left, d);
		else
			_insert(r->right, d);
	}
	void iterative_insert(T d)
	{
		if (root == nullptr)
			root = new node(d);
		node* curr = root;
		node* temp = nullptr;
		while (curr != nullptr)
		{
			temp = curr;
			if (d < curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}
		if (d < temp->data)
			temp->left = new node(d);
		else
			temp->right = new node(d);
	}
	void printsorted(node *r)
	{
		if (r != nullptr)
		{
			printsorted(r->left);
			cout << r->data;
			printsorted(r->right);
		}
	}
	tnode* min(tnode* _node)
	{
		tnode* curr = _node;
		while (curr->left != nullptr)
		{
			curr = curr->left;
		}
		return curr;
	}
	tnode* remove(tnode* _root, int d)
	{
		if (_root == nullptr)
			return _root;
		if (d < _root->d)
			_root->left = remove(_root->left, d);
		else if (d > _root->d)
			_root->right = remove(_root->right, d);
		else
		{
			if (_root->left == nullptr)
			{
				tnode *temp = _root->right;
				free(_root);
				return temp;
			}
			else if (_root->right == nullptr)
			{
				tnode* temp = _root->left;
				free(_root);
				return temp;
			}
			tnode* _temp = min(_root->right);
			_root->d = _temp->d;
			_root->right = remove(_root->right, _temp->d);
		}
		return _root;
	}
};

class _MinHeap
{
	int *arrheap;
	int maxsize;
	int heapsize;
public:

	_MinHeap(int size = 10)
	{
		heapsize = 0;
		maxsize = size;
		arrheap = new int[size];
	}
	void MinHeapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < heapsize && arrheap[l] < arrheap[i])
			smallest = l;
		if (r < heapsize && arrheap[r] < arrheap[smallest])
			smallest = r;
		if (smallest != i)
		{
			swap(arrheap[i], arrheap[smallest]);
			MinHeapify(smallest);
		}
	}

	int parentnode(int i)
	{
		return (i - 1) / 2;
	}

	int left(int i)
	{
		return (2 * i + 1);
	}

	int right(int i)
	{
		return (2 * i + 2);
	}

	int extractMin()
	{
		if (heapsize <= 0)
			return INT_MAX;
		if (heapsize == 1)
		{
			heapsize--;
			return arrheap[0];
		}

		int data = arrheap[0];
		arrheap[0] = arrheap[heapsize - 1];
		heapsize--;
		MinHeapify(0);

		return data;

	}

	void decreaseKey(int i, int new_val)
	{
		arrheap[i] = new_val;
		while (i != 0 && arrheap[parent(i)] > arrheap[i])
		{
			swap(arrheap[i], arrheap[parent(i)]);
			i = parent(i);
		}
	}

	int getMin()
	{
		return arrheap[0];
	}

	void deleteKey(int i)
	{

		decreaseKey(i, INT_MIN);
		extractMin();
	}

	void insertKey(int k) {
		if (heapsize == maxsize)
		{
			return;
		}
		heapsize++;
		int i = heapsize;
		arrheap[i] = k;

		while (i > 0) {
			if (arrheap[i] > arrheap[i / 2])
			{
				swap(arrheap[i], arrheap[arrheap[i / 2]]);
				i = i / 2;
			}
			else
				return;
		}
	}

	int getleftchildindex(int parentindex)
	{
		return 2 * parentindex + 1;
	}
	int getrightchildindex(int parentindex)
	{
		return 2 * parentindex + 2;
	}
	int getparentindex(int childindex)
	{
		return(childindex - 1) / 2;
	}
	bool hasleftchild(int index)
	{
		return getleftchildindex(index) < heapsize;
	}
	bool hasrightchild(int index)
	{
		return getrightchildindex(index) < heapsize;
	}
	bool hasparent(int index)
	{
		return getparentindex(index) >= heapsize;
	}
	int leftchild(int index)
	{
		return arrheap[getleftchildindex(index)];
	}
	int rightchild(int index)
	{
		return arrheap[getrightchildindex(index)];
	}
	int parent(int index)
	{
		return arrheap[getparentindex(index)];
	}
	void ensureextracapacity()
	{
		if (heapsize == maxsize)
		{
			maxsize *= 2;
		}
	}
	int peek()
	{
		if (heapsize != 0)
			return arrheap[0];
		return 0;
	}

};

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

/*string decode(bstnode<Treenode<dat>>* root, string encoded_str)
{
string res = "";
bstnode<Treenode<dat>>* node = root;
for (int i = 0; i != encoded_str.size(); ++i)
{
if (encoded_str[i] == '0') { // left child
node = node->left;
}
else { // rigth child
assert(encoded_str[i] == '1');
node = node->right;
}
if (node->is_leaf() == true)
{
res += node->letter;
node = root;
}
}
return res;
}*/


HashTable* Filing()
{
	char ch;
	ifstream fin;
	fin.open("data.txt");
	HashTable *Hptr = new HashTable;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin.get(ch);
			Hptr->search(ch);
		}
	}
	else
		cout << "File not opened. Please insert data.txt file.\n";
	return Hptr;
}

string decode_file(struct MinHeapNode* root, string s)
{
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0;i < s.size();i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node 
		if (curr->left == NULL and curr->right == NULL)
		{
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl; 
	return ans + '\0';
}



int main()
{
	cout << "\t\t\t\tReading from file.\n\n";
	HashTable* Hptr = Filing();
	Hptr->print();

	cout << "\n\n\n\t\t\t\tPrinting from heap.\n\n";
	heap* Heap = Hptr->consHeap();
	Heap->printHeap();

	bstnode<dat>* BSptr = Heap->HuffTree();
	cout << "\n\n\n\t\t\t\tPrinting bstTree.\n\n";
	BSptr->printbstnode();

	char arr[] = { 'l', 'x', 's', 'm', 'y', 'b','n','z','c','o','d','p','e','q','f','r','g','s','h','t','i','u','j','v','k','w',' ' };
	int freq[] = { 10,3,5,2,2,9,3,5,13,4,5,5,11,6,11,6,15,8,9,3,10,3,11,3,10,4,5 };

	int size = sizeof(arr) / sizeof(arr[0]);
	cout << "\n\n\n\n\t\t\t\tencoded data of file data.txt.\n\n\n";
	huffmanENCODING(arr, freq, size);
	cout << "\n\n\t\t\t\tdecoded data of file data.txt.\n\n\n";

	//string decodedString = decode_file(Heap,encodedstring);
	//cout << "\nDecoded Huffman Data:\n" << decodedString << endl;

	Hptr->deletehashtable(Hptr);
	Heap->deleteheap(Heap);
	_getch();
}
