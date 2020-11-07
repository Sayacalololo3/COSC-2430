#include "doublelink.h"

void removeSpaces(string &str){ 
    for(int i = 0;i < str.length();i++){
            if(str[i] == ' '){
                str.erase(i--,1); // removes spaces
            }
        }
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc,argv);
    ifstream ifs(am.get("input"));
    ifstream command(am.get("command"));
    ofstream ofs(am.get("output"));
    string line;
    doublelink dd;
    stack reserve;
    while(getline(ifs,line)){
        if(line.empty()){
            continue;
        }
        removeSpaces(line);
        dd.add(line);
    }
    while(command >> line){
        if(line == "printList"){
            dd.print_forwards(ofs);
        }
        if(line == "printListBackwards"){
            cout << "tyeet";
            dd.print_backwards(ofs);
        }
        if(line == "convertList"){
            command >> line;
            if(line == "(postfix)"){
                dd.all_to_postfix();
            }
            else if(line == "(prefix)"){
                dd.all_to_prefix();
            }
            else if(line == "(all)"){
                dd.convert_all();
            }
            else{
                int index = stoi(line.substr(1,line.length()-2));
                dd.convert_index(index);
            }
        }
        if(line == "pushReserve"){
            command >> line;
            if(line == "(postfix)"){
                dd.push_reserve_postfix(reserve);
            }
            else if(line == "(prefix)"){
                dd.push_reserve_prefix(reserve);
            }
            else if(line == "(all)"){
                dd.push_reserve_all(reserve);
            }
            else{
                int index = stoi(line.substr(1,line.length()-2));
                dd.push_reserve_index(reserve,index);
            }    
        }
        if(line == "removeList"){
            command >> line;
            if(line == "(postfix)"){
                dd.remove_postfix();
            }
            else if(line == "(prefix)"){
                dd.remove_prefix();
            }
            else if(line == "(all)"){
                dd.remove_all();
            }
            else{
                int index = stoi(line.substr(1,line.length()-2));
                dd.remove(index);
            }    
        }
        if (line == "printReserveTop"){
            ofs << "Top of Reserve: " << (reserve.empty() ? "EMPTY" : reserve.top()) << endl << endl;
        }
        if (line == "popReserve"){
            command >> line;
            int index = stoi(line.substr(1,line.length()-2));
            dd.insert(reserve.top(),index);
            reserve.pop();
        }
        if (line == "emptyReserve"){
            command >> line;
            int index = stoi(line.substr(1,line.length()-2));
            dd.empty_reserve(reserve,index);

        }
        if (line == "printReserveSize"){
            ofs << "Reserve Size: " << reserve.getsize() << endl << endl;
        }
        if (line == "flipReserve"){
            reserve.doubly_reverse(reserve.gethead());
        }
        if(line == "convertReserve"){
            reserve.convert_top();
        }
    }
    ofs << endl;
}