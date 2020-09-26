#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"


#define LEN 1000

List::List()
{
	head = nullptr;
	tail = nullptr;
	cur = nullptr;
	Size = 0;
}


List::List(int k, char* str)
{
	k = 1;
	head = tail = new Node(str);
	Size = k;
	cur = head;
}


 List::~List()
{
	clear();
}

void Node::swap(Node* node, List* list)
{

    if(this == node)
        return;

    int k=0, m=0;
    Node* tmp = list->head;
    while(tmp != this)
    {
        k++;
        tmp = tmp->pNext;
    }
    tmp = list->head;
    while(tmp != node)
    {
        m++;
        tmp = tmp->pNext;
    }

    if (k < m)
    {
        list->insert(node->data, k);
        list->insert(this->data, m + 1);
        list->removeAt(k+1);
        list->removeAt(m+1);
    }

    if (m < k)
    {
        list->insert(this->data, m);
        list->insert(node->data, k+1);
        list->removeAt(m+1);
        list->removeAt(k+1);
    }
}

void Node::swap(Node* node)
{
    char* tmp = data;
    data = node->data;
    node->data = tmp;
}

Node* List::partitionQuick(Node *l, Node *h, int (*comp)(Node*, Node*))
{
    Node *x = h;
    Node *i = l -> pPrev;

    for (Node *j = l; j != h; j = j -> pNext)
    {
        if(comp(j,x) < 0)
        {
            i = (i == nullptr) ? l : i -> pNext;
            i->swap(j);
        }
    }
    i = (i == nullptr)? l : i -> pNext;
    i -> swap(h);
    return i;
}
void List::quickSortRec(Node* l, Node *h, int (*comp)(Node*, Node*))
{
    if (h != nullptr && l != h && l != h -> pNext)
    {
        Node *p = partitionQuick(l, h, comp);
        quickSortRec(l, p -> pPrev, comp);
        quickSortRec(p -> pNext, h, comp);
    }
}

void List::quickSort(int (*comp)(Node*, Node*))
{
    quickSortRec(head, tail, comp);
}


int comparator(Node* a, Node* b) {return (*a) < (*b);}

int Node::operator < (const Node& node)
{
    return strcmp(this -> data, node.data);
}


int List::GetIndex()
{
    int k = 0;
    Node* tmp;
    tmp = head;
    while(tmp != cur)
    {
        k++;
        tmp = tmp->pNext;
    }
    return k;
}


Node* List::GetPointer()
{return cur;}

Node* List::GetNextPointer()
{return cur->pNext;}

Node* List::GetPrevPointer()
{return cur->pPrev;}

void List::push_right(const char* data)
{

    if(cur == tail)
    {
        push_back(data);
        cur = tail;
        return;
    }
    else
    {
    Node *temp = cur;
    cur = new Node(data, cur->pNext, cur);
    temp->pNext->pPrev = cur;
    temp->pNext = cur;
    Size++;
    }
}

void List::push_left(const char* data)
{
    if(cur == head)
    {
        push_front(data);
        cur = head;
        return;
    }
    Node *temp = cur;
    cur = new Node(data, temp, temp->pPrev);
    temp->pPrev->pNext = cur;
    temp->pPrev = cur;
    Size++;
}


void List::del_right()
{
    if(cur->pNext == nullptr)
        {
            return;
        }
    else if(cur->pNext == tail)
    {
        pop_back();
    }
    else
    {
        Node* tmp;
        tmp = cur->pNext;
        (tmp)->destroy();
        Size--;
        cur->pNext->pNext->pPrev = cur;
        cur->pNext = cur->pNext->pNext;

    }
}


void List::del_cur()
{
    if(cur == tail)
        pop_back();
    else if(cur == head)
        pop_front();
    else
    {
        Node* tmp;
        tmp = cur;
        tmp->destroy();
        Size--;
        cur->pPrev->pNext = cur->pNext;
        cur->pNext->pPrev = cur->pPrev;
        cur = tmp->pNext;
    }
}


void List::del_left()
{
    if(cur->pPrev == nullptr)
        return;
    else if(cur->pPrev == head)
    {
        pop_front();
    }
    else
    {
        Node* tmp;
        tmp = cur->pPrev;
        (tmp)->destroy();
        Size--;
        cur->pPrev->pPrev->pNext = cur;
        cur->pPrev = cur->pPrev->pPrev;
    }
}

void List::pop_back()
{
	if (Size > 1)
	{
		Node *temp = tail;
		tail = tail->pPrev;
		tail -> pNext = nullptr;
		//temp->destroy();
        delete temp;
	}
	else if (Size == 1)
	{
		Node *temp = tail;
		tail = head = tail->pPrev;
		//temp->destroy();
        delete temp;
	}

	Size--;
}

