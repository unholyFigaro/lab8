#include <iostream>
#include <list>     // подключаем заголовок списка
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

class Exception
{
protected:
	int error;
public:
	Exception()
	{
		error = 0;
	}
	Exception(int _error)
	{
		error = _error;
	}
	~Exception()
	{

	};
	void Print()
	{
		if (this->error == 0)
		{
			cout << "Input error! Enter int!" << endl;
		}
		if (this->error == 1)
		{
			cout << "Opening error!" << endl;
		}
		if (this->error == 2)
		{
			cout << "Input category! A, B or C" << endl;
		}
	}
};

class Bus {
private:

public:
	char category;
	char destination[50];
	int busId;
	int startTimeInSeconds;
	int finishTimeInSeconds;
	Bus(char _category, char* _destination, int _busId, int _startTimeInSeconds, int _finishTimeInSeconds) {
		category = _category;
		strcpy(destination, _destination);
		busId = _busId;
		startTimeInSeconds = _startTimeInSeconds;
		finishTimeInSeconds = _finishTimeInSeconds;
	}

	Bus() {
		category = 'A';
		strcpy(destination, "Minsk");
		busId = 0;
		startTimeInSeconds = 0;
		finishTimeInSeconds = 1000;
	}
	friend class File;
	friend ostream& operator<<(ostream& out, const Bus& b);
};

void InsertSort(int n, int* ms)
{
	int j;
	int m;
	for (int i = 1; i < n; ++i)
	{
		j = i - 1;
		m = ms[i];
		while (j >= 0 && m < ms[j])
		{
			ms[j-- + 1] = ms[j];
		}
		ms[j + 1] = m;
	}
	return;
}

ostream& operator<<(ostream& out, const Bus& b)
{
	out << "Category: " << b.category << endl;
	out << "Destination: " << b.destination << endl;
	out << "Bus ID: " << b.busId << endl;
	out << "Dispatch time: " << b.startTimeInSeconds << endl;
	out << "Arrival time: " << b.finishTimeInSeconds << endl;
	return out;
}

