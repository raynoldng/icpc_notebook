#include <iostream>
#include <iomanip>

using namespace std;

#define db(x) cerr << #x << "=" << x << endl
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << endl
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << endl

#define LSOne(S) (S & (-S))

// remove duplicated from vector
#define UNIQUE(x) x.erase(unique(x.begin(), x.end()), x.end())

// Generate all set of n elements
unsigned next_set_n(unsigned x) {
    unsigned smallest, ripple, new_smallest, ones;
    if(x==0) return 0;
    smallest = (x & -x);
    ripple = x + smallest;
    new_smallest = (ripple & -ripple);
    ones = ((new_smallest/smallest) >> 1 ) - 1;
    return ripple | ones;
}


int main()
{
    // Ouput a specific number of digits past the decimal point,
    // in this case 5    
    cout.setf(ios::fixed); cout << setprecision(5);
    cout << 100.0/7.0 << endl;
    cout.unsetf(ios::fixed);
    
    // Output the decimal point and trailing zeros
    cout.setf(ios::showpoint);
    cout << 100.0 << endl;
    cout.unsetf(ios::showpoint);
    
    // Output a '+' before positive values
    cout.setf(ios::showpos);
    cout << 100 << " " << -100 << endl;
    cout.unsetf(ios::showpos);
    
    // Output numerical values in hexadecimal
    cout << hex << 100 << " " << 1000 << " " << 10000 << dec << endl;

    // Convert int to binary string
    cout << bitset<32>(val).to_string() << endl;

}
