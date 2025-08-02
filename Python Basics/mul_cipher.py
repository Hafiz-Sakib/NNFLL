from math import gcd

# Function to find modular inverse of key modulo 26
def mod_inverse(key, mod=26):
    for x in range(1, mod):
        if (key * x) % mod == 1:
            return x
    return -1  # Inverse doesn't exist

# Encryption function
def encrypt(plaintext, key):
    ciphertext = ''
    for ch in plaintext:
        if ch.isalpha():
            base = ord('A') if ch.isupper() else ord('a')
            c = (ord(ch) - base) * key % 26
            ciphertext += chr(c + base)
        else:
            ciphertext += ch
    return ciphertext

# Decryption function
def decrypt(ciphertext, key):
    key_inv = mod_inverse(key, 26)
    if key_inv == -1:
        return "Invalid key! No modular inverse exists."
    plaintext = ''
    for ch in ciphertext:
        if ch.isalpha():
            base = ord('A') if ch.isupper() else ord('a')
            p = (ord(ch) - base) * key_inv % 26
            plaintext += chr(p + base)
        else:
            plaintext += ch
    return plaintext

# Main program
def main():
    print("Multiplicative Cipher (mod 26)")
    try:
        key = int(input("Enter key (must be coprime with 26): "))
    except ValueError:
        print("Invalid input! Key must be an integer.")
        return

    if gcd(key, 26) != 1:
        print("Invalid key! Key must be coprime with 26.")
        return

    choice = input("Encrypt or Decrypt? (e/d): ").lower()
    text = input("Enter text: ")

    if choice == 'e':
        result = encrypt(text, key)
        print("Encrypted text:", result)
    elif choice == 'd':
        result = decrypt(text, key)
        print("Decrypted text:", result)
    else:
        print("Invalid choice!")

if __name__ == "__main__":
    main()
