#include "huffman.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{

    string file_with_keys;
    cout << "Please type the filename with symbol: probability keys: ";
    cin >> file_with_keys;

    ifstream is(file_with_keys);
    Decoder decoder(is);

    decoder.encode();

    string decode_file;
    cout << "Please type the message you would like to decode," << endl;
    cout << "or 'input' for terminal input: ";
    cin >> decode_file;

    if (decode_file == "input")
    {
        decoder.print();
        decoder.decode(cin, cout);
    }
    else
    {
        string outfile;
        cout << "Please type the output file for your message: ";
        cin >> outfile;

        ifstream is(decode_file);
        ofstream os(outfile);
        decoder.decode(is, os);
    }
    return 0;
}