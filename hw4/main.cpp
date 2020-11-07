#include "server.h"
#include <vector>

void zero_case(queue &q,queue &complete,int tick){
    while(!q.empty() && q.front()->excecution == 0){
            q.front()->start = tick;
            q.front()->end = tick;
            process *zero = new process(q.front());
            complete.priority_push(zero);
            q.pop();
        }
}

int main(int argc, char* argv[]){
    ArgumentManager am(argc,argv);
    ifstream ifs(am.get("input"));
    ofstream ofs(am.get("output"));
    int max, processes, size, burst;
    ifs >> max >> processes >> size;
    ofs <<"Max time: " << max << endl
        << "Number of processes: " << processes << endl
        << "Number of servers: " << size << endl << endl;
    queue q,complete;
    vector<server> host(size);
    int count = 1;
    for(int i = 0; i < processes;i++){
        ifs >> burst;
        process *proc = new process(burst);
        proc->priority = count++;
        q.push(proc);
    }
    int tick = 0;
    zero_case(q,complete,tick);

    while(complete.get_size() != processes){
        for(int i = 0; i < host.size();i++){
            if(host[i].is_availible() && !q.empty()){
                zero_case(q,complete,tick);
                if(!q.empty()){
                    host[i].add(q.front(),tick);
                    q.pop();
                }
            }
            else if(!host[i].is_availible() && host[i].get_task() != NULL){
                if(host[i].get_task()->burst_time <= 0){
                    host[i].get_task()->end = tick;
                    complete.priority_push(host[i].get_task());
                    host[i].remove();
                    if(!q.empty()){
                        zero_case(q,complete,tick);
                        host[i].add(q.front(),tick);
                        q.pop();
                    }
                }
                else if(host[i].get_time() == max){
                    q.push(host[i].get_task());
                    host[i].remove();
                    if(!q.empty()){
                        zero_case(q,complete,tick);
                        host[i].add(q.front(),tick);
                        q.pop();
                    }
                }
                else{
                    host[i].update();
                }
            }
        }
        tick++;
        if(!q.empty()){
            q.update_burst();
        }
        
    }  
    complete.print(ofs);
}