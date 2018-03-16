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
    return tail[q->value];
}
int main()
{
    int n,k,c=1,value,i,j;
    cout<<"enter number of nodes : ";
    cin>>n;
    cout<<"Nodes are : ";
    for(i=0;i<n;i++)
    {
        cout<<i<<" ";
    }
    node *start[n],*tail[n];
    int adj[n][n];
    for(i=0;i<n;i++)
    {
        for(j=0;j<=n;j++)
        {
            adj[i][j]=0;
        }
    }
    while(c<=n*(n-1) && c!=0)
    {
        cout<<"enter edge : ";
        cin>>i>>j;
        adj[i][j]=1;
        cin>>c;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
    for(i=0;i<n;i++)
    {
        start[i]=makeset(i);
        tail[i]=start[i];
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(adj[i][j]==1)
            {
               tail[j]=union_1(start[i],start[j],tail);

                 tail[i]=NULL;
            }
            else
                continue;
        }
    }
    node * temp;
    for(i=0;i<n;i++)
    {
        if(tail[i]!=NULL)
        {
            temp=tail[i]->rep;
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
