#pragma once
#include <string>
namespace ClientFunctions {
struct stClient {
	std::string name;
	std::string accountNumber;
	std::string pincode;
	std::string phoneNumber;
	double accountBalance = 0;
	bool deleteAccount = false;
	bool updateAccount = false;

};
std::string ClientDataLine(const stClient& clientData, const std::string& delimiter) {

	std::string line = "";
	line += clientData.accountNumber + delimiter;
	line += clientData.pincode + delimiter;
	line += clientData.name + delimiter;
	line += clientData.phoneNumber + delimiter;
	line += std::to_string(clientData.accountBalance);
	return line;

}

stClient ClientDataLineToData(const std::string& dataLine, const std::string& delimiter) {
	stClient clientData;
	std::vector<std::string> data = HelperFunctions::StringSplit(dataLine, delimiter);
	clientData.accountNumber = data[0];
	clientData.pincode = data[1];
	clientData.name = data[2];
	clientData.phoneNumber = data[3];
	clientData.accountBalance = std::stod(data[4]);
	return clientData;
}
std::vector<stClient> LoadClientsDataFromFile(std::string directory, const std::string& delimiter) {
	std::vector<std::string>vDataLines = HelperFunctions::GetStringFromFile(directory);
	std::vector<stClient> clientData;
	for (std::string i : vDataLines) {
		clientData.push_back(ClientDataLineToData(i, delimiter));
	}
	return clientData;
}

void PrintClientData(const stClient& clientData) {
	std::cout << "|" << std::setw(16) << std::left << clientData.accountNumber;
	std::cout << "|" << std::setw(9) << std::left << clientData.pincode;
	std::cout << "|" << std::setw(34) << std::left << clientData.name;
	std::cout << "|" << std::setw(18) << std::left << clientData.phoneNumber;

	std::cout << "|" << clientData.accountBalance;
	std::cout << std::endl;
}
void ShortPrintClientData(const stClient& clientData) {
	std::cout << "|" << std::setw(16) << std::left << clientData.accountNumber;
	std::cout << "|" << std::setw(32) << std::left << clientData.name;

	std::cout << "|" << clientData.accountBalance;
	std::cout << std::endl;
}





bool CheckClientByAccountNumber(const std::string& targetAccountNumber, const std::string& directory, const std::string& delimiter, stClient& searchedForClient, std::vector<stClient>& clientsData) {

	for (stClient& i : clientsData) {
		if (i.accountNumber == targetAccountNumber)
		{
			searchedForClient = i;
			return true;
		}
	}

	return false;
}
stClient ReadClientData(const std::string& directory, const std::string& delimiter, std::vector<stClient>& clientsData) {

	stClient clientData;
	stClient foundClient;
	do {
		clientData.accountNumber = HelperFunctions::ReadString("Please Enter Account Number: ");
		if (CheckClientByAccountNumber(clientData.accountNumber, directory, delimiter, foundClient, clientsData)) {
			std::cout << "This  Account Already Exists under the name " << foundClient.name << std::endl;
		}
		else
			break;
	} while (true);
	clientData.pincode = HelperFunctions::ReadString("Please Enter Pincode: ");
	clientData.name = HelperFunctions::ReadString("Please Enter Name: ");
	clientData.phoneNumber = HelperFunctions::ReadString("Please Enter Phone Number: ");
	clientData.accountBalance = HelperFunctions::ReadDouble("Please Enter Account Balance: ");
	return clientData;
}
bool MarkClientForDeletion(const std::string& targetAccountNumber, const std::string& directory, const std::string& delimiter, std::vector<stClient>& clients) {

	for (stClient& c : clients)
	{
		if (c.accountNumber == targetAccountNumber) {
			c.deleteAccount = true;
			return true;
		}
	}
	return false;
}
bool MarkClientForUpdate(const std::string& targetAccountNumber, std::vector<stClient>& clients) {

	for (stClient& c : clients)
	{
		if (c.accountNumber == targetAccountNumber) {
			c.updateAccount = true;
			return true;
		}
	}
	return false;
}
void UpdateClientData(stClient& clientData) {
	clientData.pincode = HelperFunctions::ReadString("pincode:");
	clientData.name = HelperFunctions::ReadString("Name:");
	clientData.phoneNumber = HelperFunctions::ReadString("phoneNumber:");
	clientData.accountBalance = HelperFunctions::ReadDouble("account Balance:");

}
void SaveClientsChanges(std::vector<stClient>& client, const std::string& delimiter, const std::string& directory) {
	std::string line = "";
	std::ofstream file;
	file.open(directory, std::ios::out);
	for (stClient& i : client)
	{

		if (i.deleteAccount == true) {
			continue;
		}
		if (i.updateAccount == true) {
			UpdateClientData(i);
		}

		line = ClientDataLine(i, delimiter);
		file << line << std::endl;
	}
	file.close();
}
void PrintSearchedForClient(const std::string& targetAccountNumber, const std::string& directory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	stClient targetClientData;
	if (CheckClientByAccountNumber(targetAccountNumber, directory, delimiter, targetClientData, clientsData))
	{
		PrintClientData(targetClientData);
	}
	else
		std::cout << "Account number(" << targetAccountNumber << ") Not found" << std::endl;
}



void PrintClientsDetailsHeader(int clientCounter) {
	std::cout << std::right << std::setw(50) << " CLient List (" << clientCounter << ")" << "Client(s)" << std::endl;
	std::cout << "_________________________________________________________________________________________\n" << std::endl;
	std::cout << std::left << std::setw(50) << "| Account Number | PinCode | Clients Name \t\t" << "| phone\t\t | Balance" << std::endl;
	std::cout << "_________________________________________________________________________________________\n" << std::endl;
}
void PrintAllClientsDetails(const std::string& directory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	;
	PrintClientsDetailsHeader(clientsData.size());
	for (int i = 0; i < clientsData.size(); i++) {
		PrintClientData(clientsData[i]);
	}
	std::cout << "_________________________________________________________________________________________" << std::endl;


}
void ShortPrintClientsDetailsHeader(int clientCounter) {
	std::cout << std::right << std::setw(50) << " CLient List (" << clientCounter << ")" << "Client(s)" << std::endl;
	std::cout << "_________________________________________________________________________________________\n" << std::endl;
	std::cout << std::left << std::setw(50) << "| Account Number | Clients Name " << "| Balance" << std::endl;
	std::cout << "_________________________________________________________________________________________\n" << std::endl;
}
void ShortPrintAllClientsDetails(const std::string& directory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	;
	ShortPrintClientsDetailsHeader(clientsData.size());
	for (int i = 0; i < clientsData.size(); i++) {
		ShortPrintClientData(clientsData[i]);
	}
	std::cout << "_________________________________________________________________________________________" << std::endl;


}
void AddDataToFile(const std::string& directory, const stClient& clientData, const std::string& delimiter) {
	HelperFunctions::AddLineToFile(directory, ClientDataLine(clientData, delimiter));
}

void AddClientsDataToFile(const std::string& delimiter, const std::string& directory, std::vector<stClient>& clientsData) {
	char continueLoop = 'y';
	stClient clientData;
	do {
		clientData = ReadClientData(directory, delimiter, clientsData);
		AddDataToFile(directory, clientData, delimiter);

		std::cout << "Add new Client? :";
		std::cin >> continueLoop;
	} while (continueLoop == 'y' || continueLoop == 'Y');
	clientsData = LoadClientsDataFromFile(directory, delimiter);

}
void DeleteClient(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	char areYouSure = 'n';

	stClient searchedForClient;

	std::cout << std::endl;
	if (CheckClientByAccountNumber(targetUsername, usersDirectory, delimiter, searchedForClient, clientsData)) {
		PrintClientData(searchedForClient);
		std::cout << "Are You sure you Want to Delete This Client (y/n):" << std::endl;
		std::cin >> areYouSure;
		if (std::tolower(areYouSure) == 'y')
		{
			MarkClientForDeletion(targetUsername, usersDirectory, delimiter, clientsData);
			SaveClientsChanges(clientsData, delimiter, usersDirectory);
			clientsData = LoadClientsDataFromFile(usersDirectory, delimiter);
			std::cout << "Deletion Complete" << std::endl;

		}
		else
			std::cout << "Deletion Cancelled" << std::endl;
	}
	else
		std::cout << "Client was not found" << std::endl;

}
void UpdateClient(const std::string& targetAccountNumber, const std::string& directory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	char areYouSure = 'n';

	stClient searchedForClient;

	std::cout << std::endl;
	if (CheckClientByAccountNumber(targetAccountNumber, directory, delimiter, searchedForClient, clientsData)) {
		PrintClientData(searchedForClient);
		std::cout << "Are You sure you Want to Update This Client" << std::endl;
		std::cin >> areYouSure;
		if (std::tolower(areYouSure) == 'y')
		{
			MarkClientForUpdate(targetAccountNumber, clientsData);
			SaveClientsChanges(clientsData, delimiter, directory);
			clientsData = LoadClientsDataFromFile(directory, delimiter);
			std::cout << "Update Complete" << std::endl;

		}
		else
			std::cout << "update Cancelled" << std::endl;
	}
	else
		std::cout << "Client was not found" << std::endl;

}



std::string AskForAccountNumber() {
	return HelperFunctions::ReadString("Please Enter account number:");

};


double AmountToDeposit(std::string message) {
	return HelperFunctions::ReadDouble(message);
}
bool DepositOption(std::vector<stClient>& clientsData, const std::string& targetAccountNumber, const std::string& directory, const const std::string& delimiter) {
	for (stClient& client : clientsData)
	{
		if (targetAccountNumber == client.accountNumber)
		{
			PrintClientData(client);
			client.accountBalance = client.accountBalance + AmountToDeposit("How much to deposit:");
			SaveClientsChanges(clientsData, delimiter, directory);
			return true;
		}
	}

	std::cout << "Client with number :" << targetAccountNumber << " was not found" << std::endl;
	return false;
}
double GetWithdrawAmount(const stClient& client) {
	double withdrawAmount;
	do {
		withdrawAmount = HelperFunctions::ReadInt("Amount to withdraw (Must be devisable by 5):");
		if (client.accountBalance < withdrawAmount)
			std::cout << "The amount you entered is bigger than what the account has" << std::endl;
		if (withdrawAmount < 0)
			std::cout << "haha :|" << std::endl;

	} while (client.accountBalance < withdrawAmount || withdrawAmount < 0);
	return withdrawAmount;
}
bool WithdrawOption(std::vector<stClient>& clientsData, const std::string& targetAccountNumber, const std::string& directory, const std::string delimiter) {
	for (stClient& client : clientsData) {
		if (targetAccountNumber == client.accountNumber)
		{
			PrintClientData(client);
			double withdrawAmount = GetWithdrawAmount(client);
			client.accountBalance = client.accountBalance - withdrawAmount;
			SaveClientsChanges(clientsData, delimiter, directory);
			return true;
		}

	}
	std::cout << "Client with number :" << targetAccountNumber << " was not found" << std::endl;
	return false;

}

double CombineAllBalances(std::vector<stClient>& clientsData, const std::string& directory, const std::string delimiter) {
	double totalOfAllBalances = 0;
	for (stClient& client : clientsData) {
		totalOfAllBalances += client.accountBalance;
	}
	return totalOfAllBalances;
}
void ShowTotalBalances(std::vector<stClient>& clientsData, const std::string& directory, const std::string delimiter) {
	ShortPrintAllClientsDetails(directory, delimiter, clientsData);
	std::cout << std::right << std::setw(57) << "|total:" << CombineAllBalances(clientsData, directory, delimiter) << std::endl;
}
}