#include <cstdlib>
#include <ctime>
#include <iostream>
//#include "Service_funcs.h"
#include "Tickets.h"
#include "Node.h"
using namespace std;
Node::Node(Ticket* tick):left(0),right(0),height(1)
{
    data=tick;
    key=data->getNumber();
}
int Node::h_diff()
{
    return right->get_h()-left->get_h();
}
short int Node:: get_h()
        {
            return this?height:0;
        }
void Node::correct_hight()
{
    unsigned int hl = left->get_h();
    unsigned int hr = left->get_h();
    height = (hl>hr?hl:hr)+1;
}
Node* Node::findNode(int k)
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
int Node::Checker(int key,ostream& os,int CURRENTTIME)
{
    Node* a=findNode(key);
    int res;
    NumberTicket* b=dynamic_cast<NumberTicket*>(a->data);
    if (b==NULL)
    {
        TimeTicket *b=dynamic_cast<TimeTicket*>(a->data);
        res=b->TryToCome(CURRENTTIME);
        //os<<endl<<"_____"<<res<<"_____"<<endl;
        return res;
    }
    else
    {
        res=b->TryToCome();
        //os<<endl<<"_____"<<res<<"_____"<<endl;
        return res;
    }
}
Node* Node:: insertn(Ticket* tick) // insert node into tree p
{
	int k=tick->getNumber();
	if( !this ) return new Node(tick);
	if( k<key )
		left = left->insertn(tick);
	else
		right = right->insertn(tick);
	//return balance(p);
	return this;
}
void Node::print_tree(ostream &os)
    {
        if(this)
        {
            left->print_tree(cout);
            os << "key=" <<data->getNumber()<< " h_diff=" << h_diff()<< endl;
            right->print_tree(cout);
        }
    }
Node* Node:: rotateright() // right rotation around p
{
	Node* q = left;
	left = q->right;
	q->right = this;
	this->correct_hight();
	q->correct_hight();
	return q;
}
Node* Node:: rotateleft() // left rotation around p
{
	Node* q = right;
	right = q->left;
	q->left = this;
	this->correct_hight();
	q->correct_hight();
	return q;
}
Node* Node:: balance() // p balancing
{
	this->correct_hight();
	if( h_diff()==2 )
	{
		if( (right)->h_diff() < 0 )
			right = right->rotateright();
		return this->rotateleft();
	}
	if( h_diff()==-2 )
	{
		if( (left)->h_diff() > 0  )
			left = left->rotateleft();
		return this->rotateright();
	}
	return this; // already balanced
}
Node* Node:: findmin() // looking for min key in p
{
	return left?left->findmin():this;
}

Node* Node:: removemin() //remove min element from p
{
	if( left==0 )
		return right;
	left = left->removemin();
	return this->balance();
}

Node* Node:: removekey(int k) // remove key k from p
{
	if( !this ) return 0;
	if( k < key )
		left = left->removekey(k);
	else if( k > key )
		right = right->removekey(k);
	else //  k == p->key
	{
		Node* q = left;
		Node* r = right;
		delete this;
		if( !r ) return q;
		Node* min1 = r->findmin();
		min1->right = r->removemin();
		min1->left = q;
		return min1->balance();
	}
	return this->balance();
}
