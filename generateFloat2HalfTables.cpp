#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

typedef uint_least16_t uint16;

class Generate{
public:
    void generateTables()
    {
        baseTable = vector<uint16>(512, 0);
        shiftTable = vector<uint16>(512, 0);
        uint16 i;
        int e;
        for (i=0; i<256; ++i)
        {
            e = i - 127;
            if (e < -24) // Very small numbers map to zero
            {
                baseTable[i | 0x000] = 0x0000;
                baseTable[i | 0x100] = 0x8000;
                shiftTable[i | 0x000] = 24;
                shiftTable[i | 0x100] = 24;
            }
            else if (e < -14) // Small numbers map to zero
            {
                baseTable[i | 0x000] = (0x0400>>(-e-14));
                baseTable[i | 0x100] = (0x0400>>(-e-14) | 0x8000);
                shiftTable[i | 0x000] = -e-1;
                shiftTable[i | 0x100] = -e-1;
            }
            else if (e <= 15) // Normal numbers just lose precision
            {
                baseTable[i | 0x000] = ((e+15)<<10);
                baseTable[i | 0x100] = ((e+15)<<10) | 0x8000;
                shiftTable[i | 0x000] = 13;
                shiftTable[i | 0x100] = 13;
            }
            else if (e < 128) // Large numbers map to Infinity
            {
                baseTable[i | 0x000] = 0x7C00;
                baseTable[i | 0x100] = 0xFC00;
                shiftTable[i | 0x000] = 24;
                shiftTable[i | 0x100] = 24;
            }
            else // Infinity and NaN's stay Infinity and NaN's
            {
                baseTable[i | 0x000] = 0x7C00;
                baseTable[i | 0x100] = 0xFC00;
                shiftTable[i | 0x000] = 13;
                shiftTable[i | 0x100] = 13;
            }
        }
    }

    void printOut()
    {
        generateTables();

        ofstream fout1("./table/baseTable.txt");
        if(!fout1)
        {
            cout << "Create base table file failed." << endl;
            return;
        }
        ofstream fout2("./table/shiftTable.txt");
        if(!fout2)
        {
            cout << "Create shift table file failed." << endl;
            return;
        }

        fout1 << setiosflags(ios::showbase);
        for (int i=0; i<511; ++i)
        {
            fout1 << hex << baseTable[i] << " ";
            fout2 << shiftTable[i] << " ";
        }
        fout1 << hex << baseTable[511] << endl;
        fout2 << shiftTable[511] << endl;

        fout1.close();
        fout2.close();
    }
private:
    vector<uint16> baseTable;
    vector<uint16> shiftTable;
};

int main()
{
    Generate().printOut();
    return 0;
}

