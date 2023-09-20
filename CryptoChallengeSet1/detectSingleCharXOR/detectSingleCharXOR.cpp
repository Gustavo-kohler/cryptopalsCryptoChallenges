#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

map<char, int> letterFrequencyMap = {
        {'a', 8167}, {'b', 1492}, {'c', 2782}, {'d', 4253},
        {'e', 12702}, {'f', 2228}, {'g', 2015}, {'h', 6094},
        {'i', 6966}, {'j', 153}, {'k', 772}, {'l', 4025},
        {'m', 2406}, {'n', 6749}, {'o', 7507}, {'p', 1929},
        {'q', 95}, {'r', 5987}, {'s', 6327}, {'t', 9056},
        {'u', 2758}, {'v', 978}, {'w', 2360}, {'x', 150}, {'y', 1974}, {'z', 74}
};

vector<uint8_t> hexToBin(string value) {
    const string hexChar = "0123456789abcdef";

    vector<uint8_t> binaryData;

    for (size_t i=0; i<value.size(); i+=2) {
        uint8_t byte = (hexChar.find(value[i])<<4) | hexChar.find(value[i+1]);
        binaryData.push_back(byte);
    }
    return binaryData;
}

string binaryToASCII(vector<uint8_t> vector) {
    string utf8String;

    for (uint8_t byte : vector) {
        utf8String += static_cast<char>(byte);
    }
    
    return utf8String;
}

int calculateScore(vector<uint8_t> vector) {
    string utf8string = binaryToASCII(vector);
    unsigned int score = 0;

    for (char i : utf8string) {
        if(i == ' ') {
            score += 10000;
        } else {
            score += letterFrequencyMap[i];
        }
    }

    return score;
}

vector<uint8_t> decrypt(vector<uint8_t> binaryData) {
    vector<uint8_t> bestScoreVector, decryptedVector;
    unsigned int score, bestScore = 0;
    
    uint8_t key = 0b00000000;
    while (key < 0b11111111) {
        for (uint8_t Byte : binaryData) {
            uint8_t decryptedByte = (Byte ^ key);
            decryptedVector.push_back(decryptedByte);
        }

        score = calculateScore(decryptedVector);
        if (score > bestScore) {
            bestScore = score;
            bestScoreVector = decryptedVector;
        }

        decryptedVector.clear();
        key ++;
    }
    
    return bestScoreVector;
}

string findEncrypted(string file) {
    fstream doc;
    string encryptedLine;
    
    doc.open(file);
    if (doc.is_open()) {
        string line;
        unsigned int score, maiorScore = 0;
          
        while (getline(doc, line)) {
            vector<uint8_t> binaryData = hexToBin(line);

            score = calculateScore(decrypt(binaryData));
            if (score > maiorScore) {
                maiorScore = score;
                encryptedLine = line;
            }
            binaryData.clear();
        }   
    }

    return encryptedLine;
}

void detectSingleCharXOR(string file) {

    string decryptedLine = binaryToASCII(decrypt(hexToBin(findEncrypted(file))));

    cout << decryptedLine;

}

int main() {
   
    detectSingleCharXOR("../data.txt");
    
    return 0;
}
