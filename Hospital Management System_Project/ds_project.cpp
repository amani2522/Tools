#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;
struct Node {
    int id;
    int appointment_id;
    string p_name;
    int age;
    int b_group;
    string contact;
    string date;
    string disease;
    string d_name;
    int specialization;
    int patient_count;
    string time;
    Node*next;
};

struct Admin {
    string username;
    string password;
};

class Hospital {
private:
    Node*p_head;
    Node*d_head;
    Admin admin;

public:
    Hospital();
    ~Hospital();
    void menu();
    void userPanel();
    void adminPanel();
    bool authenticateAdmin();
    void insert();
    void insertd();
    void modifyAppointment(int appointment_id);
    void deleteAppointment(int appointment_id);
    void deleteDoctor(int doctor_id);
    void showAppointments(string patientName);
    void show();
    void showd();
    void showdp();

    string getBloodGroup(int b_group);
    string getSpecialization(int specialization);
    Node*findDoctorById(int id);
    bool canDoctorTakeMorePatients(Node* doctor);
    void save(Node*node);
    void saved(Node*node);
};

Hospital::Hospital():p_head(nullptr),d_head(nullptr) {
    admin.username="admin";
    admin.password="asdfgh";
}

Hospital::~Hospital() {
    Node*current=p_head;
    while(current)
        {
        Node*next=current->next;
        delete current;
        current=next;
        }
    current=d_head;
    while(current)
        {
        Node*next=current->next;
        delete current;
        current=next;
        }
}

void Hospital::menu()
{   system("cls");
    int choice;
    while(true)
   {

        cout << "\n\t\t\t =====HOSPITAL MANAGEMENT SYSTEM=====";
        cout << "\n\n\n\t\t\t\t     1.Admin Panel\n";
        cout << "\t\t\t\t     2.User Panel\n";
         cout << "\t\t\t\t     3.Exit\n";
        cout << "\t\t\t\t     \n";
        cout << "\t\t\t\t     ";
        cout << "\n\n ENTER YOUR CHOICE: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                {
                if(authenticateAdmin())
                    adminPanel();
                else cout<<"\nIncorrect credentials. Access denied."<<endl;
                break;
               }
            case 2:
                {
                userPanel();
                break;
                }
            case 3:
                {
                cout<<"\nExiting the program!\n";
                exit(0);
                }
            default:
                {
                cout<<"\nInvalid choice.Please try again.";
                break;
                }
        }
    }
}

void Hospital::adminPanel()
{   system("cls");
    int choice;
    while(true)
     {
        cout<<"\n\n\t\tAdmin Panel\n";
        cout<<"\n1. Add Patient";
        cout<<"\n2. Add Doctor";
        cout<<"\n3. Doctor list";
        cout<<"\n4. Patient list";
        cout<<"\n5. Delete Doctor";
        cout<<"\n6. Delete Appointment";
        cout<<"\n7. Return to Main Menu";

        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:{
                insert();
                break;
            }
            case 2:{
                insertd();
                break;
            }
            case 3:{
                showd();
                break;
            }
            case 4:{
                show();
                break;
            }
            case 5:{
                int doctor_id;
                cout<<"\nEnter Doctor ID to delete: ";
                cin>>doctor_id;
                deleteDoctor(doctor_id);
                break;
            }
            case 6:{
                int appointment_id;
                cout<<"\nEnter Appointment ID to delete: ";
                cin>>appointment_id;
                deleteAppointment(appointment_id);
                break;
            }
            case 7:{
                system("cls");
                return;
            }
            default:{
                cout<<"\nInvalid choice. Please try again.";
                break;
            }
        }
    }
}

