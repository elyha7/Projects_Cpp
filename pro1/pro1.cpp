#include <iostream>
#include <cassert>
using namespace std;
/*class Ticket
{
private:
    int SerialNumber, SellingTime;
public:

};*/
class NumberTicket
{
private:
    int SerialNumber, SellingTime, MaxRides, CurrRides;
public:
    NumberTicket(int RidesInit, int SerialN, int InTime)
    {
        SellingTime=InTime;
        SerialNumber=SerialN;
        MaxRides=RidesInit;
        CurrRides=MaxRides;

    }
    int getCurrRides() const
    {
        return CurrRides;
    }
    void getInfo(ostream &os)
    {
        os <<"Current rides number="<< CurrRides<< endl;
        os <<"Max rides number="<< MaxRides<< endl;
        os <<"Selling time="<< SellingTime<< endl;
    }
    void ChangeCurrNumber()
    {
        CurrRides--;
    }
    int TryToCome()
    {
        if(CurrRides==0)
        {
            cout << "Error: Not enough rides"<< endl;
            return 1;
        }
        else
        {
            cout << "Welcome"<< endl;
            ChangeCurrNumber();
            return 0;

        }
    }
    ~NumberTicket(){}

};
/*class TimeTicket
{
private:
    int SerialNumber, SellingTime, MaxRides, CurrRides;
public:
    NumberTicket(int RidesInit, int SerialN, int InTime)
    {
        //cout << "Break point 1"
        //Initialization(InTime,RidesInit,SerialN);
        //cout << "Break point 2"
        SellingTime=InTime;
        SerialNumber=SerialN;
        MaxRides=RidesInit;
        CurrRides=MaxRides;

    }
    int getCurrRides() const
    {
        return CurrRides;
    }
    void getInfo(ostream &os)
    {
        os <<"Current rides number="<< CurrRides<< endl;
        os <<"Max rides number="<< MaxRides<< endl;
        os <<"Selling time="<< SellingTime<< endl;
    }
    void ChangeCurrNumber()
    {
        CurrRides--;
    }
    int TryToCome()
    {
        if(CurrRides==0)
        {
            cout << "Error: Not enough rides"<< endl;
            return 1;
        }
        else
        {
            cout << "Welcome"<< endl;
            ChangeCurrNumber();
            return 0;

        }
    }
    ~NumberTicket(){}

};*/
class unittest
{
private:
    int c,b;
public:
    int TestNumberTicket()
    {
        NumberTicket *a=new NumberTicket(2,1, 12);
        c=a->TryToCome();
        assert(c==0);
        cout << "First test done" <<endl;
        c=a->getCurrRides();
        assert(c==1);
        cout << "Second test done" <<endl;
        c=a->TryToCome();
        assert(c==0);
        cout << "Third test done" <<endl;
        c=a->getCurrRides();
        assert(c==0);
        cout << "Fourth test done" <<endl;
        c=a->TryToCome();
        assert(c==1);
        cout << "Final test done" <<endl;
        delete a;
        return 0;

    }
};


int main()
{
    int c;
    NumberTicket *a=new NumberTicket(25,123456, 12);
    a->getInfo(cout);
    //b = a.getCurrRides();
    cout << endl << "__________"<< endl;
    unittest b;
    c=b.TestNumberTicket();
    //c= a->TryToCome();
    //c= a.TryToCome();
    //c= a.TryToCome();
    //c= a.TryToCome();
    //a->getInfo(cout);
    //delete a;
    cout << "Finished"<<endl;

}

