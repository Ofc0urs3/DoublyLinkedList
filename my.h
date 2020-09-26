#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1000
#define MAX_PRINT 10

class Node;
class List
{
 private:
    Node *head;
	Node *tail;
	Node *cur;
	int Size;
 public:
     friend class Iterator;
     friend class Node;
     List ();
     List(int k ,char* str);
	 ~List ();

    List(const List &lst);
    List& operator= (const List& str);
    void push_right(const char* data);
    void push_left(const char* data);
    void del_right();
    void del_left();
    void del_cur();
    Node* GetPointer();//
    Node* GetNextPointer();//
    Node* GetPrevPointer();//
    int read(FILE* fin);
    void AddR(const List& str);
    void AddL(const List& str);
    int GetSize() { return Size;}
    int GetIndex();//
    void removeAt(int index);
	void clear();
	void pop_front();
	void pop_back();
	void push_front(const char* data);
	void push_back(const char* data);
	void insert(char* data, int index);
	Node* GetCur(){return cur;}
    Node* partitionQuick(Node *l, Node *h, int (*comp)(Node*, Node*));
	void quickSortRec(Node* l, Node *h, int (*comp)(Node*, Node*));
	void quickSort(int (*comp)(Node*, Node*));
    void print() const;
};

class Node
{
    private:
        Node *pNext;
        Node *pPrev;
		char* data;
     public:
        friend class Iterator;

        Node (const char* data = nullptr , Node *pNext  = nullptr, Node *pPrev = nullptr )
		{
            int n = 0;
            if (data != nullptr) {
                while (data[n++] != '\0');
                this->data = new char[n + 1];
                for (int i = 0; i < n + 1; ++i) this->data[i] = data[i];
                //cout << "hh[" << endl;
            }
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
        ~Node()
        {
            destroy();
        }
		void destroy();
		void swap(Node* node, List* list);
        void swap(Node* node);
		int read(FILE* fin);
		friend class List;
		int operator< (const Node& node);
};
int comparator(Node* a, Node* b);

class Iterator
{
        Node* val;
        List const *list;
        Iterator();
        public:
        friend class List;
        friend class Node;

        Iterator(List* lst, Node* node)
        {
            this->list = lst;
            this->val = node;
        }

        Iterator(List const *lst)
        {
            this->list = lst;
            this->val = lst->head;
        }

        char* operator* () {return val->data;}

        bool operator++ ()
        {
                if (val->pNext == nullptr) return false;
                val = val->pNext;
                return true;
        }

        Iterator operator+(int n)
        {

            for(int i=0; i<n && val->pNext != nullptr; i++)
            {
                val = val->pNext;
            }
            return *this;
        }

        int operator !=(const Node *b) {return val != b;}
};
