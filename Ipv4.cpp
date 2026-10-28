#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d;

    cout << "Enter IPv4 address: ";
    cin >> a >> b >> c >> d;

    // Check whether IP is valid
    if (a < 0 || a > 255 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255)
    {
        cout << "Invalid IPv4 Address";
    }
    else
    {
        cout << "Valid IPv4 Address" << endl;

        // Class A
        if (a >= 1 && a <= 126)
        {
            cout << "Class: A" << endl;
            cout << "Network ID: " << a << ".0.0.0" << endl;
            cout << "Host ID: 0." << b << "." << c << "." << d;
        }

        // Class B
        else if (a >= 128 && a <= 191)
        {
            cout << "Class: B" << endl;
            cout << "Network ID: " << a << "." << b << ".0.0" << endl;
            cout << "Host ID: 0.0." << c << "." << d;
        }

        // Class C
        else if (a >= 192 && a <= 223)
        {
            cout << "Class: C" << endl;
            cout << "Network ID: " << a << "." << b << "." << c << ".0" << endl;
            cout << "Host ID: 0.0.0." << d;
        }

        // Class D
        else if (a >= 224 && a <= 239)
        {
            cout << "Class: D" << endl;
            cout << "Multicast Address";
        }

        // Class E
        else if (a >= 240 && a <= 255)
        {
            cout << "Class: E" << endl;
            cout << "Experimental Address";
        }

        else
        {
            cout << "Invalid/Reserved Address";
        }
    }

    return 0;
}