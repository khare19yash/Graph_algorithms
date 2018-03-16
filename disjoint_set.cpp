#include<iostream>
using namespace std;
class node
{
public:
    int value;
    node * rep;
    node *next;
};
node * makeset(int k)
{
    node *object;
    object =new node;
    object->next=NULL;
    object->rep=object;
    object->value=k;
    return object;
}
node *findset(node * x)
{
    return x->rep;
}

node * union_1(node *x, node *y,node *tail[])
{
    node *p,*q,*r,*temp;
    if(findset(x)!=findset(y))
    {
        p=findset(x);
        q=findset(y);
        r=tail[q->value];
        r->next=p;
        temp=p;
        while(temp!=NULL)
        {
            temp->rep=q;
            temp=temp->next;
        }
        temp=p;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        tail[q->value]=temp;
    }
    return q;
}
int main()
{
    int n,k,i,j;
    node *temp;
    cout<<"enter number of sets";
    cin>>n;
    cout<<"sets : ";
    for(i=0;i<n;i++)
    {
        cout<<i<<" ";
    }
    node *start[n],*tail[n];
    for(i=0;i<n;i++)
    {
        start[i]=makeset(i);
        tail[i]=start[i];
    }

    cout<<"Enter two sets for union : ";
    cin>>i>>j;
    start[j]=union_1(start[i],start[j],tail);

    start[i]=NULL;
    for(i=0;i<n;i++)
    {
        if(start[i]!=NULL)
        {
            temp=start[i];
        while(temp!=NULL)
        {
            cout<<temp->value<<" ";
            temp=temp->next;
        }
         cout<<endl;
        }

    }
    return 0;
}
