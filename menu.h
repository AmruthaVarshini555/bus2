#include<iostream>
#include<string>
using namespace std;

class Menu
{
    public:
        Menu(){
            cout<<"Default constructor invoked";
        }
        void welcomeScreen();
        void mainMenu();
        void adminLogin();
        void adminMenu();
        void userMenu();
        void viewBookingsMenu();
};
