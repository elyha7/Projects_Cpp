#include <iostream>
#include <cassert>
//#include <test.cpp>
//#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Tickets.h"
using namespace std;
int CURRENTTIME;//need to take this from sys in general
Ticket::Ticket(int SerialN,int Stime): SerialNumber(SerialN), SellingTime(Stime) {}
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
int TimeTicket::TryToCome()
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
class Node
{
    private:
        short int get_h()
        {
            return this?height:0;
        }

    public:
        int key;
        Ticket* data;
        short int height;
        Node* left;
        Node* right;
        Node(Ticket* tick):left(0),right(0),height(1)
        {
            data=tick;
            key=data->getNumber();
        }
        int h_diff()
        {
            return right->get_h()-left->get_h();
        }
        void correct_hight()
        {
            unsigned int hl = left->get_h();
            unsigned int hr = left->get_h();
            height = (hl>hr?hl:hr)+1;
        }
        Node* findNode(int k)
        {
            Node* toret;
            if( k < key )
                toret=left->findNode(k);
            else if( k > key )
                toret=right->findNode(k);
            else //  k == p->key
            {
                return this;
            }
            return toret;
        }
        int Checker(int key,ostream &os)
        {
            Node* a=findNode(key);
            int res;
            NumberTicket* b=dynamic_cast<NumberTicket*>(a->data);
            if (b==NULL)
            {
                TimeTicket *b=dynamic_cast<TimeTicket*>(a->data);
                res=b->TryToCome();
                os<<endl<<"_____"<<res<<"_____"<<endl;
                return res;
            }
            else
            {
                res=b->TryToCome();
                os<<endl<<"_____"<<res<<"_____"<<endl;
                return res;
            }
        }

};

void print_tree(Node* p,ostream &os)
    {
        os << "key=" <<p->data->getNumber()<< " h_diff=" << p->h_diff()<< endl;
        if(p->left)
            print_tree(p->left,cout);
        if(p->right)
            print_tree(p->right,cout);

    }
