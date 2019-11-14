#include <iostream>
#include <string>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

//2 байта. Сдвиг на 4 вправо.

string ciphertext(string s, unsigned int VI) {
    std::uniform_int_distribution<> range{0, 0xFF};
    std::default_random_engine random_number_generator(VI);
    string cipher;
    int len = s.length();
    if (len % 2 != 0)
        s[len] = 206;
    int i = 0;
    while (i < len) {
        unsigned short cc = (unsigned short) s[i] << 8 | ((unsigned short) s[i + 1] & 0xFF);
        short random_number = range(random_number_generator);
        unsigned short d;
        d = cc ^ random_number;
        d = (d >> 4) | (d << (12));
        unsigned char c1 = d >> 8;
        cipher += c1;
        unsigned char c2 = d;
        cipher += c2;
        i += 2;
    }

    return cipher;
};


string plaintext(string s, unsigned int VI) {
    std::uniform_int_distribution<> range{0, 0xFF};
    std::default_random_engine random_number_generator(VI);
    string plaintext;
    int len = s.length();
    if (len % 2 != 0) s[len] = 206;
    int i = 0;
    while (i < len) {
        unsigned short cc = ((unsigned short) s[i]) << 8 | ((unsigned short) s[i + 1] & 0xFF);
        short random_number = range(random_number_generator);
        unsigned short d;
        d = (cc << 4) | (cc >> (12));
        d = d ^ random_number;
        unsigned char c1 = d >> 8;
        plaintext += c1;
        unsigned char c2 = d;
        plaintext += c2;
        i += 2;
    }

    return plaintext;
};

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Enter the operating mode. If <encryption>, then press 1, if <decryption>, then press 2." << endl;
    int bbin;
    cin >> bbin;
    cin.ignore();
    string s;
    cout << "Текст: ";
    getline(cin, s);
    unsigned int VI;
    cout << "VI: ";
    cin >> VI;
    string res, res2;
    if (bbin == 1) res = ciphertext(s, VI);
    else if (bbin == 2) res = plaintext(s, VI);
    else
        cout << "Check entered data";
    if (res.length() != s.length()) {
        res2 = res;
        res.resize(res.length() - 1);
    }
    cout << "Result:" << res << endl;

    //Проверка
    cout << "Do check? (yes/no)" << endl;
    string check;
    cin >> check;
    if (check == "yes") {
        if (s.length() % 2 != 0) res = res2;
        if (bbin == 2) check = ciphertext(res, VI); else if (bbin == 1) check = plaintext(res, VI);
        if (check.length() != s.length()) check.resize(check.length() - 1);
        cout << "Check:" << endl << check;

    }
    return 0;
}