class Node
{
    private:
        int Number;
        Node* left;
        Node* right;
        short int h;
    public:
        Node(int numb):
        {
            Number=numb;
            left=right=0;
            h=1;
        }
        short int height(node* p)
        {
            return p?p->height:0;
        }
};
