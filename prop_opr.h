#include<iostream>
#include<time.h>
#include<stdlib.h>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;
class prop_opr
{
private:
    int strucgam [4][4];
    struct cord
    {
        int cordx;
        int cordy;
    };
    cord cordval[17];
    int numcord=0;
    unsigned t0,t1;
    int score=0;  
    bool valger=false,valger1=false, valregres=true; 
public:
    prop_opr();
    prop_opr(int cpystruc[4][4])
    {
        t0=clock();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                strucgam[i][j]=cpystruc[i][j];
            }
            
        }
        
        
    }
    void changevalcord(int val,int cord_x,int cord_y);
    void showstruc();
    bool moviz();
    bool movder();
    
    void algmov(int valinc,int val_y,bool valdif);

    void algmoviz(int valinc,int val_y);

    void algmovd1(int valinc,int val_y);
    
    void algmouup(int valinc,int valx);
    void algdown(int valinc,int valx);
    void moovdown(int valinc,int valx);
    void orz_ver(bool &verf, int &numic,int &valf,int &valx);

    void verfnum(bool &verf ,int &num,int &val_y,int val_inc);

    void moovup(int valinc,int valx);
    bool sliceup();
    bool slicedown();
    //////
    void  gencord(int num_x,int num_y,int valf);
    void showcord();
    void putval();
    int numrand();
    bool fillcord();
    void fillallcord(int valref);

    void llamgencord(int valf);
    int genaleatnum();
    void initgame();

    ~prop_opr();
};

prop_opr::prop_opr()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            strucgam[i][j]=0;
        }
        
    }
    t0=clock();
} 

void prop_opr::initgame()
{
    fillcord();
    showstruc();
}

void prop_opr::showstruc() //mostrar la matriz
{
    cout<<"//////////////"<<"the score is "<<score<<"////////////////////////////"<<endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout<<strucgam[i][j]<<"   ";
        }
    cout<<endl<<endl;

    }
    cout<<"//////////////////////////////////////////"<<endl;
}

void prop_opr::changevalcord(int val,int cord_x,int cord_y) //cambiar el valor de una cordenada 
{
    if(cord_x >3 || cord_y>3)
    {
        cout<<"error cordenadas muy grandes para matrix"<<endl;
    }
    else
    {
        strucgam[cord_x][cord_y]=val;
        //showstruc();
    }
    
}

bool prop_opr::moviz()
{
 for (int i = 0; i < 4; i++)
 {
     algmoviz(0,i);
 }
 valregres=fillcord();
 showstruc();
 return valregres;
}

bool prop_opr::movder()
{
    for (int i = 0; i < 4; i++)
    {
        algmovd1(3,i);
    }
    valregres=fillcord();
    showstruc();
    return valregres;
}

bool prop_opr::slicedown()
{
    for (int i = 0; i < 4; i++)
    {
        algdown(3,i);
    }
    valregres=fillcord();
    showstruc();
    return valregres;
    
}

bool prop_opr::sliceup()
{
    for (int i = 0; i < 4; i++)
    {
        algmouup(0,i);
    }
    valregres=fillcord();
    showstruc();
    return valregres;
}

void prop_opr::algmov(int valinc,int val_y,bool valdif=false)//no se usa 
{
    if( valinc<=0 )
    {
        return;
    }
    if(strucgam[val_y][valinc]==0)
    {
        algmov(valinc-1,val_y,valdif);
    }
    if(strucgam[val_y][valinc]>0)
    {
        if(strucgam[val_y][valinc-1]==strucgam[val_y][valinc] || strucgam[val_y][valinc-1]==0 )
        {
            valger=(strucgam[val_y][valinc-1]>0)?true:false;
            strucgam[val_y][valinc-1]=strucgam[val_y][valinc-1]+strucgam[val_y][valinc];
            if(valger==true) 
            {score=score+strucgam[val_y][valinc-1];
            valger=false;}
            strucgam[val_y][valinc]=0;
           if(valinc-1>0) algmov(valinc-1,val_y,valdif);
        }
        if(strucgam[val_y][valinc-1]!=strucgam[val_y][valinc]) 
        {   bool verf=false;
            verfnum(verf,valinc,val_y,0);
            if( verf==true) 
            {algmov(valinc-1,val_y,false);
            algmov(valinc,val_y);}
            else
            {
                return;
            }
        }      
    }
}

