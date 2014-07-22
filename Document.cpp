#include "Document.h"

// CONSTRUCTORS
Document::Document(){}
Document::~Document(){}

// EXPORTERS
/*  */
void Document::saveMisspelled(string save_choice)
{
	ofstream out_file;
	string file_choice = save_choice;

	out_file.open(file_choice);
	out_file << printMisspelled();
}

/*  */

// IMPORTERS
/* This function assists the Load Functions with knowing how many times to iterate the getline() functions by prereading the file. */
int Document::getFileWords(string file_choice)
{
	ifstream in_file;
	in_file.open(file_choice);
	int word_count = 0;
	string temp_word;

	do
	{
		in_file >> temp_word;
		word_count++;
		//cout << word_count;
	} 
	while (!in_file.fail());

	word_count--;
	//cout << word_count;
	return word_count;
}

///* Loads a text file and adds the misspelled words of that file to a map called misspelled_words. */
bool Document::loadDocument(string document_choice, Dictionary& dictionary_choice)
{
	cout << "-- Document Started! -- " << endl;
	bool is_working = true;
	ifstream in_file;
	string file_choice = document_choice;

	cout << "File name to load: \t" << file_choice << endl;
	//cin >> file_choice;
	in_file.open(file_choice);

	int word_count = 0;
	word_count = getFileWords(file_choice);

	if (hasWords(word_count) == false)
	{
		is_working = false;
		return is_working;
	}
	else
	{			
		//for (int i = word_count; i > 0; i = i--)
		string line_in;
		stringstream s;
		int line_num = 1;

		while (getline(in_file, line_in))
		{
			s << convert_nonalpha(line_in);
			//cout << line_num << endl;
			string word_in, word_lowercase = "";
			
			while (s >> word_in)
			{
				//cout << word_in << endl;
				// Converts letters to lowercase.
				word_lowercase = convert_lowercase2(word_in);
				// Checks to make sure it's in the dictionary if it is then it adds it to a list of words it already has checked before.
				if (checkValidWord(word_lowercase, dictionary_choice) == true)
				{
					//cout << word_lowercase << " ok." << endl;
				}
				else
				{
					misspelled_words[word_lowercase].push_back(line_num);
				}
			}
			s.clear();
			line_num++;
		}
		//is_working = true;
		cout << "-- Dictionary Ended! -- " << endl;
	}

	cout << endl;

	return is_working;
}

// MUTATORS
/* Converts words in the document to lowercase letters. */
//string Document::convert_lowercase(string word_in)
//{
	//string word_out = word_in;
	//bool is_word = false;
	
	//for (int i = 0; i < word_out.length(); i++)
	//{
		//if (isalpha(word_out[i]) == false)
		//{
			//char temp = word_out[i];
			//for (int j = i; j < word_out.length() - 1; j++)
			//{
				//word_out[j] = word_out[j + 1];	
			//}
			//word_out[word_out.length() - 1] = temp;
			//if (i == word_out.length() - 1)
			//{
				//string temp_word;
				//temp_word = word_out.substr(0, word_out.length() - 1);
				//word_out = temp_word;
			//}
		//}
		//else
		//{
			//word_out[i] = tolower(word_out[i]);
			//is_word = true;
		//}
		
		//if (is_word == false)
		//{
			//word_out = "x00000x";
		//}
	//}

	//return word_out;
//}

string Document::convert_nonalpha(string line_in)
{
	string line_out = line_in;
	char* temp_char = " ";

	for (int i = 0; i < line_out.length(); i++)
	{
		if (isalpha(line_out[i]) == false)
		{
			line_out[i] = *temp_char;
		}
	}

	return line_out;
}


string Document::convert_lowercase2(string word_in)
{
	string word_out = word_in;

	for (int i = 0; i < word_out.length(); i++)
	{
		if (isalpha(word_out[i]) == false)
		{
			//word_out[i] = *temp_char;
			//string temp_word;
			//temp_word = word_out.substr(0, word_out.length() - 1);
			//word_out = temp_word;
		}
		else
		{
			word_out[i] = tolower(word_out[i]);
		}
	}

	return word_out;
}

/*  */

// PRINTERS
/*  */
string Document::printMisspelled()
{
	map<string, vector<int>>::iterator iter;
	stringstream ss;
	int index = 0;
	//cout << "Misspelled words: " << endl;
	//cout << "Size = " << misspelled_words.size() << endl;
	for (iter = misspelled_words.begin(); iter != misspelled_words.end(); iter++)
	{
		//cout << (iter->first) << ": ";
		ss << (iter->first) << ": ";
		for (int i = 0; i < iter->second.size(); i++)
		{
			//cout << (iter->second[i]);
			ss << (iter->second[i]);
			if (i != iter->second.size() - 1)
			{
				//cout << " ";
				ss << " ";
			}
		}
		index++;
		//cout << endl;
		ss << endl;
	}
	//cout << endl;
	return ss.str();
}

/*  */

// VALIDATORS
/* Tells how many lines a text file has before it is read in. */
bool Document::hasWords(int word_count)
{
	bool has_words = false;
	if (word_count == 0)
	{
		cout << "This is an empty file." << endl;
	}
	else
	{
		has_words = true;
	}
	return has_words;
}

bool Document::hasLines(int line_count)
{
	bool has_lines = false;
	if (line_count == 0)
	{
		cout << "This is an empty file." << endl;
	}
	else
	{
		has_lines = true;
	}
	return has_lines;
}

/* Finds out if the word is already in the map or not. */
bool Document::checkValidWord(string word_in, Dictionary& dictionary_choice)
{
	bool is_valid = false;

	if (dictionary_choice.findWord(word_in) == true)
	{
		is_valid = true;
	}

	return is_valid;
}


/*  */
bool Document::checkDuplicate(string word_in)
{
	cout << "Check Duplicate Started." << endl;
	bool is_duplicate = false;

	if (checkMisspelledWord(word_in) != "blank")
	{
		is_duplicate = true;
	}

	cout << "Check Duplicate Ended." << endl;
	return is_duplicate;
}

string Document::checkMisspelledWord(string word_in)
{
	string word = "blank";
	
	//if(misspelled_words.find(word_in) != misspelled_words.end)
	//{
		//map<string, vector<int>>::iterator iter=*misspelled_words.find(word_in);
		////string test=iter
		//return *iter;
	//}

	map<string, vector<int>>::iterator iter;
	int index = 0;
	for (iter = misspelled_words.begin(); iter != misspelled_words.end(); iter++)
	{
		if (iter->first == word_in)
		{
			word = iter->first;
		}
		index++;
	}

	return word;
}
