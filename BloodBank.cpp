#include<iostream>
using namespace std;
struct Bloodunit {
    int id,quantity;
    string group,collectiondate,expirydate,testingstatus,location,status;
};
struct Hospital {
    int id;
    string name,contact;
};
struct Bloodrequest {
    int id,hospitalid,unit,allocated,urgency;
    string group,componenet,requestdate,status;
};