//new
void prop_opr::algmovd1(int valinc,int val_y)
{
    if(valinc<1)
    {
        return ;
    }
    if (strucgam[val_y][valinc-1] == 0)
    {
        algmovd1(valinc-1,val_y);
    }
    if (strucgam[val_y][valinc-1]==strucgam[val_y][valinc] || (strucgam[val_y][valinc]==0 && strucgam[val_y][valinc-1]>0))
    {
        valger= (strucgam[val_y][valinc]>0)?true:false;
        strucgam[val_y][valinc]=strucgam[val_y][valinc-1]+strucgam[val_y][valinc];
        strucgam[val_y][valinc-1]=0;
        if (valger==true) score=score+strucgam[val_y][valinc];
        if (valger==false && strucgam[val_y][valinc]==strucgam[val_y][valinc+1] && strucgam[val_y][valinc+1] !=0 )
        {
            valger=false;
            //cout<<strucgam[val_y][valinc]<<" "<<strucgam[val_y][valinc+1]<<endl;
            algmovd1(valinc+1,val_y);
        }
        valger=false;
        algmovd1(valinc-1,val_y);
    }
    else
    {
        algmovd1(valinc-1,val_y);
    }  
}
///new
void prop_opr::algmouup(int valinc,int valx)
{
    if(valinc>2)
    {
        return ;
    }
    if(strucgam[valinc+1][valx]==0)
    {
        algmouup(valinc+1,valx);
    }
    if (strucgam[valinc+1][valx]==strucgam[valinc][valx] ||(strucgam[valinc][valx]==0 && strucgam[valinc+1][valx]>0))
    {
        valger=(strucgam[valinc][valx]>0)?true:false;
        strucgam[valinc][valx]=strucgam[valinc][valx]+strucgam[valinc+1][valx];
        if (valger==true) score=score+strucgam[valinc][valx];
        strucgam[valinc+1][valx]=0;
        if(strucgam[valinc][valx]==strucgam[valinc-1][valx] && strucgam[valinc-1][valx]!=0 && valinc+1==3)
        {
            valger=false;
            algmouup(valinc-1,valx);
        }
        valger=false;
        algmouup(valinc+1,valx);
    }
    else
    {
        algmouup(valinc+1,valx);
    }
    
}
//new
void prop_opr::algmoviz(int valinc,int val_y)
{
    if(valinc>2)
    {
        return;
    }
    if(strucgam[val_y][valinc+1]==0) algmoviz(valinc+1,val_y);

    if ( strucgam[val_y][valinc+1]==strucgam[val_y][valinc] || (strucgam[val_y][valinc] ==0 && strucgam[val_y][valinc+1] >0 ))
    {
        valger=( strucgam[val_y][valinc]>0)?true:false;
        valger1=(strucgam[val_y][valinc]>0)?true:false;
        strucgam[val_y][valinc]=strucgam[val_y][valinc]+strucgam[val_y][valinc+1];
        strucgam[val_y][valinc+1]=0;
        if (valger==true) score=score+strucgam[val_y][valinc];
        if(valger==false && strucgam[val_y][valinc] == strucgam[val_y][valinc-1] && strucgam[val_y][valinc]!=0 )
        {   
            valger=false;
            algmoviz(valinc-1,val_y);
        }

        valger=false;
        algmoviz(valinc+1,val_y);
    }
    else
    {
        algmoviz(valinc+1,val_y);
    }
    
}
//new
void prop_opr::algdown(int valinc,int valx)
{
    if(valinc<=0)
    {
        return;
    }
    if(strucgam[valinc-1][valx]==0 )
    {
        algdown(valinc-1,valx);
    }
    if((strucgam[valinc-1][valx]==strucgam[valinc][valx]) || (strucgam[valinc][valx]==0 && strucgam[valinc-1][valx]>0))
    {
        valger=(strucgam[valinc][valx]>0)?true:false;
        strucgam[valinc][valx]=strucgam[valinc-1][valx]+strucgam[valinc][valx];
        strucgam[valinc-1][valx]=0;
        if(valger==true) score=score+strucgam[valinc][valx];
        if(valger==false &&  strucgam[valinc][valx]== strucgam[valinc+1][valx] && strucgam[valinc][valx]!=0) algdown(valinc+1,valx);
        valger=false;
        algdown(valinc-1,valx);
    }
    else
    {
        algdown(valinc-1,valx);
    }
    
}

