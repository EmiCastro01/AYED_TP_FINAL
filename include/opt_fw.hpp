#pragma once
#include <cstdlib>
#include <iostream>
#define INFI  9000
#define MAXNODOS  5


void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS]);
void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS],int cf[][MAXNODOS]);
void caminoFloyd(int cf[][MAXNODOS], int s, int t);

using namespace std;
/*

int main(int argc, char *argv[])
{   int peso[MAXNODOS][MAXNODOS]={INFI, INFI,    4,   13, INFI,
                                  INFI, INFI,    1, INFI, INFI,
                                  INFI, INFI, INFI,    2,   11,
                                  INFI, INFI, INFI,INFI,     2,
                                  INFI, INFI, INFI,    1, INFI      
                                 };
    int caminos[MAXNODOS][MAXNODOS];
    int cf[MAXNODOS][MAXNODOS];
    int MatrizFloyd[MAXNODOS][MAXNODOS];
    int *pdist, i, j, precede[MAXNODOS],s,t;
    
    s=0;  // vertice de inicio
    t=4;  // vertice final
    
    cout<<endl<<"Matriz de pesos";   
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",peso[i][j]);                 
           }                 
    }
    
    warshall(peso,caminos);
    cout<<"\n\n";
    cout<<"\n WARSHALL ------------------------\n";
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",caminos[i][j]); 
           }//fin for j                 
    }//fin for i
    cout<<"\n\n";
    if(caminos[s][t]==1){
                         cout<<"\n HAY CAMINO ENTRE s= "<<s
                             <<" y t= "<<t<<endl;
                         Floyd(peso,MatrizFloyd,cf);
                         cout<<"\n costo para ir de "
                             <<s<<" a "<<t<<"= "
                             <<MatrizFloyd[s][t];
                         cout<<"\n\n camino:  "<<s;
                         caminoFloyd(cf,s,t);
                         cout<<"  "<<t;  
    }
    else{
          cout<<"\n NO HAY CAMINO POSIBLE ENTRE s= "
              <<s<<" y t= "<<t<<endl;
          
    }//fin if

    cout<<endl<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
void warshall(int peso[][MAXNODOS], int caminos[][MAXNODOS])
{ int i,j,k;
//inicializo caminos haciendola igual a la adjunta impl�cita en peso  
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                if(peso[i][j]==INFI)caminos[i][j]=0;
                else                caminos[i][j]=1;
         }//fin for j
  }//fin for i
  
  for(k=0;k<MAXNODOS;k++){
         for(i=0;i<MAXNODOS;i++){
                for(j=0;j<MAXNODOS;j++){                 
                                if(caminos[i][j]==0) 
                                   caminos[i][j]=caminos[i][k]&&caminos[k][j];
                }//fin for j
         }//fin for i
  }//fin for k
}//fin warshall     

void Floyd(int peso[][MAXNODOS], int A[][MAXNODOS], int cf[][MAXNODOS])
{ int i,j,k;
  for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 A[i][j]=peso[i][j]; cf[i][j]=-1;
         }
  }
  for(i=0;i<MAXNODOS;i++) A[i][i]=0;
  
  for(k=0;k<MAXNODOS;k++){
      for(i=0;i<MAXNODOS;i++){
         for(j=0;j<MAXNODOS;j++){
                                 if((A[i][k]+ A[k][j])< A[i][j]){
                                              A[i][j]= A[i][k]+ A[k][j];
                                              cf[i][j]=k;
                                 }
         }
      }
  }
    cout<<"\n FLOYD ------------------------\n";    
    for(i=0;i<MAXNODOS;i++){
           cout<<"\n";                 
           for(j=0;j<MAXNODOS;j++){
                  printf(" %5i",A[i][j]);                 
           }                 
    }
    cout<<endl;
    system("PAUSE");
     
}

void caminoFloyd(int cf[][MAXNODOS], int s, int t)
{ int k;

  k=cf[s][t];
  if (k!=-1){
            caminoFloyd(cf,s,k);
            cout<<"  "<<k;
            caminoFloyd(cf,k,t);
            }
}

