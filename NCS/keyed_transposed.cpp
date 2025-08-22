#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>
#include <sstream>
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

// Function to process text key and remove duplicates
string processTextKey(const string &key)
{
    string processedKey = "";
    map<char, bool> usedChars;

    for (char c : key)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (usedChars.find(c) == usedChars.end())
            {
                processedKey += c;
                usedChars[c] = true;
            }
        }
    }

    return processedKey;
}

// Corrected function to generate numeric key from text key
vector<int> generateNumericKeyFromText(const string &textKey)
{
    // Create pairs of (character, original position)
    vector<pair<char, int>> charPositions;
    for (int i = 0; i < textKey.size(); i++)
    {
        charPositions.push_back({textKey[i], i});
    }

    // Sort by character (alphabetical order)
    sort(charPositions.begin(), charPositions.end(),
         [](const pair<char, int> &a, const pair<char, int> &b)
         {
             return a.first < b.first;
         });

    // Create numeric key based on original positions
    vector<int> numericKey(textKey.size());
    for (int i = 0; i < charPositions.size(); i++)
    {
        numericKey[charPositions[i].second] = i + 1; // 1-based numbering
    }

    return numericKey;
}

// Function to validate numeric key
bool isValidNumericKey(const vector<int> &numericKey)
{
    int n = numericKey.size();
    vector<bool> found(n + 1, false);

    for (int num : numericKey)
    {
        if (num < 1 || num > n || found[num])
        {
            return false;
        }
        found[num] = true;
    }

    return true;
}

// Function to parse numeric key from string
vector<int> parseNumericKey(const string &keyStr)
{
    vector<int> numericKey;
    stringstream ss(keyStr);
    string token;

    while (getline(ss, token, ' '))
    {
        try
        {
            numericKey.push_back(stoi(token));
        }
        catch (...)
        {
            // Ignore invalid tokens
        }
    }

    // If no spaces, try comma separation
    if (numericKey.empty())
    {
        stringstream ss2(keyStr);
        while (getline(ss2, token, ','))
        {
            try
            {
                numericKey.push_back(stoi(token));
            }
            catch (...)
            {
                // Ignore invalid tokens
            }
        }
    }

    // If still empty, try without any separators
    if (numericKey.empty())
    {
        for (char c : keyStr)
        {
            if (isdigit(c))
            {
                numericKey.push_back(c - '0');
            }
        }
    }

    return numericKey;
}

