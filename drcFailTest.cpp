/*
This is a modified version of the code which can be found here::https://www.codespeedy.com/rabin-cryptosystem-implementation-in-cpp/
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll p = 7919, q =7907 ; //private key pair(p,q) of the form 3 mod 4

ll n = p * q; 
ll failcnt=0;       //fail count
//n=62615533 public key  
ll countDigit(long long n) //count the number of digits in a number
{
    ll count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}     
ll countSetBits(ll num) // count the number of set bits in the binary representation of a number
    {
        ll count = 0;
        while (num) {
            num &= (num - 1);
            count++;
        }
        return count;
    }

    bool isValid(ll num) //to check whether a number is valid
    {
        /*
        A number is valid if:
        last digit: if 1 then number/1000 should have even number of digits else if it is 0 then it should have odd number of digits
        second last digit: 1 if number/1000 should have even number of set bits in binary representation else odd
        third last digit: 1 if number/1000 should be even else odd
        Four possible plain text are passed here from decrypter ..the one satisfying these conditions are valid. If more than one satisfy these conditions then we have failed.
        Taking example from line 199
        number=3727011
        last digit=1 and the number/1000 has 4 digits hence ok
        second last digit=1 and number/1000(3727) has even number of set bits hence ok
        third last digit=0 and 3727 is odd hence ok
        */
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
    //Four possible plain text are r,s,negativbe_r,negative_s
      //cout<<r<<" "<<negative_r<<" "<<s<<" "<<negative_s<<endl;
      bool r1,s1,r2,s2;
      r1=isValid(r);
      r2=isValid(negative_r);
      s1=isValid(s);
      s2=isValid(negative_s);
      ll vldc=0;// how many of the four possible are valid:: if more than one then we have failed to determine actual text
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
ll tehk(ll num) // to convert a number into our system
{
    /*
    if number is even we concatenate 1 to it else 0
    if number has even number of set bits then we concatenate 1 to it else 0
    if number has even number of digits then we concatinate 1 to it else 0
    ex:
    number =3727
    since 3727 is odd => 37270
    binary representation of 3727 is 111010001111 it has even number of set bits =>372701
    number of digits in 3727 is 4 which is even => 3727011
    and then we pass this number into encrypter
    */
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
   
    for(int i=0;i<100000;i++)
    {
e.push_back(encrypter(tehk(i+1), n));// encrypting numbers from 1 to 100001
        //cout << e[i]<<endl; //uncomment to print encrypted number
    }
  
    cout << endl;

    for(int i = 0; i < 100000; i++)
    {
        d.push_back(decrypter(e[i], p, q));
        
        cout << d[i]<<endl; //printing decrypted number
   }
   
cout<<failcnt<<endl; //number of times it failed to determine actual text from the four possible roots
    cout << endl;
    return 0;
}
