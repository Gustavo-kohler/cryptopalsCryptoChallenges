#include <iostream>
#include <vector>

using namespace std;

vector<uint8_t> hexToBin(string value) {
    const string hexChar = "0123456789abcdef";

    vector<uint8_t> binaryData;

    for (size_t i=0; i<value.size(); i+=2) {
        uint8_t byte = (hexChar.find(value[i])<<4) | hexChar.find(value[i+1]);
        binaryData.push_back(byte);
    }
    return binaryData;
}

void fixedXOR(string valor1, string valor2) {

    vector<uint8_t> bin1 = hexToBin(valor1);
    vector<uint8_t> bin2 = hexToBin(valor2);

    for (size_t i = 0; i < bin1.size(); i++) {
        cout << hex << (bin1[i] ^ bin2[i]);
    }
    cout << endl;
}

int main() {
    
    fixedXOR("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965");

    return 0;
}