// Function to encrypt using keyed transposition
string keyedTranspositionEncrypt(const string &plaintext, const vector<int> &numericKey)
{
    string cleanedText = cleanText(plaintext);
    int keyLength = numericKey.size();

    if (keyLength == 0)
    {
        return "ERROR: Invalid key!";
    }

    // Calculate number of rows needed
    int textLength = cleanedText.length();
    int rows = (textLength + keyLength - 1) / keyLength; // Ceiling division

    // Create grid with padding
    vector<vector<char>> grid(rows, vector<char>(keyLength, 'X'));

    // Fill grid row-wise
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < keyLength; j++)
        {
            if (index < textLength)
            {
                grid[i][j] = cleanedText[index++];
            }
        }
    }

    // Create mapping from numeric key to column order
    vector<pair<int, int>> keyOrder;
    for (int i = 0; i < keyLength; i++)
    {
        keyOrder.push_back({numericKey[i], i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Read columns in numeric key order
    string ciphertext = "";
    for (const auto &pair : keyOrder)
    {
        int col = pair.second;
        for (int i = 0; i < rows; i++)
        {
            ciphertext += grid[i][col];
        }
    }

    return ciphertext;
}

// Function to decrypt using keyed transposition
string keyedTranspositionDecrypt(const string &ciphertext, const vector<int> &numericKey)
{
    string cleanedText = cleanText(ciphertext);
    int keyLength = numericKey.size();

    if (keyLength == 0)
    {
        return "ERROR: Invalid key!";
    }

    // Calculate number of rows
    int textLength = cleanedText.length();
    int rows = textLength / keyLength;

    if (textLength % keyLength != 0)
    {
        return "ERROR: Ciphertext length must be multiple of key length!";
    }

    // Create mapping from numeric key to column order
    vector<pair<int, int>> keyOrder;
    for (int i = 0; i < keyLength; i++)
    {
        keyOrder.push_back({numericKey[i], i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    // Create grid
    vector<vector<char>> grid(rows, vector<char>(keyLength));

    // Fill grid column-wise in numeric key order
    int index = 0;
    for (const auto &pair : keyOrder)
    {
        int col = pair.second;
        for (int i = 0; i < rows; i++)
        {
            if (index < textLength)
            {
                grid[i][col] = cleanedText[index++];
            }
        }
    }

    // Read grid row-wise to get plaintext
    string plaintext = "";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < keyLength; j++)
        {
            plaintext += grid[i][j];
        }
    }

    return plaintext;
}

// Function to display the grid and key information
void displayGridInfo(const vector<vector<char>> &grid, const vector<int> &numericKey, const string &textKey = "")
{
    int rows = grid.size();
    int cols = grid[0].size();

    cout << "\nGrid Visualization (" << rows << "×" << cols << "):" << endl;

    if (!textKey.empty())
    {
        cout << "Text Key: " << textKey << endl;
        string sortedKey = textKey;
        sort(sortedKey.begin(), sortedKey.end());
        cout << "Sorted Key: " << sortedKey << endl;
    }

    cout << "Numeric Key: ";
    for (int num : numericKey)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "Reading Order (column numbers): ";
    vector<pair<int, int>> keyOrder;
    for (int i = 0; i < cols; i++)
    {
        keyOrder.push_back({numericKey[i], i});
    }
    sort(keyOrder.begin(), keyOrder.end());
    for (const auto &pair : keyOrder)
    {
        cout << pair.second + 1 << " ";
    }
    cout << endl;
    cout << "-------------------" << endl;

    // Display column headers
    cout << "Col# ";
    for (int j = 0; j < cols; j++)
    {
        cout << j + 1 << " ";
    }
    cout << endl;

    cout << "Key  ";
    for (int j = 0; j < cols; j++)
    {
        cout << numericKey[j] << " ";
    }
    cout << endl;

    // Display grid with row numbers
    for (int i = 0; i < rows; i++)
    {
        cout << "R" << i + 1 << "  ";
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "=== KEYED TRANSPOSITION CIPHER ===" << endl;
    cout << "==================================" << endl;
    cout << "Key Options:" << endl;
    cout << "1. Text Key (e.g., 'NETWORK')" << endl;
    cout << "2. Numeric Key (e.g., '3 1 6 7 4 5 2' or '3167452')" << endl;
    cout << "==================================" << endl;

    int choice;
    cout << "\nChoose operation:" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    int keyType;
    cout << "\nChoose key type:" << endl;
    cout << "1. Text Key" << endl;
    cout << "2. Numeric Key" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> keyType;
    cin.ignore();

    if (keyType != 1 && keyType != 2)
    {
        cout << "Invalid key type!" << endl;
        return 1;
    }

    string inputText, keyInput;
    vector<int> numericKey;
    string textKey = "";

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

    if (keyType == 1)
    {
        cout << "Enter text key: ";
        getline(cin, keyInput);
        textKey = processTextKey(keyInput);
        numericKey = generateNumericKeyFromText(textKey);
    }
    else
    {
        cout << "Enter numeric key (e.g., '3 1 6 7 4 5 2' or '3167452'): ";
        getline(cin, keyInput);
        numericKey = parseNumericKey(keyInput);
    }

    // Validate numeric key
    if (!isValidNumericKey(numericKey))
    {
        cout << "ERROR: Invalid numeric key! Key must be a permutation of 1 to N." << endl;
        return 1;
    }

    string result;

    if (choice == 1)
    {
        result = keyedTranspositionEncrypt(inputText, numericKey);

        // Recreate grid for visualization
        string cleanedText = cleanText(inputText);
        int keyLength = numericKey.size();
        int rows = (cleanedText.length() + keyLength - 1) / keyLength;
        vector<vector<char>> grid(rows, vector<char>(keyLength, 'X'));

        int index = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < keyLength; j++)
            {
                if (index < cleanedText.length())
                {
                    grid[i][j] = cleanedText[index++];
                }
            }
        }

        displayGridInfo(grid, numericKey, textKey);

        cout << "\nEncryption Results:" << endl;
        cout << "Plaintext: " << inputText << endl;
        if (keyType == 1)
        {
            cout << "Text Key: " << keyInput << " → " << textKey << " (processed)" << endl;
        }
        cout << "Numeric Key: ";
        for (int num : numericKey)
            cout << num << " ";
        cout << endl;
        cout << "Ciphertext: " << result << endl;
    }
    else
    {
        result = keyedTranspositionDecrypt(inputText, numericKey);

        if (result.substr(0, 5) == "ERROR")
        {
            cout << result << endl;
            return 1;
        }

        cout << "\nDecryption Results:" << endl;
        cout << "Ciphertext: " << inputText << endl;
        if (keyType == 1)
        {
            cout << "Text Key: " << keyInput << " → " << textKey << " (processed)" << endl;
        }
        cout << "Numeric Key: ";
        for (int num : numericKey)
            cout << num << " ";
        cout << endl;
        cout << "Plaintext: " << result << endl;
    }

    // Test the specific example
    cout << "\n==================================" << endl;
    cout << "TESTING WITH EXAMPLE: NETWORK + MEETMEATTHEPARK" << endl;
    cout << "==================================" << endl;

    string testPlaintext = "MEETMEATTHEPARK";
    string testKey = "NETWORK";

    string processedTestKey = processTextKey(testKey);
    vector<int> testNumericKey = generateNumericKeyFromText(processedTestKey);
    string testEncrypted = keyedTranspositionEncrypt(testPlaintext, testNumericKey);
    string testDecrypted = keyedTranspositionDecrypt(testEncrypted, testNumericKey);

    cout << "Plaintext: " << testPlaintext << endl;
    cout << "Key: " << testKey << endl;
    cout << "Numeric Key: ";
    for (int num : testNumericKey)
        cout << num << " ";
    cout << endl;
    cout << "Ciphertext: " << testEncrypted << endl;
    cout << "Expected:   ETXARXMTXMPXEAXEHXTEX" << endl;
    cout << "Match: " << (testEncrypted == "ETXARXMTXMPXEAXEHXTEX" ? "YES" : "NO") << endl;
    cout << "Decrypted: " << testDecrypted << endl;

    return 0;
}