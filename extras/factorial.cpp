#include <iostream>


using namespace std;


int abSub(int a,int b){
    return (a > b) ? a - b: b - a;
}

int factorial(int n){
    return (n <= 1 ? 1 : n * factorial(n - 1));
}
int main(){
    int num;
    cout << "enter a number:\n";
    cin >> num;
    cout << "The factorial of "<< num <<" is " <<factorial(num) << endl;
}