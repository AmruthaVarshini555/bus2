#include"Bus.h"
#include"header.h"
#include<iostream>
#include<string>
using namespace std;
//Getters
char Bus:: *getBusNo()
{
    return busNo;
}

char Bus:: *getSource()
{
    return source;
}

char Bus:: *getDestination()
{
    return destination;
}

char Bus:: *getStartTime()
{
    return startTime;
}

char Bus:: *getDestinationTime()
{
    return destinationTime;
}

int Bus:: getBookedSeats()
{
    return bookedseats;
}

int Bus:: getMaxSeats()
{
    return maxseats;
}

double Bus:: getFare()
{
    return busFare;
}
// SETTERS
void Bus:: setBookedSeats()
{
    bookedSeats++;
}

void Bus:: setCancelTicket()
{
    bookedSeats--;
}

void Bus:: setSource(char *s)
{
    if (s && s[0])
        strcpy(source, s);
}

void Bus:: setDestination(char *d)
{
    if (d && d[0])
        strcpy(destination, d);
}

void Bus:: setStartTime(char *s)
{
    if (s && s[0])
        strcpy(startTime, s);
}

void Bus:: setDestinationTime(char *d)
{
    if (d && d[0])
        strcpy(destinationTime, d);
}

void Bus:: setBusFare(double f)
{
    if (f)
        busFare = f;
}
//Creating bus
void Bus::addBus()
{
    fstream bus;
    system("clear");
    cout<<"\n----------ADD BUS--------";

    cout << "\n\tEnter Bus Number: ";
    cin.ignore();
    cin.getline(busNo, SIZE);
    cout << "\n\tEnter Source: ";
    cin.getline(source, BUFFER_SIZE);
    cout << "\n\tEnter Destination: ";
    cin.getline(destination, BUFFER_SIZE);
    cout << "\n\tEnter Start Time: ";
    cin.getline(startTime, 20);
    cout << "\n\tEnter Reaching Time: ";
    cin.getline(destinationTime, 20);
    cout << "\n\tEnter Bus Fare: ";
    cin >> busFare;

    bus.open("buses.dat", ios::out | ios::app | ios::binary);
    bus.write((char *)this, sizeof(*this));
    bus.close();

    cout << "\n\tBus Added Successfully... \n";
}
//edit bus
void Bus::editBus()
{
   system("clear");

    char bNo[SIZE];
    int check = 0;

    fstream bus, temp;
    cout<<"-------------EDIT BUS----------";
    cout << "\n\tEnter Bus Number: ";
    cin.ignore();
    cin.getline(bNo, SIZE);

    bus.open("buses.dat", ios::in | ios::app | ios::binary);

    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        temp.open("temp.dat", ios::out | ios::app | ios::binary);

        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                system("clear");
                cout<<"---------------EDIT BUS-------------";

                showBusDetails();
                char s[BUFFER_SIZE], d[BUFFER_SIZE], sTime[BUFFER_SIZE], dTime[BUFFER_SIZE];
                double fare;
                cout << "\n\tEnter Source: ";
                cin.getline(s, BUFFER_SIZE);
                cout << "\n\tEnter Destination: ";
                cin.getline(d,BUFFER_SIZE);
                cout << "\n\tEnter Start Time: ";
                cin.getline(sTime,BUFFER_SIZE);
                cout << "\n\tEnter Reaching Time: ";
                cin.getline(dTime, BUFFER_SIZE);
                cout << "\n\tEnter Bus Fare: ";
                cin.ignore();
                cin >> fare;
                setSource(s);
                setDestination(d);
                setStartTime(sTime);
                setDestinationTime(dTime);
                setBusFare(fare);
                temp.write((char *)this, sizeof(*this));
                check = 1;
            }
            else
            {
                temp.write((char *)this, sizeof(*this));
            }
            bus.read((char *)this, sizeof(*this));
        }

        if (check = 1)
        {
            cout << "\n\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\tBus Not Found...!!\n";
        }

        bus.close();
        temp.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

//Delete bus
void Bus::deleteBus()
{
    system("clear");

    char bNo[SIZE];
    int check = 0;
    fstream bus, temp;

    cout<<"-----------DELETE BUS-----------";
    cout << "\n\tEnter Bus No: ";
    cin.ignore();
    cin.getline(bNo, SIZE);

    bus.open("buses.dat", ios::in | ios::app | ios::binary);

    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!";
    }

    else
    {
        temp.open("temp.dat", ios::out | ios::app | ios::binary);
        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) != 0)
            {
                temp.write((char *)this, sizeof(*this));
            }
            else
            {
                check = 1;
            }
            bus.read((char *)this, sizeof(*this));
        }

        if (check == 0)
        {
            cout << "\n\tBus Not Found...!!\n";
        }
        else
        {
            cout << "\n\tBus Deleted...!!\n";
        }

        bus.close();
        temp.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

//view bus
void Bus::viewBus()
{
    system("clear");

    char bNo[SIZE];
    int check = 0;
    fstream bus;

    cout<<"\n---------VIEW BUS INFO----------";
    cout << "\n\tEnter Bus Number: ";
    cin.ignore();
    cin.getline(bNo,SIZE);

    system("clear");
    cout<<"\n--------BUS INFO--------";

    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (bus.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        bus.read((char *)this, sizeof(*this));
        while (!bus.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                showBusDetails();
                check = 1;
            }
            bus.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tBus Not Found...!!\n";
        }
        bus.close();
    }
}

//edit bus


//Show Bus Details 
void Bus::showBusDetails()
{
    cout << "\n\t Bus No: " << getBusNo();
    cout << "\n\t Source: " << getSource();
    cout << "\n\t Destination: " << getDestination();
    cout << "\n\t Time: " << getStartTime() << " - " << getDestinationTime();
    cout << "\n\t Total Seats: " << getMaxSeats();
    cout << "\n\t Seats Remaining: " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\t Bus Fare:-> " << getBusFare();
    cout << "\n";
}

//Show All bus Details
void Bus::showAllBus()
{
    system("clear");

    fstream bus;

    bus.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!bus)
        cout << "\n\t Not Found...!!!";
    else
    {
        cout<<"\n-----------BUSES------------");

        bus.read((char *)this, sizeof(*this));

        while (!bus.eof())
        {
            showBusDetails();
            bus.read((char *)this, sizeof(*this));
        }
        bus.close();
    }
}
