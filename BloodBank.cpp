#include<iostream>
using namespace std;
struct Bloodunit {
    int id,quantity;
    string group,component,collectiondDate,expiryDate,testingStatus,location,status;
};
struct Hospital {
    int id;
    string name,contact;
};
struct Bloodrequest {
    int id,hospitalid,units,allocated,urgency;
    string group,component,requestDate,status;
};
