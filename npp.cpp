#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class process{
    public:
    int pid;
    int arrivalTime;
    int bustTime;
    int waitingTime;
    int turnAroundTime;
    int completetionTime;
    int Priority;
};

int main(){
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;

    vector<process> processes(n);

    for(int i=0; i<n; ++i){
        cout<<"Enter the arrival Time of process p"<<i+1<<" : ";
        processes[i].pid=i+1;
        cin>>processes[i].arrivalTime;

        cout<<"Enter the burst Time of process p"<<i+1<<" : ";
        cin>>processes[i].bustTime;

        cout<<"Enter the priority of process p"<<i+1<<" : ";
        cin>>processes[i].Priority;
        cout<<"------------------------------------------------\n";
    }

    int currentTime=0, completed=0;
    float totalWR=0.0, totalTAT=0.0;
    vector<bool> isDone(n,false);
    while(completed<n){
        int indx=-1;
        int maxp=1e9;
        for(int i=0; i<n; ++i){
            if(!isDone[i] && processes[i].arrivalTime<=currentTime){
                if(processes[i].Priority<maxp){
                    indx=i;
                    maxp=processes[i].Priority;
                }
                else if(processes[i].Priority==processes[indx].Priority &&
                processes[i].arrivalTime<processes[indx].arrivalTime){
                    indx=i;
                }
            }
        }

        if(indx==-1){
            ++currentTime;
        }
        else{
            process &p=processes[indx];
            p.completetionTime=currentTime+p.bustTime;
            p.turnAroundTime=p.completetionTime-p.arrivalTime;
            p.waitingTime=p.turnAroundTime-p.bustTime;
            isDone[indx]=true;
            totalTAT+=p.turnAroundTime;
            totalWR+=p.waitingTime;
            currentTime=p.completetionTime;
            ++completed;
        }
    }
    cout<<"\nprocess\tAT\tBT\tCT\tTAT\tWT\n";
    for(const auto& p: processes){
        cout<<"p"<<p.pid<<"\t"<<p.arrivalTime<<"\t"<<p.bustTime<<"\t"<<p.completetionTime<<"\t"<<p.turnAroundTime<<"\t"<<p.waitingTime<<"\n";
    }
}