void List::clear()
{
        while(head)
        {
            cur = head;
            head = head -> pNext;
            delete cur;
        }
        Size = 0;
        delete head;
}


void List::pop_front()
{
	if (Size > 1)
	{
		Node *temp = head;
		head = head->pNext;
		head -> pPrev = nullptr;
		//temp->destroy();
        delete temp;
	}
	else if (Size == 1)
	{
		Node *temp = head;
		tail = head = head->pNext;
        delete temp;
	}

	Size--;
}

void List::push_front(const char* data)
{
	if (Size > 1)
	{
		Node *temp = head;
		head = new Node(data, head, nullptr);
		temp->pPrev = head;
	}
	else if (Size == 1)
	{
		head = new Node(data, head, nullptr);
		tail->pPrev = this->head;
	}
	else
	{
		head = tail = new Node(data, head, tail);
	}
	Size++;
}


void List::push_back(const char* data)
{
	if (Size > 1)
	{
		Node *temp = tail;
		tail = new Node(data, nullptr, tail);
		temp->pNext = tail;
	}
	else if (Size == 1)
	{
		tail = new Node(data, nullptr, head);
		head->pNext = this->tail;
	}
	else
	{
		head = tail = new Node(data);
	}
	Size++;
}



void List::insert(char* data, int index)
{
	if (index == 0) push_front(data);

	else if (index >= Size)
    {
       push_back(data);
    }

	else if (index < Size)
	{

		Node *previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node *newNode = new Node(data, previous->pNext, previous);

		Node *next = previous->pNext;
		previous->pNext=newNode;
		next -> pPrev = newNode;
        next = nullptr;
        previous = nullptr;
		Size++;
	}
}


void List::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if(index == Size-1)
    {
        pop_back();
    }
	else
	{
		Node *previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node *toDelete = previous->pNext;
		previous->pNext->pNext->pPrev = previous;
		previous->pNext = previous->pNext->pNext;
        delete toDelete;
		Size--;
	}

}


List::List(const List &lst)
{
    Size = 0;
    clear();
    Node* tmp = lst.head;
    while(tmp)
    {
        push_back(tmp->data);
        tmp = tmp->pNext;
    }
    tmp = nullptr;
}

List& List::operator= (const List& str)
{
    if(this==&str)
       return *this;
    while(head)
       pop_front();

    Node* tmp = str.head;
    while(tmp)
    {
        push_back(tmp->data);
        tmp = tmp->pNext;
    }
    tmp = nullptr;
    return *this;
}


void List::AddR(const List& str)
{
    List tmp;
    tmp = str;
    tmp.cur = tmp.head;
    while(tmp.cur)
    {
        push_back(tmp.cur->data);
        tmp.cur = tmp.cur->pNext;
    }
}

void List::AddL(const List& str)
{
    List tmp;
    tmp = str;
    tmp.cur = tmp.tail;
    while(tmp.cur)
    {
        push_front(tmp.cur->data);
        tmp.cur = tmp.cur->pPrev;
    }
}



void List::print() const
{
   Iterator l(this);
   do
   {
       printf("%s\n", l.val->data);
   } while (++l);
   printf("\n\n");
}



int List::read(FILE* fin)
{
    clear();
    Node* tmp;
    tmp = new Node();

    if (tmp == nullptr)
    {
        return -1;
    }

    int ret = tmp -> read (fin);
    if (ret < 0)
    {
        return delete tmp, ret;
    }
    if(ret > 0)
    {
        return delete tmp, ret;
    }

	head = cur = tail = tmp;

	for (;;)
	{
            tmp = new Node();
            if (tmp == nullptr)
            {
                return -1;
            }
            ret = tmp -> read (fin);


            if (ret < 0)
            {
                return delete tmp, ret;
            }
            if(ret > 0)
            {
                tail = cur;
                Size++;
                return delete tmp, ret;
            }

            cur -> pNext = tmp;
            tmp -> pPrev = cur;
            cur = tmp;
            tail = cur;
            tmp = nullptr;
            Size++;
	}
	return 0;
}

int Node::read(FILE* fin)
{
    char buff[LEN];
    
    if (fgets(buff, LEN, fin) == nullptr)
    {
        if(feof(fin))
        {
                return 1;
        }
        return -2;
    }

    data = new char [strlen(buff) + 1];
    if(data == nullptr)
    {
        return -1;
    }
    strcpy(data, buff);
    if(!feof(fin)) data[strlen(data)-1] = '\0';
    return 0;
}

void Node::destroy()
{
    if(data)
    {
        delete [] data;
        data = nullptr;
    }
}
