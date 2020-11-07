#include "ArgumentManager.h"
#include <sstream>
#include "linkedlist.h"

int main(int argc, char* argv[]){
	ArgumentManager am(argc,argv);
    ifstream ifs(am.get("input"));
    ofstream ofs(am.get("output"));
    ifstream command(am.get("command"));
    string line;
	map<string,int> To_Num;
    To_Num["Easy"] = 1;
    To_Num["Medium"] = 2;
    To_Num["Hard"] = 3;
    LinkedList mylist;      
   while(getline(ifs,line)){
        if(line.empty()){
        	continue;
        }
        int nameIndex = line.find_first_of(',');
        int difficultyIndex = line.find_last_of(',');
        string diff = line.substr(difficultyIndex,line.length());
		int id = stoi(line.substr(11,nameIndex));
		// stooooooopid !! string.substr(starting,length) !! second variable is not the end but how many chars you want to grab
		int toGrab = line.length() - diff.length() - nameIndex - 15;
		string name = line.substr(nameIndex + 15,toGrab);
        
		int difficulty = To_Num[line.substr(difficultyIndex + 13,line.length())];
        Node temp(id,name,difficulty);
        mylist.append(temp);
   }

    while(getline(command,line)){
        if(line.empty()){ 
            continue;
        }
        if(line[0] == 's'){
            if(mylist.getLength() <= 1){
                continue;
            }
            int state = 0;
            // 3 states : for id, name, and difficulty :
            state += (line.find("problem_id") != string::npos)? 1:0;
            state += (line.find("problem_name") != string::npos) ? 3:0;
            state += (line.find("difficulty") != string::npos) ? 5:0;
            state += (line.find("decreasing") != string::npos); // sort in decreasing or increasing order
            mylist.sort(state);
        }
        else if(line[0] == 'a'){
            int id_index = line.find("id:");
            int add_id = stoi(line.substr(id_index+3,6));
            // makes the Node object
            int difficultyIndex = line.find_last_of(',');
            string diff = line.substr(difficultyIndex,line.length());
            int name_index = line.find("ame:");
            string add_name = line.substr(name_index+4,line.length() - diff.length() - name_index - 4);
            int add_difficulty = To_Num[line.substr(difficultyIndex + 13,line.length())];
            Node new_node(add_id,add_name,add_difficulty);

            int index = line.find("problem_id:");
            int position = stoi(line.substr(8,index - 9));
            
            mylist.insert(new_node,position);
        }
        else if(line[0] == 'r'){
            if(line.find("pos:") != string::npos){
                int index = line.find(':') + 1;
                int pos = stoi(line.substr(index,line.length()-index));
                mylist.removePosition(pos);
            }
            else if(line.find("problem_id") != string::npos){
                int index = line.find(':') + 1;
                int remove_id = stoi(line.substr(index,line.length()-index));
                mylist.removeId(remove_id);
            }
            else if(line.find("problem_name") != string::npos){
                int index = line.find(':') + 1;
                string remove_name = line.substr(index,line.length()-index);
                mylist.removeName(remove_name);
            }
            else if(line.find("difficulty:") != string::npos){
                int index = line.find(':') + 1;
                string remove_difficulty = line.substr(index,line.length()-index);
                mylist.removeDifficulty(remove_difficulty);
            }
        }  
    }
    mylist.print_forwards(mylist.getHead(),ofs);
}