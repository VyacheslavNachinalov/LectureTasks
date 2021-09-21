#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;



class Protocol {
public:
		virtual void send(char* buf, int len) {

		}
		virtual void sendName() {
		}
};

struct ConnectionList {
	Protocol* mas[100];
	int count = 0;
};

class BinaryProtocol : public Protocol {
public:
	void send(char* buf, int len) {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < 8; j++) {
				cout << ((buf[i]-0) & (256>>j+1) ? '1' : '0');
			}
			cout << " ";
		}
		cout << endl;
	}
	void sendName() {
		cout << "BinaryProtocol" << endl;
	}
};

class HexProtocol : public Protocol {
public:
	void send(char* buf, int len) {
		cout.setf(ios::showbase);
		for (int i = 0; i < len; i++) {
			cout << hex << buf[i]-0<< " ";
		}
		cout.unsetf(ios::showbase);
		cout<<endl;
	}
	void sendName() {
		cout << "HexProtocol" << endl;
	}
};

void addProtocol(ConnectionList* p, Protocol* newProtocol) {
	p->mas[p->count] = newProtocol;
	p->count++;
}
void sendAll(ConnectionList* p) {

	for (int i = 0; i < p->count; i++) {
		p->mas[i]->sendName();
	}
}

void readFile() {
	ifstream file;
	string filename, str;
	string buff = "";
	cout << "Введите имя файла включая расширение: ";
	cin >> filename;
	file.open(filename);
	if (file.is_open() != true)
	{
		cout << "Ошибка! Не удаётся открыть файл!" << endl;
		return;
	}
	int count=0;
	while (file >> str)
	{
		buff.push_back(str[0]);
		count++;
	}
	file.close();

	ConnectionList* list = new ConnectionList;
	for (int i = 0; i < buff.size(); i++) {
		if (buff[i] == 'B') {
			addProtocol(list, new BinaryProtocol);
		}
		else if (buff[i] == 'H') {
			addProtocol(list, new HexProtocol);
		}
	}
	cout << "Колличество протоколов в структуре: " << list->count << endl;
	sendAll(list);
}

int main() {
	setlocale(LC_ALL, "RUS");
	BinaryProtocol str1;
	HexProtocol str2;
	char c[] = "ABC";
	cout << c << endl;
	str1.send(c, strlen(c));
	str2.send(c, strlen(c));
	readFile();
	return 0;
}