#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>
#include<queue>
#include<stack>

using namespace std;
struct BloodUnit {
    int id,quantity;
    string group,component,collectiondDate,expiryDate,testingStatus,location,status;
};
struct Hospital {
    int id;
    string name,contact;
};
struct Bloodrequest {
    int id,hospitalid,unit,allocated,urgency;
    string group,componenet,requestdate,status;
};