void prop_opr::verfnum(bool &verf ,int &num,int &val_y, int val_inc)
{
    int valant=3;
        for (int i = val_inc; i < num+1; i++)
    {
        if(strucgam[val_y][i]==0 )
        {
            verf=true;
        }
        if(strucgam[val_y][i]==valant)
        {
            verf=true;
        }
        valant=strucgam[val_y][i];
    }
}

//old
void prop_opr::moovdown(int valinc,int valx)// no se usa esta funcion
{
    if(valinc>=3)
    {
        return;
    }
    if(strucgam[valinc][valx]==0)
    {
        moovdown(valinc+1,valx);
    }
    else  
    {
        if(strucgam[valinc][valx]==strucgam[valinc+1][valx] || strucgam[valinc+1][valx]==0)
        {
            valger=(strucgam[valinc+1][valx]>0)?true:false;
            strucgam[valinc+1][valx]=strucgam[valinc+1][valx]+strucgam[valinc][valx];
            if(valger==true)
            {
                score=score+strucgam[valinc+1][valx];
                valger=false;
            }
            strucgam[valinc][valx]=0;
            moovdown(valinc+1,valx);
        }
        else
        {
        bool verf=false;
        int valf=3;
        orz_ver(verf,valinc,valf,valx);
        if( verf==true)
            {
                moovdown(valinc+1,valx);
                moovdown(valinc,valx);
            }
            else
            {
                return;
            }
            
        }  
    }   
}


//old
void prop_opr::moovup(int valinc,int valx)// no se usa esta funcion
{
    if(valinc <= 0)
    {
        return;
    }
    if(strucgam[valinc][valx]==0)
    {
        moovup(valinc-1,valx);
    }
    else  
    {
        if(strucgam[valinc][valx]==strucgam[valinc-1][valx] || strucgam[valinc-1][valx]==0)
        {
            valger=(strucgam[valinc-1][valx]>0)?true:false;
            strucgam[valinc-1][valx]=strucgam[valinc-1][valx]+strucgam[valinc][valx];
            if(valger==true)
            {
                score=score+strucgam[valinc-1][valx];
                valger=false;
            }
            strucgam[valinc][valx]=0;
            moovup(valinc-1,valx);
        }
        else
        {
        bool verf=false;
        int valf=0;
        orz_ver(verf,valf,valinc,valx);
        if(verf==true)
            {
                moovup(valinc+1,valx);
                moovup(valinc,valx);
            }
            else
            {
                return;
            }
            
        }  
    }   
}

void prop_opr::orz_ver(bool &verf, int &numic,int &valf,int &valx)// no se usa esta funcion
{
    int valant=3;
    for (int i = numic; i < valf; i++)
    {
        if(strucgam[i][valx]==0) 
        {verf=true;}
        if(strucgam[i][valx]==valant)
        {
            valf=true;
        }
        valant=strucgam[i][valx];
    }
    
}

/////////////////////////////////
prop_opr::~prop_opr()
{
}

void  prop_opr::gencord(int num_x,int num_y,int valf) //funcion recursiva para bsucar cierto valor y lo almacena en cordval
    {

        if(num_x >=2)
        {
            return;
        }
        if(num_y<4)
        {
            if(strucgam[num_x][num_y]==valf  )
            {
                cordval[numcord].cordx=num_x;
                cordval[numcord].cordy=num_y;
                numcord++;
            }
            if (strucgam[num_x+2][num_y]==valf)
            {
                cordval[numcord].cordx=num_x+2;
                cordval[numcord].cordy=num_y;
                numcord++;
            }
            if (num_y+1<4)
            {
                gencord(num_x,num_y+1,valf);
            }
            if (num_y+1>=4)
            {
                num_y=0;
                gencord(num_x+1,num_y,valf);
            }     
        }
    }

void prop_opr::showcord() //mostrar las cordenadas de la variable cordval
{
    cout<<numcord<<endl;
    for (int i = 0; i < numcord; i++)
    {
        cout<<i<<" x="<<cordval[i].cordx<<" y="<<cordval[i].cordy<<endl;
    }
    
}

