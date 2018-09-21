#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::bitset;
using std::string;
using std::cout;

int main()
{
    ifstream fin("led.in");
    if (!fin)
    {
        cout << "Error opening input file" << endl;
        return -1;
    }

    ofstream fout("led.out");


    return 0;
}