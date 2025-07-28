
# RSA Encryption and Decryption Program

This C++ program implements RSA encryption and decryption. It allows users to encrypt and decrypt files using RSA keys generated from two prime numbers. The program ensures that the primes are valid, performs modular exponentiation for efficient encryption and decryption, and provides a user-friendly interface for file operations.

## Features

- **RSA Encryption**: Encrypt a text file with a public key.
- **RSA Decryption**: Decrypt an encrypted file with the private key.
- **Prime Validation**: Ensures that the keys provided are prime numbers.
- **Efficient Modular Exponentiation**: Uses exponentiation by squaring for faster encryption and decryption of large numbers.
- **File Handling**: Reads plaintext from a file, encrypts it, and saves it to a new encrypted file. Decrypts an encrypted file back to plaintext.
<br>
<hr>
## Prerequisites

- A C++ compiler (such as `g++`).
- <hr>
- Basic understanding of how RSA encryption works.

## How to Use
<hr>

### 1. Clone the Repository
Clone this repository to your local machine using:
bash
git clone https://github.com/RAP7255/RSA-Algorithm-Encryption.git

### 2. Compile the Program
Navigate to the project directory and compile the code:

g++ rsa.cpp -o rsa
3. Run the Program
Run the executable:

bash
Copy code
./rsa
