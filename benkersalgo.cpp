#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int n,r;
    cout<<"Enter the number of process : ";
    cin>>n;
    cout<<"Enter the number of resource : ";
    cin>>r;
    vector<vector<int>> allocation(n,vector<int>(r,0));
    vector<vector<int>> maxNeed(n,vector<int>(r,0));
    vector<vector<int>> needed(n,vector<int>(r,0));
    vector<int> available(r,0);

    cout<<"Enter allocation Matrix :\n";

    for(int i=0; i<n; ++i){
        for(int j=0; j<r; ++j){
            cin>>allocation[i][j];
        }
    }

    cout<<"Enter max Matrix : \n";

    for(int i=0; i<n; ++i){
        for(int j=0; j<r; ++j){
            cin>>maxNeed[i][j];
            needed[i][j]=maxNeed[i][j]-allocation[i][j];
        }
    }

    cout<<"Enter Available resource \n";

    for(int j=0; j<r; ++j){
        cin>>available[j];
    }

    vector<bool> isDone(n,false);
    vector<int> safeSequence;
    int count=0;
    while(count<n){
        bool found=false;
        for(int i=0; i<n; ++i){
            if(!isDone[i]){
                bool canAllocate=true;
                for(int j=0; j<r; ++j){
                    if(needed[i][j]>available[j]){
                        canAllocate=false;
                        break;
                    }
                }
                if(canAllocate){
                    for(int j=0; j<r; ++j){
                        available[j]+=needed[i][j];
                    }
                    isDone[i]=true;
                    safeSequence.push_back(i);
                    found=true;
                    count++;
                }
            }
        }
        if(!found){
            cout<<"\nSystem is not in safe state (Deadlock possible)"<<endl;
            return 0;
        }
    }

    cout<<"System in Safe State.\nSafe Sequence is: ";

    for(int i=0; i<n; ++i){
        cout<<"p"<<safeSequence[i];
        if(i<n-1) cout<<"->";
    }
    cout<<endl;

}