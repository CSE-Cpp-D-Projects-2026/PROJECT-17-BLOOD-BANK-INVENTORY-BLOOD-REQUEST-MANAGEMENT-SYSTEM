#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>
#include<queue>
#include<stack>
using namespace std;
struct BloodUnit
{
    int id,quantity;
    string group,component,collectionDate,expiryDate,testingStatus,location,status;
};

struct Hospital
{
    int id;
    string name,contact;
};

struct BloodRequest
{
    int id,hospitalId,units,allocated,urgency;
    int hospitalId;
    string group,component,requestedDate,status;
};
vector<BloodUnit> blood;
vector<Hospital> hospitals;
vector<BloodRequest> requests;
list<int> transactionHistory;
set<int> usedUnitIds;
map<int, string> hospitalNames;
queue<int> waitingRequests;
stack<string> undoHistory;
