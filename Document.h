#pragma once
#include <iostream>
#include <map>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "Dictionary.h"
using namespace std;


class Document
{
private:
	// DATA
	map<string, vector<int>> misspelled_words;
	vector<string> document_inline;
	
public:
	// CONSTRUCTORS
	Document();
	~Document();

	// ANALYZERS
	/*  */
	string checkMisspelledWord(string word_in);
	/*  */

	// EXPORTERS
	/*  */
	void saveMisspelled(string save_choice);
	/*  */

	// IMPORTERS
	int getFileWords(string file_choice);
	///* Imports command line argument #1 and makes each 4 lines into a student in the all_students vector. */
	bool loadDocument(string document_choice, Dictionary& dictionary_choice);
	///*  */
	void notVerifiedMispelled();
	//int getFileLines(string file_choice);

	// MUTATORS
	/* Converts words in the document to lowercase letters. */
	//string convert_lowercase(string word_in);
	/* Converts words in the document to lowercase letters. */
	string convert_lowercase2(string word_in);
	/* Removes symbols and numbers and replaces them with blank spaces. */	
	string convert_nonalpha(string line_in);

	// PRINTERS
	/*  */
	string printMisspelled();
	/*  */

	// VALIDATORS
	/*  */
	bool hasWords(int word_count);
	bool hasLines(int line_count);
	bool checkDuplicate(string word_in);
	bool checkValidWord(string word_in, Dictionary& dictionary_choice);
	/*  */
};