void prop_opr::putval() //no se usa  
    {
        int val[2];
        if(numcord>2)
        { 
            for (int i = 0; i < 2; i++)
            {
                val[i]=numrand();
            }
            if (val[0]==val[1])
            {
                while (val[0]==val[1])
                {
                    val[1]=numrand();
                }  
            }
            cout<<"the cal is"<<val[0]<<"the val2 is "<<val[1]<<endl;
            changevalcord(2,cordval[val[0]].cordx,cordval[val[0]].cordy);
            changevalcord(2,cordval[val[1]].cordx,cordval[val[1]].cordy);

        }
        if(numcord==2)
        {

            changevalcord(2,cordval[val[0]].cordx,cordval[val[0]].cordy);
            changevalcord(2,cordval[val[1]].cordx,cordval[val[1]].cordy);
        }
        if (numcord<1)
        {
            changevalcord(2,cordval[0].cordx,cordval[0].cordy);
            gencord(0,0,2);
            if(numcord>0) 
            {
                val[0]=numrand();
                changevalcord(2,cordval[val[0]].cordx,cordval[val[0]].cordy);
            }

            else
            {
                cout<<"dont have space game over "<<endl;
                return;
            }
            
        }
        if(numcord==0)
        {
            gencord(0,0,2);
            if(numcord>2)
            { 
                for (int i = 0; i < 2; i++)
                {
                    val[i]=numrand();
                }
                if (val[0]==val[1])
                {
                    while (val[0]==val[1])
                    {
                        val[1]=numrand();
                    }  
                }
            }
            else
            {
                cout<<"the space over"<<endl;
            }
            
        }
    }

bool prop_opr::fillcord() //llena en dos cordenadas con un valor de 2 si no tiene espacio termina el juego  las lineas comentadas es por que antes generaba dos numeros 
{
    int num0=0,num2=0,varamcord[2];
    llamgencord(0);
    num0=numcord;
    llamgencord(2);
    num2=numcord;
    if(num0>=1)
    {
        cout<<"in to val case  0"<<endl;
        llamgencord(0);
        varamcord[0]=genaleatnum();
        // cout<<"num aleat 1 "<<genaleatnum()<<endl;
        // varamcord[1]=genaleatnum();
        // cout<<"num aleat 2 "<<genaleatnum()<<endl;
        // while(varamcord[0]==varamcord[1])
        // {
        //     varamcord[1]=genaleatnum();
        // }
        // cout<<"num aleat 2 "<<genaleatnum()<<endl;
        // cout<<"finallistcord val1 "<<varamcord[0]<<" val2= " <<varamcord[1] <<endl;
        changevalcord(2,cordval[varamcord[0]].cordx,cordval[varamcord[0]].cordy);
        // changevalcord(2,cordval[varamcord[1]].cordx,cordval[varamcord[1]].cordy);
        return true;
    }
    else if (num2>=1)
    {
        cout<<"in to val case 2 and 0"<<endl;
        // llamgencord(0);
        // changevalcord(2,cordval[0].cordx,cordval[0].cordy);
        llamgencord(2);
        changevalcord(4,cordval[0].cordx,cordval[0].cordy);
        return true;
    }
    // else if (num2>2)
    // {
    //     llamgencord(2);
    //     cout<<"in to val case 2"<<endl;
    //     varamcord[0]=genaleatnum();
    //     varamcord[1]=genaleatnum();
    //     while(varamcord[0]==varamcord[1])
    //     {
    //         varamcord[1]=numrand();
    //     }
    //     changevalcord(4,cordval[varamcord[0]].cordx,cordval[varamcord[0]].cordy);
    //     changevalcord(4,cordval[varamcord[1]].cordx,cordval[varamcord[1]].cordy);   
    // }
    else if(num0==0 && num2==0)
    {
        cout<<"game over"<<endl;
        return false;
    }    
}

void prop_opr::fillallcord(int valref) //llenar toda la matris de un valor enviado 
{
    for (int i = 0; i < numcord; i++)
    {
        changevalcord(valref,cordval[i].cordx,cordval[i].cordy);
    }
    
}

void prop_opr::llamgencord(int valf)
{
    numcord=0;
    gencord(0,0,valf);
}

int prop_opr::genaleatnum() //genera nunero aleatorio 
{
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    
    int valt=0,vall2=0,vall3=0, valf=0;
    float valrand=0,valand=0,valexp=0,val5f=0,numreg=numcord;
    double val4=0;
    valt= (time *1000);
    valrand = (valt%100);
    valand = (valrand/100);
    valexp=exp(valand);
    vall2=valexp*10000;
    vall3=vall2%1000;
    val4=int((numreg/1000)*vall3);
    valf=int(val4);
    return int(valf);
}

int prop_opr::numrand() //numero random
{
    int numra;
    srand(time(NULL));
    numra = rand() % numcord;
    return numra;
}