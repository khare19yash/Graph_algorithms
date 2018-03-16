#include<iostream>
using namespace std;
class vertex
{
public:
    int value;
    int weight;
    vertex *next;
};
vertex *create_list(int i,int j,int weight,vertex *adj_list[])
{
    if(adj_list[i]==NULL)
    {
        adj_list[i]=new vertex;
        adj_list[i]->next=NULL;
        adj_list[i]->value=j;
        adj_list[i]->weight=weight;
        return adj_list[i];
    }
    else
    {
        vertex *temp,*object;
        object=new vertex;
        object->next=NULL;
        object->value=j;
        object->weight=weight;
        temp=adj_list[i];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=object;
        return adj_list[i];
    }
}
void initialize_single_source(int *d,int *pred,int source,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        d[i]=9999;
        pred[i]=-1;
    }
    d[source]=0;
}
void relaxation(int u,int v,int *d,int *pred,vertex *adj_list[])
{
    vertex *temp;
    temp=adj_list[u];
    while(temp->value!=v)
    {
        temp=temp->next;
    }
    if(d[v]>d[u]+temp->weight)
    {
        d[v]=d[u]+temp->weight;
        pred[v]=u;
    }
}
void bellman_ford(vertex *adj_list[],int source,int *d,int *pred,int n)
{
    int i,j;
    vertex *temp;
    initialize_single_source(d,pred,source,n);
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            temp=adj_list[j];
            while(temp!=NULL)
            {
                relaxation(j,temp->value,d,pred,adj_list);
                temp=temp->next;
            }
        }
    }
    /*for(i=0;i<n;i++)
    {
        temp=adj_list[i];
        while(temp!=NULL)
        {
            if(d[temp->value]>d[i]+temp->weight)

            else
                return 0;
        }
    }*/
}
int main()
{
    int n,i,j,weight,c=1,p;
    cout<<"Enter number of vertex : ";
    cin>>n;
    vertex *adj_list[n];
    int *d,*pred;
    d=new int[n];
    pred=new int[n];
    for(i=0;i<n;i++)
    {
        adj_list[i]=NULL;
    }
    while(c)
    {
        cout<<"Enter edge and edge weight : ";
        cin>>i>>j>>weight;
        adj_list[i]=create_list(i,j,weight,adj_list);
        cin>>c;
    }
    bellman_ford(adj_list,0,d,pred,n);
    for(i=0;i<n;i++)
    {
        vertex *temp;
        temp=adj_list[i];
        while(temp!=NULL)
        {
            cout<<temp->value<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
    for(i=0;i<n;i++)
    {
        cout<<d[i]<<" ";
    }
    return 0;
}
