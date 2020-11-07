#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

class linked_list
{
private:
    Node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_Node(int n)
    {
        Node *tmp = new Node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    Node* gethead()
    {
        return head;
    }

    static void display(Node *head)
    {
        if(head == NULL)
        {
            cout << "NULL" << endl;
        }
        else
        {
            cout << head->data << endl;
            display(head->next);
        }
    }

    static void concatenate(Node *a,Node *b)
    {
        if( a != NULL && b!= NULL )
        {
            if (a->next == NULL)
                a->next = b;
            else
                concatenate(a->next,b);
        }
        else
        {
            cout << "Either a or b is NULL\n";
        }
    }
};

int main()
{
    linked_list a;
    a.add_Node(1);
    a.add_Node(2);
    linked_list b;
    b.add_Node(3);
    b.add_Node(4);
    linked_list::concatenate(a.gethead(),b.gethead());
    linked_list::display(a.gethead());
    return 0;
}