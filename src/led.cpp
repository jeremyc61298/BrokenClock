#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

using std::ifstream;
using std::ofstream;
using std::endl;
using std::bitset;
using std::string;
using std::cout;
using std::stringstream;
using std::vector;
using std::pair;
using std::set;

// Global Variable for the BitSet size
const size_t CLOCKBITS = 8;

void initDigitBitSets(vector<bitset<CLOCKBITS>> &clockDigits)
{
    clockDigits[0] = bitset<CLOCKBITS> {string("00000000")};
    clockDigits[1] = bitset<CLOCKBITS> {string("01001000")};
    clockDigits[2] = bitset<CLOCKBITS> {string("10111010")};
    clockDigits[3] = bitset<CLOCKBITS> {string("11011010")};
    clockDigits[4] = bitset<CLOCKBITS> {string("01011100")};
    clockDigits[5] = bitset<CLOCKBITS> {string("11010110")};
    clockDigits[6] = bitset<CLOCKBITS> {string("11110110")};
    clockDigits[7] = bitset<CLOCKBITS> {string("01001010")};
    clockDigits[8] = bitset<CLOCKBITS> {string("11111111")};
    clockDigits[9] = bitset<CLOCKBITS> {string("01011110")};
}

void breakClock(bitset<CLOCKBITS> &brokenClock, stringstream &s)
{
    int brokenDigit;
    s >> brokenDigit;

    while(brokenDigit != 0)
    {
        brokenClock.reset(brokenDigit);
        s >> brokenDigit;
    }
}

void findMatchingNumbers(set<pair<int, int>> &matchingNumbers,
                        vector<bitset<CLOCKBITS>> &clockDigits,
                        bitset<CLOCKBITS> brokenClock
                        )
{
    // Use iterators instead
    for (int i = 0; i < clockDigits.size(); i++)
    {
        bitset<CLOCKBITS> b = clockDigits[i] & brokenClock;
    }
}

int main()
{
    ifstream fin("led.in");
    if (!fin)
    {
        cout << "Error opening input file" << endl;
        return -1;
    }

    ofstream fout("led.out");
    vector<bitset<CLOCKBITS>> clockDigits(10);
    bitset<CLOCKBITS> workingClock(string("11111110"));
    bitset<CLOCKBITS> brokenClock = workingClock;

    initDigitBitSets(clockDigits);

    string line;
    getline(fin, line);

    while (line != "0")
    {
        stringstream s;
        s << line;

        breakClock(brokenClock, s);
        set<pair<int, int>> matchingNumbers;
        findMatchingNumbers(matchingNumbers, clockDigits, brokenClock);


        getline(fin, line);
    }
    return 0;
}