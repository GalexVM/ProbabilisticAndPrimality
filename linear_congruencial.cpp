#include<iostream>
#include<NTL/ZZ.h>
#include<vector>
#include<bits/stdc++.h>
#include<windows.h>
#include<winuser.h>
#include<stdlib.h>
#include<fstream>

using namespace std;
using namespace NTL;


ZZ mod(ZZ a, ZZ b);
ZZ modular_exponentation( ZZ a, ZZ e, ZZ n );
bool MillerRabinTest(ZZ n, ZZ k);
vector<ZZ>fact_2(ZZ n);



ZZ linear(ZZ seed, ZZ a, ZZ b, ZZ m){

ZZ x0;

string num;

x0 = mod((a*(seed)+b),m);

ostringstream numero;

for (int i=0; i < 3; i++){
   x0 = mod(((a*seed)+b),m);
   seed=x0;
   numero << x0;
    num += numero.str();

}



istringstream salida(num);
ZZ final_ ;
salida>>final_;

return final_;

}

ZZ RANDBIGINTEGER( int a){

int x,y;

for (int i=0; i< 4; i++){
    POINT mouse;

    GetCursorPos(&mouse);

    x= mouse.x;
    y=mouse.y;

}

ZZ seed;



if (a == 16){

seed = conv<ZZ> (x);

ZZ a=conv<ZZ>("3"); //22
ZZ m=conv<ZZ>("5"); //22
ZZ b=conv<ZZ>(y);
return  (linear(seed,a,b,m)/10);
}



if (a == 128){

seed = conv<ZZ> (x);

ZZ a=conv<ZZ>("55"); //22
ZZ m=conv<ZZ>("11111111111111111111111111"); //22
ZZ b=conv<ZZ>(y);

cout << x << "; " << y << endl;
return  linear(seed,a,b,m);
}



if (a == 512){

seed = conv<ZZ> (x);

ZZ a=conv<ZZ>("12232639213"); //22
ZZ m=conv<ZZ>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"); //22
ZZ b=conv<ZZ>(y);

return  linear(seed,a,b,m);
}



if (a == 1024){
seed = conv<ZZ> (x);
ZZ a=conv<ZZ>("122326392656236150795712287871"); //22
ZZ m=conv<ZZ>("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
ZZ b=conv<ZZ>(y);
return  linear(seed,a,b,m);
}



if (a == 2048){
seed = conv<ZZ> (x);
ZZ a=conv<ZZ>("12232639265623615079571223263926562361507957"); //22
ZZ m=conv<ZZ>("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
ZZ b=conv<ZZ>(y);
return linear(seed,a,b,m);
}


}


bool PRIMECHECK(ZZ n, ZZ k = conv<ZZ> ("10")){
   bool continueFor=false;
    //1. Write n as 2^r*d + 1; d odd; factoring out of n-1.
    ZZ r(0);
    ZZ d(1);
    vector<ZZ>facts = fact_2(ZZ(n-1));
    r = facts[0];
    d = facts[1];

        //cout<<"r: "<<r<<" d: "<<d<<endl;
    //2. WitnessLoop.
    ZZ a,x;

    for(int i = 0; i < k; i++){//Repeat k times

        a = RandomBnd(n-2-2)+2;

            //cout<<"a: "<<a<<endl;
        x = modular_exponentation(a,d,n);
        if(x == 1 || x == n - 1)
            continue;
        for(int i = 0; i < n-1; i++){//repeat n-1 times
            x = mod(x*x,n);
            if(x == n-1)
                continueFor=true;
                break;
        }
        if(continueFor==true)continue;
        return false;


    }
    return true;
}


vector<ZZ>fact_2(ZZ n){
    vector<ZZ>facts;
    ZZ a (0);
    while(mod(n,ZZ(2))==0){
        n = n/2;
        a++;
    }
    facts.push_back(a);
    facts.push_back(n);
    return facts;
}

ZZ mod(ZZ a, ZZ b){
	ZZ q= a/b;
	ZZ	r= a- (q*b);
	if(a<ZZ(0)){
		ZZ ar=r;
	    r= b+ar;
	}
	return r;
}

ZZ modular_exponentation( ZZ a, ZZ e, ZZ n ) {
    ZZ result (1);
    while( e != ZZ(0)) {
        if( mod(e,ZZ(2)) == ZZ(1))
            result  = mod(result*a,n);
        e >>= 1;
        a = mod(a*a,n);
    }
    return result;
}

int main(){



ZZ a(RANDBIGINTEGER(1024));
//cout << a << endl << endl;



//cout << PRIMECHECK(a);

}
