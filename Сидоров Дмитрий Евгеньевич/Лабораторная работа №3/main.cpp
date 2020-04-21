#include <iostream>

#define n 10

int *v;
bool *u;

int hsh (int k){
return k%n;
}

void add (int k) {
int ke=hsh(k);

while (u[ke] and v[ke]!=k )
ke=(ke+1)%n;
if(!u[ke]) {
u[ke]=true;
v[ke]=k;
}
}

using namespace std;

int main()
{
v = new int [n];
u = new bool [n];

for(int i=0;i<n;i++) { u[i]=false; v[i]=0; };

add(5);
add(15);
add(7);
add(42);
add(32);

for(int i=0;i<n;i++) cout << v[i] << " ";

return 0;
}


