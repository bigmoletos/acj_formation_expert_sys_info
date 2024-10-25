#include <iostream>
using namespace std;

int main(){
// Boucle de 0 à 10 avec un pas de 2
for (int k = 0; k <= 10; k += 2)
{
    int sum = 0;
    // Boucle de i = k à 2*k avec un pas de 1
    for (int i = k; i <= 2 * k; i += 1)
        sum += i;

    cout << k << " -> " << sum << "\n";
}
return 0;
}