#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to find modular multiplicative inverse
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to check if key is valid (must be coprime with 26)
bool isValidKey(int key)
{
    if (key % 2 == 0 || key % 13 == 0)
    {
        return false;
    }
    return true;
}

// Function to clean text (remove non-alphabetic characters and convert to uppercase)
string cleanText(const string &text)
{
    string cleaned = "";
    for (char c : text)
    {
        if (isalpha(c))
        {
            cleaned += toupper(c);
        }
    }
    return cleaned;
}

// Function to encrypt using multiplicative cipher
string multiplicativeEncrypt(const string &plaintext, int key)
{
    if (!isValidKey(key))
    {
        return "ERROR: Invalid key! Key must be coprime with 26 (cannot be even or divisible by 13)";
    }

    string cleanedText = cleanText(plaintext);
    string ciphertext = "";

    for (char c : cleanedText)
    {
        int encryptedValue = ((c - 'A') * key) % 26;
        char encryptedChar = encryptedValue + 'A';
        ciphertext += encryptedChar;
    }

    return ciphertext;
}

// Function to decrypt using multiplicative cipher
string multiplicativeDecrypt(const string &ciphertext, int key)
{
    if (!isValidKey(key))
    {
        return "ERROR: Invalid key! Key must be coprime with 26 (cannot be even or divisible by 13)";
    }

    int inverseKey = modInverse(key, 26);
    if (inverseKey == -1)
    {
        return "ERROR: Modular inverse doesn't exist for this key!";
    }

    string cleanedText = cleanText(ciphertext);
    string plaintext = "";

    for (char c : cleanedText)
    {
        int decryptedValue = ((c - 'A') * inverseKey) % 26;
        char decryptedChar = decryptedValue + 'A';
        plaintext += decryptedChar;
    }

    return plaintext;
}

int main()
{
    cout << "=== MULTIPLICATIVE CIPHER ===" << endl;
    cout << "=============================" << endl;
    cout << "Valid keys: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25" << endl;
    cout << " (Keys must be coprime with 26)" << endl;
    cout << "=============================" << endl;

    int choice;
    cout << "\nChoose operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    cin.ignore(); // Clear the input buffer

    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice! Please run the program again and choose 1 or 2." << endl;
        return 1;
    }

    string inputText;
    int key;

    if (choice == 1)
    {
        cout << "\n--- ENCRYPTION ---" << endl;
        cout << "Enter plaintext: ";
        getline(cin, inputText);
    }
    else
    {
        cout << "\n--- DECRYPTION ---" << endl;
        cout << "Enter ciphertext: ";
        getline(cin, inputText);
    }

    cout << "Enter key (must be coprime with 26): ";
    cin >> key;

    // Validate key
    if (!isValidKey(key))
    {
        cout << "\nERROR: Invalid key! Key must be coprime with 26." << endl;
        cout << "Valid keys: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25" << endl;
        return 1;
    }

    string result;

    if (choice == 1)
    {
        result = multiplicativeEncrypt(inputText, key);
        cout << "\nEncryption Results:" << endl;
        cout << "Plaintext: " << inputText << endl;
        cout << "Key: " << key << endl;
        cout << "Ciphertext: " << result << endl;
    }
    else
    {
        result = multiplicativeDecrypt(inputText, key);
        cout << "\nDecryption Results:" << endl;
        cout << "Ciphertext: " << inputText << endl;
        cout << "Key: " << key << endl;
        cout << "Plaintext: " << result << endl;
    }

    cout << "\nThank you for using Multiplicative Cipher!" << endl;

    return 0;
}