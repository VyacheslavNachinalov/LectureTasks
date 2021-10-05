#pragma once
#include <string>
#include <optional>
#include <iostream>

using namespace std;

template <typename DataType> 
class List
{
	private:
		struct Node
		{
			Node* next;
			DataType data;
		}*head;

	public:
		List(DataType newData) 
		{
			head = new Node;
			head->data = newData;
			head->next = nullptr;
		}
	//List(List&&) {}
		~List() {}
		void InsertNode(DataType newData, int position)
		{
			Node* newNode = new Node;
			newNode->data = newData;
			int curPosition = 0;
			for (Node* cur = head; cur != nullptr; cur = cur->next)
			{
				if (curPosition == position - 1)
				{
					newNode->next = cur->next;
					cur->next = newNode;
					return;
				}
				curPosition++;
			}
		}
		void RemoveNode(int position)
		{
			int curPosition = 0;
			for (Node* cur = head; cur != nullptr; cur = cur->next)
			{
				if (curPosition == position - 1)
				{
					Node* x = cur->next;
					cur->next = cur->next->next;
					free(x);
					return;
				}
				curPosition++;
			}
		}
		DataType& GetElement(size_t position) 
		{
			int curPosition = 0;
			for (Node* cur = head; cur != nullptr; cur = cur->next) 
			{
				if (curPosition == position)
				{
					return cur->data;
				}
				curPosition++;
			}
		}
		void PrintList() 
		{
			for (Node* cur = head; cur != nullptr; cur = cur->next)
			{
				cout << cur->data << " ";
			}
			cout << endl;
		}
		void testInt()
		{
			PrintList();
			InsertNode(6, 1);
			InsertNode(3, 2);
			PrintList();
			InsertNode(2, 1);
			PrintList();
			RemoveNode(1);
			PrintList();
			cout << GetElement(1) << endl;
		}
		void testString()
		{
			PrintList();
			InsertNode("world ", 1);
			PrintList();
			InsertNode("everyone ", 1);
			InsertNode("in the ", 2);
			PrintList();
			RemoveNode(1);
			RemoveNode(1);
			PrintList();
			cout << GetElement(1) << endl;
		}
};

template <typename DataType, int mx, int my> class Image 
{
	private:
		
		DataType img[mx][my];
	public:
		Image() {}
		~Image() {}
		void InitZero()
		{
			for (int i = 0; i < my; i++)
			{
				for (int j = 0; j < mx; j++)
				{
					img[j][i] = 0;
				}
			}
		}
		void InitChar()
		{
			for (int i = 0; i < my; i++)
			{
				for (int j = 0; j < mx; j++)
				{
					img[j][i] = 'A'+j;
				}
			}
		}
		int get(int x, int y) 
		{
			if (x > -1 && y > -1 && x < mx && y < my)
			{
				return img[x][y];
			}
		}
		void set(int x, int y, DataType data) {
			if (x > -1 && y > -1 && x < mx && y < my)
			{
				img[x][y] = data;
			}
		}
		void print()
		{
			for (int i = 0; i < my; i++)
			{
				for (int j = 0; j < mx; j++)
				{
					cout << img[j][i]<< " ";
				}
				cout << endl;
			}
		}
		void testInt() 
		{
			InitZero();
			set(1, 1, 1);
			set(2, 2, 2);
			cout<< get(0, 0)<< " "<<get(1, 1) << " " << get(2, 2) << endl;
			print();
		}
		void testChar()
		{
			InitChar();
			set(0, 0, 'Z');
			cout << get(0, 0) << endl;
			print();
		}
};

int main()
{
	List<int> intList (5);
	List<std::string> stringList("Hello ");

	intList.testInt();
	stringList.testString();

	Image<int,5,5> image1;
	Image<char, 5, 5> image2;

	image1.testInt();
	image2.testChar();
	return 0;
}

