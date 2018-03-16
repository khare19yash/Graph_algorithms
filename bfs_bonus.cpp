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
    int n,i,j,c=1,source,size,destination;
    cout<<"Enter number of nodes : ";
    cin>>n;
    size=n*n;
    int matrix[10][10],nodes[10][10],k=0;
    int q[size],*d,*color,*parent;
    vertex * adj_list[size];
    d=new int[size];
    color=new int[size];
    parent=new int[size];

    for(i=0;i<size;i++)
    {
        adj_list[i]=NULL;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>matrix[i][j];
            nodes[i][j]=k;
            k++;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
                 if(i+1>=0 && i+1<n && matrix[i+1][j]!=0)
                 {
                      adj_list[nodes[i][j]]=create_list(nodes[i][j],nodes[i+1][j],adj_list);

                 }

                 if(i-1>=0 && i-1<n && matrix[i-1][j]!=0)
                 {
                      adj_list[nodes[i][j]]=create_list(nodes[i][j],nodes[i-1][j],adj_list);

                 }

                 if(j+1>=0 && j+1<n && matrix[i][j+1]!=0)
                 {
                     adj_list[nodes[i][j]]=create_list(nodes[i][j],nodes[i][j+1],adj_list);

                 }

                 if(j-1>=0 && j-1<n && matrix[i][j-1]!=0)
                 {
                     adj_list[nodes[i][j]]=create_list(nodes[i][j],nodes[i][j-1],adj_list);

                 }


        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(matrix[i][j]==1)
            {

                 break;


            }

        }
        if(j!=n)
        {
            break;
        }
    }
    source = nodes[i][j];
    bfs(adj_list,d,color,parent,q,size,source);
    //fun(i,j,matrix,nodes,n,adj_list);
    //adj_list[nodes[i][j]]=create_list(nodes[i][j],nodes[i+1][j],adj_list);

    for(i=0;i<size;i++)
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
        for(j=0;j<n;j++)
        {
            if(matrix[i][j]==2)
            {

                 break;

            }

        }
        if(j!=n)
        {
            break;
        }
    }
    destination=nodes[i][j];
    cout<<"Shortest distance : "<<d[destination]<<endl;
     print_path(parent,source,destination);
    cout<<destination<<endl;
    for(i=0;i<size;i++)
    {
        cout<<d[i]<<" ";
    }

    return 0;
}


