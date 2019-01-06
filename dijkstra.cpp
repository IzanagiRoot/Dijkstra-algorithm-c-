#include<iostream>
#include<fstream>
#include <string>
#include<vector>

using namespace std;

int N;
int a,b,w,w2;
int am[100][100];
int dis[100];
int visited[100]={0};
string inter[100];
string town[100];
int node;
string beginning,target;
vector<int>before;
vector<int>path;
int nb;

int exist(string ch)
{
    int veref=0;
    for(int i=1;i<=node;i++)
        if(ch==inter[i])
        {
            veref=i;
            break;
        }
    return veref;
}


void dij_input()
{
    string const file("dijkstra.txt");
    ofstream flow(file.c_str());
    int dist,j,k,cpt(1);
    bool here=false,there(false);
    cin>>node>>beginning>>target;
    flow<<node<<endl;
    inter[1]=beginning;inter[node]=target;
    for(int i=1;i<=node;i++)
    {
        cin>>town[i]>>town[i+1]>>dist;
        here=false;there=false;
        for(int m=1;m<=node;m++)
        {
            if(town[i]==inter[m]){ here=true; break; }
        }

        for(int m=1;m<=node;m++)
        {
            if(town[i+1]==inter[m]){ there=true; break; }
        }
        if(here==false && there==false)
            {
                inter[cpt+1]=town[i];
                inter[cpt+2]=town[i+1];
                cpt+=2;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==true && there==false)
            {
                inter[cpt+1]=town[i+1];
                cpt++;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==false && there==true)
            {
                inter[cpt+1]=town[i];
                cpt++;
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
        else if(here==true && there==true)
            {
                j=exist(town[i]);
                k=exist(town[i+1]);
                flow<<j<<" "<<k<<" "<<dist<<endl;
            }
    }

}


int dij(int x){
    visited[x]=1;
    //MSJ
    for(int i=1;i<=N;i++)
    {
        if((visited[i]==0) && (am[x][i]!=-1)){
          if((dis[x]+am[x][i]<dis[i]) || (dis[i]==-1))
          {
              dis[i]=dis[x]+am[x][i];
              int size=before.size()-1;
              if(i==N) nb=x;
              if(before[size]!=x)
                before.push_back(x);
          }
        }
    }
    //Je selectionne un nouveau noeud
    int smaller=-1,sw=-1;
    for(int i=0;i<=N;i++)
    {
        if((visited[i]==0)&&(dis[i]>=0)&&((sw>dis[i])|| (sw==-1))){
            sw=dis[i];
            smaller=i;
        }
    }
    if(smaller!=-1)
    {
        dij(smaller);
        return 0;
        }
    return 0;
}


void print_path()
{

    int i;
    int size1=before.size()-1;

    for(i=1;i<size1;i++)
        if(nb==before[i]) break;

    path.push_back(nb);
    bool find_it=false;
    for(int k=i;k>0;k--)
    {
        ifstream find("dijkstra.txt");
        find>>N;
        find_it=false;
        while(!find.eof())
        {
            find>>a>>b>>w;
            if((before[k]==a && nb==b))
            {
                path.push_back(a);
                nb=before[k];
                find_it=true;
                w2=w;
                break;
            }
            else if((before[k]==b && nb==a))
            {
                path.push_back(b);
                nb=before[k];
                find_it=true;
                w2=w;
                break;
            }
        }
        if(find_it==false)
        {
            ifstream find("dijkstra.txt");
            find>>N;
            while(!find.eof())
            {
                find>>a>>b>>w;
                if((before[k]==a && before[k+2]==b))
                {
                    if((dis[before[k+1]]+w2)>(dis[before[k]]+w))
                        {
                            nb=before[k];
                            path.pop_back();
                            path.push_back(nb);
                        }
                    break;
                }
                else if((before[k]==b && before[k+2]==a))
                {
                    if((dis[before[k+1]]+w2)>(dis[before[k]]+w))
                        {
                            nb=before[k];
                            path.pop_back();
                            path.push_back(nb);
                        }
                    break;
                }
            }
        }
    }

    int size=path.size()-1;
    for(int i=size;i>=0;i--)
    cout<<inter[path[i]]<<"->";
    cout<<target;
    before.clear();
    path.clear();
    for(int y=0;y<100;y++)
    {
        inter[y]="*";
        town[y]="*";
    }
}


int main()
{
    int P;
    cin>>P;
for(int k=0;k<P;k++)
{
    dij_input();
    ifstream fin("dijkstra.txt");
    //charge le fichier
    fin>>N;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=N;j++)
        {
            am[i][j]=-1;
        }
    }

    for(int i=0;i<=N;i++)
    visited[i]=0;

    for(int i=0;i<=N;i++)
    dis[i]=-1;

    dis[1]=0;
    while(!fin.eof())
    {
        fin>>a>>b>>w;
        am[a][b]=w;
        am[b][a]=w;
    }
    before.push_back(-1);
    dij(1);
    cout<<endl;
    print_path();
    cout<<" "<<dis[N]<<endl;
    cout<<endl;
}
    return 0;
}
