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

string binaryBase64(vector<uint8_t> binaryData) {
    const string charBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string base64;

    size_t i = 0;
    while (i < binaryData.size()) {
        
        uint8_t byte1 = binaryData[i++];
        base64 += charBase64[(byte1 >> 2) & 0b00111111];

        if (i < binaryData.size()) {
            uint8_t byte2 = binaryData[i++];
            base64 += charBase64[((byte1 & 0b00000011) << 4) | ((byte2 >> 4) & 0b00001111)];

            if (i < binaryData.size()) {
                uint8_t byte3 = binaryData[i++];
                base64 += charBase64[((byte2 & 0b00001111) << 2) | ((byte3 >> 6) & 0b00000011)];
                base64 += charBase64[byte3 & 0b00111111];
            } else {
                base64 += charBase64[(byte2 & 0b00001111) << 2];
            }
        } else {
            base64 += charBase64[(byte1 & 0b00000011) << 4];
        }
    }

    return base64;
}

void hexBase64(string hexValue) {

    vector<uint8_t> binaryData = hexToBin(hexValue);
    string base64 = binaryBase64(binaryData);
    cout << base64 << endl;

}

int main() {
    
    hexBase64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");

    return 0;
}
