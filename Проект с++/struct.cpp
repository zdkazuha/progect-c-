#include "struct.h"

void fillDB()
{
	int tmp;
	cout << "Enter number of source --> "; cin >> tmp;
	for (size_t i = 0; i < tmp; i++)
	{
		Source temp;
		editSource(temp);
		save(temp);
	}
}

void editSource(Source& source)
{
	int tmp;
	cout << "\tEnter type fo source ([1] - BOOK, [2] - MAGAZINE, [3] - NEWSPAPER) --> ";
	cin >> tmp;
	source.type = (Type)tmp;

	cin.ignore();
	cout << "\tEnter title  --> "; cin.getline(source.name, SIZE);
	if (source.type == Type::BOOK)
	{
		cout << "\tEnter author --> "; cin.getline(source.author, SIZE);
		cout << "\tEnter genre  --> "; cin.getline(source.genre, SIZE);
	}
	cout << "\tEnter year   --> "; cin >> source.year;
}

void print(Source source, int index)
{
	string line = "==================================";
	cout << "\n\t" << line << " " << (index != -1 ? "#" + to_string(index) + " " : "") << (source.type == Type::BOOK ? "BOOK" : (source.type == Type::MAGAZINE) ? "MAGAZINE" : "NEWSPAPER") << " " << line << endl;
	cout << "\t\t Title  :: " << source.name << endl;
	if (source.type == Type::BOOK)
	{
		cout << "\t\t Author :: " << source.author << endl;
		cout << "\t\t Genge  :: " << source.genre << endl;
	}
	cout << "\t\t Year   :: " << source.year << endl;
}

void printAll(Source* sources, const int& size, bool numeric){
	for (size_t i = 0; i < size; i++)
	{
		numeric ? print(sources[i], i + 1) : print(sources[i]);
	}
}

void save(Source source, string fname)
{
	ofstream file(fname, ios_base::app | ios_base::binary);
	if (!file.is_open()) {
		cout << "Error" << endl;
		return;
	}

	file.write((char*)&source, sizeof(Source));
	file.close();
}

Source* read(int& size, string fname)
{
	ifstream file(fname);
	if (!file.is_open()) {
		cout << "Error file read" << endl;
		return nullptr;
	}

	file.seekg(0, ios_base::end);
	if (file.tellg() == 0)
	{
		cout << "Error file read" << endl;
		return nullptr;
	}
	size = file.tellg() / sizeof(Source);
	file.seekg(0);

	Source* tmp = new Source[size];
	for (size_t i = 0; i < size; i++)
	{
		file.read((char*)&tmp[i], sizeof(Source));
	}
	file.close();
	return tmp;
}

void clear(Source*& sources, int& size)
{
	if (sources != nullptr)
	{
		delete[] sources;
		sources = nullptr;
		size = 0;
	}
}

void remove_(Source* sources, const size_t& size, const int& id, string fname){
	remove(fname.c_str());
	for (size_t i = 0; i < size - 1; i++)
	{
		i < (id - 1) ? save(sources[i]) : save(sources[i + 1]);
	}
}

void printAllinorder(Source* sources, const int&size, bool numeric) {
	string line = "==================================";

	for (size_t i = 0; i < size; i++) {
		if (sources[i].type == Type::BOOK) {
			cout << "\n\t" << line << " " << (numeric ? "#" + to_string(i + 1) + " " : "") << "BOOK " << line << endl;
			cout << "\t\t Title  :: " << sources[i].name << endl;
			cout << "\t\t Author :: " << sources[i].author << endl;
			cout << "\t\t Genre  :: " << sources[i].genre << endl;
			cout << "\t\t Year   :: " << sources[i].year << endl;
		}
	}

	for (size_t i = 0; i < size; i++) {
		if (sources[i].type == Type::MAGAZINE) {
			cout << "\n\t" << line << " " << (numeric ? "#" + to_string(i + 1) + " " : "") << "MAGAZINE " << line << endl;
			cout << "\t\t Title  :: " << sources[i].name << endl;;
			cout << "\t\t Year   :: " << sources[i].year << endl;
		}
	}

	for (size_t i = 0; i < size; i++) {
		if (sources[i].type == Type::NEWSPAPER) {
			cout << "\n\t" << line << " " << (numeric ? "#" + to_string(i + 1) + " " : "") << "NEWSPAPER " << line << endl;
			cout << "\t\t Title  :: " << sources[i].name << endl;
			cout << "\t\t Year   :: " << sources[i].year << endl;
		}
	}
}

