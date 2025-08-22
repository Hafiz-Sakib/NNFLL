#include <iostream>
#include <string>
#include <cctype>
using namespace std;

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

// Function to encrypt using additive cipher
string additiveEncrypt(const string &plaintext, int key)
{
    string cleanedText = cleanText(plaintext);
    string ciphertext = "";

    for (char c : cleanedText)
    {
        char encryptedChar = ((c - 'A' + key) % 26) + 'A';
        ciphertext += encryptedChar;
    }

    return ciphertext;
}

// Function to decrypt using additive cipher
string additiveDecrypt(const string &ciphertext, int key)
{
    string cleanedText = cleanText(ciphertext);
    string plaintext = "";

    for (char c : cleanedText)
    {
        int decryptedValue = (c - 'A' - key) % 26;
        if (decryptedValue < 0)
        {
            decryptedValue += 26;
        }
        char decryptedChar = decryptedValue + 'A';
        plaintext += decryptedChar;
    }

    return plaintext;
}

int main()
{
    cout << "=== ADDITIVE CIPHER ===" << endl;
    cout << "=======================" << endl;

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

    cout << "Enter key (0-25): ";
    cin >> key;

    // Validate and adjust key
    key = key % 26;
    if (key < 0)
    {
        key += 26;
    }

    string result;

    if (choice == 1)
    {
        result = additiveEncrypt(inputText, key);
        cout << "\nEncryption Results:" << endl;
        cout << "Plaintext: " << inputText << endl;
        cout << "Key: " << key << endl;
        cout << "Ciphertext: " << result << endl;
    }
    else
    {
        result = additiveDecrypt(inputText, key);
        cout << "\nDecryption Results:" << endl;
        cout << "Ciphertext: " << inputText << endl;
        cout << "Key: " << key << endl;
        cout << "Plaintext: " << result << endl;
    }

    cout << "\nThank you for using Additive Cipher!" << endl;

    return 0;
}