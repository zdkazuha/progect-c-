#include <iostream>
#include "struct.h"
using namespace std;

int main()
{

	int choice;


	Source* sources = nullptr;
	int size = 0;
	while (true)
	{
		cout << "\t [1] - fill db; \n\t [2] - print; \n\t [3] - add; \n\t [4] - remove; \n\t [5] - Organizing by fields; \n\t [6] - Search: clarity of the given book \n\t [7] - Sample \n\t [8] - Calculation: number of books of individual categories \n\t [9] - Correction: publication of summaries about the newspaper for a certain year \n\t [0] - exit; \n\t\t Enter :: ";
		cin >> choice;

		if (choice == 0) {
			cout << "\tThe program has ended!!!";
			break;
		}
		switch (choice)
		{
		case 1: {
			fillDB();
			break;
		}
		case 2: {
			clear(sources, size);
			sources = read(size);
			if (sources == nullptr) {
				continue;
			}
			printAll(sources, size);
			cout << "\n\n";
			break;
		}
		case 3: {
			Source tmp;
			editSource(tmp);
			save(tmp);
			break;
		}
		case 4: {
			printAll(sources, size, true);
			int id;
			cout << "Enter #id :: ";
			cin >> id;

			remove_(sources, size, id);
			break;
		}
		case 5: {
			printAllinorder(sources, size);
			break;
		}
		case 6: {
			searchforavailability(sources, size);
			break;
		}
		case 7: {
			Sample(sources, size);
			break;
		}
		case 8: {
			Calculationofbooksofcertaincategories(sources, size);
			break;
		}
		case 9: {
			printAll(sources, size, true);
			cout << "\n\n";
			int id = (deleteNewpaper(sources, size)) - 1;
			remove_(sources, size, id);
			break;
		}
		}
	}
}