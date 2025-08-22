#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

class PlayfairCipher {
private:
    vector<vector<char>> keyMatrix;
    string key;
    
    // Prepare the key by removing duplicates and handling 'J'
    string prepareKey(string key) {
        string preparedKey = "";
        bool used[26] = {false};
        
        // Convert to uppercase and handle 'J'
        for (char &c : key) {
            c = toupper(c);
            if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        }
        
        // Add key characters
        for (char c : key) {
            if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
                preparedKey += c;
                used[c - 'A'] = true;
            }
        }
        
        // Add remaining alphabet characters
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'J' && !used[c - 'A']) {
                preparedKey += c;
            }
        }
        
        return preparedKey;
    }
    
    // Build the 5x5 key matrix
    void buildMatrix() {
        string preparedKey = prepareKey(key);
        keyMatrix.resize(5, vector<char>(5));
        
        int index = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                keyMatrix[i][j] = preparedKey[index++];
            }
        }
    }
    
    // Prepare plaintext for encryption
    string prepareText(string text) {
        string preparedText = "";
        
        // Convert to uppercase and remove non-alphabetic characters
        for (char c : text) {
            if (isalpha(c)) {
                c = toupper(c);
                if (c == 'J') c = 'I'; // Treat 'J' as 'I'
                preparedText += c;
            }
        }
        
        // Handle double letters and odd length
        string result = "";
        for (int i = 0; i < preparedText.length(); i++) {
            result += preparedText[i];
            
            // If next character is same, insert 'X'
            if (i + 1 < preparedText.length() && preparedText[i] == preparedText[i + 1]) {
                result += 'X';
            }
        }
        
        // If odd length, add 'X' at the end
        if (result.length() % 2 != 0) {
            result += 'X';
        }
        
        return result;
    }
    
    // Find position of a character in the key matrix
    pair<int, int> findPosition(char c) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (keyMatrix[i][j] == c) {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // Should never happen
    }
    
public:
    PlayfairCipher(string key) : key(key) {
        buildMatrix();
    }
    
    // Display the key matrix
    void displayMatrix() {
        cout << "Playfair Key Matrix:" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << keyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // Encrypt plaintext
    string encrypt(string plaintext) {
        string preparedText = prepareText(plaintext);
        string ciphertext = "";
        
        for (int i = 0; i < preparedText.length(); i += 2) {
            char first = preparedText[i];
            char second = preparedText[i + 1];
            
            auto pos1 = findPosition(first);
            auto pos2 = findPosition(second);
            
            int row1 = pos1.first, col1 = pos1.second;
            int row2 = pos2.first, col2 = pos2.second;
            
            // Same row
            if (row1 == row2) {
                ciphertext += keyMatrix[row1][(col1 + 1) % 5];
                ciphertext += keyMatrix[row2][(col2 + 1) % 5];
            }
            // Same column
            else if (col1 == col2) {
                ciphertext += keyMatrix[(row1 + 1) % 5][col1];
                ciphertext += keyMatrix[(row2 + 1) % 5][col2];
            }
            // Different row and column (rectangle)
            else {
                ciphertext += keyMatrix[row1][col2];
                ciphertext += keyMatrix[row2][col1];
            }
        }
        
        return ciphertext;
    }
    
    // Decrypt ciphertext
    string decrypt(string ciphertext) {
        string plaintext = "";
        
        // Convert to uppercase
        for (char &c : ciphertext) {
            c = toupper(c);
        }
        
        for (int i = 0; i < ciphertext.length(); i += 2) {
            char first = ciphertext[i];
            char second = ciphertext[i + 1];
            
            auto pos1 = findPosition(first);
            auto pos2 = findPosition(second);
            
            int row1 = pos1.first, col1 = pos1.second;
            int row2 = pos2.first, col2 = pos2.second;
            
            // Same row
            if (row1 == row2) {
                plaintext += keyMatrix[row1][(col1 + 4) % 5]; // +4 instead of -1 for modulo
                plaintext += keyMatrix[row2][(col2 + 4) % 5];
            }
            // Same column
            else if (col1 == col2) {
                plaintext += keyMatrix[(row1 + 4) % 5][col1];
                plaintext += keyMatrix[(row2 + 4) % 5][col2];
            }
            // Different row and column (rectangle)
            else {
                plaintext += keyMatrix[row1][col2];
                plaintext += keyMatrix[row2][col1];
            }
        }
        
        return plaintext;
    }
};

int main() {
    string key, text;
    int choice;
    
    cout << "=== Playfair Cipher Implementation ===" << endl;
    cout << "Enter the key: ";
    getline(cin, key);
    
    PlayfairCipher cipher(key);
    cipher.displayMatrix();
    
    cout << "\nChoose operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    cin.ignore(); // Clear input buffer
    
    if (choice == 1) {
        cout << "Enter plaintext to encrypt: ";
        getline(cin, text);
        
        string encrypted = cipher.encrypt(text);
        cout << "Encrypted text: " << encrypted << endl;
        
    } else if (choice == 2) {
        cout << "Enter ciphertext to decrypt: ";
        getline(cin, text);
        
        string decrypted = cipher.decrypt(text);
        cout << "Decrypted text: " << decrypted << endl;
        
    } else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}