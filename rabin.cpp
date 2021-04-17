#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll p = 7919, q =7907 ; //private key pair(p,q) of the form 3 mod 4

ll n = p * q; 
ll failcnt=0;       //public key n
//n=62615533 /   
ll countDigit(long long n)
{
    ll count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}      //....1    .....2
ll countSetBits(ll num)
    {
        ll count = 0;
        while (num) {
            num &= (num - 1);
            count++;
        }
        return count;
    }

    bool isValid(ll num)
    {
        if(num<1000)
        return false;
        ll lstd=num%10;
        ll slstd=(num%100)/10;
        ll tlstd=(num%1000)/100;
        //cout<<lstd<<" "<<slstd<<endl;
        
        ll als,asld,atld;
        num=num/1000;
        if(num%2==0)
        {
            atld=1;
        }
        else
        atld=0;
        if(countSetBits(num)%2==0)
        asld=1;
        else
        asld=0;
        if(countDigit(num)%2==0)
        als=1;
        else
        als=0;
        //cout<<als<<" "<<asld<<endl;
                if(als==lstd && asld==slstd && atld==tlstd)
        return true;
        else
        return false;

    }
ll encrypter(ll m, ll n)
{
    ll c = (m * m)%n;    // c = (m^2) mod n
    return c;
}

ll mod(ll k, ll b, ll m) //chinese remainder theorem implementation
{
    ll i=0;
    ll a=1;
    vector<int> t;
    while(k>0){
        t.push_back(k%2);
        k=(k-t[i])/2;
        i++;
    }
    for(int j=0; j<i; j++){
        if(t[j]==1){
            a=(a*b)%m;
            b=(b*b)%m;
        } else{
            b=(b*b)%m;
        }
    }
    return a;
}

ll modulo (ll a, ll b)
{
    return a >= 0 ? a % b : ( b - abs ( a%b ) ) % b;
}

vector<ll> Extended_Euclid(ll a, ll b)
{
    if (b>a) {
        ll temp=a; a=b; b=temp;
    }
    ll x=0;
    ll y=1;
    ll lastx=1;
    ll lasty=0;
    while (b!=0) {
        ll q= a/b;
        ll temp1= a%b;
        a=b;
        b=temp1;
        ll temp2 = x;
        x=lastx-q*x;
        lastx = temp2;
        ll temp3 = y;
        y = lasty-q*y;
        lasty=temp3;
    }
    vector<ll>arr(3);
    arr[0] = lastx;
    arr[1] = lasty;
    arr[2] = 1;
    return arr;
}

ll decrypter(ll c, ll p, ll q)
{
    ll mp = mod((p+1)/4, c, p);
    ll mq = mod((q+1)/4, c, q);

    vector<ll> arr = Extended_Euclid(p, q);
    ll rootp = arr[0]*p*mq;
    ll rootq = arr[1]*q*mp;
    double r = modulo((rootp+rootq), n);
      ll s = modulo((rootp-rootq), n);
     ll negative_r = n - r;
      ll negative_s = n - s;
      //cout<<r<<" "<<negative_r<<" "<<s<<" "<<negative_s<<endl;
      bool r1,s1,r2,s2;
      r1=isValid(r);
      r2=isValid(negative_r);
      s1=isValid(s);
      s2=isValid(negative_s);
      ll vldc=0;
      ll ans=0;
      if(r1)
      {
          ans=r;
          vldc++;
      }
      if(r2)
      {
          ans=negative_r;
          vldc++;
      }
      if(s1)
      {
          ans=s;
          vldc++;

      }
      if(s2)
      {
          ans=negative_s;
          vldc++;
      }

if(vldc==1)
return ans;
else{
    failcnt++;
    cout<<"fail"<<failcnt<<endl;
    //cout<<r1%100/10<<endl;
   // cout<<countSetBits(r1)<<endl;
    //cout<<r<<" "<<r1<<" "<<negative_r<<" "<<r2<<" "<<s<<" "<<s1<<" "<<negative_s<<" "<<s2<<endl;
    }

return -1;
}
ll tehk(ll num)
{
    ll num1;
    ll a=0,b=0;
    if(num%2==0)
    {
        num1=num*10+1;
        a=1;
    }
    else
    {
        num1=num*10;
    }
   // if(num==5)
   // cout<<countSetBits(num)<<" here"<<endl;
    if(countSetBits(num)%2==0)
    {
        
        num1=num1*10+1;
        b=1;
    }
    else
    num1=num1*10;
    if(countDigit(num)%2==0)
    num1=num1*10+1;
    else
    num1=num1*10;
    return num1;
}
int main()
{
    vector<ll>e; //vector to store the encrypted message
    vector<ll>d; //vector to store the decrypted message
    string message ="C";
   // cout << "Plain text: " << message << endl;
    ll len = strlen(message.c_str());
    for(int i=0;i<100000;i++)
    {
e.push_back(encrypter(tehk(i+1), n));
        //cout << e[i]<<endl;
    }
   // e.push_back(encrypter(tehk(5), n));
    //cout << "Encrypted text: ";
    //for(int i = 0; i < len; i++)
    //{   if(i==0)
        //e.push_back(encrypter(tehk(10), n));
       // cout << e[0];
   // }
   //number<(n-11)/100
   //number_even_even1's
   //check1-last 3 digits 1,0 ke alava---cut
   //if i am gitting a definite answer
   //loop 1-62615533(6*10^8)
   //10111--decrypt-4 possible roots-check-one final answer--flg=true

//132---
//132111
    cout << endl;

    for(int i = 0; i < 100000; i++)
    {
        d.push_back(decrypter(e[i], p, q));
        //if(d[i]==-1)
        cout << d[i]<<endl;
   }
    //cout << "Decrypted text: ";
   // for(int i=0;i<d.size();i++)
     // cout << d[i];
cout<<failcnt<<endl;
    cout << endl;
    return 0;
}
