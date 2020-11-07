#include "queue.h"

class server{
    private:
    bool availible;
    int time;
    process *task;
    
    public:
    server(){
        time = 0;
        availible = true;
        task = NULL;
    }
    void add(process *t,int tick){
        task = new process(t);
        if(task->burst_time == task->excecution){
            task->start = tick;
        }
        time = 0;
        availible = false;
        update();
    }
    void remove(){
        time = 0;
        task = NULL;
        availible = true;
    }
    int get_time(){
        return time;
    }
    bool is_availible(){
        return availible;
    }
    void update(){
        time++;
        task->burst_time--;
    }
    process* get_task(){
        return task;
    }

};