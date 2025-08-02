#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to compute modular inverse
int modInverse(int key, int mod) {
    key = key % mod;
    for (int x = 1; x < mod; ++x) {
        if ((key * x) % mod == 1)
            return x;
    }
    return -1; // No inverse exists
}

// Encrypt function
string encrypt(string plaintext, int key) {
    string ciphertext = "";
    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int p = ch - base;
            int c = (p * key) % 26;
            ciphertext += static_cast<char>(c + base);
        } else {
            ciphertext += ch; // Keep non-alpha characters unchanged
        }
    }
    return ciphertext;
}

// Decrypt function
string decrypt(string ciphertext, int key) {
    string plaintext = "";
    int keyInv = modInverse(key, 26);
    if (keyInv == -1) {
        return "Invalid key! No modular inverse exists.";
    }
    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int c = ch - base;
            int p = (c * keyInv) % 26;
            if (p < 0) p += 26; // Ensure positive result
            plaintext += static_cast<char>(p + base);
        } else {
            plaintext += ch;
        }
    }
    return plaintext;
}

int main() {
    int key;
    string input;
    char choice;

    cout << "Multiplicative Cipher\n";
    cout << "Enter key (must be coprime with 26): ";
    cin >> key;

    if (modInverse(key, 26) == -1) {
        cout << "Invalid key! No inverse exists modulo 26.\n";
        return 1;
    }

    cout << "Encrypt or Decrypt? (e/d): ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    cout << "Enter text: ";
    getline(cin, input);

    if (choice == 'e' || choice == 'E') {
        string cipher = encrypt(input, key);
        cout << "Encrypted: " << cipher << endl;
    } else if (choice == 'd' || choice == 'D') {
        string plain = decrypt(input, key);
        cout << "Decrypted: " << plain << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
