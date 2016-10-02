#include "boost/filesystem.hpp" ///For reading directory
#include "boost/lexical_cast.hpp" ///For converting and checking data in file
#include <iostream> ///Cout
#include <fstream> ///Open file
#include <future>

using namespace std;
using namespace boost::filesystem;
/*
* Func for reading and checking file content.Return readed value.
*/
int ReadFile(path InputFileWithPath)
{
	using boost::lexical_cast;
	using boost::bad_lexical_cast;
	int Answer = 0;
	std::ifstream InputFile(InputFileWithPath.string());
	string tmpString;
	if(InputFile.is_open())
	{
		while(!InputFile.eof())
		{
			getline(InputFile, tmpString);
		}
		
	}
	try {
		Answer=lexical_cast<int>(tmpString);
		cout << InputFileWithPath.filename() << ": " << Answer << endl;
	}
	catch (const bad_lexical_cast &) {
		return 0;
	}
	return Answer;
}

int main(int argc, char *argv[])
{
	path InputPath(argv[1]);

	directory_iterator EndIterator;
	
	int Answer = 0;

	for(directory_iterator FileIterator(InputPath);FileIterator!=EndIterator;++FileIterator)
	{
		if(is_regular_file(FileIterator->path()))
		{
			cout << FileIterator->path().filename().string()<<endl;
			Answer += ReadFile(FileIterator->path());
		}
	}

	cout << "Final sum: " << Answer << endl;

	return 0;
}