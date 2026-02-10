
#include <vector>
#include "UserFunctions.h"
#include "ClientFunctions.h"
#include "HelperFunctions.h"
#include "MenuOptions.h"

void StartBankApp(std::string &usersDirectory,std::string &clientsDirectory) {
	std::string delimiter = "#//#";
	std::vector<ClientFunctions::stClient>clientsData = ClientFunctions::LoadClientsDataFromFile(clientsDirectory, delimiter);
	std::vector<UserFunctions::stUser>usersData = UserFunctions::LoadUserDataFromFile(usersDirectory, delimiter);

	do {
		UserFunctions::stUser currentUser = Login(usersDirectory, delimiter, usersData);
		MenuOptions::MainMenuOptions(usersDirectory, clientsDirectory, delimiter, currentUser, usersData, clientsData);
	} while (true);
}
int main()
{	
	std::string clientsDirectory = "Clients.txt";
	std::string usersDirectory = "Users.txt";

	/*stUser admin = UserDataLineToData("Admin#//#1233#//#-1", delimiter);
	AddUserDataToFile(usersDirectory, admin, delimiter);*/
	StartBankApp(usersDirectory, clientsDirectory);
	return 0;
}
