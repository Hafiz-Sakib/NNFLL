#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
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

// Function to encrypt using keyless transposition (columnar)
string transpositionEncrypt(const string &plaintext)
{
    string cleanedText = cleanText(plaintext);
    int length = cleanedText.length();

    if (length == 0)
        return "";

    // Determine number of columns (square root of length, rounded up)
    int cols = ceil(sqrt(length));
    int rows = ceil((double)length / cols);

    // Create the grid
    vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

    // Fill the grid row-wise
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (index < length)
            {
                grid[i][j] = cleanedText[index++];
            }
        }
    }

    // Read the grid column-wise to get ciphertext
    string ciphertext = "";
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            ciphertext += grid[i][j];
        }
    }

    return ciphertext;
}

// Function to decrypt using keyless transposition
string transpositionDecrypt(const string &ciphertext)
{
    string cleanedText = cleanText(ciphertext);
    int length = cleanedText.length();

    if (length == 0)
        return "";

    // Determine number of columns (square root of length, rounded up)
    int cols = ceil(sqrt(length));
    int rows = ceil((double)length / cols);

    // Create the grid
    vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

    // Fill the grid column-wise (reverse of encryption)
    int index = 0;
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            if (index < length)
            {
                grid[i][j] = cleanedText[index++];
            }
        }
    }

    // Read the grid row-wise to get plaintext
    string plaintext = "";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            plaintext += grid[i][j];
        }
    }

    return plaintext;
}

// Function to display the grid for visualization
void displayGrid(const string &text, bool isEncryption)
{
    string cleanedText = cleanText(text);
    int length = cleanedText.length();

    if (length == 0)
        return;

    int cols = ceil(sqrt(length));
    int rows = ceil((double)length / cols);

    vector<vector<char>> grid(rows, vector<char>(cols, ' '));

    if (isEncryption)
    {
        // Fill row-wise for encryption visualization
        int index = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (index < length)
                {
                    grid[i][j] = cleanedText[index++];
                }
                else
                {
                    grid[i][j] = 'X';
                }
            }
        }
    }
    else
    {
        // Fill column-wise for decryption visualization
        int index = 0;
        for (int j = 0; j < cols; j++)
        {
            for (int i = 0; i < rows; i++)
            {
                if (index < length)
                {
                    grid[i][j] = cleanedText[index++];
                }
                else
                {
                    grid[i][j] = 'X';
                }
            }
        }
    }

    cout << "\nGrid Visualization (" << rows << "×" << cols << "):" << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "=== KEYLESS TRANSPOSITION CIPHER ===" << endl;
    cout << "====================================" << endl;
    cout << "Method: Columnar transposition with automatic grid sizing" << endl;
    cout << "Grid size: ceil(sqrt(text_length)) columns" << endl;
    cout << "Padding: 'X' characters for empty cells" << endl;
    cout << "====================================" << endl;

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

    if (choice == 1)
    {
        cout << "\n--- ENCRYPTION ---" << endl;
        cout << "Enter plaintext: ";
        getline(cin, inputText);

        string encrypted = transpositionEncrypt(inputText);
        displayGrid(inputText, true); // Show original grid

        cout << "\nEncryption Results:" << endl;
        cout << "Plaintext: " << inputText << endl;
        cout << "Ciphertext: " << encrypted << endl;
    }
    else
    {
        cout << "\n--- DECRYPTION ---" << endl;
        cout << "Enter ciphertext: ";
        getline(cin, inputText);

        string decrypted = transpositionDecrypt(inputText);
        displayGrid(inputText, false); // Show encrypted grid

        cout << "\nDecryption Results:" << endl;
        cout << "Ciphertext: " << inputText << endl;
        cout << "Plaintext: " << decrypted << endl;
    }

    cout << "\nThank you for using Keyless Transposition Cipher!" << endl;

    return 0;
}