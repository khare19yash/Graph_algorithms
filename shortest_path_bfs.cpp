
#include<iostream>
using namespace std;
static int top=-1,rear=-1;
int white=0,gray=1,black=2;
class vertex
{
public:
    int value;
    vertex *next;
};
void enqueue(int q[],int k)
{
    if(top==-1)
    {
        top=top+1;
        rear=top;
        q[top]=k;
    }
    else
    {
        rear=rear+1;
        q[rear]=k;
    }
}
int dequeue(int q[])
{
    if(top==-1)
    {
        return -1;
    }
    else
    {
        int temp;
        temp=top;
        top=top+1;
        return q[temp];
    }
}
vertex * create_list(int i,int j,vertex * adj_list[])
{
    if(adj_list[i]==NULL)
    {
        adj_list[i]=new vertex;
        adj_list[i]->next=NULL;
        adj_list[i]->value=j;
        return adj_list[i];
    }
    else
    {
        vertex *temp,*object;
        temp=adj_list[i];
        object=new vertex;
        object->next=NULL;
        object->value=j;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=object;
        return adj_list[i];
    }
}
void bfs(vertex* adj_list[],int *d,int *color,int *parent,int q[],int n,int source)
{
    int i;
    for(i=0;i<n;i++)
    {
        color[i]=white;
        d[i]=-1;
        parent[i]=-1;
    }
    color[source]=gray;
    d[source]=0;
    parent[source]=-1;
    enqueue(q,source);
    while(top<=rear)
    {
        int u;
        u=dequeue(q);
        vertex *temp;
        temp=adj_list[u];
        while(temp!=NULL)
        {
            if(color[temp->value]==white)
            {
                color[temp->value]=gray;
                d[temp->value]=d[u]+1;
                parent[temp->value]=u;
                enqueue(q,temp->value);
            }
            temp=temp->next;
        }
        color[u]=black;
    }
}
void print_path(int *parent,int source,int destination)
{
    if(parent[destination]==source)
    {
        cout<<parent[destination]<<" ";
        return;
    }
    else
    {

        print_path(parent,source,parent[destination]);
        cout<<parent[destination]<<" ";
    }
}
int main()
{
    int n,i,j,c=1,source,destination;
    cout<<"Enter number of nodes : ";
    cin>>n;
    vertex *adj_list[n];
    int q[n],*d,*color,*parent;
    d=new int[n];
    color=new int[n];
    parent=new int[n];

    for(i=0;i<n;i++)
    {
        adj_list[i]=NULL;
    }
    while(c)
    {
        cout<<"enter edge : ";
        cin>>i>>j;
        adj_list[i]=create_list(i,j,adj_list);
        adj_list[j]=create_list(j,i,adj_list);
        cin>>c;
    }
    cout<<"Enter source and destination vertex : ";
    cin>>source>>destination;
    bfs(adj_list,d,color,parent,q,n,source);
    cout<<"Length of shortest path : "<<d[destination]<<endl;
    cout<<"Path is : ";
    print_path(parent,source,destination);
    cout<<destination<<endl;
    return 0;
}

