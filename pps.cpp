#include<iostream>
#include<vector>
using namespace std;
class process{
    public:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int turnAroundTime;
    int completedTime;
    int waitingTime;
};
int main()
{
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;

    vector<process> processes(n);

    for(int i=0; i<n; ++i){
        cout<<"Enter the arrival Time of process p"<<i+1<<" : ";
        processes[i].pid=i+1;
        cin>>processes[i].arrivalTime;

        cout<<"Enter the burst Time of process p"<<i+1<<" : ";
        cin>>processes[i].burstTime;
        processes[i].remainingTime=processes[i].burstTime;

        cout<<"Enter the priority of process p"<<i+1<<" : ";
        cin>>processes[i].priority;
        cout<<"------------------------------------------------\n";
    }
    int currentTime=0, completed=0;
    float totalTAT=0.0, totalWT=0.0;
    vector<bool> isDone(n,false);
    while(completed<n){
        int inx=-1;
        int mxp=1e9;
        for(int i=0; i<n; ++i){
            if(!isDone[i] && processes[i].arrivalTime<=currentTime){
                if(processes[i].priority<mxp){
                    inx=i;
                    mxp=processes[i].priority;
                }
                else if(processes[i].priority==processes[inx].priority &&
                processes[i].arrivalTime<processes[inx].arrivalTime){
                    inx=i;
                }
            }
        }
        if(inx==-1){
            ++currentTime;
        }
        else{
            --processes[inx].remainingTime;
            ++currentTime;

            if(processes[inx].remainingTime==0){
                processes[inx].completedTime=currentTime;
                processes[inx].turnAroundTime=currentTime-processes[inx].arrivalTime;
                processes[inx].waitingTime=processes[inx].turnAroundTime-processes[inx].burstTime;
                isDone[inx]=true;
                ++completed;
                totalTAT+=processes[inx].turnAroundTime;
                totalWT+=processes[inx].waitingTime;
            }

        }
        
    }
    return 0;
}