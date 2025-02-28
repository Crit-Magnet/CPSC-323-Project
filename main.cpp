#include <iostream> /* cout cin */
#include <fstream>  /* fstream  */
// #include <stdio.h>  
#include <string>   /*  stoi     */
using namespace std;

struct lexReturn
{
	string token;
	string lexeme;
};

lexReturn lexer(string target, fstream* file);
string FSMLetter(string target, fstream* file);
string FSMDigitReal(string target, fstream* file);


int state = 1;

int main()
{
	fstream  file;
	fstream* filePtr;
	file.open("input.txt"); // open input for parsing

	lexReturn value;

	filePtr = &file;
	string output = "";


    // I think this is the lexer but its in main cause thats were my initial tests came from
	while(!filePtr->eof())
	{
        state = 1;
		if(isspace(filePtr->peek()))
		{
			//cout << test << endl;
			output = "";
			//cout << "skip" << endl;
			filePtr->ignore(1);
		}
        else if(isalpha(filePtr->peek()))
        {
            output += filePtr->get();
            // char test[100];
            // if(filePtr -> getline(test, 100));
            // else
            // {
            // output = FSMLetter(output, filePtr);
            // }
        }
		else if(isdigit(filePtr->peek()))
		{
			output += filePtr->get();
            FSMDigitReal(output, filePtr);
		}
        else
        {
            // cout << "not found";
            filePtr->ignore(1);
        }
        // cout << output << endl;
		// value = lexer(output, filePtr);
	}

	file.close(); // close input after parsing
	return 0;
}

/* checks both digits and reals */
/*    ACCEPTED RETURN STATES    */
/*        INTEGER = 2           */
/*        REAL    = 4           */

string FSMDigitReal(string target, fstream* file)
{
    if(isspace(file->peek()) || file->peek()==';')
    {
        // check for rejected state
        if(state == 1 || state == 3 || state == 5)
        {
            cout << "rejected";
            return target;
        }
        else
        {
            cout << "accepted\n";
        }

        cout << target;
        state = 1;
        return target;
    }

    target += file->get();

    if(isdigit(target.back()))
    {
        state = 2;
    }
    else if(isdigit(target.back() && state == 3))
    {
        state = 4;
    }
    else if(target.back() == '.')
    {
        state = 3;
    }
    else
    {
        state = 5;
    }
    
    return FSMDigitReal(target, file);
}