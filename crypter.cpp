#include "crypter.h"
#include <string>
#include <fstream>


void Crypter::Crypt() {
	std::string password;
	password.reserve(64);
	for (int i = 0; i < 64; i++) {
		switch (std::rand() % 3) {
		case 0:
			password += static_cast<char>(std::rand() % 10 + '0');
			break;
		case 1:
			password += static_cast<char>(std::rand() % 26 + 'A');
			break;
		case 2:
			password += static_cast<char>(std::rand() % 26 + 'a');
			break;
		}
	}
	std::string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in students.txt -out students.txt.enc -pass pass:";
	command += password;
	system(command.c_str());
	remove("students.txt");
	std::ofstream file;
	file.open("key.txt", std::ios::binary);
	file.write(password.c_str(), 65);
	file.close();
	command = "openssl\\bin\\openssl.exe pkeyutl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
	system(command.c_str());
	remove("key.txt");
}


void Crypter::Decrypt() {
	std::string password;
	std::string command = "openssl\\bin\\openssl.exe pkeyutl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
	system(command.c_str());
	remove("key.txt.enc");
	std::ifstream file;
	password.resize(64);
	file.open("key.txt", std::ios::binary);
	file.read(password.data(), 64);
	file.close();
	remove("key.txt");
	command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in students.txt.enc -out students.txt -pass pass:";
	command += password;
	system(command.c_str());
	remove("students.txt.enc");
}
