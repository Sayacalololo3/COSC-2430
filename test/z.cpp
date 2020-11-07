#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
//my dear friend jason helped me to understand so his understanding and my understanding is basically the same :)
// i'm really trying
using namespace std;

struct node{
    int input;
    struct node *list;
};
void print(node* point){
    if(point->list != NULL){
        return;
    }
    print(point->list);
    cout << point->input << " ";
    //if i wanted forwards this is the way print(point->list // so that it would iterate for the next node); 
}


int main() {
    string blah = "problem_id:321038, problem_name:Binary Search Tree to Greater Sum Tree, difficulty:Medium";
    return 0;
}