void searchforavailability(Source* sources, const int& size, bool numeric) {
	string line = "==================================";
	int option = 0;
	string name;
	string author;

	cout << "\tSearch by [1] name or [2] author :: ";
	cin >> option;
	cin.ignore();

	bool found = false;

	if (option == 1) {
		cout << "\tEnter name of the source :: ";
		getline(cin, name);

		for (size_t i = 0; i < size; i++) {
			if (sources[i].type == Type::BOOK && toLowerCase(string(sources[i].name)) == toLowerCase(name)) {
				cout << "\tSo, the source called :: " << name << " is in existence." << endl;
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "\tSo, there is no source called :: " << name << endl;
			cout << "\n\n";
		}
	}
	else if (option == 2) {
		cout << "\tEnter author of the source :: ";
		getline(cin, author);

		for (size_t i = 0; i < size; i++) {
			if (sources[i].type == Type::BOOK && toLowerCase(string(sources[i].author)) == toLowerCase(author)) {
				cout << "\tSo, sources by author :: " << author << " exist." << endl;
				cout << "\n\n";
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "\tSo, there is no source by author :: " << author << endl;
			cout << "\n\n";
		}
	}
	else {
		cout << "\tInvalid option selected!" << endl;
		cout << "\n\n";
	}
}

void Calculationofbooksofcertaincategories(Source* sources, const int& size) {
	string genre;
	int counter_genre = 0;
	cin.ignore();
	cout << "\tYou want to know the number of books by genre :: "; getline(cin, genre);
	for (size_t i = 0; i < size; i++) {
		if (sources[i].type == Type::BOOK && toLowerCase(sources[i].genre) == toLowerCase(genre)) {
				counter_genre++;
		}
	}
	cout << "\n\tBooks by category " << genre << " number of books :: " << counter_genre << endl;
}

int deleteNewpaper(Source* sources, const int& size) {
	string line = "\n==================================";
	int year = 0;
	int id = 0;
	cout << "\tEnter the year for which you want to delete the newspaper :: "; cin >> year;
	for (size_t i = 0; i < size; i++)
	{
		if (sources[i].type == Type::NEWSPAPER && sources[i].year == year) {
			i = id;
		}
		return id;
	}

}

void Sample(Source* sources, const int& size) {
	int a = 0;
	string line = "==================================";
	int option = 0;
	cout << "\tChoose an option for action [1]books by the author XX(genre) [2]Magazines for a certain year :: "; cin >> option;
	if (option == 1) {
		string autor;
		cin.ignore();
		cout << "\tEnter autor :: "; getline(cin, autor);
		cout << "\n\n";

		for (size_t i = 0; i < size; i++)
		{
			if (sources[i].type == Type::BOOK && toLowerCase(sources[i].author) == toLowerCase(autor)) {
				cout << "\n\t" << line << " " << (1 ? "#" + to_string(i + 1) + " " : "") << "BOOK " << line << endl;
				cout << "\t\t Title  :: " << sources[i].name << endl;
				cout << "\t\t Genre  :: " << sources[i].genre << "\n\n";
			}
		}
	}
	if (option == 2) {
		int year = 0;
		cout << "\tEnter the year for which you want to find magazines :: "; cin >> year;
		for (size_t i = 0; i < size; i++)
		{
			if (sources[i].type == Type::MAGAZINE && sources[i].year == year) {
				cout << "\n\t" << line << " " << (a ? "#" + to_string(i + 1) + " " : "") << "NEWSPAPER " << line << endl;
				cout << "\t\t Title  :: " << sources[i].name << endl;
				cout << "\t\t Year   :: " << sources[i].year << "\n\n";
			}
		}
	}
}

string toLowerCase(const string& input) {
	string result = input;
	for (char& c : result) {
		if (c >= 'A' && c <= 'Z') {
			c = c + 32;
		}
	}
	return result;
}