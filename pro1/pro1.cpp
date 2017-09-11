#include <iostream>
#include <cassert>
//#include <test.cpp>
//#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "Tickets.h"
#include "Node.h"
using namespace std;
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
        int CURRENTTIME;
        TimeTicket *a=new TimeTicket(1234,50,10);
        cout << "TimeTicket test" <<endl;
        CURRENTTIME=20;
        c=a->TryToCome(CURRENTTIME);
        assert(c==5);
        cout << "First test done" <<endl;
        c=a->getLeftTime(20);
        assert(c==40);
        cout << "Second test done" <<endl;
        CURRENTTIME=70;
        c=a->TryToCome(CURRENTTIME);
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
        //srand(17);
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
        /*tree=insertn(tree,a2);
        tree=insertn(tree,a3);
        tree=insertn(tree,a4);
        tree=insertn(tree,a5);
        tree=insertn(tree,a6);
        tree=insertn(tree,a7);*/
        tree->insertn(a2);
        tree->insertn(a3);
        tree->insertn(a4);
        tree->insertn(a5);
        tree->insertn(a6);
        tree->insertn(a7);
        //tree=insertn(tree,a8);
        tree->print_tree(cout);
        //Node* a=findNode(tree,mass[5]);
        //cout<<endl<<a->data->getNumber();
        cout << endl << "__________"<< endl;
        //print_tree(tree,cout);
        int CURRENTTIME;
        CURRENTTIME=70;
        int res;
        res=tree->Checker(mass[5],cout,CURRENTTIME);
        assert(res==1);
        cout << "First test done" <<endl;
        CURRENTTIME=20;
        res=tree->Checker(mass[5],cout,CURRENTTIME);
        assert(res==5);
        cout << "Second test done" <<endl;
        res=tree->Checker(mass[4],cout,CURRENTTIME);
        assert(res==10);
        cout << "Third test done" <<endl;
        tree->removekey(mass[1]);
        cout << endl << "__________"<< endl;
        tree->print_tree(cout);
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
