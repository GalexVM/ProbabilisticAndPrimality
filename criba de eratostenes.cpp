#include <NTL/ZZ.h>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;
using namespace NTL;

ZZ mod(ZZ a, ZZ b){
	ZZ q= a/b;
	ZZ	r= a- (q*b);
	if(a<ZZ(0)){
		ZZ ar=r;
	    r= b+ar;
	}
	return r;
}

/**************************************************************************\

                              ​PRIME

\**************************************************************************/
bool test_primalidad100(ZZ n){
    if (n==ZZ(1)or n==ZZ(0) ) return 0;
	ZZ lista[4]={ZZ(2),ZZ(3),ZZ(5),ZZ(7)};
	for (ZZ *i=lista; i<lista+4; i++){
	    if (mod(n,*i )==ZZ(0) and n!=*i ) {return 0;	}
	}
	return 1;
}

bool prime(ZZ n){
	ZZ n2= SqrRoot (n);
	for (ZZ i=ZZ(0); i<n2;i++ ){
		if (i<=ZZ(100) and test_primalidad100(i)) {
            if (mod(n,i)==ZZ(0)) return 0;
        }
        else if(i>ZZ(100) and prime(i) and mod(n,i)==ZZ(0)) return 0;
	}
	return 1;
}

/**************************************************************************\

                              ​Criba de eratostenes

\**************************************************************************/

ZZ mod(ZZ a, ZZ b);
ZZ modular_exponentation( ZZ a, ZZ n, ZZ m );
bool MillerRabinTest(ZZ n, ZZ k);
vector<ZZ>fact(ZZ n);

bool MillerRabinTest(ZZ n, ZZ k){
   bool continueFor=false;
    //1. Write n as 2^r*d + 1; d odd; factoring out of n-1.
    ZZ r(0);
    ZZ d(1);
    vector<ZZ>facts = fact(ZZ(n-1));
    r = facts[0];
    d = facts[1];

    //2. WitnessLoop.
    ZZ a,x;

    for(int i = 0; i < k; i++){//Repeat k times

        a = RandomBnd(n-2-2)+2;

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

vector<ZZ>fact(ZZ n){
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

ZZ modular_exponentation( ZZ a, ZZ n, ZZ m ) {
    ZZ result (1);

    while( n != ZZ(0)) {

        if( mod(n,ZZ(2)) == ZZ(1))
            result  = mod(result*a,m);
        n >>= 1;
        //cout<<n<<endl;
        a = mod(a*a,m);
    }
    return result;
}


class nodo{
public:
    ZZ key, val ;
    nodo *next ;
    nodo (ZZ k, ZZ v, nodo *n=nullptr ) : key (k), val(v), next (n) {}
/*
    nodo (int RSA){ //criba
        nodo *h;
        ZZ pot=power2_ZZ(RSA);
        ZZ max= pot-1;

        for ( ZZ min=pot/2 ;min<= max; min++){
            if ( (min<=ZZ(100) and test_primalidad100(min) ) or (min>ZZ(100) and prime(min) ) ) {
                cout << min <<endl;
                if ( !h->next) h->next = new nodo (ZZ(1), min);
                else  h->add(h,min);
                h->print_val(h);
            }
        }
    }
*/
    bool find_key (nodo* head, ZZ k, nodo *& pos){
        pos = nullptr;
        nodo *t= head->next;
        for ( ; t and t->key < k ;pos= t, t= t->next );
        if(t and t->key == k)  return 1;
        else return 0;
    }

    void add(nodo* head,ZZ v){
        nodo *pos = nullptr;
        nodo *t= head->next;
        for ( ; t ; pos= t, t= t->next );
        pos->next = new nodo( (pos->key)+1, v);
    }


    ZZ valor( nodo* head,ZZ k){ //devuelve el valor usando la key (indice del vector)
        nodo *pos = nullptr;
        nodo *t= head->next;
        for ( ; t and t->key < k  ; pos= t, t= t->next );
        if(t and t->key == k)  return t->val;
        else return ZZ(0);
    }

    ZZ size(nodo* head){
        nodo *pos = nullptr;
        nodo *t= head->next;
        for ( ; t ; pos= t, t= t->next );
        return pos->key;
    }


    void print_val(nodo* head){
        cout <<"head:" << head->next <<endl;
        for (nodo* temp = head->next; temp ; temp = temp->next){
        cout <<"key:" << temp->key <<endl;
        cout <<"val:" << temp->val <<endl;
        cout <<"next:" << temp->next <<endl;
        cout <<"........................ "<<endl;
       }
    }

    ~nodo(){
        cout << "delete"<<endl;
    }

};

int main(){

    //nodo *HEAD(5);
   // HEAD->print_val(HEAD );

    int RSA=64;
        ZZ pot=power2_ZZ(RSA);
        ZZ max= pot-1;

        nodo *h= new nodo (ZZ(0), ZZ(0));
        nodo *t= h;
        cout <<" rango = [" << pot/2<<", "<<pot-1<<" ]"<<endl;
        cout <<"Ini for: "<<endl;
        for ( ZZ min=pot/2 ;min<= max; min++){
            //if ( (min<=ZZ(100) and test_primalidad100(min) ) or (min>ZZ(100) and prime(min) ) ) {
            if ( MillerRabinTest(conv<ZZ>(min),ZZ(10))){
                cout << "key: "<<t->key<<endl;
                cout << "val: "<<t->val<<endl;
                cout <<"........................ "<<endl;
                t->next = new nodo( (t->key)+1, min);
                t= t->next;
            }
        }
        //h->print_val(h);
/*
    void add(nodo* head,ZZ v){
        nodo *pos = nullptr;
        nodo *t= head->next;
        for ( ; t ; pos= t, t= t->next );
        pos->next = new nodo( (pos->key)+1, v);
    }

      nodo *h;
    h->next= new nodo (ZZ(1), ZZ(2));
    h->add(h,ZZ(11));
    h->add(h,ZZ(13));
    h->add(h,ZZ(19));


    h->print_val(h);
cout << "valor: "<< h->valor(h,ZZ(1))<<endl;
cout << "valor: "<< h->valor(h,ZZ(2))<<endl;
cout << "valor: "<< h->valor(h,ZZ(3))<<endl;
cout << "valor: "<< h->valor(h,ZZ(4))<<endl;
cout << "valor: "<< h->valor(h,ZZ(5))<<endl;
cout << "size: "<< h->size(h)<<endl;


*/
}
