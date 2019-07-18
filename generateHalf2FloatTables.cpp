#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

typedef uint_least32_t uint32;

class Generate{
public:
    void generateExponentTable()
    {
        ofstream fout("./table/exponentTable.txt");
        if (!fout)
        {
            cout << "Create exponent table file failed." << endl;
            return;
        }

        fout << setiosflags(ios::showbase);
        for (int i=0; i<64; ++i)
        {
            if (i == 0)
                fout << setiosflags(ios::showbase) << hex << 0x00000000 << " ";
            else if (i == 31)
                fout << hex << 0x47800000 << " ";
            else if (i == 32)
                fout << hex << 0x80000000 << " ";
            else if (i == 63)
                fout << hex << 0xC7800000 << endl;
            else if (i >= 1 && i <= 30)
                fout << hex << (i<<23) << " ";
            else
                fout << hex << (0x80000000 + ((i-32)<<23)) << " ";
        }

        fout.close();
    }

    void generateOffsetTable()
    {
        ofstream fout("./table/offsetTable.txt");
        if (!fout)
        {
            cout << "Create offset table file failed." << endl;
            return;
        }

        fout << setiosflags(ios::showbase);
        fout << 0 << " ";
        for (int i=1; i<63; ++i)
        {
            if (i == 32)
                fout << 0 << " ";
            else
                fout << 1024 << " ";
        }
        fout << 1024 << endl;
        fout.close();
    }

    void generateMantissaTable()
    {
        ofstream fout("./table/mantissaTable.txt");
        if (!fout)
        {
            cout << "Create mantissa table file failed." << endl;
            return;
        }

        fout << setiosflags(ios::showbase);
        fout << hex << 0x00000000 << " ";
        for (int i=1; i<2047; ++i)
        {
            if (i <= 1023)
                fout << hex << convertMantissa(i) << " ";
            else
                fout << hex << 0x38000000 + ((i-1024)<<13) << " ";
        }
        fout << hex << 0x38000000 + ((2047-1024)<<13) << " ";
        fout.close();
    }

    void generateTables()
    {
        generateExponentTable();
        generateOffsetTable();
        generateMantissaTable();
    }
private:
    uint32 convertMantissa(uint32 i)
    {
        uint32 m = i<<13; // Zero pad mantissa bits
        uint32 e = 0;     // Zero exponent

        while (!(m & 0x00800000)) // While not normalized
        {
            e -= 0x00800000;      // Decrement exponent (1<<23)
            m <<= 1;               // Shift mantissa
        }

        m &= ~0x00800000;   // Clear leading 1 bit
        e += 0x38800000;    // Adjust bias ((127-14)<<23)

        return m | e;       // Return combined number
    }
};

int main()
{
    Generate().generateTables();
    return 0;
}

