// ------------------------------------------------------------------
// led.cpp
// Jeremy Campbell
// This program will determine if, given some broken led components,
// any digits will be indistinguishable from one another
// ------------------------------------------------------------------

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
using std::set;

// Global Variable for the BitSet size
const size_t CLOCKBITS = 8;

void initDigitBitSets(vector<bitset<CLOCKBITS>> &clockDigits)
{
    clockDigits[0] = bitset<CLOCKBITS> (string("11101110"));
    clockDigits[1] = bitset<CLOCKBITS> (string("01001000"));
    clockDigits[2] = bitset<CLOCKBITS> (string("10111010"));
    clockDigits[3] = bitset<CLOCKBITS> (string("11011010"));
    clockDigits[4] = bitset<CLOCKBITS> (string("01011100"));
    clockDigits[5] = bitset<CLOCKBITS> (string("11010110"));
    clockDigits[6] = bitset<CLOCKBITS> (string("11110110"));
    clockDigits[7] = bitset<CLOCKBITS> (string("01001010"));
    clockDigits[8] = bitset<CLOCKBITS> (string("11111111"));
    clockDigits[9] = bitset<CLOCKBITS> (string("01011110"));
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

void buildSetEntry(set<int> &buildingSet, int i, int j)
{
    // Ensure that they will always display the smaller number first,
    // so there are no redundant entries
        if (i < j)
        {
            buildingSet.insert(i);
            buildingSet.insert(j);
        }
        else
        {
            buildingSet.insert(j);
            buildingSet.insert(i);
        }
}

void findMatchingNumbers(set<set<int>> &matchingNumbers,
                        vector<bitset<CLOCKBITS>> &clockDigits,
                        bitset<CLOCKBITS> brokenClock
                        )
{
    set<int> buildingSet;
    // Use iterators instead
    for (int i = 0; i < clockDigits.size(); i++)
    {
        bitset<CLOCKBITS> a = clockDigits[i] & brokenClock;
        for (int j = 0; j < clockDigits.size(); j++)
        {
            bitset<CLOCKBITS> b = clockDigits[j] & brokenClock;
            if (a == b && j != i)
            {
                buildSetEntry(buildingSet, i, j);
            }
        }
        if (buildingSet.size() != 0)
        {
            matchingNumbers.insert(buildingSet);
            buildingSet.clear();
        }
    }
}

void printMatchingNumbers(const set<set<int>> &matchingNumbers,
                        ofstream& fout,
                        string line)
{
    string noTrailZero = line.substr(0, line.find(" 0"));
    fout << "Case <";

    // Print the numbers of the broken bits that were read in
    auto endOfString = noTrailZero.end();
    for(auto it = noTrailZero.begin(); it != noTrailZero.end(); it++)
    {
        if (*it != ' ')
        {
            fout << *it;
            if (it != endOfString - 1)
            {
                fout << ",";
            }
        }
    }

    fout << ">:";

    // Print out all the matching sets
    for (set<int> singleSet : matchingNumbers)
    {
        fout << " {";
        auto end = --singleSet.end();
        for (auto it = singleSet.begin(); it != singleSet.end(); it++)
        {
            fout << *it;
            if (it != end)
                fout << ",";
        }

        fout << "}";
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
        set<set<int>> matchingNumbers;
        findMatchingNumbers(matchingNumbers, clockDigits, brokenClock);

        printMatchingNumbers(matchingNumbers, fout, line);
        getline(fin, line);

        if (line != "0")
            fout << endl;

        brokenClock = workingClock;
    }
    return 0;
}