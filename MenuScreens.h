#pragma once
#include <iostream>
namespace MenuScreens {
	void MainMenuScreen() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(30) << "Main Menu" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "\t\t" << "[1]Show Client list" << std::endl;
		std::cout << "\t\t" << "[2]add New Client" << std::endl;
		std::cout << "\t\t" << "[3]Delete Client " << std::endl;
		std::cout << "\t\t" << "[4]Find Client" << std::endl;
		std::cout << "\t\t" << "[5]Update Client " << std::endl;
		std::cout << "\t\t" << "[6]Transactions " << std::endl;
		std::cout << "\t\t" << "[7]Manage Users " << std::endl;
		std::cout << "\t\t" << "[8]logout " << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
	}
	void TransactionsMenuScreen() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(31) << "Transactions Menu" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "\t\t" << "[1]Deposit" << std::endl;
		std::cout << "\t\t" << "[2]Withdraw" << std::endl;
		std::cout << "\t\t" << "[3]Total Balances " << std::endl;
		std::cout << "\t\t" << "[4]return to main menu " << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
	}
	void ManageUserMenuScreen() {
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::right << std::setw(31) << "Manage User Menu" << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << "\t\t" << "[1]List Users" << std::endl;
		std::cout << "\t\t" << "[2]Add New User" << std::endl;
		std::cout << "\t\t" << "[3]Delete User " << std::endl;
		std::cout << "\t\t" << "[4]Update User " << std::endl;
		std::cout << "\t\t" << "[5]Find User " << std::endl;
		std::cout << "\t\t" << "[6]Return To Main Menu " << std::endl;
		std::cout << "____________________________________________________" << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
	}
}