#include "boost/filesystem.hpp" ///For reading directory
#include "boost/lexical_cast.hpp" ///For converting and checking data in file
#include <iostream> ///Cout
#include <fstream> ///Open file
#include <atomic> ///For total sum
#include <thread> ///Parallel working
#include <queue> ///Join threads


using namespace std;
using namespace boost::filesystem;


atomic_int TotalSum;
/*
* Func for reading and checking file content.Return readed value.
*/
void ReadFile(path InputFileWithPath)
{
	if (is_regular_file(InputFileWithPath))
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
			TotalSum += Answer;
			this_thread::sleep_for(chrono::seconds(1));
		}
		catch (const bad_lexical_cast &) {
			///Do nothing
		}
	}
}

int main(int argc, char *argv[])
{
	TotalSum = 0;

	queue<thread> FileReadingQueue;

	path InputPath(argv[1]);

	directory_iterator EndIterator;

	for(directory_iterator FileIterator(InputPath);FileIterator!=EndIterator;++FileIterator)
	{
		FileReadingQueue.push(thread(ReadFile, move(FileIterator->path())));
	}
	while(FileReadingQueue.size()>0)
	{
		FileReadingQueue.front().join();
		FileReadingQueue.pop();
	}
	cout << "Final sum: " << TotalSum << endl;

	return 0;
}