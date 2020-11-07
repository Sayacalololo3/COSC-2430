#include <iostream>
#include <map>
#include <fstream>
#ifndef LINKEDLinkedList_H
#define LINKEDLinkedList_H
using namespace std;
struct Node{
   int id;
   string name;
   int difficulty;
   struct Node *next;
   Node(int _id,string _name,int _diffuculty){
       id = _id;
       name = _name;
       difficulty = _diffuculty;
   }
};
class LinkedList{
    private:
        Node *head,*tail;
        int length = 0;
        string Id_Library;
    public:
    LinkedList();
        Node* getHead();
        void append(Node);
        int getLength();
        void sort(int);
        void print_forwards(Node*,ofstream&);
        void insert(Node,int);
        Node* getNode(int);
        void removePosition(int);
        void removeId(int);
        void removeName(string);
        void removeDifficulty(string);
        string getIdLibrary();
};
LinkedList::LinkedList(){
        head = NULL;
        tail = NULL;
}
Node* LinkedList::getHead(){
        return head;
}
int LinkedList::getLength(){
        return length;
}

Node* LinkedList::getNode(int position){
    Node* current = head;
    for(int i = 0;i<position;i++){
        current = current->next;
    }
    return current;
}
void LinkedList::append(Node new_data) {
    
    if(Id_Library.find(to_string(new_data.id)) != string::npos){
        return;
    }
    // Create new node and load in the data
    Node* new_node = new Node(new_data);
    // set next node to null

    new_node->next = NULL;
    if(head == NULL){
        head = new_node;
        tail = new_node;
    }
    else{
        tail->next = new_node;
        tail = tail->next;
    }
    length++;
    Id_Library.append("-" + to_string(new_node->id) + "-");
}

void LinkedList::insert(Node data, int position){
    Node* mynode = new Node(data);
    if(head == NULL){
        Id_Library.clear();
        mynode->next = NULL;
        head = mynode;
        tail = mynode;
        Id_Library.append("-" + to_string(mynode->id) + "-");
        length++;
        return;
    }
    if(Id_Library.find(to_string(data.id)) != string::npos){
        return;
    }
    if(position <=  0){
        mynode->next = head;
        head = mynode;
        return;
    }
    Node* current = head;
    int i = 0;
    for(int i = 0;current->next!=NULL && i < position-1;i++){ 
        current = current->next;
    }
    mynode->next = current->next;
    current->next = mynode;
    Id_Library.append("-"+to_string(mynode->id) + "-"); 
}
void LinkedList::print_forwards(Node *begin,ofstream &ofs) {
    map<int,string> ToString;
    ToString[1] = "Easy";
    ToString[2] = "Medium";
    ToString[3] = "Hard";
    if(begin== NULL){
            return;
    }
    ofs <<"problem_id:" <<begin->id << ", problem_name:" << begin->name << ", difficulty:"<< ToString[begin->difficulty] << endl;
    print_forwards(begin->next,ofs);      
}
bool swapNodes(Node* right,Node* left){
    Node temp(right->id,right->name,right->difficulty);
    right->id = left->id;
	right->name = left->name;
	right->difficulty = left->difficulty;

	left->id = temp.id;
	left->name = temp.name;
	left->difficulty = temp.difficulty;
    return true;
}
void LinkedList::sort(int state){
    int count = length;
    while(count--){
        Node* current = head;
        while(current->next != NULL){
            int count = 0;
            switch (state){
                case 1: 
                    count += (current->id > current->next->id);
                    break;
                case 2: 
                    count += (current->id < current->next->id);
                    break;
                case 3: 
                   count += (current->name > current->next->name);
                break;
                case 4: 
                    count += (current->name < current->next->name);
                    break;
                case 5: 
                    count += (current->difficulty > current->next->difficulty);
                    break;
                default:
                    count += (current->difficulty < current->next->difficulty);
                    break;
            }
            if(count != 0){
                swapNodes(current,current->next);
            }
            current = current->next;
        }
    }
}
void LinkedList::removePosition(int position) { 
    if (head == NULL || position < 0){
            return; 
    }
    else if(position == 0){ 
        Node* temp = head;
        head = head->next;
        length--; 
        delete temp; // gets rid of first node 
        return; 
    }
    
    // Find previous node of the node to be deleted 
    int i = 1;
    Node* current = head; 
    while(current->next!=NULL && i++ < position){ 
        current = current->next;
    }
    // Out of bounds
    if (current->next == NULL){
        return; 
    }
    int index = Id_Library.find(to_string(current->next->id));
    Id_Library.erase(index,6);
    length--; 
    Node *new_next = current->next->next; 
    delete current->next;
    current->next = new_next; 
}
void LinkedList::removeId(int id){
    Node** current = &head; 
    while (*current != NULL) { 
        Node* key = *current;
        if (key->id == id) {
            int index = Id_Library.find(to_string(key->id));
            Id_Library.erase(index,7);
            *current = key->next; //changes the references pointer
            delete key;
            length--;
            return;
        } 
        current = &key->next; // moves to next node
    } 
}
void LinkedList::removeName(string name){
    Node** current = &head; 
    while (*current != NULL) { 
        Node* key = *current;
        if (key->name == name) { 
            int index = Id_Library.find(to_string(key->id));
            Id_Library.erase(index,7);
            *current = key->next; //changes the references pointer
            delete key;
            length--;
        }
        else{
             current = &key->next; // moves to next node
        } 
    } 
}
void LinkedList::removeDifficulty(string name){
    map<int,string> ToString;
    ToString[1] = "Easy";
    ToString[2] = "Medium";
    ToString[3] = "Hard";
    Node** current = &head; 
    while (*current != NULL) { 
        Node* key = *current;
        if (ToString[key->difficulty] == name) { 
            int index = Id_Library.find(to_string(key->id));
            Id_Library.erase(index,7);
            *current = key->next; //changes the references pointer
            delete key;
            length--; 
        }
        else{
             current = &key->next; // moves to next node
        } 
    } 
}
string LinkedList::getIdLibrary(){
    return Id_Library;
}
#endif