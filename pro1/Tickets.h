#ifndef TICKETS_H_INCLUDED
#define TICKETS_H_INCLUDED
#include<iostream>
using namespace std;
class Ticket
{
private:
    int SerialNumber, SellingTime;
public:
    Ticket(int SerialN,int Stime);
    int getNumber() const;
    int getSellingTime() const;
    virtual void getInfo(ostream &os)=0;
    virtual ~Ticket(){}
};
class NumberTicket : public Ticket
{
private:
    int MaxRides, CurrRides;
    void ChangeCurrNumber();
public:
    NumberTicket(int SerialN,  int InTime, int RidesInit);
    int getCurrRides() const;
    void getInfo(ostream &os);
    int TryToCome();

};
class TimeTicket :public Ticket
{
private:
    int WorkTime;
public:
    TimeTicket(int SerialN, int WTime, int InTime);
    int getLeftTime(int CurrTime) const;
    void getInfo(ostream &os);
    int TryToCome();
};

#endif // TICKETS_H_INCLUDED
