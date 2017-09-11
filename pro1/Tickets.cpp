#include "Tickets.h"
#include <cstdlib>
#include <ctime>
using namespace std;
Ticket::Ticket(int SerialN,int Stime): SerialNumber(SerialN), SellingTime(Stime) {}
int CURRENTTIME;
int Ticket::getNumber() const
{
    return SerialNumber;
}
int Ticket::getSellingTime() const
{
    return SellingTime;
}

NumberTicket::NumberTicket(int SerialN,  int InTime, int RidesInit):
    Ticket(SerialN,InTime),MaxRides(RidesInit),CurrRides(RidesInit) {}
int NumberTicket::getCurrRides() const
{
    return CurrRides;
}
void NumberTicket::ChangeCurrNumber()
{
    CurrRides--;
}
void NumberTicket::getInfo(ostream &os)
{
    os <<"Current rides number="<< CurrRides<< endl;
    os <<"Max rides number="<< MaxRides<< endl;
    os <<"Selling time="<< getSellingTime()<< endl;
    os <<"Ticket number="<< getNumber() <<endl;
}
int NumberTicket::TryToCome()
{
    if(CurrRides==0)
    {
        //cout << "Error: Not enough rides"<< endl;
        return 1;
    }
    else
    {
        //cout << "Welcome"<< endl;
        ChangeCurrNumber();
        return 10;

    }
}


TimeTicket::TimeTicket(int SerialN, int WTime, int InTime):Ticket(SerialN,InTime), WorkTime(WTime) {}
int TimeTicket::getLeftTime(int CurrTime) const
    {
        int LeftTime;
        LeftTime=getSellingTime()+WorkTime-CurrTime;
        if (LeftTime<0){return 0;}
        else {return LeftTime;}
    }
void TimeTicket::getInfo(ostream &os)
{
    os <<"Work time="<< WorkTime<< endl;
    os <<"Selling time="<< getSellingTime()<< endl;
    os <<"Ticket number="<< getNumber() <<endl;
}
int TimeTicket::TryToCome(int CURRENTTIME)
{
    if(getLeftTime(CURRENTTIME)==0)
        {
            //os << "Error: Time is over"<< endl;
            return 1;
        }
        else
        {
            //os << "Welcome"<< endl;
            return 5;

        }
}
