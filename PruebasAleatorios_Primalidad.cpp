#include <iostream>
#include <NTL/ZZ.h>
#include<vector>
#include <sstream>
using namespace std;
using namespace NTL;
#include <sys/time.h>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;


ZZ mod(ZZ a, ZZ b);
ZZ modular_exponentation( ZZ a, ZZ e, ZZ n );
bool PRIMECHECK(ZZ n, ZZ k=conv<ZZ>(10));
vector<ZZ>fact_2(ZZ n);
ZZ newTime();
string int_a_string(ZZ conversion);
ZZ string_a_int(string conversion);
ZZ pot(ZZ base, ZZ exponente);
ZZ middleSquareNumberRan(ZZ number, ZZ intervalo_mayor, ZZ intervalo_menor);
ZZ RANDBIGINTEGER(ZZ number, ZZ bits);

int main(){
    for(int i = 0; i < 20; i++){
        ZZ a (RANDBIGINTEGER(newTime(),ZZ(16)));
        cout<<i+1<<": "<<endl<<a<<endl<<"Primo?: "<<PRIMECHECK(a)<<endl;
    }


}

bool PRIMECHECK(ZZ n, ZZ k){
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

        //a = RandomBnd(n-2-2)+2;
        ZZ aux (newTime());
        //cout<<"aux: "<<aux<<endl<<endl;
        a = middleSquareNumberRan(aux,n-2,ZZ(2));


            //cout<<"a: "<<a<<endl;
        x = modular_exponentation(a,d,n);
            //cout<<"x: "<<x<<endl;
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

ZZ newTime()
{
    ZZ x;
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    x = ZZ(millisec_since_epoch);

    x = string_a_int(int_a_string(x).substr(6,9));

    x = pot(x+5,ZZ(3));
    return x;
}

string int_a_string(ZZ conversion){
  ostringstream convertido;
  convertido << conversion;
  return convertido.str();
}

ZZ string_a_int(string conversion){
  istringstream convertido(conversion);
  ZZ entero;
  convertido >> entero;
  return entero;
}

ZZ pot(ZZ base, ZZ exponente) {
    if (exponente == 0) return ZZ(1);
    ZZ x = pot(base, exponente/2);
    if (mod(exponente,ZZ(2))==0) return x*x;
    return x*x*base;
}

ZZ middleSquareNumberRan(ZZ number, ZZ intervalo_mayor, ZZ intervalo_menor) {
   //ZZ intervalo_mayor = pot(ZZ(2),bits)-1;
   //ZZ intervalo_menor = pot(ZZ(2),bits)/2;

   ZZ sqn = number * number, next_number = number;
   while(next_number < intervalo_mayor)
   {
     int tam1  = int_a_string(next_number).length();
     int t = (tam1 / 2);
     ZZ limite = pot(ZZ(10),conv<ZZ>(t));
      sqn =  next_number / limite;
      next_number = sqn * sqn * sqn;

   }
   next_number = mod(next_number, intervalo_mayor);
   if(next_number < intervalo_menor)
   {
     next_number += intervalo_menor;
   }

   return next_number;
}

ZZ RANDBIGINTEGER(ZZ number, ZZ bits) {
   ZZ intervalo_mayor = pot(ZZ(2),bits)-1;
   ZZ intervalo_menor = pot(ZZ(2),bits)/2;

   ZZ sqn = number * number, next_number = number;
   while(next_number < intervalo_mayor)
   {
     int tam1  = int_a_string(next_number).length();
     int t = (tam1 / 2);
     ZZ limite = pot(ZZ(10),conv<ZZ>(t));
      sqn =  next_number / limite;
      next_number = sqn * sqn * sqn;

   }
   next_number = mod(next_number, intervalo_mayor);
   if(next_number < intervalo_menor)
   {
     next_number += intervalo_menor;
   }

   return next_number;
}
