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
// Template specialization
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
    // Default constructor
     BloodBank()
    {
        bankName = "Simple Blood Bank";
    }

    // Parameterized constructor
    BloodBank(string name) : bankName(name)
    {
     }
       // Copy constructor
   BloodBank(const BloodBank &b)
    {
        bankName = b.bankName;
    }
    // Destructor
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
bool availableFilter(BloodUnit u)
{
  return u.status == "Available";
}
void filterUnits(bool (*filter)(BloodUnit))
{
    cout << "\nAvailable units:\n";
    for (int i=0;i<(int)blood.size(); i++)
    {
        if (filter(blood[i]))        {
           cout<<blood[i].id<< " "<<blood[i].group<< " "<<blood[i].component<<endl;
        }
    }
}
int countAvailable(int index)
{
    if (index>=(int)blood.size())
        return 0;
    int current = 0;
    if (blood[index].status == "Available")
        current = 1;
    return current + countAvailable(index + 1);
}
bool isValidDate(string date)
{
    if (date.length() != 10)
        return false;
    if (date[4]!='-'||date[7]!='-')
        return false;
    for (int i=0;i<10;i++)
    {
        if(i==4||i==7)
            continue;
        if(date[i]<'0'||date[i]>'9')
            return false;
    }
    int year=stoi(date.substr(0, 4));
    int month=stoi(date.substr(5, 2));
    int day=stoi(date.substr(8, 2));
    if(year<2000||month<1||month>12)
        return false;
    int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (year % 400==0 || (year % 4==0 && year % 100 != 0))
        days[1]=29;
    return day>=1 && day<=days[month - 1];
}
bool isExpired(string date)
{
    time_t now=time(0);
    tm *current=localtime(&now);
    char today[11];
    sprintf(today, "%04d-%02d-%02d",
            current->tm_year + 1900,
            current->tm_mon + 1,
            current->tm_mday);
    return date < string(today);
}
int findUnit(int id)
{
    for (int i=0;i<(int)blood.size(); i++)
    {
        if (blood[i].id==id)
            return i;
    }
    return -1;
}
int findHospital(int id)
{
    for (int i=0;i<(int)hospitals.size(); i++)
    {
        if (hospitals[i].id==id)
            return i;
    }
    return -1;
}
int findRequest(int id)
{
    for (int i=0; i<(int)requests.size(); i++)
    {
        if (requests[i].id == id)
            return i;
    }
    return -1;
}
bool isCompatible(string recipient, string donor)
{
    int r=-1;
    int d=-1;
    for (int i=0;i<8;i++)
    {
        if(BloodGroups[i]==recipient)
            r=i;
        if(BloodGroups[i]==donor)
            d=i;
    }
    if (r==-1 || d==-1)
        return false;
    return compatibility[r][d]==1;
}

void addUnit()
{
    BloodUnit u;
    cout<<"\nEnter unit ID: ";
    cin>>u.id;
    if (findUnit(u.id) != -1)
        throw runtime_error("Duplicate unit ID!");
    cout<<"Blood group: ";
    cin>>u.group;
    cout<<"Component: ";
    cin>>u.component;
    cout<<"Collection date (YYYY-MM-DD): ";
    cin>>u.collectionDate;
    cout<<"Expiry date (YYYY-MM-DD): ";
    cin>>u.expiryDate;
    if (!isValidDate(u.collectionDate) ||
        !isValidDate(u.expiryDate))
        throw runtime_error("Invalid date!");
    if (u.expiryDate < u.collectionDate)
        throw runtime_error("Expiry date cannot be earlier!");
    cout<<"Quantity: ";
    cin>>u.quantity;
    if (u.quantity<=0)
        throw runtime_error("Quantity must be positive!");
    cout<<"Testing status (Tested/Untested): ";
    cin>>u.testingStatus;
    cout<<"Storage location: ";
    cin>>u.location;
    if (u.group != "O-" && u.group != "O+" && u.group != "A-" && u.group != "A+" && u.group != "B-" && u.group != "B+" && u.group != "AB-" && u.group != "AB+")
        throw runtime_error("Invalid blood group!");
    if (u.component != "WholeBlood"&&u.component != "RedCells" &&u.component != "Plasma" &&u.component != "Platelets")
        throw runtime_error("Invalid component!");
    if (u.testingStatus != "Tested" &&
        u.testingStatus != "Untested")
        throw runtime_error("Invalid testing status!");
    u.status = "Available";
    blood.push_back(u);
    usedUnitIds.insert(u.id);
    transactionHistory.push_back(u.id);
    undoHistory.push("Unit registered");
    BloodBank::totalOperations++;
    cout << "Blood unit registered successfully!\n";
        }
 void addHospital() 
 {
    Hospital h;
    cout<<"\nEnter hospital ID: ";
    cin>>h.id;
    if(findHospital(h.id)!=-1)
        throw runtime_error("Duplicate hospital ID!");
    cout<<"Hospital name: ";
    cin>>ws;
    getline(cin, h.name);
    cout<<"Contact: ";
    getline(cin, h.contact);
    if (h.name.empty() || h.contact.empty())
        throw runtime_error("Required field cannot be empty!");
    hospitals.push_back(h);
    hospitalNames[h.id]=h.name;
    transactionHistory.push_back(h.id);
    cout<<"Hospital registered successfully!\n";
}
void addRequest()
{
    BloodRequest r;
    cout<<"\nEnter request ID: ";
    cin>>r.id;
    if (findRequest(r.id) != -1)
        throw runtime_error("Duplicate request ID!");
    cout<<"Hospital ID: ";
    cin>>r.hospitalId;
    if(findHospital(r.hospitalId)==-1)
        throw runtime_error("Hospital not found!");
    cout<<"Required blood group: ";
    cin>>r.group;
    cout<<"Component: ";
    cin>>r.component;
    cout<<"Number of units: ";
    cin>>r.units;
    if (r.units<=0)
        throw runtime_error("Invalid number of units!");
    cout<<"Urgency (1 = Normal, 2 = Urgent): ";
    cin>>r.urgency;
    if (r.urgency!=1 && r.urgency!=2)
        throw runtime_error("Invalid urgency!");
    cout<<"Requested date (YYYY-MM-DD): ";
    cin>>r.requestedDate;
    if(!isValidDate(r.requestedDate))
        throw runtime_error("Invalid date!");
    r.allocated=0;
    r.status="Submitted";
    requests.push_back(r);
    waitingRequests.push(r.id);
    transactionHistory.push_back(r.id);
    cout<<"Request created successfully!\n";
}
void showUnits()
{
    if(blood.empty())
    {
        cout<<"No blood units found.\n";
        return;
    }
    cout<<"\nID  GROUP  COMPONENT  QUANTITY  STATUS\n";
    for(int i = 0; i < (int)blood.size(); i++)
    {
        cout<<blood[i].id<< " "<<blood[i].group<< " "<<blood[i].component<<" " <<blood[i].quantity<< " "<<blood[i].status<<endl;
    }
}
void showHospitals()
{
    for(int i=0;i<(int)hospitals.size(); i++)
    {
        cout<<hospitals[i].id<< " "<<hospitals[i].name<< " "<<hospitals[i].contact<<endl;
    }
}
void showRequests()
{
    for (int i=0;i<(int)requests.size(); i++)
    {
        cout<<requests[i].id<< " "<<requests[i].hospitalId<< " "<<requests[i].group<< " "<<requests[i].component<< " "<<requests[i].units<< " "<< requests[i].allocated<< " "<<requests[i].status<<endl;
    }
}