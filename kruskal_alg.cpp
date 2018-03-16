#include<iostream>
using namespace std;
class edge
{
public:
    int i;
    int j;
    int weight;
};
class vertex
{
public:
    int name;
    vertex *next;
    vertex *rep;
};
void swap_1(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}
int partition_1(edge *sets[],int p,int r)
{
    int x,i,j;
    x=sets[r]->weight;
    i=p-1;
    for(j=p;j<r;j++)
    {
        if(sets[j]->weight<=x)
        {
            i=i+1;
           swap(sets[i],sets[j]);
        }

    }
    i=i+1;
    swap(sets[i],sets[r]);
    return i;
}
void quicksort(edge *sets[],int p,int r)
{
    if(p<r)
    {
        int q=partition_1(sets,p,r);
        quicksort(sets,p,q-1);
        quicksort(sets,q+1,r);
    }
}
edge *makeset(int i,int j,int weight)
{
    edge *object;
    object=new edge;
    object->i=i;
    object->j=j;
    object->weight=weight;
    return object;
}
vertex *makeset(int k)
{
    vertex *object;
    object=new vertex;
    object->name=k;
    object->rep=object;
    object->next=NULL;
    return object;
}
vertex *findset(vertex *x)
{
    return x->rep;
}
vertex *union_1(vertex *x,vertex *y,vertex *tail[])
{
    vertex *p,*q,*r;
        p=x->rep;
        q=y->rep;
    if(findset(x)!=findset(y))
    {
        r=tail[q->name];
        r->next=p;
        while(r!=NULL)
        {
            r->rep=q;
            r=r->next;
        }
        tail[q->name]=tail[p->name];
    }
    return tail[q->name];
}
int main()
{
    int n,i,j,weight,c=1,counter=-1,u,v;
    cout<<"Enter number of vertex :";
    cin>>n;
    edge *sets[n*(n-1)];
    vertex *points[n],*tail[n],*temp;
    for(i=0;i<n;i++)
    {
        points[i]=makeset(i);
        tail[i]=points[i];
    }
    while(c<=n*(n-1) && c!=0)
    {
        counter++;
        cout<<"enter edge and edge weight: ";
        cin>>i>>j>>weight;
        sets[counter]=makeset(i,j,weight);
        cin>>c;
    }

    quicksort(sets,0,counter);
    for(i=0;i<=counter;i++)
    {
        u=sets[i]->i;
        v=sets[i]->j;
        if(findset(points[u])!=findset(points[v]))
        {
            tail[v]=union_1(points[u],points[v],tail);
            tail[u]=NULL;
            cout<<u<<" "<<v<<endl;
        }
    }
    for(i=0;i<n;i++)
    {
        if(tail[i]!=NULL)
        {
            temp=tail[i]->rep;
            while(temp!=NULL)
            {
                cout<<temp->name<<" ";
                temp=temp->next;
            }
            cout<<endl;
        }
    }
    return 0;
}
