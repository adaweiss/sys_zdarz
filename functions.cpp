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

    for(int i =0;i<n+1;i++){
        for(int j =0;j<n;j++){
            if((j/8)==(i/9)){
                switch(j%8)
                {
                case 0:
                    tab[i+1][j]=-1;
                    tab[i+2][j]=1;
                    break;
                case 1:
                    tab[i][j]=-1;
                    tab[i+2][j]=-1;
                    tab[i+3][j]=1;
                    break;
                case 2:
                    tab[i][j]=1;
                    tab[i+3][j]=-1;
                    tab[i+4][j]=1;
                    break;
                case 3:
                    tab[i+1][j]=1;
                    tab[i+4][j]=-1;
                    tab[i+8][j]=-1;
                    break;
                case 4:
                    tab[i+1][j]=-1;
                    tab[i+5][j]=1;
                    break;
                case 5:
                    tab[i][j]=-1;
                    tab[i+5][j]=-1;
                    tab[i+6][j]=1;
                    break;
                case 6:
                    tab[i][j]=1;
                    tab[i+6][j]=-1;
                    tab[i+7][j]=1;
                    break;
                case 7:
                    tab[i+1][j]=1;
                    tab[i+7][j]=-1;
                    tab[i+8][j]=-1;
                    break;

                default:
                    cout<<"Error in generating incident matrix!"<<endl;
                    break;
                }
            } else {
                tab[i][j]=0;
            }
        }
    }

    return tab;
}
