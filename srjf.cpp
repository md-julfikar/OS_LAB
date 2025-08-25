#include<iostream>
#include<vector>
using namespace std;
class Process{
    public:
    int pid;
    int arrivalTime;
    int remainingTime;
    int burstTime;
    int turnAroundTime;
    int WaitingTime;
    int completionTime;
    Process():
    pid(0), arrivalTime(0),remainingTime(0),burstTime(0),turnAroundTime(0),
    WaitingTime(0),completionTime(0) {}
};


int main(){
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;
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
    while(completed<n){
        int inx=-1;
        int srtn=INT_MAX;

        for(int i=0; i<n; ++i){
            if(processes[i].remainingTime!=0 && processes[i].arrivalTime<=currentTime){
                if(processes[i].remainingTime<srtn){
                    inx=i;
                    srtn=processes[i].remainingTime;
                }
                else if(processes[i].remainingTime==srtn && processes[i].arrivalTime<processes[inx].arrivalTime){
                    inx=i;
                }
            }
        }

        if(inx==-1){
            ++currentTime;
        }
        else{
            Process &p=processes[inx];
            --p.remainingTime;
            ++currentTime;

            if(p.remainingTime==0){
                p.completionTime=currentTime;
                p.turnAroundTime=currentTime-p.arrivalTime;
                p.WaitingTime=p.turnAroundTime-p.burstTime;
                totalTAT+=p.turnAroundTime;
                totalWT+=p.WaitingTime;
                ++completed;
            }
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
            << p.WaitingTime << "\n";
    }

    cout << "\nAverage Turnaround Time: " << avgTAT;
    cout << "\nAverage Waiting Time: " << avgWT << "\n";
    return 0;
}