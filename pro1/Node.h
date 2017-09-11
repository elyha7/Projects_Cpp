#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include<iostream>
#include "Tickets.h"
using namespace std;
class Node
{
    private:
        int key;
        Ticket* data;
        short int height;
        Node* left;
        Node* right;
        int h_diff();
        void correct_hight();
        short int get_h();
        Node* findNode(int k);
        Node* rotateright();
        Node* rotateleft();
        Node* balance();
        Node* findmin();
        Node*  removemin();
    public:

        Node(Ticket* tick);
        int Checker(int key,ostream &os,int CURRENTTIME);
        Node* insertn(Ticket* tick);
        Node* removekey( int k);
        void print_tree(ostream &os);
        ~Node()
        {
            //delete left;
            //delete right;
            delete data;
        }
};

#endif // NODE_H_INCLUDED
