#include<iostream>
using namespace std;
int W[20][20];
int minimum(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;
}
void floyd_warshall(int W[][20],int n)
{
    int D[n+1][n+1][n+1],i,j,k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            D[0][i][j]=W[i][j];
        }
    }
    for(k=1;k<=n;k++)
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                D[k][i][j]=minimum(D[k-1][i][j],D[k-1][i][k]+D[k-1][k][j]);
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<D[n][i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    int n,i,j,c=1,weight,counter=0;
    cout<<"Enter number of nodes : ";
    cin>>n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i==j)
                W[i][j]=0;
            else
                W[i][j]=9999;
        }
    }
    while(c!=0 && counter<=n*(n-1))
    {
        cout<<"Enter edge and weight : ";
        cin>>i>>j>>weight;
        W[i][j]=weight;
        counter++;
        cin>>c;
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<W[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    floyd_warshall(W,n);
    return 0;
}