void Hospital::userPanel() {

    system("cls");
    int choice;
    while(true){
        cout<<"\n\n\t\tUser Panel";
        cout<<"\n1. Booking Appointment";
        cout<<"\n2. Show appointments by patient name";
        cout<<"\n3. Modify appointment";
        cout<<"\n4. Cancel appointment";
        cout<<"\n5. Return to main menu";

        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice) {
             case 1:{
                insert();
                break;
            }
            case 2:{
                string patientName;
                cout<<"\nEnter patient name: ";
                cin.ignore();
                getline(cin, patientName);
                showAppointments(patientName);
                break;
            }
            case 3:{
                int appointment_id;
                cout<<"\nEnter appointment ID to modify: ";
                cin>>appointment_id;
                modifyAppointment(appointment_id);
                break;
            }
            case 4:{
                int appointment_id;
                cout<<"\nEnter appointment ID to cancel: ";
                cin>>appointment_id;
                deleteAppointment(appointment_id);
                break;
            }
            case 5:{
                return;
            }
            default:{
                cout<<"\nInvalid choice. Please try again.";
                break;
            }
        }
    }
}

bool Hospital::authenticateAdmin() {
    string username,password;
    cout<<"\nEnter Admin Username: ";
    cin>>username;
    cout<<"Enter Admin Password: ";
    cin>>password;
    return(username==admin.username&&password==admin.password);
}

    void Hospital::insert()

{   system("cls");
    cout<<"\n\t______Hospital Management______\n";
    showdp();
    int doctor_id;
    cout<<"\nEnter Doctor ID from the above list:";
    cin>>doctor_id;

    Node*doctor=findDoctorById(doctor_id);
    if(!doctor)
    {
        cout<<"\nInvalid Doctor ID. Please try again."<<endl;
        return;
    }

    if(!canDoctorTakeMorePatients(doctor))
    {
        cout<<"\nThis doctor cannot take more appointments (maximum 5 patients)."<<endl;
        return;
    }

    Node*new_node= new Node;
    new_node->id = doctor_id;
    new_node->appointment_id=rand()%1000+1;

    cin.ignore();
    cout<<"\nEnter Patient Name      :";
    getline(cin,new_node->p_name);
    cout<<"Enter Patient Age       :";
    cin>>new_node->age;
    cout<<"Enter Blood Group       :\n1:A+,\n2:A-,\n3:B+,\n4:B-,\n5:AB+,\n6:AB-,\n7:O+,\n8:O-\n\n";
    cin>>new_node->b_group;
    cin.ignore();
    cout<<"\nEnter Patient Contact :";
    getline(cin,new_node->contact);
    cout<<"Enter Appointment Date(dd/mm/yy)           :";
    getline(cin, new_node->date);
    cout<<"Enter If Any Major Disease Suffered Earlier:";
    getline(cin,new_node->disease);

    new_node->next=nullptr;
    if(p_head==nullptr)
    {
        p_head=new_node;
    }
    else
    {
        Node* ptr=p_head;
        while(ptr->next!=nullptr)
        {
            ptr=ptr->next;
        }
        ptr->next=new_node;
    }
    doctor->patient_count++;
    save(new_node);
    cout<<"\n\n\t\t New Appointment Done!"<<endl;

}

void Hospital::insertd()
{   system("cls");
    cout<<"\n___Add New Doctor___\n";

    Node*new_node=new Node;

    cout<<"\nEnter Doctor ID              :";
    cin>>new_node->id;
    cout<<"Enter Doctor Name            :";
    cin.ignore();
    getline(cin,new_node->d_name);
    cout<<"Enter Doctor Specialization  :";
    cout<<"\n1 : Internal medicine, \n2 : Oncology, \n3 : Pediatrics, \n4 : Neurology, \n5 : Cardiology,";
    cout<<"\n6 : Gynaecology, \n7 : Orthopedics, \n8 : Dermatology, \n9 : Hematology, \n10: Urology,";
    cout<<"\n11: Endocrinology, \n12: Gastroenterology, \n13: Physiology, \n14: Surgery, \n15: ENT,";
    cout<<"\n16: Radiology\n";
    cin>>new_node->specialization;
    cin.ignore();
    cout<<"\nEnter Visiting Time        :";
    getline(cin,new_node->time);

    new_node->patient_count=0;
    new_node->next=nullptr;

    if(d_head==nullptr)
        {
        d_head=new_node;
        }
    else{
        Node*ptr=d_head;
        while(ptr->next!=nullptr)
        {
            ptr=ptr->next;
        }
        ptr->next=new_node;
    }
    saved(new_node);
    cout<<"\nNew Doctor Added Successfully."<<endl;
}

