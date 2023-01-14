#ifndef __TICKET_H__
#define __TICKET_H__
#include<iostream>
#include"header.h"
#include"logger.h"
class Ticket
{
    private:
        char name[BUFFER_SIZE], pnrNo[BUFFER_SIZE],date[BUFFER_SIZE];
        Bus bus;
    public:
        Ticket(){
            LOG_INFO("Default constructor of ticket");
        }
        void generateTicket(char*,Bus);
        void bookTicket();
        void editTicket();
        void cancelTicket();
        void displayTicket();
        void showAllTickets();
        //getters
        char *getName();
        char *getPnrNo();
        char *getDate();
        //setters
        void setName(char*);
        //destructor
        ~Ticket(){
            LOG_INFO("Destructor of ticket");
         }
};

#endif //__TICKET_H__
