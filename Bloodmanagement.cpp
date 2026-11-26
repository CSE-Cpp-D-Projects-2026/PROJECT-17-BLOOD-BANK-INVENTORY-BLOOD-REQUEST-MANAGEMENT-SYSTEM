#include<iostream>
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