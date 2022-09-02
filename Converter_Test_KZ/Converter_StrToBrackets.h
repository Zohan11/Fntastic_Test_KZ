#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Char types
enum class ECharType {Alphabet, Digit, SpecialChar, WhiteSpace, Invalid};

//Struct with applied char data
struct CharStruct
{
	CharStruct(char &InputChar, int &Index)
	{
		ObservedChar = InputChar;
		StrIndex = Index;
	}
	
	char ObservedChar; //Char itself
	int StrIndex = -1; //Char index in observed string on first occurence
};

//Converter of char symbols to brackets
class Converter_StrToBrackets
{
	
public:
	Converter_StrToBrackets(string& InputString) : _rObservedString(InputString)
	{

	}
	
	string &GetObservedString() { return _rObservedString; }
	void SetObservedString(string InputString) { _rObservedString = InputString; }

	//Converts observed string chars from converter instance to brackets
	void Convert()
	{
		while (_rObservedString.find("Exit") == string::npos)
		{
			cout << "Type some symbols or type Exit to quit\n";
			getline(cin, _rObservedString);

			if (_rObservedString.find("Exit") != string::npos)
			{
				return;
			}

			for (int i = 0; i < _rObservedString.length(); i++)
			{
				ECharType type = _assignCharType(_rObservedString[i]);
				if (type == ECharType::Invalid)
				{
					_rObservedString = _rObservedString[i] + "*is an invalid symbol*";
					break;
				}

				_assignRelevantCharStructData(type);
				_rObservedString[i] = _selectBracket(_rObservedString[i], i);
			}

			_clearStructs();
			cout << _rObservedString + "\n";
		}
	}

private:

	string &_rObservedString; //input string

	//Containers for unique chars of different types
	vector <CharStruct> _alphabet;
	vector <CharStruct> _digits;
	vector <CharStruct> _specialChars;
	vector <CharStruct> _whiteSpaces;

	vector <CharStruct> *_pCurrentCharStruct = &_alphabet; // will be assigned one of CharStructs

	//Selects ECharType from input char
	ECharType _assignCharType(char &InputChar)
	{
		ECharType returnType = ECharType::Invalid;

		if (isalnum(InputChar) || ((isalnum(InputChar)) && (isdigit(InputChar))))
		{
			if (isalpha(InputChar))
			{
				if (islower(InputChar)) InputChar = toupper(InputChar);

				returnType = ECharType::Alphabet;
			}
			else returnType = ECharType::Digit;

			return returnType;
		}

		else if (ispunct(InputChar)) return returnType = ECharType::SpecialChar;
		else if (isspace(InputChar)) return returnType = ECharType::WhiteSpace;

		return returnType;
	}

	//Selects charStruct to work with
	void _assignRelevantCharStructData(ECharType &InputCharType)
	{
		switch (InputCharType)
		{
			case ECharType::Alphabet:
				_pCurrentCharStruct = &_alphabet;
				break;

			case ECharType::Digit:
				_pCurrentCharStruct = &_digits;
				break;

			case ECharType::SpecialChar:
				_pCurrentCharStruct = &_specialChars;
				break;

			case ECharType::WhiteSpace:
				_pCurrentCharStruct = &_whiteSpaces;
				break;
			
			case ECharType::Invalid:
				break;
		}
	}

	//Selects a bracket to replace an input char and replaces if previously occured
	const char _selectBracket(char &InputChar, int &StrIndex)
	{
		char outputChar = '(';
		vector <CharStruct>& selectedCharStruct = *_pCurrentCharStruct;

		if (!selectedCharStruct.empty())
		{
			for (int i = 0; i < selectedCharStruct.size(); i++)
			{
				if (InputChar == selectedCharStruct[i].ObservedChar)
				{
					outputChar = ')';
					_rObservedString[selectedCharStruct[i].StrIndex] = ')';
					return outputChar;
				}
			}
		}

		selectedCharStruct.push_back(CharStruct(InputChar, StrIndex));

		return outputChar;
	}

	//Clear all symbol structs after converting
	void _clearStructs()
	{
		_alphabet.clear();
		_digits.clear();
		_specialChars.clear();
		_whiteSpaces.clear();
	}
};

