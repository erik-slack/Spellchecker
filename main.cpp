#include <iostream>
#include <iomanip>
#include "Dictionary.h"
#include "Document.h"
using namespace std;


int main(int argc, char* argv[])
{
	string dictionary_choice = argv[1];
	string document_choice = argv[2];
	string save_choice = argv[3];

	Dictionary dic1;
	Document doc1;

	dic1.loadDictionary(dictionary_choice);
	cout << "Load Dictionary complete" << endl;
	//dic1.printDictionary();

	doc1.loadDocument(document_choice, dic1);
	cout << "Load Document complete" << endl;
	//doc1.printMisspelled();

	doc1.saveMisspelled(save_choice);
	cout << "Save Misspelled complete" << endl;
	
	//cin.get();
	return 0;
}
