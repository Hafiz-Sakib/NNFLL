#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <set>
using namespace std;

// Function to prepare the key by removing duplicates and handling 'J'
string prepareKey(string key)
{
    string preparedKey = "";
    set<char> usedChars;

    // Convert to uppercase
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    // Process key characters
    for (char c : key)
    {
        if (isalpha(c))
        {
            if (c == 'J')
                c = 'I'; // Treat 'J' as 'I'
            if (usedChars.find(c) == usedChars.end())
            {
                preparedKey += c;
                usedChars.insert(c);
            }
        }
    }

    // Add remaining alphabet characters
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c != 'J' && usedChars.find(c) == usedChars.end())
        {
            preparedKey += c;
            usedChars.insert(c);
        }
    }

    return preparedKey;
}

// Function to build the 5x5 key matrix
vector<vector<char>> buildMatrix(const string &key)
{
    string preparedKey = prepareKey(key);
    vector<vector<char>> matrix(5, vector<char>(5));

    int index = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrix[i][j] = preparedKey[index++];
        }
    }

    return matrix;
}

// Function to display the key matrix
void displayMatrix(const vector<vector<char>> &matrix)
{
    cout << "\nPlayfair Key Matrix:" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to prepare text for processing
string prepareText(const string &text, bool isEncrypt = true)
{
    string preparedText = "";

    // Convert to uppercase and remove non-alphabetic characters
    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J')
                c = 'I'; // Treat 'J' as 'I'
            preparedText += c;
        }
    }

    if (isEncrypt)
    {
        // For encryption: handle double letters and odd length
        string result = "";
        for (size_t i = 0; i < preparedText.length(); i++)
        {
            result += preparedText[i];

            // If next character is same, insert 'X'
            if (i + 1 < preparedText.length() && preparedText[i] == preparedText[i + 1])
            {
                result += 'X';
            }
        }

        // If odd length, add 'X' at the end
        if (result.length() % 2 != 0)
        {
            result += 'X';
        }

        return result;
    }

    return preparedText; // For decryption, just clean the text
}

// Function to find position of a character in the key matrix
pair<int, int> findPosition(const vector<vector<char>> &matrix, char c)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matrix[i][j] == c)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never happen
}

// Function to encrypt plaintext
string encryptText(const vector<vector<char>> &matrix, const string &plaintext)
{
    string preparedText = prepareText(plaintext, true);
    string ciphertext = "";

    for (size_t i = 0; i < preparedText.length(); i += 2)
    {
        char first = preparedText[i];
        char second = preparedText[i + 1];

        auto pos1 = findPosition(matrix, first);
        auto pos2 = findPosition(matrix, second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        // Same row
        if (row1 == row2)
        {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        }
        // Same column
        else if (col1 == col2)
        {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        }
        // Different row and column (rectangle)
        else
        {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }

    return ciphertext;
}

// Function to decrypt ciphertext
string decryptText(const vector<vector<char>> &matrix, const string &ciphertext)
{
    string cleanedText = prepareText(ciphertext, false);
    string plaintext = "";

    // Ensure even length for decryption
    if (cleanedText.length() % 2 != 0)
    {
        cout << "Warning: Ciphertext should have even length. Adding 'X' at the end." << endl;
        cleanedText += 'X';
    }

    for (size_t i = 0; i < cleanedText.length(); i += 2)
    {
        char first = cleanedText[i];
        char second = cleanedText[i + 1];

        auto pos1 = findPosition(matrix, first);
        auto pos2 = findPosition(matrix, second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        // Same row
        if (row1 == row2)
        {
            plaintext += matrix[row1][(col1 + 4) % 5]; // +4 instead of -1 for modulo
            plaintext += matrix[row2][(col2 + 4) % 5];
        }
        // Same column
        else if (col1 == col2)
        {
            plaintext += matrix[(row1 + 4) % 5][col1];
            plaintext += matrix[(row2 + 4) % 5][col2];
        }
        // Different row and column (rectangle)
        else
        {
            plaintext += matrix[row1][col2];
            plaintext += matrix[row2][col1];
        }
    }

    return plaintext;
}

// Function to get user input
string getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main()
{
    cout << "=== Playfair Cipher Implementation ===" << endl;

    // Get key from user
    string key = getInput("Enter the key: ");

    // Build and display key matrix
    vector<vector<char>> matrix = buildMatrix(key);
    displayMatrix(matrix);

    // Get operation choice
    string choiceStr = getInput("Choose operation:\n1. Encrypt\n2. Decrypt\nEnter choice (1 or 2): ");
    int choice = stoi(choiceStr);

    if (choice == 1)
    {
        // Encryption
        string plaintext = getInput("Enter plaintext to encrypt: ");
        string encrypted = encryptText(matrix, plaintext);
        cout << "Encrypted text: " << encrypted << endl;
    }
    else if (choice == 2)
    {
        // Decryption
        string ciphertext = getInput("Enter ciphertext to decrypt: ");
        string decrypted = decryptText(matrix, ciphertext);
        cout << "Decrypted text: " << decrypted << endl;
    }
    else
    {
        cout << "Invalid choice! Please enter 1 or 2." << endl;
    }

    return 0;
}