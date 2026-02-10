#pragma once
#include "MenuScreens.h"
#include "UserFunctions.h"
#include "ClientFunctions.h"
#include "HelperFunctions.h"
namespace MenuOptions {

	enum enMainMenuChoices {
		showOption = 1, addOption = 2, deleteOption = 3, searchOption = 4, updateOption = 5, transactionsOption = 6, usersMenu = 7, userLogout = 8
	};
	enum enTransactionsMenu {
		deposit = 1, withdraw = 2, totalBalances = 3, returnToMainMenu = 4
	};
	enMainMenuChoices NumberToMainMenuChoicesEnum(int choice) {
		return static_cast<enMainMenuChoices>(choice);
	}
	enTransactionsMenu NumberToTransactionMenuChoicesEnum(int choice) {
		return static_cast<enTransactionsMenu>(choice);
	}

	void TransactionOptions(std::string& directory, std::string& delimiter, std::vector<ClientFunctions::stClient>& clientsData) {
		enTransactionsMenu choice;
		do
		{
			MenuScreens::TransactionsMenuScreen();
			choice = NumberToTransactionMenuChoicesEnum(HelperFunctions::ReadInt("Choose what you want to do:"));
			system("cls");
			switch (choice) {

			case enTransactionsMenu::deposit:
				DepositOption(clientsData, ClientFunctions::AskForAccountNumber(), directory, delimiter);
				HelperFunctions::ResetScreen();
				break;
			case enTransactionsMenu::withdraw:
				WithdrawOption(clientsData, ClientFunctions::AskForAccountNumber(), directory, delimiter);
				HelperFunctions::ResetScreen();
				break;
			case enTransactionsMenu::totalBalances:
				ShowTotalBalances(clientsData, directory, delimiter);
				HelperFunctions::ResetScreen();
				break;
			}

		} while (choice != enTransactionsMenu::returnToMainMenu);
	}

	enum enManageUserMenu {
		usersList = 1, addNewUser = 2, deleteUser = 3, updateUser = 4, findUser = 5, returnToMain = 6,
	};
	enManageUserMenu NumberToManageUserEnum(int choice) {
		return static_cast<enManageUserMenu>(choice);
	}
	void UserOptions(std::string& usersDirectory, std::string& delimiter, UserFunctions::stUser& currentUser, std::vector<UserFunctions::stUser>& usersData) {
		enManageUserMenu choice;
		do
		{
			if (currentUser.deleteAccount == true)
			{
				break;
			}
			MenuScreens::ManageUserMenuScreen();
			choice = NumberToManageUserEnum(HelperFunctions::ReadInt("Choose what you want to do:"));
			system("cls");
			switch (choice) {

			case enManageUserMenu::usersList:

				PrintAllUsersDetails(usersDirectory, delimiter, usersData);
				HelperFunctions::ResetScreen();
				break;
			case enManageUserMenu::addNewUser:
				AddUsersData(delimiter, usersDirectory, usersData);
				HelperFunctions::ResetScreen();
				break;
			case enManageUserMenu::deleteUser:
				DeleteUser(UserFunctions::AskForUsername(), usersDirectory, delimiter, currentUser, usersData);

				HelperFunctions::ResetScreen();
				break;
			case enManageUserMenu::updateUser:
				UpdateUser(UserFunctions::AskForUsername(), usersDirectory, delimiter, usersData);
				HelperFunctions::ResetScreen();
				break;
			case enManageUserMenu::findUser:
				PrintSearchedForUser(UserFunctions::AskForUsername(), usersDirectory, delimiter, usersData);
				HelperFunctions::ResetScreen();
				break;
			}

		} while (choice != enManageUserMenu::returnToMain);
	}
	void MainMenuOptions(std::string& usersDirectory, std::string& clientsDirectory, std::string& delimiter, UserFunctions::stUser& currentUser, std::vector<UserFunctions::stUser>& usersData, std::vector<ClientFunctions::stClient>& clientsData) {
		enMainMenuChoices choice;

		do {
			if (currentUser.deleteAccount == true)
			{
				UserFunctions::MarkUserForDeletion(currentUser.username, usersDirectory, delimiter, usersData);
				UserFunctions::SaveUsersChanges(usersData, delimiter, usersDirectory);
				usersData = UserFunctions::LoadUserDataFromFile(usersDirectory, delimiter);
				system("cls");
				std::cout << "Its sad to see you go :(" << std::endl;
				break;
			}
			MenuScreens::MainMenuScreen();
			choice = NumberToMainMenuChoicesEnum(HelperFunctions::ReadInt("Choose what you want to do:"));
			system("cls");
			switch (choice) {

			case enMainMenuChoices::showOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::showOptionCode)))
					ClientFunctions::PrintAllClientsDetails(clientsDirectory, delimiter, clientsData);
				else
					HelperFunctions::AccessDeniedScreen();

				HelperFunctions::ResetScreen();
				break;
			case enMainMenuChoices::addOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::addOptionCode)))
				{
					HelperFunctions::AddNewClientScreen();
					ClientFunctions::AddClientsDataToFile(delimiter, clientsDirectory, clientsData);
				}
				else
					HelperFunctions::AccessDeniedScreen();

				HelperFunctions::ResetScreen();
				break;
			case enMainMenuChoices::deleteOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::deleteOptionCode)))
				{
					HelperFunctions::DeleteClientScreen();
					ClientFunctions::DeleteClient(ClientFunctions::AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
				}
				else
					HelperFunctions::AccessDeniedScreen();

				HelperFunctions::ResetScreen();
				break;
			case enMainMenuChoices::searchOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::searchOptionCode)))
				{
					HelperFunctions::SearchClientScreen();
					ClientFunctions::PrintSearchedForClient(ClientFunctions::AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
				}
				else
					HelperFunctions::AccessDeniedScreen();

				HelperFunctions::ResetScreen();
				break;
			case enMainMenuChoices::updateOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::updateOptionCode)))
				{
					HelperFunctions::UpdateClientScreen();
					ClientFunctions::UpdateClient(ClientFunctions::AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
				}
				else
					HelperFunctions::AccessDeniedScreen();
				HelperFunctions::ResetScreen();
				break;
			case enMainMenuChoices::transactionsOption:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::transactionsOptionCode)))
				{
					TransactionOptions(clientsDirectory, delimiter, clientsData);
				}
				else
					HelperFunctions::AccessDeniedScreen();
				break;
			case enMainMenuChoices::usersMenu:
				if (currentUser.permissions == -1 || UserFunctions::IsAllowedAccess(currentUser.permissions, UserFunctions::enAllowAccessToInt(UserFunctions::enAllowAccess::usersMenuCode)))
				{
					UserOptions(usersDirectory, delimiter, currentUser, usersData);
				}
				else
					HelperFunctions::AccessDeniedScreen();
			}


		} while (choice != enMainMenuChoices::userLogout);

	}

}