void Hospital::modifyAppointment(int appointment_id) {
    system("cls");
    Node*ptr=p_head;
    while(ptr!=nullptr) {
        if(ptr->appointment_id==appointment_id)
             {
            cout<<"\nModify Appointment ID    : "<<ptr->appointment_id;
            cout<<"\nEnter New Patient Name   : ";
            cin.ignore();
            getline(cin,ptr->p_name);
            cout<<"\nEnter New Patient Age    : ";
            cin>>ptr->age;
            cout<<"\nEnter New Blood Group    : ";
            cout<<"\n1:A+,\n2: A-,\n3: B+,\n4: B-,\n5: AB+,\n6: AB-,\n7: O+,\n8: O-\n";
            cin>>ptr->b_group;
            cin.ignore();
            cout<<"\nEnter New Patient Contact: ";
            getline(cin,ptr->contact);
            cout<<"\nEnter New Appointment Date (dd/mm/yyyy) : ";
            getline(cin,ptr->date);
            cout<<"\nEnter Any Major Disease Suffered Earlier: ";
            getline(cin,ptr->disease);

            save(ptr);

            cout<<"\nAppointment Modified Successfully."<<endl;
            return;
            }
        ptr=ptr->next;
    }

    cout<<"\nAppointment ID not found."<<endl;
}

void Hospital::deleteAppointment(int appointment_id) {
    system("cls");
    Node*current=p_head;
    Node*prev=nullptr;

    while(current!=nullptr)
        {
        if(current->appointment_id==appointment_id) {
            if(prev==nullptr)
            {
                p_head=current->next;
            } else
            {
                prev->next=current->next;
            }
            delete current;
            cout<<"\nAppointment ID"<<appointment_id<<" deleted successfully."<<endl;
            return;
        }

        prev=current;
        current=current->next;
    }

    cout<<"\nAppointment ID "<<appointment_id<<"not found."<<endl;
}

void Hospital::deleteDoctor(int doctor_id) {
    system("cls");
    Node*current=d_head;
    Node*prev=nullptr;


    while(current!=nullptr)
        {
        if(current->id==doctor_id)
        {
            if(prev==nullptr) {
                d_head=current->next;
            } else {
                prev->next=current->next;
            }
            delete current;
            cout<<"\nDoctor ID "<<doctor_id<<"deleted successfully."<<endl;
            return;
        }

        prev=current;
        current=current->next;
       }

    cout<<"\nDoctor ID "<<doctor_id<<" not found."<<endl;
}

void Hospital::showAppointments(string patientName) {
    system("cls");
    Node*ptr=p_head;
    bool found=false;

    while(ptr!=nullptr)
        {
        if(ptr->p_name==patientName) {
            found=true;
            cout<<"\nAppointment ID  :"<<ptr->appointment_id;
            cout<<"\nPatient Name    :"<<ptr->p_name;
            cout<<"\nAge             :"<<ptr->age;
            cout<<"\nBlood Group     :"<<getBloodGroup(ptr->b_group);
            cout<<"\nContact         :"<<ptr->contact;
            cout<<"\nAppointment Date:"<<ptr->date;
            cout<<"\nDisease         :"<<ptr->disease;
            cout<<"\nDoctor ID       :"<<ptr->id<<endl;
        }
        ptr = ptr->next;
    }

    if (!found) {
        cout << "\nNo appointments found for patient '" << patientName << "'." << endl;
    }
}


void Hospital::show() {
    system("cls");
    Node*ptr=p_head;

    if(ptr==nullptr) {
        cout<<"\nNo patients found."<<endl;
        return;
    }

    cout<<"\n____All Patients____\n";
    while(ptr != nullptr) {
        cout<<"\nPatient ID    :"<<ptr->id;
        cout<<"\nName          :"<<ptr->p_name;
        cout<<"\nAge           :"<<ptr->age;
        cout<<"\nBlood Group   :"<<getBloodGroup(ptr->b_group);
        cout<<"\nContact       :"<<ptr->contact;
        cout<<"\nMajor Disease :"<<ptr->disease;
        cout<<"\nAppointment ID:"<<ptr->appointment_id<<endl;
        cout<<"-------------------------------------"<<endl;
        ptr=ptr->next;
    }
}

