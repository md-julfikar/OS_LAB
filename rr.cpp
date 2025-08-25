#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
class Process{
    public:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int turnAroundTime;
    int waitingTime;
    int completionTime;
};


int main(){
    int n,quantum;
    cout<<"Enter The Number of Process : ";
    cin>>n;
    cout<<"Enter Time Quantum : ";
    cin>>quantum;
    cout<<"------------------------------\n";
    vector<Process> processes(n);
    for(int i=0; i<n; ++i){
        processes[i].pid=i+1;
        cout<<"Enter the arrival Time of process p"<<i+1<<" : ";
        cin>>processes[i].arrivalTime;
        cout<<"Enter the Burst Time of process p"<<i+1<<" : ";
        cin>>processes[i].burstTime;
        processes[i].remainingTime=processes[i].burstTime;
        cout<<"-------------------------------------------\n";
    }
    int currentTime=0, completed=0;
    float totalWT=0, totalTAT=0;
    queue<int> q;
    vector<bool> inque(n,false);
    while(completed<n){
        for(int i=0; i<n; ++i){
            if(!inque[i] && processes[i].arrivalTime<=currentTime && processes[i].remainingTime>0){
                q.push(i);
                inque.at(i)=true;
            }
        }
        if(q.empty()){
            ++currentTime;
            continue;
        }
        int inx=q.front();
        q.pop();
        int execTime=min(quantum,processes[inx].remainingTime);
        processes[inx].remainingTime-=execTime;
        currentTime+=execTime;
        for(int i=0; i<n; ++i){
            if(!inque[i] && processes[i].arrivalTime<=currentTime && processes[i].remainingTime>0){
                q.push(i);
                inque.at(i)=true;
            }
        }
        if(processes[inx].remainingTime>0){
            q.push(inx);
            inque[inx]=true;
        }
        else{
            processes[inx].completionTime=currentTime;
            processes[inx].turnAroundTime=currentTime-processes[inx].arrivalTime;
            processes[inx].waitingTime=processes[inx].turnAroundTime-processes[inx].burstTime;
            inque[inx]=false;
            totalTAT+=processes[inx].turnAroundTime;
            totalWT+=processes[inx].waitingTime;
            ++completed;
        }
    }
    float avgTAT=totalTAT/n, avgWT=totalWT/n;
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(const auto& p : processes){
        cout << "P" << p.pid << "\t"
            << p.arrivalTime << "\t"
            << p.burstTime << "\t"
            << p.completionTime << "\t"
            << p.turnAroundTime << "\t"
            << p.waitingTime << "\n";
    }

    cout << "\nAverage Turnaround Time: " << avgTAT;
    cout << "\nAverage Waiting Time: " << avgWT << "\n";
    return 0;
}