#include "ArgumentManager.h"
#include <fstream>

using namespace std;


string postfix_to_prefix(string);
string prefix_to_postfix(string);
void reverseString(string&);

struct node{
    string data;
    struct node *next;
    struct node *prev;
    node(string d){
        data = d;
        next = NULL;
        prev = NULL;
    }
};

class stack{
    private:
    node *head,*tail;
    int size;
    public:
    stack(){
        head = NULL;
        size = 0;
    }
    string top(){
        return head->data;
    }
    node* gethead(){
        return head;
    }
    int getsize(){
        return size;
    }
    bool empty(){
        return head == NULL;
    }
    void push(string c){
        node *new_node = new node(c);
        size++;
        if(head == NULL){
            head = new_node;
            return;
        }
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    void pop(){
        if(head == NULL){
                return;
        }
        size--;
        if(head->next == NULL){
                head = NULL;
                return;
        }
        head = head->next;
        delete head->prev;
        head->prev = NULL;
    }
    node* doubly_reverse(node* ptr){
        if(ptr == NULL)
            return NULL;

        if(ptr->next == NULL)
        {
            head = ptr;
            ptr->prev = NULL;
            return ptr;
        }
        node* temp = doubly_reverse(ptr->next);
        temp->next = ptr;
        ptr->prev = temp;
        ptr->next = NULL;
        return ptr;
    }
    void print_forwards(ofstream &ofs){
        ofs << "Reserve:\n";
        node* current = head;
        while(current != NULL){
            ofs << current->data << endl;
            current = current->next;
        }
        ofs << endl;
    }
    void remove(int index){
        if(index <= 0){
            pop();
            size--;
            return;
        }
        node* current = head;
        for(int i = 0; i < index && current != NULL;i++){
            current = current->next;
        }
        if(current == NULL){
            return;
        }
        size--;
        if(current->next == NULL){
            current = current->prev;
            delete current->next;
            current->next = NULL;
            tail = current;
            return;
        }
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
    }
    void flip_reserve(){
        node* current = head;
        while(current != NULL){
            if(current->data[1] == 'r'){
                    string input = current->data.substr(7,current->data.length());
                    reverseString(input);
                    current->data = "postfix:" + prefix_to_postfix(input);
            }
            else if (current->data[1] == 'o'){
                    string input = current->data.substr(8,current->data.length());
                    current->data = "prefix:" + postfix_to_prefix(input);
            }
            current = current->next;
        }
    }
    void convert_top(){
        if(head == NULL){
            return;
        }
        if(head->data[1] == 'r'){
                    string input = head->data.substr(7,head->data.length());
                    reverseString(input);
                    head->data = "postfix:" + prefix_to_postfix(input);
        }
        else{
                    string input = head->data.substr(8,head->data.length());
                    head->data = "prefix:" + postfix_to_prefix(input);
        }
    }
};


void reverseString(string &s){
    int start = 0;
    int end = s.length() - 1;
    while(start < end){
        swap(s[start++],s[end--]);
    }
}

string prefix_to_postfix(string s){ 
    stack stored;
    for(char i : s){
        if(isalpha(i)){
            stored.push(string(1,i));
        }
        else{
            string var1 = stored.top();
            stored.pop();
            string var2 = stored.top();
            stored.pop();
            stored.push( var1  + var2 + i);
        }
    }
    return stored.top();
}
string postfix_to_prefix(string s){
    stack stored;
    for(char i: s){
        if(isalpha(i)){
            stored.push(string(1,i));
        }
        else{
            string var1 = stored.top();
            stored.pop();
            string var2 = stored.top();
            stored.pop();
            stored.push(i + var2 + var1);
        }
    }
    return stored.top();
} 