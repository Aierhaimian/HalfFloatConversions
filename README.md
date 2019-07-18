# Half float convert

---

This repo is about how to convert the half-float data type to single precision(32-bit) IEEE 754 standard representations and it's backward conversion.

The algorithm is followed from [Jeroen van der Zijp](ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf "Fast Half Float Conversions").

The file explanation:

- convert.cpp: This file contains halt2float and float2half functions, which can convert halt-float numbers to float and vice-versa.
- generateFloat2HalfTables.cpp: This file generates the lookup table required by the floating point to half floating point algorithm.
- generateHalf2FloatTables.cpp: This file generates the lookup table required by the half floating point to floating point algorithm. 
- table: This directory is all the generated lookup tables.
