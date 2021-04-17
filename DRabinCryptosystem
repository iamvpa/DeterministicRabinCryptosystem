#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll p,q; //private key pair(p,q) of the form 3 mod 4

ll n = p * q; 
 
ll countDigit(long long n)
{
    ll count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}     
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
   
    cout<<"fail"<<endl;
    
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
   cout<<"Enter private keys p and q::"<<endl;
   cin>>p>>q;
   n=p*q;
   ll pt;
   cout<<"Enter number to be encrypted"<<endl;
   cin>>pt;
   if(pt>=(n-111)/1000)
   {
       cout<<"Invalid choice"<<endl;
       return 0;
   }
   cout << "Encrypted number: ";
   e.push_back(encrypter(tehk(pt), n));
   cout << e[0]<<endl;
   d.push_back(decrypter(e[0], p, q));
    cout << "Decrypted number: ";
    cout << d[0]/1000<<endl;
    cout << endl;

    
  
    return 0;
}
