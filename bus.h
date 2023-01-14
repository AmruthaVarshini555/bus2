#ifndef __BUS_H__
#define __BUS_H__
#include<iostream>
#include"header.h"
#include"logger.h"
using namespace std;
class Bus
{
    private:
          char busNo[SIZE];
          char source[BUFFER_SIZE];
          char destination[BUFFER_SIZE];
          char startTime[BUFFER_SIZE];
          char destinationTime[BUFFER_SIZE];
          int maxseats,bookedseats;
          double busFare;
    public:
         Bus()
         {
             LOG_INFO("\nDefault constructor of Bus");
         }
         void addBus();
         void editBus();
         void deleteBus();
         void viewBus();
         void showBusDetails();
         void showAllBus();
         ~Bus()
         {
             INFO_LOG("\nDestructor of Bus");
         }
        //GETTERS
        char *getBusNo();
        char *getSource();
        char *getDestination();
        char *getStartTime();
        char *getDestinationTime();
        int getBookedSeats();
        int getMaxSeats();
        double getFare();
         // SETTERS
        void setBookedSeats();
        void setCancelTicket();
        void setSource(char*);
        void setDestination(char*);
        void setStartTime(char*);
        void setDestinationTime(char*);
        void setBusFare(double);
};
#endif /*__BUS_H__*/
