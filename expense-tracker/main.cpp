#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* include:
	- add expense with amount, description, and date
	- update an expense
	- delete an expense
	- view all expenses
	- view a summary of all expenses
	- view summary for specific timeframe (month/year)
	*/

struct dateStruct { //-> could do this as vector tbh
	int day;
	int month;
	int year;
};

struct expense {
	string name;
	float amount;
	string description;
	dateStruct date;
};

vector<expense> expenses; // vector to store all expenses

void displayMenu()
{
	cout << "\n\tmenu\n";
	cout << "[1] add expense\n";
	cout << "[2] view expenses\n";
	cout << "[3] update an expense\n";
	cout << "[4] delete expense\n";
	cout << "[5] view total expense summary\n";
	cout << "[6] view expense summary for timeframe\n";
	cout << "[7] exit\n";
	cout << "choice: ";
}

void addExpense()
{
	expense newExpense;

	cout << "\nenter expense name: ";
	cin >> newExpense.name;
	cin.ignore();

	cout << "\nenter expense amount: ";
	cin >> newExpense.amount;
	cin.ignore();

	cout << "\nenter expense description: ";
	getline(cin, newExpense.description);

	cout << "\nenter expense date (dd mm yyyy): ";
	cin >> newExpense.date.day >> newExpense.date.month >> newExpense.date.year;
	cin.ignore();

	expenses.push_back(newExpense);

	cout << "\nexpense added successfully!\n";
}

void viewExpenses()
{
	if (expenses.empty())
	{
		cout << "\nno expenses to display.\n";
		return;
	}

	cout << "\nall expenses:\n";

	for (size_t i = 0; i < expenses.size(); ++i)
	{
		cout << "expense " << i + 1 << ": " << expenses[i].name << "\n";
		cout << "amount: £" << expenses[i].amount << "\n";
		cout << "description: " << expenses[i].description << "\n";
		cout << "date: " << expenses[i].date.day << "/" << expenses[i].date.month << "/" << expenses[i].date.year << "\n\n";
	}
}

void updateExpenseName(int expenseIndex)
{
	string input;

	cout << "\ncurrent name: " << expenses[expenseIndex].name << "\n";
	cout << "enter new name: ";
	getline(cin, input);

	if (!input.empty())
	{
		expenses[expenseIndex].name = input;
	}
	else
	{
		cout << "\nname cannot be empty. keeping current name.\n";
	}

	cout << "\nexpense name updated successfully!\n";
}

void updateExpenseAmount(int expenseIndex)
{
	string input;

	cout << "\ncurrent amount: £" << expenses[expenseIndex].amount << "\n";
	cout << "enter new amount: ";
	getline(cin, input);

	if (!input.empty())
	{
		expenses[expenseIndex].amount = stof(input);
	}
	else
	{
		cout << "\namount cannot be empty. keeping current amount.\n";
	}

	cout << "\nexpense amount updated successfully!\n";
}

void updateExpenseDescription(int expenseIndex)
{
	string input;

	cout << "\ncurrent description: " << expenses[expenseIndex].description << "\n";
	cout << "enter new description: ";
	getline(cin, input);

	if (!input.empty())
	{
		expenses[expenseIndex].description = input;
	}
	else
	{
		cout << "\ndescription cannot be empty. keeping current description.\n";
	}

	cout << "\nexpense description updated successfully!\n";
}

void updateExpenseDate(int expenseIndex)
{
	string input;

	cout << "\ncurrent date: " << expenses[expenseIndex].date.day << "/" << expenses[expenseIndex].date.month << "/" << expenses[expenseIndex].date.year << "\n";
	cout << "enter new date (dd mm yyyy): ";
	getline(cin, input);

	if (!input.empty())
	{
		sscanf_s(input.c_str(), "%d %d %d", &expenses[expenseIndex].date.day, &expenses[expenseIndex].date.month, &expenses[expenseIndex].date.year);
	}
	else
	{
		cout << "\ndate cannot be empty. keeping current date.\n";
	}

	cout << "\nexpense date updated successfully!\n";
}

void updateExpense()
{
	if (expenses.empty())
	{
		cout << "\nno expenses to update.\n";
		return;
	}

	int expenseIndex;

	cout << "\nenter the expense number to update: ";
	cin >> expenseIndex;
	cin.ignore();

	if (expenseIndex < 1 || expenseIndex > expenses.size())
	{
		cout << "\ninvalid expense number.\n";
		return;
	}

	expense &exp = expenses[expenseIndex - 1];
	cout << "\nupdating expense " << expenseIndex << ":\n";

	int choice;

	cout << "what value would you like to update?\n";
	cout << "[1] name\n";
	cout << "[2] amount\n";
	cout << "[3] description\n";
	cout << "[4] date\n";
	cout << "choice: ";

	cin >> choice;
	cin.ignore();

	if (choice < 1 || choice > 4)
	{
		cout << "\ninvalid choice, please choose again: \n";
		cin >> choice;
		cin.ignore();
		return;
	}

	switch (choice)
	{
	case 1:
		updateExpenseName(expenseIndex - 1);
		break;
	case 2:
		updateExpenseAmount(expenseIndex - 1);
		break;
	case 3:	
		updateExpenseDescription(expenseIndex - 1);
		break;
	case 4:
		updateExpenseDate(expenseIndex - 1);
		break;
	default:
		break;
	}
}

void deleteExpense()
{
	if (expenses.empty())
	{
		cout << "\nno expenses to delete.\n";
		return;
	}

	int expenseIndex;

	viewExpenses();

	cout << "\nenter the expense number to delete: ";
	cin >> expenseIndex;
	cin.ignore();

	if (expenseIndex < 1 || expenseIndex > expenses.size())
	{
		cout << "\ninvalid expense number.\n";
		return;
	}

	expenses.erase(expenses.begin() + expenseIndex - 1);

	cout << "\nexpense deleted successfully!\n";
}

void viewTotalExpenseSummary()
{
	if (expenses.empty())
	{
		cout << "\nno expenses to summarize.\n";
		return;
	}

	float total = 0.0f;

	for (const auto &exp : expenses)
	{
		total += exp.amount;
	}

	cout << "\ntotal expenses amount: £" << total << "\n";
}

void viewExpenseSummaryForTimeframe()
{
	if (expenses.empty())
	{
		cout << "\nno expenses to summarize.\n";
		return;
	}

	int month, year;

	float total = 0.0f;

	cout << "\nenter month and year (mm yyyy): ";
	cin >> month >> year;
	cin.ignore();

	for (const auto &exp : expenses)
	{
		if (exp.date.month == month && exp.date.year == year)
		{
			total += exp.amount;
		}
	}

	cout << "\ntotal expenses amount for " << month << "/" << year << ": £" << total << "\n";
}

int main()
{
	int userChoice;

	while (true)
	{
		displayMenu();

		cin >> userChoice;
		cin.ignore();

		switch (userChoice)
		{
		case 1:
			addExpense();
			break;
		case 2:
			viewExpenses();
			break;
		case 3:
			updateExpense();
			break;
		case 4:
			deleteExpense();
			break;
		case 5:
			viewTotalExpenseSummary();
			break;
		case 6:
			viewExpenseSummaryForTimeframe();
			break;
		case 7:
			system("clear");
			return 0;
			break;
		default:
			cout << "\ninvalid choice, please try again! ";
			userChoice = 0;
			break;
		}
	}

	return 0;

}