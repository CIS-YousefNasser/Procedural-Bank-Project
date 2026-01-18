
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <Windows.h>

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

	return number;
}
int valdiateNumber(std::string message) {
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
int GetRandomNumber(int from, int to) {
	int randomNumber = rand() % (to - from + 1) + from;
	return randomNumber;
}

std::string JoinString(std::vector<std::string> vector, std::string delimiter) {
	std::string text = "";
	for (std::string i : vector)
	{
		text += i + delimiter;
	}
	return text.substr(0, text.length() - delimiter.length());
}

std::string JoinString(std::string arr[], int length, std::string delimiter) {
	std::string text = "";
	for (int i = 0; i < length; i++)
	{
		text += arr[i] + delimiter;
	}
	return text.substr(0, text.length() - delimiter.length());
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
enum enTrim {
	Trim, TrimLeft, TrimRight
};
std::string TrimLeft1(std::string text) {
	for (int i = 0; i < text.length(); i++) {
		if (text[i] != ' ') {
			return text.substr(i, text.length() - i);
		}
	}
	return "";
}
std::string TrimRight1(std::string text) {
	for (int i = text.length() - 1; i >= 0; i--) {
		if (text[i] != ' ') {
			return text.substr(0, i + 1);

		}
	}
	return "";
}
std::string TrimString(std::string text, enTrim trim = enTrim::Trim) {
	switch (trim) {
	case enTrim::Trim:
	case enTrim::TrimLeft:
		text = TrimLeft1(text);
		break;
	case enTrim::TrimRight:
		text = TrimRight1(text);
		break;
	default:
		std::cout << "HOW DID YOU DO THAT" << std::endl;

	}
	return text;
}
std::string ReverseWordsString(std::string text) {
	std::string reversedString = "";
	for (int i = text.length() - 1; i >= 0; i--) {
		reversedString += text[i];
	}
	return reversedString;
}
std::string ReverseString(std::string text) {
	std::vector<std::string>vtext = StringSplit(text, " ");
	std::string reversedString = "";
	for (int i = vtext.size() - 1; i >= 0; i--) {
		reversedString += vtext[i] + " ";
	}
	return reversedString;
}
std::string CaptalizeLettersInSentence(std::string sentence) {

	for (int i = 0; i < sentence.length(); i++) {
		sentence[i] = std::toupper(sentence[i]);
	}
	return sentence;
}
std::string ReplaceWordInString(std::string text, std::string target, std::string replacement, bool caseMatch = true) {
	std::vector<std::string>vtext = StringSplit(text, " ");
	std::string temp;
	if (!caseMatch) {
		target = CaptalizeLettersInSentence(target);

	}
	std::string ChangedText = "";
	for (int i = 0; i < vtext.size(); i++) {
		if (caseMatch)
		{
			if (vtext[i] == target)
				vtext[i] = replacement;
		}
		else
		{
			temp = CaptalizeLettersInSentence(vtext[i]);
			if (temp == target)
				vtext[i] = replacement;
		}

		ChangedText += vtext[i] + " ";
	}
	ChangedText.pop_back();
	return ChangedText;
}
std::string FastReplaceWordInString(std::string text, std::string target, std::string replacement) {
	int pos = text.find(target);
	while (pos != std::string::npos) {
		text.replace(pos, target.length(), replacement);
		pos = text.find(target);
	}
	return text;
}
std::string RemovePunct(std::string& text) {
	std::string noPunctString = "";
	for (char& i : text) {
		if (!ispunct(i))
		{
			noPunctString += i;
		}
	}
	return noPunctString;
}

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
stClient ClientDataLineToData(const std::string& dataLine, const std::string& dilimiter) {
	stClient clientData;
	std::vector<std::string> data = StringSplit(dataLine, dilimiter);
	clientData.accountNumber = data[0];
	clientData.pincode = data[1];
	clientData.name = data[2];
	clientData.phoneNumber = data[3];
	clientData.accountBalance = std::stod(data[4]);
	return clientData;
}
std::vector<stClient> LoadDataFromFile(std::string directory, const std::string& dilimiter) {
	std::vector<std::string>vDataLines = GetStringFromFile(directory);
	std::vector<stClient> clientData;
	for (std::string i : vDataLines) {
		clientData.push_back(ClientDataLineToData(i, dilimiter));
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
		clientData.accountNumber = ReadString("Please Enter Account Number: ");
		if (CheckClientByAccountNumber(clientData.accountNumber, directory, delimiter, foundClient, clientsData)) {
			std::cout << "This  Account Already Exists under the name " << foundClient.name << std::endl;
		}
		else
			break;
	} while (true);
	clientData.pincode = ReadString("Please Enter Pincode: ");
	clientData.name = ReadString("Please Enter Name: ");
	clientData.phoneNumber = ReadString("Please Enter Phone Number: ");
	clientData.accountBalance = ReadDouble("Please Enter Account Balance: ");
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
	clientData.pincode = ReadString("pincode:");
	clientData.name = ReadString("Name:");
	clientData.phoneNumber = ReadString("phoneNumber:");
	clientData.accountBalance = ReadDouble("account Balance:");

}
void UpdateClientInFile(std::vector<stClient>& client, const std::string& delimiter, const std::string& directory) {
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
void AddDataToFile(const std::string& directory, const stClient& clientData, const std::string& dilimiter) {
	AddLineToFile(directory, ClientDataLine(clientData, dilimiter));
}

void AddClientsDataToFile(const std::string& dilimiter, const std::string& directory, std::vector<stClient>& clientsData) {
	char continueLoop = 'y';
	stClient clientData;
	do {
		clientData = ReadClientData(directory, dilimiter, clientsData);
		AddDataToFile(directory, clientData, dilimiter);

		std::cout << "Add new Client? :";
		std::cin >> continueLoop;
	} while (continueLoop == 'y' || continueLoop == 'Y');
	clientsData = LoadDataFromFile(directory, dilimiter);

}
void DeleteClient(const std::string& targetUsername, const std::string& usersDirectory, const std::string& delimiter, std::vector<stClient>& clientsData) {
	char areYouSure = 'n';

	stClient searchedForClient;

	std::cout << std::endl;
	if (CheckClientByAccountNumber(targetUsername, usersDirectory, delimiter, searchedForClient, clientsData)) {
		PrintClientData(searchedForClient);
		std::cout << "Are You sure you Want to Delete This Client (i think he is pretty cool)" << std::endl;
		std::cin >> areYouSure;
		if (std::tolower(areYouSure) == 'y')
		{
			MarkClientForDeletion(targetUsername, usersDirectory, delimiter, clientsData);
			UpdateClientInFile(clientsData, delimiter, usersDirectory);
			clientsData = LoadDataFromFile(usersDirectory, delimiter);
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
			UpdateClientInFile(clientsData, delimiter, directory);
			clientsData = LoadDataFromFile(directory, delimiter);
			std::cout << "Update Complete" << std::endl;

		}
		else
			std::cout << "update Cancelled" << std::endl;
	}
	else
		std::cout << "Client was not found" << std::endl;

}
void mainMenuScreen() {
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
std::string AskForAccountNumber() {
	return ReadString("Please Enter account number:");

};
std::string AskForUsername() {
	return ReadString("Please Enter username:");

};
struct stUser {
	std::string username = "";
	std::string Password = "";
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
	choice = ReadChar("Do you want to give permission to everything y / n:");
	if (toupper(choice) == 'Y') {
		permission = enAllowAccessToInt(enAllowAccess::all);
	}
	else {
		if (tolower(ReadChar("Allow user to Show Clients Data:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::showOptionCode);//2^0
		}
		if (tolower(ReadChar("Allow user to Add New Clients:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::addOptionCode);//2^1
		}
		if (tolower(ReadChar("Allow user to Delete A Clients:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::deleteOptionCode);//2^2
		}
		if (tolower(ReadChar("Allow user to Find Clients:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::searchOptionCode);//2^3
		}
		if (tolower(ReadChar("Allow user to Update Clients:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::updateOptionCode);//2^4
		}
		if (tolower(ReadChar("Allow user to use transcation:")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::transactionsOptionCode);//2^5
		}
		if (tolower(ReadChar("Allow user to Manage users :")) == 'y') {
			permission = permission | enAllowAccessToInt(enAllowAccess::usersMenuCode);//2^6
		}
	}

	return permission;
}
bool IsAllowedAccess(short userPermissonNumber, short choiceNumber) {
	return ((choiceNumber & userPermissonNumber) == choiceNumber);
}
void AccessDeniedScreen() {
	std::cout << "\n------------------------" << std::endl;
	std::cout << "Access Denied" << std::endl;
	std::cout << "\nPlease Contact admin" << std::endl;
	std::cout << "------------------------" << std::endl;



}
stUser ReadUserData() {
	stUser user;
	std::cout << "Please Enter Username:";
	std::getline(std::cin >> std::ws, user.username);
	std::cout << "Please Enter password:";
	std::getline(std::cin >> std::ws, user.Password);
	return user;
}
void PrintUserData(const stUser& clientData) {
	std::cout << "|" << std::setw(24) << std::left << clientData.username;
	std::cout << "|" << std::setw(29) << std::left << clientData.Password;
	std::cout << "|" << clientData.permissions;
	std::cout << std::endl;
}

std::string UserDataLine(const stUser& user, const std::string& delimiter) {
	std::string line = "";
	line += user.username + delimiter;
	line += user.Password + delimiter;
	line += std::to_string(user.permissions);
	return line;
}
stUser UserDataLineToData(const std::string& dataLine, const std::string& dilimiter) {
	stUser userData;
	std::vector<std::string> data = StringSplit(dataLine, dilimiter);
	userData.username = data[0];
	userData.Password = data[1];
	userData.permissions = std::stoi(data[2]);
	return userData;
}
std::vector<stUser> LoadUserDataFromFile(const std::string& usersDirectory, const std::string& delimiter) {
	std::vector<std::string>vDataLines = GetStringFromFile(usersDirectory);
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
		if (i.username == enteredUser.username && i.Password == enteredUser.Password)
		{
			enteredUser = i;
			return true;
		}
	}
	return false;
}
void AddUserDataToFile(const std::string& usersDirectory, const stUser& userData, const std::string& delimiter) {
	AddLineToFile(usersDirectory, UserDataLine(userData, delimiter));
}
stUser ReadUserData(const std::string& directory, const std::string& delimiter, std::vector<stUser>& usersData) {

	stUser userData;
	do {
		userData.username = ReadString("Please Enter username: ");
		if (CheckUserByUsername(userData.username, directory, delimiter, usersData)) {
			std::cout << "This  username is used" << std::endl;
		}
		else
			break;
	} while (true);
	userData.Password = ReadString("Please Enter Password: ");
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
	user.Password = ReadString("Password:");
	user.permissions = GetPermissions();

}

void UpdateUserInFile(std::vector<stUser>& usersData, const std::string& delimiter, const std::string& usersDirectory) {
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
			UpdateUserInFile(usersData, delimiter, usersDirectory);
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
			if (tolower(ReadChar("Are you sure you want to delete your own account (y/n):")) == 'y') {

				currentUser.deleteAccount = true;
			}

		}
		else {
			PrintUserData(searchedforUser);
			std::cout << "Are You sure you Want to Delete This User (i think he is pretty cool) y/n:";
			std::cin >> areYouSure;
			if (std::tolower(areYouSure) == 'y')
			{
				MarkUserForDeletion(targetUsername, usersDirectory, delimiter, usersData);
				UpdateUserInFile(usersData, delimiter, usersDirectory);
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
void LoginScreen() {
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << std::right << std::setw(28) << "Login" << std::endl;
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}
void WelcomeScreen() {
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << std::right << std::setw(29) << "Welcome!!" << std::endl;
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;

	WaitAndClear();
}
void InvalidScreen() {
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << std::right << std::setw(29) << "Invalid!!" << std::endl;
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;

	WaitAndClear();
}
stUser Login(const std::string& usersDirectory, const std::string& delimiter, std::vector<stUser>& usersData) {

	LoginScreen();
	stUser loginAttempt = ReadUserData();
	ProcessingScreen();

	while (!IsUsernameAndPasswordCorrect(usersDirectory, delimiter, loginAttempt, usersData)) {
		system("cls");
		InvalidScreen();
		LoginScreen();
		loginAttempt = ReadUserData();
		ProcessingScreen();
	}
	WelcomeScreen();
	return loginAttempt;
}
enum enMainMenuChoices {
	showOption = 1, addOption = 2, deleteOption = 3, searchOption = 4, updateOption = 5, transactionsOption = 6, usersMenu = 7, logout = 8
};
enum enTranscationsMenu {
	deposit = 1, withdraw = 2, totalBalances = 3, returnToMainMenu = 4
};
enMainMenuChoices NumberToMainMenuChoicesEnum(int choice) {
	return static_cast<enMainMenuChoices>(choice);
}
enTranscationsMenu NumberToTransactionMenuChoicesEnum(int choice) {
	return static_cast<enTranscationsMenu>(choice);
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
double AmountToDeposit(std::string message) {
	double amount;
	std::cout << message;
	std::cin >> amount;
	return amount;
}
bool DepositOption(std::vector<stClient>& clientsData, const std::string& targetAccountNumber, const std::string& directory, const const std::string& delimiter) {
	for (stClient& client : clientsData)
	{
		if (targetAccountNumber == client.accountNumber)
		{
			PrintClientData(client);
			client.accountBalance = client.accountBalance + AmountToDeposit("How much to deposit:");
			UpdateClientInFile(clientsData, delimiter, directory);
			return true;
		}
	}

	std::cout << "Client with number :" << targetAccountNumber << " was not found" << std::endl;
	return false;
}

bool WithDrawOption(std::vector<stClient>& clientsData, const std::string& targetAccountNumber, const std::string& directory, const std::string delimiter) {
	for (stClient& client : clientsData) {
		if (targetAccountNumber == client.accountNumber)
		{
			PrintClientData(client);
			double withdrawAmount;
			do {
				withdrawAmount = AmountToDeposit("How much to withdraw:");
				if (client.accountBalance < withdrawAmount)
					std::cout << "The amount you entered is bigger than what the account has" << std::endl;
				if (withdrawAmount < 0)
					std::cout << "haha :|" << std::endl;

			} while (client.accountBalance < withdrawAmount || withdrawAmount < 0);

			client.accountBalance = client.accountBalance - withdrawAmount;
			UpdateClientInFile(clientsData, delimiter, directory);
			return true;
		}

	}
	std::cout << "Client with number :" << targetAccountNumber << " was not found" << std::endl;
	return false;

}
double CompineAllBalances(std::vector<stClient>& clientsData, const std::string& directory, const std::string delimiter) {
	double totalOfAllBalances = 0;
	for (stClient& client : clientsData) {
		totalOfAllBalances += client.accountBalance;
	}
	return totalOfAllBalances;
}
void ShowTotalBalances(std::vector<stClient>& clientsData, const std::string& directory, const std::string delimiter) {
	ShortPrintAllClientsDetails(directory, delimiter, clientsData);
	std::cout << std::right << std::setw(57) << "|total:" << CompineAllBalances(clientsData, directory, delimiter) << std::endl;
}
void ResetScreen() {
	system("pause");
	system("cls");
}
void TranscationOptions(std::string& directory, std::string& delimiter, std::vector<stClient>& clientsData) {
	enTranscationsMenu choice;
	do
	{
		TransactionsMenuScreen();
		choice = NumberToTransactionMenuChoicesEnum(valdiateNumber("Choose what you want to do:"));
		system("cls");
		switch (choice) {

		case enTranscationsMenu::deposit:
			DepositOption(clientsData, AskForAccountNumber(), directory, delimiter);
			ResetScreen();
			break;
		case enTranscationsMenu::withdraw:
			WithDrawOption(clientsData, AskForAccountNumber(), directory, delimiter);
			ResetScreen();
			break;
		case enTranscationsMenu::totalBalances:
			ShowTotalBalances(clientsData, directory, delimiter);
			ResetScreen();
			break;
		}

	} while (choice != enTranscationsMenu::returnToMainMenu);
}


enum enManageUserMenu {
	usersList = 1, addNewUser = 2, deleteUser = 3, updateUser = 4, findUser = 5, returnToMain = 6,
};
enManageUserMenu NumberToManageUserEnum(int choice) {
	return static_cast<enManageUserMenu>(choice);
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
void UserOptions(std::string& usersDirectory, std::string& delimiter, stUser& currentUser, std::vector<stUser>& usersData) {
	enManageUserMenu choice;
	do
	{
		if (currentUser.deleteAccount == true)
		{
			break;
		}
		ManageUserMenuScreen();
		choice = NumberToManageUserEnum(valdiateNumber("Choose what you want to do:"));
		system("cls");
		switch (choice) {

		case enManageUserMenu::usersList:

			PrintAllUsersDetails(usersDirectory, delimiter, usersData);
			ResetScreen();
			break;
		case enManageUserMenu::addNewUser:
			AddUsersData(delimiter, usersDirectory, usersData);
			ResetScreen();
			break;
		case enManageUserMenu::deleteUser:
			DeleteUser(AskForUsername(), usersDirectory, delimiter, currentUser, usersData);

			ResetScreen();
			break;
		case enManageUserMenu::updateUser:
			UpdateUser(AskForUsername(), usersDirectory, delimiter, usersData);
			ResetScreen();
			break;
		case enManageUserMenu::findUser:
			PrintSearchedForUser(AskForUsername(), usersDirectory, delimiter, usersData);
			ResetScreen();
			break;
		}

	} while (choice != enManageUserMenu::returnToMain);
}

void MainMenuOptions(std::string& usersDirectory, std::string& clientsDirectory, std::string& delimiter, stUser& currentUser, std::vector<stUser>& usersData, std::vector<stClient>& clientsData) {
	enMainMenuChoices choice;

	do {
		if (currentUser.deleteAccount == true)
		{
			MarkUserForDeletion(currentUser.username, usersDirectory, delimiter, usersData);
			UpdateUserInFile(usersData, delimiter, usersDirectory);
			usersData = LoadUserDataFromFile(usersDirectory, delimiter);
			system("cls");
			std::cout << "Its sad to see you go :(" << std::endl;
			break;
		}
		mainMenuScreen();
		choice = NumberToMainMenuChoicesEnum(valdiateNumber("Choose what you want to do:"));
		system("cls");
		switch (choice) {

		case enMainMenuChoices::showOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::showOptionCode)))
				PrintAllClientsDetails(clientsDirectory, delimiter, clientsData);
			else
				AccessDeniedScreen();

			ResetScreen();
			break;
		case enMainMenuChoices::addOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::addOptionCode)))
			{
				AddNewClientScreen();
				AddClientsDataToFile(delimiter, clientsDirectory, clientsData);
			}
			else
				AccessDeniedScreen();

			ResetScreen();
			break;
		case enMainMenuChoices::deleteOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::deleteOptionCode)))
			{
				DeleteClientScreen();
				DeleteClient(AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
			}
			else
				AccessDeniedScreen();

			ResetScreen();
			break;
		case enMainMenuChoices::searchOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::searchOptionCode)))
			{
				SearchClientScreen();
				PrintSearchedForClient(AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
			}
			else
				AccessDeniedScreen();

			ResetScreen();
			break;
		case enMainMenuChoices::updateOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::updateOptionCode)))
			{
				UpdateClientScreen();
				UpdateClient(AskForAccountNumber(), clientsDirectory, delimiter, clientsData);
			}
			else
				AccessDeniedScreen();
			ResetScreen();
			break;
		case enMainMenuChoices::transactionsOption:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::transactionsOptionCode)))
			{
				TranscationOptions(clientsDirectory, delimiter, clientsData);
			}
			else
				AccessDeniedScreen();
			break;
		case enMainMenuChoices::usersMenu:
			if (currentUser.permissions == -1 || IsAllowedAccess(currentUser.permissions, enAllowAccessToInt(enAllowAccess::usersMenuCode)))
			{
				UserOptions(usersDirectory, delimiter, currentUser, usersData);
			}
			else
				AccessDeniedScreen();
		}


	} while (choice != enMainMenuChoices::logout);

}
void StartBankApp(std::string usersDirectory, std::string clientsDirectory) {
	std::string delimiter = "#//#";
	std::vector<stClient>clientsData = LoadDataFromFile(clientsDirectory, delimiter);
	std::vector<stUser>usersData = LoadUserDataFromFile(usersDirectory, delimiter);

	do {
		stUser currentUser = Login(usersDirectory, delimiter, usersData);
		MainMenuOptions(usersDirectory, clientsDirectory, delimiter, currentUser, usersData, clientsData);
	} while (true);
}
int main()
{
	srand(time(NULL));
	std::string clientDirectory = "Clients.txt";
	std::string usersDirectory = "User.txt";
	std::string delimiter = "#//#";
	StartBankApp(usersDirectory, clientDirectory);
	return 0;
}
