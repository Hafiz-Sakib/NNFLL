#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to find greatest common divisor (GCD)
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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

// Function to check if key 'a' is valid (must be coprime with 26)
bool isValidKeyA(int a)
{
    return gcd(a, 26) == 1;
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

// Function to encrypt using affine cipher
string affineEncrypt(const string &plaintext, int a, int b)
{
    if (!isValidKeyA(a))
    {
        return "ERROR: Invalid key 'a'! Key 'a' must be coprime with 26.";
    }

    string cleanedText = cleanText(plaintext);
    string ciphertext = "";

    for (char c : cleanedText)
    {
        int encryptedValue = ((c - 'A') * a + b) % 26;
        char encryptedChar = encryptedValue + 'A';
        ciphertext += encryptedChar;
    }

    return ciphertext;
}

// Function to decrypt using affine cipher
string affineDecrypt(const string &ciphertext, int a, int b)
{
    if (!isValidKeyA(a))
    {
        return "ERROR: Invalid key 'a'! Key 'a' must be coprime with 26.";
    }

    int inverseA = modInverse(a, 26);
    if (inverseA == -1)
    {
        return "ERROR: Modular inverse doesn't exist for key 'a'!";
    }

    string cleanedText = cleanText(ciphertext);
    string plaintext = "";

    for (char c : cleanedText)
    {
        int decryptedValue = (inverseA * (c - 'A' - b + 26)) % 26;
        char decryptedChar = decryptedValue + 'A';
        plaintext += decryptedChar;
    }

    return plaintext;
}

// Function to display valid keys for 'a'
void displayValidKeys()
{
    cout << "Valid keys for 'a': ";
    int validKeys[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
    int size = sizeof(validKeys) / sizeof(validKeys[0]);

    for (int i = 0; i < size; i++)
    {
        cout << validKeys[i];
        if (i < size - 1)
            cout << ", ";
    }
    cout << endl;
}

int main()
{
    cout << "=== AFFINE CIPHER ===" << endl;
    cout << "=====================" << endl;
    cout << "Formula: C = (a × P + b) mod 26" << endl;
    cout << "Key 'a' must be coprime with 26" << endl;
    cout << "Key 'b' can be any integer (0-25)" << endl;
    displayValidKeys();
    cout << "=====================" << endl;

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
    int a, b;

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

    cout << "Enter key 'a' (must be coprime with 26): ";
    cin >> a;
    cout << "Enter key 'b' (0-25): ";
    cin >> b;

    // Validate and adjust keys
    a = a % 26;
    if (a < 0)
        a += 26;
    b = b % 26;
    if (b < 0)
        b += 26;

    // Validate key 'a'
    if (!isValidKeyA(a))
    {
        cout << "\nERROR: Invalid key 'a'! Key 'a' must be coprime with 26." << endl;
        displayValidKeys();
        return 1;
    }

    string result;

    if (choice == 1)
    {
        result = affineEncrypt(inputText, a, b);
        cout << "\nEncryption Results:" << endl;
        cout << "Plaintext: " << inputText << endl;
        cout << "Key a: " << a << endl;
        cout << "Key b: " << b << endl;
        cout << "Ciphertext: " << result << endl;
    }
    else
    {
        result = affineDecrypt(inputText, a, b);
        cout << "\nDecryption Results:" << endl;
        cout << "Ciphertext: " << inputText << endl;
        cout << "Key a: " << a << endl;
        cout << "Key b: " << b << endl;
        cout << "Plaintext: " << result << endl;
    }

    cout << "\nThank you for using Affine Cipher!" << endl;

    return 0;
}