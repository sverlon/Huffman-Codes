#include "huffman.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void print_test(string message)
{
    cout << "========================" << endl;
    cout << "TESTING: " << message << endl;
    cout << "========================" << endl
         << endl;
}

void pass()
{
    cout << "========================" << endl;
    cout << "          PASS" << endl;
    cout << "========================" << endl
         << endl;
}

void test_ctor_and_print()
{
    print_test("ctor and print");

    ifstream is("example.in");

    Decoder decoder(is);

    decoder.print();

    pass();
}

void test_encode()
{
    print_test("encode");

    ifstream is("example.in");

    Decoder decoder(is);

    decoder.encode();

    decoder.print();

    pass();
}

void test_encode_large()
{
    print_test("encode english");

    ifstream is("english.in");

    Decoder decoder(is);

    decoder.encode();

    decoder.print();

    pass();
}

void test_decode()
{
    print_test("decode");

    ifstream is("example.in");

    Decoder decoder(is);

    decoder.encode();

    decoder.decode(cin, cout);

    pass();
}

int main()
{

    cout << "RUNNING TEST SUITE" << endl;
    cout << "==================" << endl;
    cout << endl;

    test_ctor_and_print();

    test_encode();

    test_encode_large();

    test_decode();

    return 0;
}