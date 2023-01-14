#include"ticket.h"
#include"header.h"
#include"logger.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<iomanip>
using namespace std;

//Getters
char Ticket:: *getName(){
    return name;
}
char Ticket:: *getPnrNo(){
    return prnNo;
}
char Ticket:: *getDate(){
    return date;
}
//Setters
void Ticket:: setName(char *n)
{
    if(n && n[0])
        strcpy(name,n);
}

//Generating ticket
void Ticket:: generateTicket(){
    LOG_INFO("\nticket generation");
    strcpy(name,n);
    strcpy(pnrNo,generatePNR(99999).c_str());
    strcpy(date,getCurrentDate().c_str());
    bus = b;
}

//Booking ticket
void Ticket:: bookTicket(){
    system("clear");
    char source[BUFFER_SIZE], destination[BUFFER_SIZE];
    int check=0;
    Bus b;
    fstream bus,ticket,temp;
    cout<<"\n-------------BOOK TICKET------------";
    bus.open("buses.dat",ios::in | ios::app | ios::binary);
    if(bus.fail()){
        cout<<"\nCan't open the file..\n";
    }
    else{
        cout<<"\nEnter Source: ";
        cin.ignore();
        cin.getline(source,BUFFER_SIZE);
        cout<<"\nEnter Destination: ";
        cin.getline(destination,BUFFER_SIZE);
        system("clear");
        cout<<"\n-------------AVAILABLE BUSES-----------";
        bus.read((char*)&b, sizeof(b));
        while(!bus.eof()){
            if(strcmp(b.getSource(),source) == 0 && strcmp(b.getDestination(),destination)==0)
            {
                b.showBusDetails();
                check=1;
            }
            bus.read((char*)&b,sizeof(b));
        }
        bus.close();
    }
    if(check==0)
    {
        cout<<"\nNo Buses Found..!\n";
    }
    else{
        char bNo[SIZE];
        int booked=0;
        cout<<"\nEnter bus number: ";
        cin.getline(bNo,SIZE);
        
        bus.open("buses.dat",ios::in | ios::app | ios::binary);
        temp.open("temp.dat",ios::out | ios::app | ios::binary);
        bus.read((char*)&b,sizeof(b));
        while(!bus.eof())
        {
            if(strcmp(b.getSource(),source)==0 && strcmp(b.getDestination(),destination)==0 && strcmp(b.getBusNo(), bNo)==0)
            {
                if(b.getBookedSeats() >= 32)
                {
                    cout<<"\nSeats not available..\n";
                    break;
                }
                else{
                    system("clear");
                    cout<<"\n----------BOOK TICKET----------";
                    char n[BUFFER_SIZE];
                    cout<<"\n\nEnter Customer Name: ";
                    cin.getline(n,BUFFER_SIZE);
                    b.setBookedSeats();
                    generateTicket(n,b);
                    ticket.open("tickets.dat",ios::out | ios::app | ios::binary);
                    ticket.write((char*)this,sizeof(*this));
                    ticket.close();
                    temp.write((char*)&b,sizeof(b));
                    booked=1;
                    system("clear");
                    cout<<"---------BOOKING DETAILS---------";
                    displayTicket();
                    cout<<"\n\tTicket Booked Successfully...";
                }
            }
            else{
                temp.write((char*)&b, sizeof(b));
            }
            bus.read((char*)&b,sizeof(b));
        }
        if(booked==1)
        {
            bus.close();
            temp.close();
            remove("buses.dat");
            rename("temp.dat","buses.dat");
        }
    }
    bus.close();
    LOG_INFO("\nBook ticket");
}
//Modifying ticket
void Ticket:: editTicket(){
    system("clear");
    char pnr[SIZE];
    int check=0;
    fstream ticket,temp;
    cout<<"-----------EDIT TICKET----------";
    cout<<"\nEnter PNR Number: ";
    cin.ignore();
    cin.getline(pnr,SIZE);
    ticket.open("tickets.dat",ios::in | ios::app | ios::binary);
    if(ticket.fail()){
        cout<<"\n\tCan't open the file..";
    }
    else{
        temp.open("temp.dat",ios::out | ios::app | ios::binary);
        ticket.read((char*)this,sizeof(*this));
        while(!ticket.eof()){
            if(strcmp(getPnrNo(),pnr)==0)
            {
                system("clear");
                cout<<"\n-----------EDIT TICKET----------";
                displayTicket();
                char n[BUFFER_SIZE];
                cout<<"\n\tEnter Passenger Name: ";
                cin.getline(n,BUFFER_SIZE);
                setName(n);
                temp.write((char*)this,sizeof(*this));
                check=1;
            }
            else{
                temp.write((char*)this,sizeof(*this));
            }
            ticket.read((char*)this,sizeof(*this));
        }
        if(check==1){
            cout<<"\n\tTicket Updated Successfully..";
        }
        else{
            cout<<"\n\tTicket not found..";
        }
        ticket.close();
        temp.close();
        remove("tickets.dat");
        rename("temp.dat","tickets.dat");
    }
    LOG_INFO("\nEdit ticket");
}
//Cancel ticket
void Ticket:: cancelTicket(){
    system("clear");
    char pnr[SIZE];
    int check=0;
    fstream bus,ticket,temp,busTemp;
    cout<<"---------CANCEL TICKET----------";
    cin.ignore();
    cin.getline(pnr,SIZE);
    ticket.open("tickets.dat",ios::in | ios::app | ios::binary);
    temp.open("temp.dat",ios::out | ios::app | ios::binary);
    if(ticket.fail()){
        cout<<"\n\tCan't Open File..\n";
    }
    else{
        ticket.read((char*)this, sizeof(*this));
        while(!ticket.eof()){
            if(strcmp(getPnrNo(),pnr)!=0){
                temp.write((char*)this,sizeof(*this));
            }
            else{
                Bus b;
                bus.open("buses.dat",ios::in | ios::app | ios::binary);
                busTemp.open("bustemp.dat",ios::out | ios::app | ios::binary);
                
                bus.read((char*)&b,sizeof(b));
                while(!bus.eof()){
                    if(strcmp(b.getBusNo(),bus.getBusNo())==0){
                        b.setCancelTicket();
                        busTemp.write((char*)&b,sizeof(b));
                    }
                    else{
                        bus.write((char*)&b,sizeof(b));
                    }
                    bus.read((char*)&b,sizeof(b));
                }
                bus.close();
                busTemp.close();
                remove("buses.dat");
                rename("bustemp.dat","buses.dat");
                check=1;
            }
            ticket.read((char*)this,sizeof(*this));
            }
            if(check==0){
                ticket.close();
                temp.close();
                cout<<"\n\tTicket Not Found..\n";
            }
             else{
                ticket.close();
            temp.close();
            remove("tickets.dat");
            rename("temp.dat","tickets.dat");
            cout<<"\n\tTicket cancelled...\n";
        }
    }
    LOG_INFO("\nCancel ticket");
}

