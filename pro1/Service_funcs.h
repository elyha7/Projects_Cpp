#ifndef SERVICE_FUNCS_H_INCLUDED
#define SERVICE_FUNCS_H_INCLUDED
#include "Node.h"
/*void print_tree(Node* p,ostream &os)
    {
        os << "key=" <<p->data->getNumber()<< " h_diff=" << p->h_diff()<< endl;
        if(p->left)
            print_tree(p->left,cout);
        if(p->right)
            print_tree(p->right,cout);

    }*/
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
/*Node* insertn(Node* p, Ticket* tick) // insert node into tree p
{
	int k=tick->getNumber();
	if( !p ) return new Node(tick);
	if( k<p->key )
		p->left = insertn(p->left,tick);
	else
		p->right = insertn(p->right,tick);
	//return balance(p);
	return p;
}*/
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

#endif // SERVICE_FUNCS_H_INCLUDED