Node* rotateright(Node* p) // right rotation around p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	p->correct_hight();
	q->correct_hight();
	return q;
}
Node* rotateleft(Node* p) // left rotation around p
{
	Node* q = p->right;
	p->right = q->left;
	q->left = p;
	p->correct_hight();
	q->correct_hight();
	return q;
}
Node* balance(Node* p) // p balancing
{
	p->correct_hight();
	if( p->h_diff()==2 )
	{
		if( (p->right)->h_diff() < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( p->h_diff()==-2 )
	{
		if( (p->left)->h_diff() > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // already balanced
}
Node* insertn(Node* p, Ticket* tick) // insert node into tree p
{
	int k=tick->getNumber();
	if( !p ) return new Node(tick);
	if( k<p->key )
		p->left = insertn(p->left,tick);
	else
		p->right = insertn(p->right,tick);
	//return balance(p);
	return p;
}
Node* findmin(Node* p) // looking for min key in p
{
	return p->left?findmin(p->left):p;
}

Node* removemin(Node* p) //remove min element from p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

Node* removekey(Node* p, int k) // remove key k from p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = removekey(p->left,k);
	else if( k > p->key )
		p->right = removekey(p->right,k);
	else //  k == p->key
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if( !r ) return q;
		Node* min1 = findmin(r);
		min1->right = removemin(r);
		min1->left = q;
		return balance(min1);
	}
	return balance(p);
}
class unittest
{
private:
    int c,b;
public:
    int TestNumberTicket()
    {
        NumberTicket *a=new NumberTicket(1234,10,2);
        cout << "NumberTicket test" <<endl;
        c=a->TryToCome();
        assert(c==10);
        cout << "First test done" <<endl;
        c=a->getCurrRides();
        assert(c==1);
        cout << "Second test done" <<endl;
        c=a->TryToCome();
        assert(c==10);
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
    int TestTimeTicket()
    {
        TimeTicket *a=new TimeTicket(1234,50,10);
        cout << "TimeTicket test" <<endl;
        CURRENTTIME=20;
        c=a->TryToCome();
        assert(c==5);
        cout << "First test done" <<endl;
        c=a->getLeftTime(20);
        assert(c==40);
        cout << "Second test done" <<endl;
        CURRENTTIME=70;
        c=a->TryToCome();
        assert(c==1);
        cout << "Third test done" <<endl;
        c=a->getLeftTime(70);
        assert(c==0);
        cout << "Final test done" <<endl;
        delete a;
        return 0;
    }
    int TestTree()
    {
        cout << "Tree test" <<endl;
        int mass[8];
        int i,j;
        for (i=0;i<8;i++)
        {
            int r;
            char flag=0;
            while(flag==0)
            {
                r=rand()%10+1;
                flag=1;
                for(j=0;j<i;j++)
                    if(mass[j]==r){flag=0;}
            }
            mass[i]=r;
        }
        for(i=0;i<8;i++)
        {
            cout<<mass[i] <<" ";
        }
        cout <<endl;
        NumberTicket *a1=new NumberTicket(mass[0],10,2);
        NumberTicket *a2=new NumberTicket(mass[1],10,2);
        NumberTicket *a3=new NumberTicket(mass[2],10,2);
        NumberTicket *a4=new NumberTicket(mass[3],10,2);
        NumberTicket *a5=new NumberTicket(mass[4],10,2);
        TimeTicket *a6=new TimeTicket(mass[5],50,10);
        NumberTicket *a7=new NumberTicket(mass[6],10,2);
        //NumberTicket *a8=new NumberTicket(mass[7],10,2);
        Node* tree=new Node(a1);
        tree=insertn(tree,a2);
        tree=insertn(tree,a3);
        tree=insertn(tree,a4);
        tree=insertn(tree,a5);
        tree=insertn(tree,a6);
        tree=insertn(tree,a7);
        //tree=insertn(tree,a8);
        print_tree(tree,cout);
        //tree=removekey(tree,10);
        //Node* a=findNode(tree,mass[5]);
        //cout<<endl<<a->data->getNumber();
        cout << endl << "__________"<< endl;
        //print_tree(tree,cout);
        CURRENTTIME=70;
        int res;
        res=tree->Checker(mass[5],cout);
        assert(res==1);
        cout << "First test done" <<endl;
        CURRENTTIME=20;
        res=tree->Checker(mass[5],cout);
        assert(res==5);
        cout << "Second test done" <<endl;
        res=tree->Checker(mass[4],cout);
        assert(res==10);
        cout << "Final test done" <<endl;
        //tree->data->getInfo(cout);
        return 0;
    }


};


int main()
{
    srand ( time(NULL) );
    int c;
    NumberTicket *a=new NumberTicket(25,123456, 12);
    a->getInfo(cout);
    delete a;
    //b = a.getCurrRides();
    cout << endl << "__________"<< endl;
    unittest b;
    c=b.TestNumberTicket();
    cout << endl << "__________"<< endl;
    c=b.TestTimeTicket();
    cout << "Finished"<<endl;
    c=b.TestTree();

}
/*class Ticket
{
private:
    int SerialNumber, SellingTime;
public:
    Ticket(int SerialN,int Stime): SerialNumber(SerialN), SellingTime(Stime) {}
    int getNumber() const
    {
        return SerialNumber;
    }
    int getSellingTime() const
    {
        return SellingTime;
    }
    virtual void getInfo(ostream &os){}
    virtual ~Ticket(){}
};*/

/*class TimeTicket :public Ticket
{
private:
    int WorkTime;
public:
    TimeTicket(int SerialN, int WTime, int InTime):Ticket(SerialN,InTime), WorkTime(WTime) {}
    int getLeftTime(int CurrTime) const
    {
        int LeftTime;
        LeftTime=getSellingTime()+WorkTime-CurrTime;
        if (LeftTime<0){return 0;}
        else {return LeftTime;}
    }
    void getInfo(ostream &os)
    {
        os <<"Work time="<< WorkTime<< endl;
        os <<"Selling time="<< getSellingTime()<< endl;
        os <<"Ticket number="<< getNumber() <<endl;
    }
    int TryToCome(int CurrTime,ostream &os)
    {
        if(getLeftTime(CurrTime)==0)
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

};*/
/*class NumberTicket : public Ticket
{
private:
    int MaxRides, CurrRides;
    void ChangeCurrNumber()
    {
        CurrRides--;
    }

public:
    NumberTicket(int SerialN,  int InTime, int RidesInit):
    Ticket(SerialN,InTime),MaxRides(RidesInit),CurrRides(RidesInit) {}
    int getCurrRides() const
    {
        return CurrRides;
    }
    void getInfo(ostream &os)
    {
        os <<"Current rides number="<< CurrRides<< endl;
        os <<"Max rides number="<< MaxRides<< endl;
        os <<"Selling time="<< getSellingTime()<< endl;
        os <<"Ticket number="<< getNumber() <<endl;
    }
    int TryToCome()
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

};*/
