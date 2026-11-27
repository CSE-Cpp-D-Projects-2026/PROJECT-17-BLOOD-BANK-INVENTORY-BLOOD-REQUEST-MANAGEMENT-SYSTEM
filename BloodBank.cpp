#include<vector>
#include<list>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include <iostream>
using namespace std;
struct BloodUnit {
    int id,quantity;
    string group,component,collectionDate,expiryDate,testingStatus,location,status;
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
int compatibility[8][8] ={
    {1,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0},
    {1,0,1,0,0,0,0,0},
    {1,1,1,1,0,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,1,0,0,1,1,0,0},
    {1,0,1,0,1,0,1,0},
    {1,1,1,1,1,1,1,1}
};
void addUnit();
void addHospital();
void addRequest();
void showUnits();
void showHospitals();
void showRequests();
void allocateBlood();
void searchUnit();
void updateUnit();
void cancelRequest();
void stockReport();
void saveData();
void loadData();
void saveBinary();
void loadBinary();
int findUnit(int id);
int findHospital(int id);
int findRequest(int id);
bool isCompatible(string recipient, string donor);
bool isExpired(string date);
bool isValidDate(string date);
void clearInput();
void showMenu();
inline int remainingUnits(int total, int allocated)
{
    return total - allocated;
}
int calculateTotal(int units)
{
    return units * 100;
}
int calculateTotal(int units, int price)
{
    return units * price;
}
template <class T>
void showMessage(T message)
{
    cout << message << endl;
}
template <>
void showMessage<string>(string message)
{
    cout << "MESSAGE: " << message << endl;
}
template <class T>
class Record
{
public:
    T value;

    Record(T v)
    {
        value = v;
    }

    void display()
    {
        cout << value << endl;
    }
};
class Report
{
public:

    virtual void generate() = 0;
    virtual ~Report()
    {
     }
};
class StockReport : public Report
{
public:

    void generate() override
    {
        cout << "\n----- STOCK REPORT -----\n";

        for (int i = 0; i < (int)blood.size(); i++)
        {
            cout << blood[i].id << " "
                 << blood[i].group << " "
                 << blood[i].component << " "
                 << blood[i].quantity << " "
                 << blood[i].status << endl;
        }
    }
};
class BloodBank
{
private:
    string bankName;
public:
    static int totalOperations;
     BloodBank()
    {
        bankName = "Simple Blood Bank";
    }

    // Parameterized constructor
    BloodBank(string name) : bankName(name)
    {
     }
   BloodBank(const BloodBank &b)
    {
        bankName = b.bankName;
    }
    ~BloodBank()
    {
    }
    void display()
    {
        cout << "Blood Bank: " << bankName << endl;
    }
    void operation()
    {
        totalOperations++;
    }
    static void showOperations()
    {
        cout << "Total operations: " << totalOperations << endl;
    }
    void changeName(string name)
    {
        this->bankName = name;
    } 
       friend void showBankName(BloodBank b);
};
int BloodBank::totalOperations = 0;

void showBankName(BloodBank b)
{
    cout << "Bank name: " << b.bankName << endl;
}
class Quantity
{
public:
    int value;
    Quantity(int v = 0)
    {
        value = v;
    }
    Quantity operator+(Quantity q)
    {
        return Quantity(value + q.value);
    }
    bool operator<(Quantity q)
    {
        return value < q.value;
    }
};
