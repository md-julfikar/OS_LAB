#include <iostream>
# include <vector>
#include <algorithm>
using namespace std;
class process{
    public:
    int pid;
    int arrivalTime;
    int bustTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};
bool compare_arrival(process p1, process p2){
    return p1.arrivalTime<p2.arrivalTime;
}
int main(){
    int n;
    cout<<"Enter the Number of Process : ";
    cin>>n;
    vector <process> processes(n);

    for(int i=0; i<n; ++i){
        processes[i].pid=i+1;
        cout<<"enter arrival time of process p"<<i+1<<" : ";
        cin>>processes[i].arrivalTime;

        cout<<"enter Bust time of process p"<<i+1<<" : ";
        cin>>processes[i].bustTime;

    }

    sort(processes.begin(),processes.end(),compare_arrival);

    int currentTime=0;
    float totalWT=0, totalTAT=0;

    for(int i=0; i<n; ++i){
        if(currentTime<processes[i].arrivalTime){
            currentTime=processes[i].arrivalTime;
        }

        processes[i].completionTime=currentTime+processes[i].bustTime;
        processes[i].turnAroundTime=processes[i].completionTime-processes[i].arrivalTime;
        processes[i].waitingTime=processes[i].turnAroundTime-processes[i].bustTime;

        currentTime=processes[i].completionTime;
        totalWT+=processes[i].waitingTime;
        totalTAT+=processes[i].turnAroundTime;
    }



    cout<<"\nprocess\tAT\tBT\tCT\tTAT\tWT\n";

    for(const auto &p: processes){
        cout<<'p'<<p.pid<<"\t"<<p.arrivalTime<<"\t"<<p.bustTime<<"\t"<<p.completionTime<<"\t"<<p.turnAroundTime<<"\t"<<p.waitingTime<<endl;
    }

    cout<<"\n AVG WT = "<<(totalWT/n)<<endl;

    cout<<"\n AVG TAT = "<<(totalTAT/n)<<endl;

}