#include<iostream>
#include<vector>
using namespace std;
class process{
    public:
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int turnAroundTime;
    int complitationTime;
    int waitingTime;
};

int main(){
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;
    cout<<"------------------------------------------------\n";
    vector<process> processes(n);

    for(int i=0; i<n; ++i){
        cout<<"Enter the arrival Time of process p"<<i+1<<" : ";
        processes[i].pid=i+1;
        cin>>processes[i].arrivalTime;

        cout<<"Enter the burst Time of process p"<<i+1<<" : ";
        cin>>processes[i].burstTime;
        processes[i].remainingTime=processes[i].burstTime;
        cout<<"------------------------------------------------\n";
    }

    int currentTime=0, completed=0;
    float totalTAT=0.0, totalWT=0.0;
    while(completed<n){
        int inx=-1;
        int sj=INT_MAX;
        for(int i=0; i<n; ++i){
            if(processes[i].remainingTime!=0 && processes[i].arrivalTime<=currentTime){
                if(processes[i].burstTime<sj){
                    inx=i;
                    sj=processes[i].burstTime;
                }
                else if(processes[i].burstTime==processes[inx].burstTime
                && processes[i].arrivalTime<processes[inx].arrivalTime){
                    inx=i;
                }
            }
        }
        if(inx==-1){
            ++currentTime;
        } else {
            process &p=processes[inx];
            p.complitationTime=currentTime+p.burstTime;
            p.turnAroundTime=p.complitationTime-p.arrivalTime;
            p.waitingTime=p.turnAroundTime-p.burstTime;
            p.remainingTime=0;
            currentTime=p.complitationTime;
            ++completed;
        }
    }
    cout<<"\nprocess\tAT\tBT\tCT\tTAT\tWT\n";

    for(const auto &p: processes){
        cout<<'p'<<p.pid<<"\t"<<p.arrivalTime<<"\t"<<p.burstTime<<"\t"<<p.complitationTime<<"\t"<<p.turnAroundTime<<"\t"<<p.waitingTime<<endl;
    }

    cout<<"\n AVG WT = "<<(totalWT/n)<<endl;

    cout<<"\n AVG TAT = "<<(totalTAT/n)<<endl;
}