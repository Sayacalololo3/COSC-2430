#include  "Btree.h"


int main(int argc, char* argv[]){
    ArgumentManager am(argc,argv);
    ifstream ifs(am.get("input"));
    ifstream command(am.get("command"));
    ofstream ofs(am.get("output"));
    int num;
    while(ifs >> num){
        cout << num << " " ;
    }
}