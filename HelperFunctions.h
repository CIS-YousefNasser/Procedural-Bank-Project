#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <Windows.h>
namespace HelperFunctions {

	//Reading Input Helper Functions
	std::string ReadString(std::string message) {

		std::string text;
		std::cout << message;
		std::getline(std::cin >> std::ws, text);
		return text;
	}
	char ReadChar(std::string message) {

		char character;
		std::cout << message;
		std::cin >> character;
		return character;
	}
	double ReadDouble(std::string message) {
		double number;
		std::cout << message;
		std::cin >> number;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "please Enter a number:";
			std::cin >> number;
		}
		return number;
	}
	int ReadInt(std::string message) {
		int number;
		std::cout << message;
		std::cin >> number;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "please Enter a number:";
			std::cin >> number;
		}
		return number;
	}



	std::vector<std::string> StringSplit(std::string text, std::string delimiter) {
		std::string word = "";
		int pos = 0;
		std::vector<std::string> container;

		while ((pos = text.find(delimiter)) != std::string::npos) {
			word = text.substr(0, pos);
			if (word != "") {
				container.push_back(word);
			}
			text.erase(0, pos + delimiter.length());
		}
		if (text != "") {
			container.push_back(text);
		}
		return container;
	}
    //file handling functions
	void AddLineToFile(const std::string directory, const std::string& text) {
		std::ofstream file;
		file.open(directory, std::ios::app | std::ios::out);
		file << text << std::endl;
		file.close();
	}
	void NewLinesToFile(const std::string directory, const std::vector<std::string>& newDataLines) {
		std::ofstream file;
		file.open(directory, std::ios::out);
		for (std::string DataLine : newDataLines)
			file << DataLine << std::endl;
		file.close();
	}
	std::vector<std::string> GetStringFromFile(const std::string& directory) {
		std::ifstream file;
		std::vector<std::string> vDataLines;
		std::string line;
		file.open(directory, std::ios::in);
		if (file.is_open()) {
			while (std::getline(file, line)) {
				vDataLines.push_back(line);
			}
			file.close();
			return vDataLines;
		}
		file.close();

	}
    //screen Control functions
	void ResetScreen() {
		system("pause");
		system("cls");
	}
	void WaitAndClear() {
		Sleep(1000);
		system("cls");
	}

	//Helper screens
	void WelcomeScreen() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(29) << "Welcome!!" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;

	}
	void InvalidScreen() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(29) << "Invalid!!" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
	}
	void AccessDeniedScreen() {
		std::cout << "\n------------------------" << std::endl;
		std::cout << "Access Denied" << std::endl;
		std::cout << "\nPlease Contact admin" << std::endl;
		std::cout << "------------------------" << std::endl;
	}

	//helper headers
	void LoginHeader() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(28) << "Login" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
	}
	void AddNewClientScreen() {
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::right << std::setw(19) << "Add New Client" << std::endl;
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "\n";
	};
	void UpdateClientScreen() {
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::right << std::setw(19) << "Update Client" << std::endl;
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "\n";
	};
	void SearchClientScreen() {
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::right << std::setw(19) << "Search for Client" << std::endl;
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "\n";
	};
	void DeleteClientScreen() {
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::right << std::setw(19) << "Delete Client" << std::endl;
		std::cout << "_________________________" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "\n";
	};
}