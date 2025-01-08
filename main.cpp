#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Function prototypes
int gcd(int a, int b);
int modInverse(int a, int m);
bool isPrime(int num);
int modExp(int base, int exp, int mod);

// Class for RSA encryption
class Encrypt {
private:
    int e, n;

public:
    Encrypt(int e, int n)
    {
        this->e = e;
        this->n = n;
    }

    string encrypt(const string& plaintext) {
        string ciphertext = "";
        for (char plainChar : plaintext) {
            int plainNum = (int)plainChar;
            int cipherNum = modExp(plainNum, e, n);
            ciphertext += to_string(cipherNum) + " ";
        }
        return ciphertext;
    }
};

// Class for RSA decryption
class Decrypt {
private:
    int d, n;

public:
    Decrypt(int d, int n) : d(d), n(n)
    {
        this->d = d;
        this->n = n;
    }

    string decrypt(const string& ciphertext) {
        string decryptedText = "";
        string numStr = "";
        for (char cipherChar : ciphertext) {
            if (cipherChar == ' ') {
                if (!numStr.empty()) {
                    int cipherNum = stoi(numStr);
                    int plainNum = modExp(cipherNum, d, n);
                    decryptedText += static_cast<char>(plainNum);
                    numStr = "";
                }
            } else {
                numStr += cipherChar;
            }
        }
        return decryptedText;
    }
};

// Function to calculate greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Return -1 if no modular inverse exists
}

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1)
        return false;
    if (num == 2)
        return true;
    if (num % 2 == 0)
        return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Efficient modular exponentiation (exponentiation by squaring)
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q; // Prime number 1 and 2
    int e, d, n;

    cout << "Welcome to RSA Encryption/Decryption Program!" << endl;

    // Step 1: User Input for p and q
    cout << "Enter the prime number p: ";
    cin >> p;
    if (!isPrime(p)) {
        cout << "p is not a valid prime number!" << endl;
        return 1;
    }
    cout << "Enter the prime number q: ";
    cin >> q;
    if (!isPrime(q)) {
        cout << "q is not a valid prime number!" << endl;
        return 1;
    }

    // Step 2: Compute RSA Modulus and Totient
    n = p * q;
    int phi = (p - 1) * (q - 1);

    // Step 3: Find a valid public exponent e
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            break;
        }
    }

    // Step 4: Compute private exponent d
    d = modInverse(e, phi);
    if (d == -1) {
        cout << "No modular inverse exists for e. Exiting." << endl;
        return 1;
    }

    cout << "Public key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;

    char choice;

    do {
        // Display menu
        cout << "\nMenu:" << endl;
        cout << "1. Encrypt a file" << endl;
        cout << "2. Decrypt a file" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1, 2, or 3): ";
        cin >> choice;

        if (choice == '1') {
            // Prompt user to enter filename for encryption
            string fileName;
            cout << "Enter file name to encrypt (e.g., input.txt): ";
            cin >> fileName;

            // Read plaintext from file
            ifstream inputFile(fileName);
            if (!inputFile) {
                cerr << "Error opening input file." << endl;
                continue;
            }

            string line, plaintext = "";
            while (getline(inputFile, line)) {
                plaintext += line + "\n";
            }
            inputFile.close();

            // Encrypt the plaintext
            Encrypt encryptor(e, n);
            string ciphertext = encryptor.encrypt(plaintext);

            // Save encrypted text to file
            string encryptedFilePath = fileName.substr(0, fileName.find_last_of('.')) + ".ciphertext";
            ofstream encryptedFile(encryptedFilePath);
            if (!encryptedFile) {
                cerr << "Error creating encrypted file." << endl;
                continue;
            }
            encryptedFile << ciphertext;
            encryptedFile.close();

            cout << "Encryption complete. Encrypted file saved as: " << encryptedFilePath << endl;
        } 
        else if (choice == '2') {
            // Prompt user to enter filename for decryption
            string fileName;
            cout << "Enter file name to decrypt (e.g., encrypted.ciphertext): ";
            cin >> fileName;

            // Read encrypted text from file
            ifstream encryptedFile(fileName);
            if (!encryptedFile) {
                cerr << "Error opening encrypted file." << endl;
                continue;
            }

            string line, encryptedText = "";
            while (getline(encryptedFile, line)) {
                encryptedText += line + " ";
            }
            encryptedFile.close();

            // Decrypt the ciphertext
            Decrypt decryptor(d, n);
            string decryptedText = decryptor.decrypt(encryptedText);

            // Save decrypted text to a file
            string decryptedFilePath = fileName.substr(0, fileName.find_last_of('.')) + "_decrypted.txt";
            ofstream decryptedFile(decryptedFilePath);
            if (!decryptedFile) {
                cerr << "Error creating decrypted file." << endl;
                continue;
            }
            decryptedFile << decryptedText;
            decryptedFile.close();

            cout << "Decryption complete. Decrypted file saved as: " << decryptedFilePath << endl;
        } 
        else if (choice == '3') {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please enter '1', '2', or '3'." << endl;
        }
    } while (true);

    return 0;
}
