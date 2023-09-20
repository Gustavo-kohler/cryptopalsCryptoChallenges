#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<unsigned char> stringToBin(string str) {
    vector<unsigned char> binaryData;

    for (unsigned char i : str) {
        binaryData.push_back(i);
    }

    return binaryData;
}

vector<unsigned char> repKeyXOREncrypt(vector<unsigned char> binaryData, string key) {
    vector<unsigned char> encryptedVector;
    
    size_t i = 0;
    while (i < binaryData.size()) {    
           encryptedVector.push_back((binaryData[i++] ^ key[0]));

        if (i < binaryData.size()) {
            encryptedVector.push_back((binaryData[i++] ^ key[1]));

            if (i < binaryData.size()) {
                encryptedVector.push_back((binaryData[i++] ^ key[2]));

            }
        } 
    }

    return encryptedVector;
}

void repeatingKeyXOR(string str, string key) {

    vector<unsigned char> encryptedString = repKeyXOREncrypt(stringToBin(str), key);

    for (size_t i = 0; i < encryptedString.size(); i++) {
        cout << setfill('0') << setw(2) << hex << static_cast<int>(encryptedString[i]);
    }
    cout << endl;

}

int main() {
    
    repeatingKeyXOR("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", "ICE");

    return 0;
}