class File
{
	string path;
public:
	File()
	{
		this->path = " ";
	}
	File(string _path)
	{
		this->path = _path;
	}
	void ReadTextBin()
	{
		char* msg;
		msg = new char[10];
		fstream fs;
		fs.open(path, fstream::in | fstream::binary);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		fs.read(msg, 10);
		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			if (msg[i] >= 97 && msg[i] <= 122 || msg[i] >= 65 && msg[i] <= 90)
			{
				count++;
			}
		}
		for (int i = 0; i < count; i++)
		{
			cout << msg[i];
		}
		cout << endl;
		fs.close();
	}

	void WriteText()
	{
		string msg;
		fstream fs;
		fs.open(path, fstream::out | fstream::app);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		cout << "Enter message: ";
		cin >> msg;
		fs << msg << "\n";
		fs.close();
	}

	void WriteBin(Bus pr)
	{
		fstream fs;
		fs.open(path, fstream::out | fstream::binary | fstream::app);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		fs.write((char*)&pr, sizeof(pr));
		fs.close();
	}


	void ReadBin(int n);
	int Del(int index, int n)
	{
		fstream fs;
		fs.open(path, fstream::in | fstream::binary | fstream::out);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return 0;
		}
		Bus* ms;
		ms = new Bus[n];
		for (int i = 0; i < n; i++)
		{
			fs.read((char*)&ms[i], sizeof(ms[i]));
		}
		fs.close();
		fstream fs1;
		fs1.open(path, fstream::binary | fstream::out | fstream::trunc);
		fs1.close();
		fstream fs2;
		fs2.open(path, fstream::binary | fstream::out);
		for (int i = 0; i < index; i++)
		{
			this->WriteBin(ms[i]);
		}
		for (int i = index + 1; i < n; i++)
		{
			this->WriteBin(ms[i]);
		}
		n = n - 1;
		cout << "After deletion: " << endl;
		this->ReadBin(n);
		fs2.close();
		return n;
	}

	void Sort(int n)
	{
		if (n == 1)
		{
			this->ReadBin(n);
			return;
		}
		fstream fs;
		fs.open(path, fstream::in | fstream::binary | fstream::out);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		int* m;
		m = new int[n];
		Bus* ms;
		ms = new Bus[n];
		int i = 0;
		for (int k = 0; k < n; k++)
		{
			fs.read((char*)&ms[i], sizeof(ms[i]));
			m[i] = ms[i].busId;
			i++;
		}
		InsertSort(n, m);
		fs.close();
		fstream fs1;
		fs1.open(path, fstream::binary | fstream::out | fstream::trunc);
		try
		{
			if (!fs1.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		fs1.close();
		fstream fs2;
		fs2.open(path, fstream::binary | fstream::out);
		try
		{
			if (!fs2.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		cout << "Sort by amount of products:  " << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (ms[j].busId == m[i])
				{
					this->WriteBin(ms[j]);
				}
			}
		}
		this->ReadBin(n);
		fs2.close();
		delete[] ms;
		delete[] m;
	}
	void ReadText()
	{
		string msg;
		fstream fs;
		fs.open(path, fstream::in);
		try
		{
			if (!fs.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}
		cout << "File " << path << ":" << endl;
		while (!fs.eof())
		{
			while (getline(fs, msg))
			{
				cout << msg << endl;
			}
		}
		fs.close();
	}
	void ReadBinArr(int n, int a);
};

void QuickSort(int n, int* ms)
{
	int j;
	int m;
	for (int i = 1; i < n; ++i)
	{
		j = i - 1;
		m = ms[i];
		while (j >= 0 && m < ms[j])
		{
			ms[j-- + 1] = ms[j];
		}
		ms[j + 1] = m;
	}
	return;
}

void File::ReadBin(int n)
{
	fstream fs;
	fs.open(path, fstream::in | fstream::binary | fstream::out);
	try
	{
		if (!fs.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
		return;
	}
	cout << "____________________________________" << endl;
	Bus pr;
	//while (fs.read((char*)&pr, sizeof(Bus)))
	//{
	//	cout << pr;
	//	cout << "____________________________________" << endl;
	//}
	for (int i = 0; i < n; i++) {
		fs.read((char*)&pr, sizeof(Bus));
		cout << pr;
		cout << "____________________________________" << endl;
	}
	fs.close();
}

void File::ReadBinArr(int n, int a)
{
	fstream fs;
	fs.open(path, fstream::in | fstream::binary | fstream::out);
	try
	{
		if (!fs.is_open())
		{
			throw 1;
		}
	}
	catch (int i)
	{
		Exception ex(i);
		ex.Print();
		return;
	}
	cout << "____________________________________" << endl;
	Bus pr;
	//while (fs.read((char*)&pr, sizeof(Bus)))
	//{
	//	cout << pr;
	//	cout << "____________________________________" << endl;
	//}
	for (int i = 0; i < n; i++) {
		fs.read((char*)&pr, sizeof(Bus));
		if (pr.finishTimeInSeconds < a) {
			cout << pr;
			cout << "____________________________________" << endl;
		}
	}
	fs.close();
}

int main() {
	File file2("2.bin");

	char* _category;
	char* _destination[50];
	int* _busId;
	int* _startTimeInSeconds;
	int* _finishTimeInSeconds;

	int n, index, choice, ch;
	cout << "Work with text or binary file? Choose 1 or 2: ";
	cin >> choice;
	if (choice == 1)
	{
		system("CLS");
		cout << "Text file mode:" << endl;
		File file1("1.txt");
		file1.WriteText();
		file1.ReadText();
		cout << "Read as a binary file: " << endl;
		file1.ReadTextBin();
	}
	if (choice == 2) {
		system("CLS");
		cout << "Writing the file: " << endl;
		cout << "Enter the number of products: ";
		try
		{
			cin >> n;
			if (cin.fail())
			{
				throw 0;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return 0;
		}
		_category = new char[n];
		//_destination = new char[n];
		_busId=new int[n];
		_startTimeInSeconds = new int[n];
		_finishTimeInSeconds = new int[n];
		for (int i = 0; i < n; i++) {
			cout << "Enter the type of bus" << endl;
			cin >> _category[i];
			cout << "Enter the destination" << endl;
			char _destination[50];
			cin >> _destination;
			cout << "Enter the bus id" << endl;
			cin >> _busId[i];
			cout << "Enter the pratch time";
			cin >> _startTimeInSeconds[i];
			cout << "Enter the arravial time";
			cin >> _finishTimeInSeconds[i];
			Bus b(_category[i], _destination,_busId[i], _startTimeInSeconds[i], _finishTimeInSeconds[i]); //_CRT_SECURE_NO_WARNINGS
			file2.WriteBin(b);
		}
		cout << "\nRead the file - 1" << endl;
		cout << "Find by arrival tinme - 2" << endl;
		cout << "Sort - 3" << endl;
		cout << "Deletion - 4" << endl;
		cin >> ch; // 2 3 A Minsk 1 0 400 B Vitebsk 2 200 500 C Mogilev 3 500 700
		while (1) {
			if (ch == 1)
			{
				cout << "File: " << endl;
				file2.ReadBin(n);
			}
			if (ch == 2)
			{
				int a;
				cout << "Enter the arrival time";
				cin >> a;
				file2.ReadBinArr(n, a);
			}
			if (ch == 3)
			{
				file2.Sort(n);
			}
			if (ch == 4)
			{
				cout << "Enter index of element for deletion: ";
				try
				{
					cin >> index;
					if (cin.fail())
					{
						throw 0;
					}
				}
				catch (int i)
				{
					Exception ex(i);
					ex.Print();
					return 0;
				}
				int k;
				k = file2.Del(index, n);
				n = k;
			}
			cin >> ch;
		}

	}
	return 0;
}