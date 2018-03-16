#include<iostream>
using namespace std;
static int top=-1,rear=-1;
int white=0,gray=1,black=2;
class vertex
{
    public:
    int value;
    vertex * next;
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
vertex * create_list(int i,int j,vertex *adj_list[])
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
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        object=new vertex;
        object->next=NULL;
        object->value=j;
        temp->next=object;
        return adj_list[i];
    }
}


void bfs(vertex *adj_list[],int source,int *d,int q[],int *color,int *parent,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
              d[i]=-1;
              parent[i]=-1;
              color[i]=white;
    }
    d[source]=0;
    parent[source]=-1;
    color[source]=gray;
    enqueue(q,source);
    while(top<=rear)
    {
        int u;
        vertex *temp;
        u=dequeue(q);
        temp=adj_list[u];
        while(temp!=NULL)
        {
            if(color[temp->value]==white)
            {
                d[temp->value]=d[u]+1;
                parent[temp->value]=u;
                color[temp->value]=gray;
                enqueue(q,temp->value);
            }
            temp=temp->next;
        }
        color[u]=black;
    }

}
int main()
{
    int n,i,j,c=1;
    cout<<"Enter number of nodes : ";
    cin>>n;
    int *d,q[n],*parent,*color;
    vertex *adj_list[n];
    d=new int[n];
    parent=new int[n];
    color=new int[n];

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
    bfs(adj_list,1,d,q,color,parent,n);
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