void Hospital::showd() {
    system("cls");
    Node*ptr=d_head;

    if(ptr==nullptr) {
        cout<<"\nNo doctors found."<<endl;
        return;
    }

    cout<<"\n____All Doctors____\n";
    while(ptr!=nullptr) {
        cout<<"\nDoctor ID          :"<<ptr->id;
        cout<<"\nName               :"<<ptr->d_name;
        cout<<"\nSpecialization     :"<<getSpecialization(ptr->specialization);
        cout<<"\nNumber of Patients :"<<ptr->patient_count;
        cout<<"\nVisiting Hours     :"<<ptr->time<<endl;
        cout<<"------------------------------------------"<<endl;
        ptr=ptr->next;
    }
}

void Hospital::showdp() {
    system("cls");
    Node*ptr=d_head;

    if (ptr == nullptr) {
        cout<<"\nNo doctors found."<<endl;
        return;
    }

    cout << "\n____All Doctors____\n";
    while(ptr!=nullptr) {
        cout<<"\nDoctor ID      :" <<ptr->id;
        cout<<"\nName           :"<<ptr->d_name;
        cout<<"\nSpecialization :"<<getSpecialization(ptr->specialization);
        cout<<"\nVisiting Hours :"<<ptr->time<<endl<<endl;
        cout<<"---------------------------------------"<<endl;
        ptr=ptr->next;
    }
}

string Hospital::getBloodGroup(int b_group) {
    switch(b_group) {
        case 1: return "A+";
        case 2: return "A-";
        case 3: return "B+";
        case 4: return "B-";
        case 5: return "AB+";
        case 6: return "AB-";
        case 7: return "O+";
        case 8: return "O-";
        default: return "Unknown";
    }
}

string Hospital::getSpecialization(int specialization) {
    switch(specialization)
    {
        case 1:  return "Internal Medicine";
        case 2:  return "Oncology";
        case 3:  return "Paediatrics";
        case 4:  return "Neurology";
        case 5:  return "Cardiology";
        case 6:  return "Gynaecology";
        case 7:  return "Orthopedics";
        case 8:  return "Dermatology";
        case 9:  return "Haematology";
        case 10: return "Urology";
        case 11: return "Endocrinology";
        case 12: return "Gastroenterology";
        case 13: return "Physiotherapy";
        case 14: return "Surgery";
        case 15: return "ENT";
        case 16: return "Radiology";
        default: return "Unknown";
    }
}

Node* Hospital::findDoctorById(int id) {
    Node* ptr=d_head;
    while(ptr!=nullptr) {
        if(ptr->id==id) {
            return ptr;
        }
        ptr=ptr->next;
    }
    return nullptr;
}

bool Hospital::canDoctorTakeMorePatients(Node* doctor) {
    return doctor->patient_count<5;
}

void Hospital::save(Node*node)
{
    ofstream fout("patients.txt",ios::app);
    if(!fout)
        {
        cout<<"\nError in opening file.";
        return;
        }
    fout<<"Patient Id      :"<<node->id<<endl;
    fout<<"Name            :"<<node->p_name<<endl;
    fout<<"Age             :"<<node->age<<endl;
    fout<<"Blood Group     :"<<node->b_group<<endl;
    fout<<"Contact         :"<<node->contact<<endl;
    fout<<"Appointment Date:"<<node->date<<endl;
    fout<<"Disease         :"<<node->disease<<endl;
    fout<<"Doctor ID       :"<<node->id<<endl;
    fout<<"Appointment Id  :"<<node->appointment_id<<endl<<endl;
    fout<<"-----------------------------------"<<endl;
    fout.close();
}

void Hospital::saved(Node*node)
{
    ofstream fout("doctors.txt",ios::app);
    if(!fout)
        {
        cout<<"\nError in opening file.";
        return;
        }
    fout<<"Doctor ID         :"<<node->id<<endl;
    fout<<"Doctor Name       :"<<node->d_name<<endl;
    fout<<"Specialization    :"<<node->specialization<<endl;
    fout<<"Number of Patients:"<<node->patient_count<<endl;
    fout<<"-------------------------------------------"<<endl;
    fout.close();
}

int main()
{
    Hospital h;
    h.menu();
    return 0;
}
