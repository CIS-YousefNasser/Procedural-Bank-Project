#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "HelperFunctions.h"
namespace UserFunctions {

	struct stUser {
		std::string username = "";
		std::string password = "";
		short permissions = 0;
		bool deleteAccount = false;
		bool updateAccount = false;

	};
	enum enAllowAccess {
		all = -1, showOptionCode = 1, addOptionCode = 2, deleteOptionCode = 4, searchOptionCode = 8, updateOptionCode = 16, transactionsOptionCode = 32, usersMenuCode = 64

	};
	short enAllowAccessToInt(enAllowAccess choice) {
		return static_cast<short>(choice);
	}
	short GetPermissions() {
		//enMainMenuChoices choices;
		int permission = 0;
		char choice;
		choice = HelperFunctions::ReadChar("Do you want to give permission to everything y / n:");
		if (toupper(choice) == 'Y') {
			permission = enAllowAccessToInt(enAllowAccess::all);
		}
		else {
			if (tolower(HelperFunctions::ReadChar("Allow user to Show Clients Data:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::showOptionCode);//2^0
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to Add New Clients:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::addOptionCode);//2^1
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to Delete A Clients:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::deleteOptionCode);//2^2
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to Find Clients:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::searchOptionCode);//2^3
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to Update Clients:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::updateOptionCode);//2^4
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to use Transaction:")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::transactionsOptionCode);//2^5
			}
			if (tolower(HelperFunctions::ReadChar("Allow user to Manage users :")) == 'y') {
				permission = permission | enAllowAccessToInt(enAllowAccess::usersMenuCode);//2^6
			}
		}

		return permission;
	}
	bool IsAllowedAccess(short userPermissonNumber, short choiceNumber) {
		return ((choiceNumber & userPermissonNumber) == choiceNumber);
	}

	std::string AskForUsername() {
		return HelperFunctions::ReadString("Username:");

	};
	std::string AskForPassword() {
		return HelperFunctions::ReadString("Password:");

	};
	stUser ReadUserData() {
		stUser user;
		user.username = AskForUsername();
		user.password = AskForPassword();
		return user;
	}
	void PrintUserData(const stUser& clientData) {
		std::cout << "|" << std::setw(24) << std::left << clientData.username;
		std::cout << "|" << std::setw(29) << std::left << clientData.password;
		std::cout << "|" << clientData.permissions;
		std::cout << std::endl;
	}

	std::string UserDataLine(const stUser& user, const std::string& delimiter) {
		std::string line = "";
		line += user.username + delimiter;
		line += user.password + delimiter;
		line += std::to_string(user.permissions);
		return line;
	}
	stUser UserDataLineToData(const std::string& dataLine, const std::string& delimiter) {
		stUser userData;
		std::vector<std::string> data = HelperFunctions::StringSplit(dataLine, delimiter);
		userData.username = data[0];
		userData.password = data[1];
		userData.permissions = std::stoi(data[2]);
		return userData;
	}
	std::vector<stUser> LoadUserDataFromFile(const std::string& usersDirectory, const std::string& delimiter) {
		std::vector<std::string>vDataLines = HelperFunctions::GetStringFromFile(usersDirectory);
		std::vector<stUser> usersData;
		for (std::string& i : vDataLines) {
			usersData.push_back(UserDataLineToData(i, delimiter));
		}
		return usersData;
	}
	bool CheckUserByUsername(const std::string& targetUsername, const std::string& usersdirectory, const std::string& delimiter, stUser& searchedForUser, std::vector<stUser>& usersData) {

		for (stUser& i : usersData) {
			if (i.username == targetUsername)
			{
				searchedForUser = i;
				return true;
			}
		}

		return false;
	}
	bool CheckUserByUsername(const std::string& targetUsername, const std::string& usersdirectory, const std::string& delimiter, std::vector<stUser>& usersData) {

		for (stUser& i : usersData) {
			if (i.username == targetUsername)
			{
				return true;
			}
		}

		return false;
	}
	bool IsUsernameAndPasswordCorrect(const std::string& directory, const std::string& delimiter, stUser& enteredUser, std::vector<stUser>& usersData) {

		for (const stUser& i : usersData) {
			if (i.username == enteredUser.username && i.password == enteredUser.password)
			{
				enteredUser = i;
				return true;
			}
		}
		return false;
	}
	void AddUserDataToFile(const std::string& usersDirectory, const stUser& userData, const std::string& delimiter) {
		HelperFunctions::AddLineToFile(usersDirectory, UserDataLine(userData, delimiter));
	}
	stUser ReadUserData(const std::string& directory, const std::string& delimiter, std::vector<stUser>& usersData) {

		stUser userData;
		do {
			userData.username = HelperFunctions::ReadString("Please Enter username: ");
			if (CheckUserByUsername(userData.username, directory, delimiter, usersData)) {
				std::cout << "This  username is used" << std::endl;
			}
			else
				break;
		} while (true);
		userData.password = HelperFunctions::ReadString("Please Enter Password: ");
		userData.permissions = GetPermissions();
		return userData;
	}
	void AddUsersData(const std::string& delimiter, const std::string& usersDirectory, std::vector<stUser>& usersData) {
		char continueLoop = 'y';
		stUser userData;
		do {
			userData = ReadUserData(usersDirectory, delimiter, usersData);
			AddUserDataToFile(usersDirectory, userData, delimiter);

			std::cout << "Add new User? :";
			std::cin >> continueLoop;
		} while (continueLoop == 'y' || continueLoop == 'Y');
		usersData = LoadUserDataFromFile(usersDirectory, delimiter);

	}



	void UpdateUserData(stUser& user) {
		user.password = AskForPassword();
		user.permissions = GetPermissions();

	}

	void SaveUsersChanges(std::vector<stUser>& usersData, const std::string& delimiter, const std::string& usersDirectory) {
		std::string line = "";
		std::ofstream file;
		file.open(usersDirectory, std::ios::out);
		for (stUser& i : usersData)
		{

			if (i.deleteAccount == true) {
				continue;
			}
			if (i.updateAccount == true) {
				UpdateUserData(i);
			}

			line = UserDataLine(i, delimiter);
			file << line << std::endl;
		}
		file.close();
	}
	bool MarkUserForUpdate(const std::string& targetUsername, std::vector<stUser>& usersData) {

		for (stUser& u : usersData)
		{
			if (u.username == targetUsername) {
				u.updateAccount = true;
				return true;
			}
		}
		return false;
	}
	void UpdateUser(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, std::vector<stUser>& usersData) {
		char areYouSure = 'n';

		stUser searchedForUser;

		std::cout << std::endl;
		if (CheckUserByUsername(targetUsername, usersDirectory, delimiter, searchedForUser, usersData)) {
			PrintUserData(searchedForUser);
			std::cout << "Are You sure you Want to Update This User y/n:";
			std::cin >> areYouSure;
			if (std::tolower(areYouSure) == 'y')
			{
				MarkUserForUpdate(targetUsername, usersData);
				SaveUsersChanges(usersData, delimiter, usersDirectory);
				usersData = LoadUserDataFromFile(usersDirectory, delimiter);
				std::cout << "Update Complete" << std::endl;

			}
			else
				std::cout << "update Cancelled" << std::endl;
		}
		else
			std::cout << "User was not found" << std::endl;

	}
	bool MarkUserForDeletion(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, std::vector<stUser>& usersData) {

		for (stUser& u : usersData)
		{
			if (u.username == targetUsername) {
				u.deleteAccount = true;
				return true;
			}
		}
		return false;

	}
	void DeleteUser(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, stUser& currentUser, std::vector<stUser>& usersData) {
		char areYouSure = 'n';

		stUser searchedforUser;

		std::cout << std::endl;
		if (CheckUserByUsername(targetUsername, usersDirectory, delimiter, searchedforUser, usersData)) {
			if (searchedforUser.username == "Admin") {
				std::cout << "Admin cannot be deleted" << std::endl;
			}
			else if (searchedforUser.username == currentUser.username)
			{
				if (tolower(HelperFunctions::ReadChar("Are you sure you want to delete your own account (y/n):")) == 'y') {

					currentUser.deleteAccount = true;
				}

			}
			else {
				PrintUserData(searchedforUser);
				std::cout << "Are You sure you Want to Delete This User  (y/n):";
				std::cin >> areYouSure;
				if (std::tolower(areYouSure) == 'y')
				{
					MarkUserForDeletion(targetUsername, usersDirectory, delimiter, usersData);
					SaveUsersChanges(usersData, delimiter, usersDirectory);
					usersData = LoadUserDataFromFile(usersDirectory, delimiter);
					std::cout << "Deletion Complete" << std::endl;

				}
				else
					std::cout << "Deletion Cancelled" << std::endl;
			}

		}
		else
			std::cout << "User was not found" << std::endl;

	}
	void PrintSearchedForUser(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, std::vector<stUser>& usersData) {
		stUser targetUserData;
		if (CheckUserByUsername(targetUsername, usersDirectory, delimiter, targetUserData, usersData))
		{
			PrintUserData(targetUserData);
		}
		else
			std::cout << "Account number(" << targetUsername << ") Not found" << std::endl;
	}

	stUser Login(const std::string& usersDirectory, const std::string& delimiter, std::vector<stUser>& usersData) {
        // for testing purposes only. 
		std::cout << "Admin username:Admin,password:1233" << std::endl;
		// In production, these should be hashed and hidden.
		HelperFunctions::LoginHeader();
		stUser loginAttempt = ReadUserData();

		while (!IsUsernameAndPasswordCorrect(usersDirectory, delimiter, loginAttempt, usersData)) {
			system("cls");
			HelperFunctions::InvalidScreen();
			HelperFunctions::WaitAndClear();
			HelperFunctions::LoginHeader();
			loginAttempt = ReadUserData();

		}
		system("cls");
		HelperFunctions::WelcomeScreen();
		HelperFunctions::WaitAndClear();
		return loginAttempt;
	}
	



	void PrintUsersDetailsHeader(int usersCounter) {
		std::cout << std::right << std::setw(50) << " Users List (" << usersCounter << ")" << "Users(s)" << std::endl;
		std::cout << "_________________________________________________________________________________________\n" << std::endl;
		std::cout << std::left << std::setw(25) << "| Username" << std::left << std::setw(30) << "|password" << "| Permissions" << std::endl;
		std::cout << "_________________________________________________________________________________________\n" << std::endl;
	}
	void PrintAllUsersDetails(const std::string& directory, const std::string& delimiter, std::vector<stUser>& usersData) {
		;
		PrintUsersDetailsHeader(usersData.size());
		for (int i = 0; i < usersData.size(); i++) {
			PrintUserData(usersData[i]);
		}
		std::cout << "_________________________________________________________________________________________" << std::endl;


	}


}