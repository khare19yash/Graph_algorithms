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
int parent(int i)
{
    if(i==0)
        return -1;
    else
    return i-1/2;
}
int leftchild(int i)
{
    return 2*i+1;
}
int rightchild(int i)
{
    return 2*i+2;
}
void heapify(int *a,int *b,int i)
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
        swap_1(b+i,b+minimum);
        heapify(a,b,minimum);
    }
}
int extract_min(int *a,int *b)
{
    int minimum,index;
    minimum=a[0];
    index=b[0];
    a[0]=a[heapsize];
    b[0]=b[heapsize];
    heapsize=heapsize-1;
    heapify(a,b,0);
    return index;
}
void decrease_key(int *a,int *b,int i,int key)
{
    a[i]=key;
    while(i>0 && a[parent(i)]>a[i])
    {
        swap_1(a+i,a+parent(i));
        swap_1(b+i,b+parent(i));
        i=parent(i);
    }
}
void insert_key(int *a,int *b,int key)
{
    heapsize=heapsize+1;
    a[heapsize]=9999;
    decrease_key(a,b,heapsize,key);
}
bool check_q(int *q_index,int value)
{
    int i;
    if(heapsize==-1)
        return true;
    else
    {
        for(i=0;i<=heapsize;i++)
        {
            if(q_index[i]==value)
            return true;
        }
        if(i>heapsize)
        return false;
    }

}
void prim(vertex *adj_list[],int r,int *q_weight,int *q_index,int *key,int *pred,int n)
{
    int i,v,u;
    vertex *temp;
    for(i=0;i<n;i++)
    {
        key[i]=9999;
        pred[i]=-1;
    }
    key[r]=0;
    for(i=0;i<n;i++)
    {
        q_index[i]=i;
        insert_key(q_weight,q_index,key[i]);
    }
    while(heapsize>=0)
    {

        u=extract_min(q_weight,q_index);
        temp=adj_list[u];
        while(temp!=NULL)
        {
            v=temp->value;
            if(check_q(q_index,v) && temp->weight<key[v])
            {
                for(i=0;i<=heapsize;i++)
                {
                    if(q_weight[i]==key[v])
                        break;
                }
                key[v]=temp->weight;
                pred[v]=u;
                if(heapsize>=0)
                decrease_key(q_weight,q_index,i,key[v]);
            }
            temp=temp->next;
        }
    }

}

int main()
{
    int n,i,c=1,j,weight;
    cout<<"Enter number of nodes : ";
    cin>>n;
    vertex *adj_list[n],*temp;
    int *key,*q_weight,*q_index,*pred;
    key=new int[n];
    q_weight=new int[n];
    q_index=new int[n];
    pred=new int[n];
    heapsize=-1;
    for(i=0;i<n;i++)
    {
        adj_list[i]=NULL;
    }
    while(c<=n*(n-1) && c!=0)
    {
        cout<<"Enter edge and weight : ";
        cin>>i>>j>>weight;
        adj_list[i]=create_list(i,j,weight,adj_list);
        adj_list[j]=create_list(j,i,weight,adj_list);
        cin>>c;
    }
    for(i=0;i<n;i++)
    {
        temp=adj_list[i];
        while(temp!=NULL)
        {
            cout<<temp->value<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
    prim(adj_list,0,q_weight,q_index,key,pred,n);
    for(i=0;i<n;i++)
    {
        cout<<key[i]<<" ";
    }
    for(i=0;i<n;i++)
    {
        cout<<pred[i]<<" ";
    }
    return 0;
}
