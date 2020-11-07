#include<iostream>
using namespace std;

#ifndef Tvector_H
#define Tvector_H

struct Problem{
    int number;
    struct Problem *next;
        Problem(); 
    Problem(char n){
        number = n;
        next = NULL;
    }
};

class Tvector{
    private:
    Problem *head,*tail;
    public:
    Tvector(){
        head = NULL;
        tail = NULL;
    }
    void push_back(char input){
        Problem *new_Problem = new Problem(input);
        if(head == NULL){
            head = new_Problem;
            tail = new_Problem;
        }
        else{
            tail->next = new_Problem;
            tail = tail->next;
        }
    }
    void removeIndex(int index){
        if(index == 0){
            Problem* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Problem *current = head;
        for(int i = 0; i < index - 1 && current != NULL;i++){
            current = current->next;
        }
        if(current == NULL || current->next == NULL){
            return;
        }
        Problem* temp = current->next->next;
        delete current->next;
        current->next = temp;
    }
    void push_front(char input){
        Problem* new_Problem = new Problem(input);
        new_Problem->next = head;
        head = new_Problem;
    }
    void pop_front(){
        Problem * temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back(){
        Problem * current = head;
        while(current->next->next != NULL){
            current = current->next;
        }
        current->next;
        delete current->next;
        current->next = NULL;
        tail = current;
    }
    void print(){
        Problem* current = head;
        while(current != NULL){
            cout << current->number << " ";
            current= current->next;
        }
    }
    int front(){
        return head->number;
    }
    int back(){
        return tail->number;
    }
    bool Empty(){
        return head == NULL;
    }
    int find(int target){
        int index = 0;
        Problem *current = head;
        while(current != NULL){
            if(current->number == target){
                return index;
            }
            index++;
            current = current->next;
        }
        return -1;
    }
};



#endif