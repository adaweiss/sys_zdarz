#include <iostream>
using namespace std;
/*
* k - number of machines
*/

int** build_incident_matrix(int k){
  int n=k*8; //nb of translations and states in one machine
  int** tab = new int* [n+1]; //nb of translations and states in one machine and one transport robot
  for(int i =0;i<n+1;i++)
  tab[i] = new int [n];
  for(int i =0;i<n+1;i++)
  for(int j =0;j<n;j++)
  tab[i][j]=0;
  cout<<"nie tu"<<endl;

  for(int i =0;i<n;i=i+8){
    for(int j =0;j<n;j=j+8){
      tab[i+1][j]=-1;
      tab[i+2][j]=1;
      tab[i][j+1]=-1;
      tab[i+2][j+1]=-1;
      tab[i+3][j+1]=1;
      tab[i][j+2]=1;
      tab[i+3][j+2]=-1;
      tab[i+4][j+2]=1;
      tab[i+1][j+3]=1;
      tab[i+4][j+3]=-1;
      tab[i+1][j+4]=-1;
      tab[i+5][j+4]=1;
      tab[i][j+5]=-1;
      tab[i+5][j+5]=-1;
      tab[i+6][j+5]=1;
      tab[i][j+6]=1;
      tab[i+6][j+6]=-1;
      tab[i+7][j+6]=1;
      tab[i+1][j+7]=1;
      tab[i+7][j+7]=-1;
    }
  }


  cout<<"n"<<endl;
  for(int i=0;i<n;i=i+8){
    tab[n][i+3]=1;
    tab[n][i+7]=-1;
    cout<<i+3<<" "<<i+7<<endl;
  }

  cout<<"nie tu3"<<endl;
  for(int i =0;i<n+1;i++){
    for(int j =0;j<n;j++)
    cout<<tab[i][j]<<" ";
    cout<<endl;
  }

 return tab;
}
