#include<bits/stdc++.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<cstdio>
using namespace std;

class bus_reservation
{

public:
     string name;
    int bus_num;
    int seat_num;

    static int available_seats[100];
    void bus_reserve();
    void details();
    void cancel_booking();
    void ticket(string name, int a, int b, float x);
    void selected_bus(int y);
    float price(int b, int s);
    void updateSeatAvailability(int bus_num, int booked_seats);
    void showAvailableSeats();
    void cancelReservation(string name);
};

void bus_reservation::cancel_booking()
{
    system("cls");
    cout << "Enter your name: ";
    cin >> name;

    ifstream passengerFile("passenger_info.txt");
    ofstream tempFile("temp_passenger_info.txt");

    if (!passengerFile)
    {
        cout << "No passenger information found." << endl;
        return;
    }

    bool found = false;
    char line[256];

    while (passengerFile.getline(line, sizeof(line)))
    {
        string data = line;
        if (data.find("Name: " + string(name)) != string::npos)
        {

            for (int i = 0; i < 4; i++)
            {
                if (!passengerFile.getline(line, sizeof(line)))
                    break;
            }
            found = true;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    passengerFile.close();
    tempFile.close();

    if (found)
    {
        remove("passenger_info.txt");
        rename("temp_passenger_info.txt", "passenger_info.txt");
        cout << "Booking canceled successfully." << endl;
    }
    else
    {
        remove("temp_passenger_info.txt");
        cout << "Booking not found." << endl;
    }
}

int bus_reservation::available_seats[100];

void bus_reservation::updateSeatAvailability(int bus_num, int booked_seats)
{

    available_seats[bus_num - 194200] -= booked_seats;
}


void bus_reservation::showAvailableSeats()
{
    system("cls");
    cout << "\nAvailable Seats:\n";
    for (int i = 1; i <= 5; i++)
    {
        int bus_number = 194200 + 10*i;
        cout << "Bus " << bus_number << ": " << available_seats[i*10] << " seats available\n";
    }
    cout << "\nPress any key to go back to Main menu";
    getch();
}
void bus_reservation::bus_reserve()
{
    bus_reservation bus;
    char confirm;
    int i = 0;
    float cost;
    ofstream outfile;
    system("cls");
    fflush(stdin);
    cout << "Enter your name:";
    cin >> bus.name;
    cout << "Enter number of seats:";
    cin >> bus.seat_num;
    cin.ignore();
    cout << "\n\n>>Press Enter To View Available Bus<< ";
    getch();
    system("cls");
    details();
    cout << "\n\nEnter bus number: ";

start1:
    cin >> bus.bus_num;
    if (bus.bus_num == 194210 || bus.bus_num == 194220 || bus.bus_num == 194230 || bus.bus_num == 194240 || bus.bus_num == 194250 )
    {
        cost = price(bus.bus_num, bus.seat_num);
        ticket(bus.name, bus.seat_num, bus.bus_num, cost);
    }
    else
    {
        cout << "\nInvalid bus Number! Enter again-> ";
        goto start1;
    }

    cout << "\n\nConfirm Ticket (YES/NO):";
start:
    cin >> confirm;
    if (confirm == 'y')
    {

        cout << "==================";
        cout << "\n Reservation successful\n";
        ofstream passengerFile;
        passengerFile.open("passenger_info.txt", ios::app);
        passengerFile << "Name: " << bus.name << "\nBus Number:   " << bus.bus_num << "\nSeat Number: " << seat_num << "\nCost: " << cost << endl;
        passengerFile.close();
        cout << "==================";
        cout << "\nPress any key to go back to Main menu";

        updateSeatAvailability(bus.bus_num, bus.seat_num);
    }
    else
    {
        if (confirm == 'n')
        {
            cout << "\nReservation Not Done!\nPress any key to go back to Main menu!";
        }
        else
        {
            cout << "\nInvalid choice entered! Enter again-> ";
            goto start;
        }
    }

    outfile.close();
    getch();
}

void bus_reservation::details()
{
    system("cls");
    fstream my_file;
    my_file.open("busdetails.txt", ios::in);

    if (!my_file) {
        cout << "No such file";
    } else {
        char ch;

        while (1) {
            my_file.get(ch);
            if (my_file.eof())
                break;

            if (ch == ' ') {

                cout << ' ';
            } else if (ch == '\n') {

                cout << endl;
            } else {

                cout << ch;
            }
        }

        my_file.close();
        return;
    }
}

float bus_reservation::price(int bus_num, int seat_num)
{
    if (bus_num == 194210)
    {
        return (400 * seat_num);
    }
    if (bus_num == 194220)
    {
        return (600 * seat_num);
    }
    if (bus_num == 194230)
    {
        return (400 * seat_num);
    }
    if (bus_num == 194240)
    {
        return (1200 * seat_num);
    }
    else if (bus_num == 194250)
    {
        return (400 * seat_num);
    }
    return 0;
}

void bus_reservation::ticket(string name, int seat_num, int bus_num, float price)
{
    bus_reservation bus;

    if(seat_num > bus.available_seats[bus_num - 194200])
    {
        cout << "Sorry, Demanded seat is more than remaining seats" << endl;
        return;
    }

    system("cls");
    cout << "\t~~~~~~~~\n";
    cout << "\t\tTICKET\n";
    cout << "\t~~~~~~~~\n\n";
    cout << "NAME OF PASSENGER:\t" << name;
    cout << "\nNUMBER OF SEATS:\t" << seat_num;
    cout << "\nBUS NUMBER:\t\t" << bus_num;
    bus.selected_bus(bus_num);
    cout << "\nTOTAL COST:\t\t" << price;
}

void bus_reservation::selected_bus(int bus_num)
{
    if (bus_num == 194210)
    {
        cout << "\nBUS NAME:\t\tDahlia";
        cout << "\nDESTINATION:\t\tChittagong to Dhaka";
        cout << "\nTIME:\t\t\t6 A.M.";
    }
    if (bus_num == 194220)
    {
        cout << "\nBUS NAME:\t\tGreen Line";
        cout << "\nDESTINATION:\t\tChittagong to Rajshahi";
        cout << "\nTIME:\t\t\t5 A.M.";
    }
    if (bus_num == 194230)
    {
        cout << "\nBUS NAME:\t\tShohagh";
        cout << "\nDESTINATION:\t\tDhaka to Sylhet";
        cout << "\nTIME:\t\t\t11 P.M.";
    }
    if (bus_num == 194240)
    {
        cout << "\nBUS NAME:\t\tShyamoli";
        cout << "\nDESTINATION:\t\tSylhet to Cox's Bazar";
        cout << "\nTIME:\t\t\t5 A.M.";
    }
    if (bus_num == 194250)
    {
        cout << "\nBUS NAME:\t\tSoudia";
        cout << "\nDESTINATION:\t\tCox's Bazar to Chittagong";
        cout << "\nTIME:\t\t\t2 P.M.";
    }
}

int main()
{
    bus_reservation bus;

    for (int i = 0; i < 100; i++)
    {
        bus.available_seats[i] = 50;
    }

p:
    system("cls");
    string email, pass;
    char ch;
    cout << "\n\n\t\t\t*Security Are Required*";
    cout << "\n\n Email : ";
    cin >> email;
    cout << "\n\n Password : ";
    for (int i = 1; i <= 6; i++)
    {
        ch = getch();
        pass += ch;
        cout << "*";
    }
    if (email == "project@gmail.com" && pass == "ticket")
    {
        goto q;
    }
    else
    {
        cout << "\n\n\t\tYour Email & Password is Wrong....";
        getch();
        goto p;
    }


q:
    int choice = 1;
    while (1)
    {

        cout << "\n\t\t\t=====BUS TICKET MANAGEMENT SYSTEM=====";
        cout << "\n\n\n\t\t\t\t     1.Book Tickets\n";
        cout << "\t\t\t\t     2.Bus List\n";
         cout << "\t\t\t\t     3.Available seats\n";
         cout << "\t\t\t\t     4.Cancel ticket\n";
        cout << "\t\t\t\t     5.Exit\n";
        cout << "\t\t\t\t    _\n";
        cout << "\t\t\t\t     ";
        cout << "\n\n ENTER YOUR CHOICE: ";
        cin >> choice;
        if (choice == -1) break;

        switch (choice)
        {
        case 1:
            bus.bus_reserve();
            break;
        case 2:
            bus.details();
            break;
        case 3:
            bus.showAvailableSeats();
            break;
        case 4:
            bus.cancel_booking();
            break;
        case 5:
            cout << "\n\t\t\t\t  Press any key to exit\n";
            return 0;
        }
        getch();
    }


    return 0;
}
