#include<iostream>
#include"prop_opr.h"
#include <ctime>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main()
{
    unsigned t0,t1;
    t0=clock();
    prop_opr *game1=new prop_opr();
    bool state=true;
    game1->initgame();
    char a[1];
    while (state==true)
    {
        cout<<"mover derecha tecla (D), izquierda tecla(A), arriba (W), abajo (S)"<<endl;
        a[1]=cin.get();
        a[1]=toupper(a[1]);
        switch (a[1])
        {
        case 'A': state= game1->moviz();

            break;
        case 'D': state= game1->movder();
        break;
        case 'S': state=game1->slicedown();
        break;
        case 'W': state= game1->sliceup();
        break;
        default: cout<<"error tecla no valida"<<endl;
        break;
        }
        fflush(stdin);

    }
    


    t1 = clock();
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    

    cout << "Execution Time: " << time << endl;
}