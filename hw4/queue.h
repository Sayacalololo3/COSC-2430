#include "ArgumentManager.h"
#include <fstream>
 
struct process{
    int start, wait, end, burst_time, excecution, priority;
    process* next;
    process(int b){
        excecution = burst_time = b;
        start = end = 0;
        wait = 0;
        next = NULL;
    }
    process(process *r){
        start = r->start;
        wait = r->wait;
        end = r->end;
        burst_time = r->burst_time;
        excecution = r->excecution;
        priority = r->priority;
        next = NULL;
    }
};
 
class queue{
    private:
    process *head, *tail;
    int size;
    public:
    queue(){
        head = tail = NULL;
        size = 0;
    }
    void push(process* new_process){
        if(head == NULL){
            head = tail = new_process;
        }
        else{
            tail = tail->next = new_process;
        }
        size++;
    }
    void pop(){
        if(head == NULL){
            return;
        }
        process* temp = head;
        head = head->next;
        delete temp;
    }
    process* front(){
        return head;
    }
    void print(ofstream &ofs){
       process* current = head;
       while(current != NULL){
           ofs << "Process: " << current->priority << endl
               << "Execution time: " << current->excecution << endl
               << "Wait Time: " << current->wait << endl
               << "Start Time: " << current->start << endl
               << "End Time: " << current->end << endl << endl;
           current = current->next;
       }
    }
    bool empty(){
        return head == NULL;
    }
    int get_size(){
        return size;
    }
    void update_burst(){
        process *current = head;
        while(current != NULL){
            current->wait++;
            current = current->next;
        }
    }
    void priority_push(process* n){
        size++;
        if(head == NULL){
            head = n;
            return;
        }
        if(head->priority > n->priority){
            n->next = head;
            head = n;
            return;
        }
        process* prev = head;
        process* current = head->next;
        while(current != NULL){
            if(current->priority > n->priority){
                prev->next = n;
                n->next = current;
                return;
            }
            prev = prev->next;
            current = current->next;
        }
        prev->next = n;
    }
};
