#include<vector>
#include<list>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<string>
using namespace std;
struct BloodUnit {
    int id,quantity;
    string group,collectionDate,expiryDate,testingStatus,location,status;
};
struct Hospital {
    int id;
    string name,contact;
};
struct BloodRequest {
    int id,hospitalId,units,allocated,urgency;
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
int nextUnitId = 1;
int nextHospitalId = 1;
int nextRequestId = 1;
string BloodGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};