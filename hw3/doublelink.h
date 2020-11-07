#include "stack.h"

using namespace std;

class doublelink{
    private:
    node *head,*tail;
    public:
    doublelink(){
        head = NULL;
        tail = NULL;
    }
    void add(string data){
        node* new_node = new node(data);
        if(head == NULL){
            head = new_node;
            tail = new_node;
        }
        else{
            tail->next = new_node;
            new_node->prev = tail;
            tail = tail->next;
        }
    }
    void popFront(){
        if(head == NULL){
                return;
        }
        if(head->next == NULL){
                head = NULL;
                tail = NULL;
                return;
        }
        head = head->next;
        delete head->prev;
        head->prev = NULL;
    }
    void popBack(){
        if(tail == NULL){
                return;
        }
        if(tail->prev == NULL){
                tail = NULL;
                return;
        }
        tail = tail->prev;
        delete tail->next;
        tail->next= NULL;
    }
    void remove(int index){
        if(index == 0){
            popFront();
            return;
        }
        node* current = head;
        for(int i = 0; i < index && current != NULL;i++){
            current = current->next;
        }
        if(current == NULL){
            return;
        }
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

    void print_backwards(ofstream &ofs){
        ofs << "Reversed List: \n";
        if(Empty()){
            ofs << "EMPTY\n";
        }
        node* current = tail;
        while(current != NULL){
            ofs << current->data << endl;
            current = current->prev;
        }
        ofs << endl;
    }
    void print_forwards(ofstream &ofs){
        ofs << "List:\n";
        if(Empty()){
            ofs << "EMPTY\n\n";
            return;
        }
        node* current = head;
        while(current != NULL){
            ofs << current->data << endl;
            current = current->next;
        }
        ofs << endl;

    }
    node* gethead(){
        return head;
    }
    node* gettail(){
        return tail;
    }
    string Front(){
        return head->data;
    }
    string Back(){
        return tail->data;
    }
    bool Empty(){
        return head == NULL || tail == NULL;
    }
    void insert(string val,int index){
        node *new_node = new node(val);
        node *current = head;

        if(index <= 0){
            new_node->next = head;
            head = new_node;
            return;
        }

        for(int i = 0;i < index - 1 && current != NULL; i++){
            current = current->next;
        }
        if(current == NULL){
            add(val);
            return;
        }

        new_node->next = current->next;
        new_node->prev = current;
        current->next = new_node;   
    }
    void all_to_postfix(){
        node* current = head;
        while(current != NULL){
            if(current->data[1] == 'o'){
                string input = current->data.substr(8,current->data.length());
                current->data = "prefix:" + postfix_to_prefix(input);
            }
            current = current->next;
        }
    }
    void all_to_prefix(){
        node* current = head;
        while(current != NULL){
            if(current->data[1] == 'r'){
                string input = current->data.substr(7,current->data.length());
                reverseString(input);
                current->data = "postfix:" + prefix_to_postfix(input);
            }
            current = current->next;
        }
    }
    void convert_all(){
        node* current = head;
        while(current != NULL){
            if(current->data[1] == 'r'){
                    string input = current->data.substr(7,current->data.length());
                    reverseString(input);
                    current->data = "postfix:" + prefix_to_postfix(input);
            }
            else{
                    string input = current->data.substr(8,current->data.length());
                    current->data = "prefix:" + postfix_to_prefix(input);
            }
            current = current->next;
        }
    }
    void convert_index(int index){
        node* current = head;
        for(int i = 0; i < index && current != NULL;i++){
            current = current->next;
        }
        if(current == NULL){
            return;
        }
        if(current->data[1] == 'r'){
            string input = current->data.substr(7,current->data.length());
            reverseString(input);
            current->data = "postfix:" + prefix_to_postfix(input);
        }
        else{
            string input = current->data.substr(8,current->data.length());
            current->data = "prefix:" + postfix_to_prefix(input);
        }
    }

    void push_reserve_postfix(stack &reserve){
        node* current = head;
        int i = 0;
        while(current != NULL){
            if(current->data[1] == 'o'){
                reserve.push(current->data);
                remove(i);
                i--;
            }
            current = current->next;
            i++;
        }
    }
    
    void push_reserve_prefix(stack &reserve){
        node* current = head;
        int i = 0;
        while(current != NULL){
            if(current->data[1] == 'r'){
                reserve.push(current->data);
                remove(i);
                i--;
            }
            current = current->next;
            i++;
        }
    }
    void push_reserve_all(stack &reserve){
        while(!Empty()){
            reserve.push(head->data);
            popFront();
        }
    }
    void push_reserve_index(stack &reserve,int index){
        node* current = head;
        for(int i = 0; i < index && current != NULL;i++){
            current = current->next;
        }
        if(current == NULL){
            return;
        }
        reserve.push(current->data);
        remove(index);
    }
    void empty_reserve(stack &reserve,int position){
        while(!reserve.empty()){
            insert(reserve.top(),position);
            reserve.pop();
        }
    }
    void remove_all(){
        while(!Empty()){
            popFront();
        }
        
    }
    void remove_prefix(){
        node* current = head;
        int i = 0;
        while(current != NULL){
            if(current->data[1] == 'r'){
                remove(i);
                i--;
            }
            current = current->next;
            i++;
        }
    }
    void remove_postfix(){
        node* current = head;
        int i = 0;
        while(current != NULL){
            if(current->data[1] == 'o'){
                remove(i);
                i--;
            }
            current = current->next;
            i++;
        }
    }
};
