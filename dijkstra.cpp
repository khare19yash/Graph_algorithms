#include<iostream>
using namespace std;
static int heapsize;
class vertex
{
public:
    int value;
    int weight;
    vertex *next;
};
void swap_1(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}
int parent(int i)
{
    if(i!=0)
        return i-1/2;
    else
        return -1;
}
int leftchild(int i)
{
    return 2*i+1;
}
int rightchild(int i)
{
    return 2*i+2;
}
void heapify(int *a,int i)
{
    int l,r,minimum;
    l=leftchild(i);
    r=rightchild(i);
    if(l<=heapsize && a[l]<a[i])
        minimum=l;
    else
        minimum=i;
    if(r<=heapsize && a[r]<a[minimum])
        minimum=r;
    if(minimum!=i)
    {
        swap_1(a+i,a+minimum);
        heapify(a,minimum);
    }
}

int extract_min(int *a)
{
    int minimum;
    minimum=a[0];
    a[0]=a[heapsize];
    heapsize=heapsize-1;
    heapify(a,0);
    return minimum;
}
void decrease_key(int *a,int i,int key)
{
    a[i]=key;
    while(i>0 && a[parent(i)]>a[i])
    {
        swap_1(a+i,a+parent(i));
        i=parent(i);
    }
}
void insert_key(int *a,int key)
{
    heapsize=heapsize+1;
    a[heapsize]=9999;
    decrease_key(a,heapsize,key);
}

//function to create adjacency list
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
        temp = adj_list[i];
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=object;
        return adj_list[i];
    }
}
void initialize_single_source(int n,int source,int *d,int *pred)
{
    int i;
    for(i=0;i<n;i++)
    {
        d[i]=9999;
        pred[i]=-1;
    }
    d[source]=0;
}
void relaxation(int *d,int *pred,int *priority_q,int u,int v,vertex *adj_list[])
{
    int i;
    vertex *temp;
    temp=adj_list[u];
    while(temp->value!=v)
    {
        temp=temp->next;
    }
    if(d[v]>d[u]+temp->weight)
    {
        for(i=0;i<=heapsize;i++)
        {
            if(priority_q[i]==d[v])
                break;
        }
        d[v]=d[u]+temp->weight;
        pred[v]=u;
        if(heapsize>=0)
        decrease_key(priority_q,i,d[v]);
    }
}
void dijkstra(vertex *adj_list[],int source,int n,int *d,int *pred,int *priority_q)
{
    int i,u;
    vertex *temp;
    initialize_single_source(n,source,d,pred);
    /*for(i=0;i<n;i++)
    {
        temp=adj_list[i];
        while(temp!=NULL)
        {
            insert_key(priority_q,temp->weight);
            //cout<<temp->weight;
            temp=temp->next;
        }
    }*/
    for(i=0;i<n;i++)
    {
        insert_key(priority_q,d[i]);
    }
    while(heapsize>=0)
    {
        u=extract_min(priority_q);
        for(i=0;i<n;i++)
        {
            if(d[i]==u)
                break;
            else
                continue;
        }
        u=i;
        temp=adj_list[u];
        while(temp!=NULL)
        {
            relaxation(d,pred,priority_q,u,temp->value,adj_list);
            temp=temp->next;
        }
    }
}
int main()
{
    int n,i,j,weight,c=1,counter=0,number=0;
    cout<<"Enter number of vertices : ";
    cin>>n;
    vertex * adj_list[n];
    int *d,*pred,*priority_q;
    d=new int[n];
    pred=new int[n];
    priority_q=new int[n*n];
    heapsize=-1;
    for(i=0;i<n;i++)
    {
        adj_list[i]=NULL;
    }
    while(number<=n*(n-1) && c!=0)
    {
        cout<<"Enter edge and edge weight : ";
        cin>>i>>j>>weight;
        adj_list[i]=create_list(i,j,weight,adj_list);
        number++;
        cin>>c;
    }
    for(i=0;i<n;i++)
    {
        vertex *temp;
        temp=adj_list[i];
        while(temp!=NULL)
        {
            counter++;
            cout<<temp->value<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
    dijkstra(adj_list,0,n,d,pred,priority_q);
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<d[i]<<" ";
    }
    return 0;
}
