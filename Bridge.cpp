
#include <iostream>
#include <vector>
#include<string>
#include <Windows.h>
using namespace std;
struct Date {
	string fileName;
	int size;
};

class Storage
{
protected:
	vector<Date> date;
public:
	Storage() {};
	virtual void addDate(Date date_) {
		this->date.push_back(date_);
	}
	string getDate() {
		string date__;
		for (Date d : this->date) {
			date__ += d.fileName + "\n";
			date__ += to_string(d.size) + "MB\n";
		}
		return date__;
	}
	int getMemoryFilled() {
		int m = 0;
		for (Date d : this->date) {
			m += d.size;
		}
		return m;
	}
};

class Flash : public Storage {
public:
	virtual void addDate(Date date_) override {
		this->date.push_back(date_);
		cout << "Added to Flash\n";
	}
};

class HardDrive : public Storage {
public:
	virtual void addDate(Date date_) override {
		this->date.push_back(date_);
		cout << "Added to HardDrive\n";
	}
};

class SaveDate {
protected:
	Storage* storage;
	int storageCap;
	int freeSpace;
public:
	SaveDate(Storage* storage, int capacity) { this->storage = storage;
	this->storageCap = capacity;
	this->freeSpace = capacity;
	}
	bool addDate(Date date) {
		if ((this->freeSpace - date.size) < 0) {
			cout << "Not enough space\n";
			return false;
		}
		this->storage->addDate(date);
		this->freeSpace = this->freeSpace- date.size;
		return true;
	};
	string readDate() {
		return storage->getDate();
	}
};

class Save512GB : public SaveDate {
public:
	Save512GB(Storage* storage, int capacity) :SaveDate(storage, capacity) {}

};

class Save1TB : public SaveDate {
public:
	Save1TB(Storage* storage, int capacity) :SaveDate(storage, capacity) {}

};

int main()
{
	Storage* flash = new Flash;
	Storage* hardDrive = new HardDrive;
	SaveDate* save512GBFlash = new Save512GB(flash, 512*1024);
	SaveDate* save1TBHardDrive = new Save1TB(hardDrive, 1024*1024);
	SaveDate* save512GBHardDrive = new Save512GB(hardDrive, 512 * 1024);
	Date date;
	while (true) {
		cout << "Name of file: ";
		cin >> date.fileName;
		cout << "Size (MB): ";
		cin >> date.size;
		string menu;
		cout << "Choose the path :\n";
		cout << "Flash 512GB ------ 1\n";
		cout << "Hard Drive 512GB - 2\n";
		cout << "Hard Drive 1TB --- 3\n";
		cin >> menu;
		if (menu == "1") {
			save512GBFlash->addDate(date);
		}
		else if (menu == "2") {
			save512GBHardDrive->addDate(date);
		}
		else if (menu == "3") {
			save1TBHardDrive->addDate(date);
		}
		cout << "Input any key to continue (but e to exit): ";
		cin >> menu;
		system("cls");
		if (menu == "e" || menu == "E") {
			break;
		}
	}

	cout << "Flash 512GB:\n" << save512GBFlash->readDate() << endl << endl;
	cout << "Hard Drive 512GB:\n" << save512GBHardDrive->readDate() << endl << endl;
	cout << "Hard Drive 1TB:\n" << save1TBHardDrive->readDate() << endl;



}