//Displaying ticket details
void Ticket:: displayTicket(){
    cout<<"\n\t--------------TICKET----------------";
    cout<<"\n\t\tName: "<<getName();
    cout<<"\n\t\tPNR No: "<<bus.getBusNo();
    cout<<"\n\t\tSeat No: "<<bus.getBookedSeats();
    cout<<"\n\t\tDate: "<<getDate();
    cout<<"\n\t\tFrom: "<<bus.getSource();
    cout<<"\n\t\tTo: "<<bus.getDestination();
    cout<<"\n\t\tStart Time: "<<bus.getStartTime();
    cout<<"\n\t\tDestination Time: "<<bus.getDestinationTime();
    cout<<fixed<<setprecision(2);
    cout<<"\n\t\tBus Fare: "<<bus.getBusFare();
    cout<<"\n";
    LOG_INFO("\ndisplay ticket");
}
//Display all bookings
void Ticket:: showAllTickets(){
    system("clear");
    fstream ticket;
    cout<<"-----------BOOKINGS----------";
    ticket.open("tickets.dat",ios::in | ios::app |ios::binary);
    if(ticket.fail()){
        cout<<"\n\tCan't open File..";
    }
    else{
        ticket.read((char*)this,sizeof(*this));
        while(!ticket.eof()){
            displayTicket();
            ticket.read((char*)this,sizeof(*this));
        }
        ticket.close();
    }
    LOG_INFO("\nshow all tickets");
}

// SHOW TICKET BY PNR
void Ticket::showTicketsByPNR()
{
    system("clear");

    char pnr[SIZE];
    int check = 0;
    fstream ticket;

    cout<<"------------SHOW BOOKINGS BY PNR-------------";
    cout << "\n\tEnter PNR Number: ";
    cin.ignore();
    cin.getline(pnr,SIZE);
    system("clear");
    cout<<"--------------BOOKINGS--------------";
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout <<"\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout<<"\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
}

// SHOW TICKET BY NAME
void Ticket::showTicketsByName()
{
    system("clear");

    char n[BUFFER_SIZE];
    int check = 0;
    fstream ticket;
    cout<<"---------SHOW BOOKINGS BY NAME---------");
    cout << "\n\tEnter Passenger Name: ";
    cin.ignore();
    cin.getline(n, BUFFER_SIZE);
    system("clear");
    cout<<"----------BOOKINGS---------";

    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }

    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(getName(), n) == 0)
            {
                displayTicket();
                check = 1;
            }
        }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
}

// SHOW TICKET BY BUS
void Ticket::showTicketsByBus()
{
    system("clear");
    char bNo[SIZE];
    int check = 0;
    fstream ticket;

    cout<<"----------SHOW BOOKINGS BY NAME-----------";
    cout<<"\n\tEnter Bus Number: ";
    cin.ignore();
    cin.getline(bNo, SIZE);
    system("clear");
    cout<<"------------BOOKINGS----------");
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\ttCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getBusNo(), bNo) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout<<"\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
}

// SHOW TICKET BY SOURCE
void Ticket::showTicketsBySource()
{
    system("clear");
    char s[BUFFER_SIZE];
    int check = 0;
    fstream ticket;
    cout<<"----------SHOW BOOKINGS BY SOURCE-----------";
    cout << "\n\tEnter Source: ";
    cin.ignore();
    cin.getline(s, BUFFER_SIZE);
    system("clear");
    cout<<"-----------BOOKINGS------------";
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getSource(), s) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (check == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
}

// SHOW TICKET BY DESTINATION
void Ticket::showTicketsByDestination()
{
    system("clear");

    char d[BUFFER_SIZE];
    int check = 0;
    fstream ticket;

    cout<<"--------SHOW BOOKINGS BY DESTINATION-------";
    cout << "\n\tEnter Destination: ";
    cin.ignore();
    cin.getline(d, BUFFER_SIZE);
    system("clear");
    printHeading("---------BOOKINGS----------");
    ticket.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticket.fail())
    {
        cout << "\n\tCan't Open File...!!\n";
    }
    else
    {
        ticket.read((char *)this, sizeof(*this));
        while (!ticket.eof())
        {
            if (strcmp(bus.getDestination(), d) == 0)
            {
                displayTicket();
                check = 1;
            }
            ticket.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\tNo Bookings...!!\n";
        }
        ticket.close();
    }
}
