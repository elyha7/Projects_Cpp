#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include<iostream>
using namespace std;
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
        Node(Ticket* tick);
        int h_diff();
        void correct_hight();
        Node* findNode(int k);
        int Try_ticket(int key,ostream &os);

};

#endif // NODE_H_INCLUDED
