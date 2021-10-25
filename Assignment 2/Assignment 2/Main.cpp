#include <iostream>
#include <vector>
#include <omp.h>
#include <stack>
#include <string>
using namespace std;

int singleThreadDotProduct() {
	int size, element, dotProduct = 0;

	cout << "SINGLE THREADED" << endl;
	cout << "Please enter size of vectors: ";
	cin >> size;
	cout << endl;

	vector<int> vectorElements; //I use a single vector to minimize amount of code

	for (int i = 0; i < 2; i++) {
		cout << endl << "Please enter matrix " << i + 1 << ":" << endl << endl;
		for (int j = 0; j < size; j++) {
			cout << "Please enter element " << j + 1 << ": ";
			cin >> element;
			vectorElements.push_back(element);	//Read elements into both vectors
		}
	}

	for (int i = 0; i < size; i++) {	//compute dot product
		dotProduct += (vectorElements.at(i) * vectorElements.at(i + size));
	}

	return dotProduct;
}


int multiThreadDotProduct() {
	int size, element, dotProduct = 0;

	cout << "MULTI THREADED" << endl;
	cout << "Please enter size of vectors: ";
	cin >> size;
	cout << endl;

	vector<int> vectorElements;	////I use a single vector to minimize amount of code

	for (int i = 0; i < 2; i++) {
		cout << endl << "Please enter matrix " << i + 1 << ":" << endl << endl;
		for (int j = 0; j < size; j++) {
			cout << "Please enter element " << j + 1 << ": ";
			cin >> element;
			vectorElements.push_back(element);	//Read elements into both vectors
		}
	}

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < size; i++) {	//compute multi threaded dot product
#pragma omp atomic
		dotProduct += (vectorElements.at(i) * vectorElements.at(i + size));
	}

	return dotProduct;
}


string decToBinary()
{
	int n;

	cout << "Enter number to convert to binary: ";
	cin >> n;

	stack<int> binary;
	string finalBinary;

	int i = 0;	//counter for binary stack
	while (n > 0) {
		binary.push(n % 2);	//storing remainder in binary stack
		n = n / 2;
		i++;
	}

	for (int j = i - 1; j >= 0; j--) {	//printing binary stack in reverse order 
		finalBinary += to_string(binary.top());
		binary.pop();
	}

	return finalBinary;
}

double postfix() {
	string expression, temp = "";
	vector<string> expressionElements;
	stack<double> expressionStack;

	cin.ignore();
	cout << "Please enter a postfix expression: ";
	getline(cin, expression);	//gets user input on postfix string. Spaces must be between operators and numbers

	for (int i = 0; i < expression.length(); i++) {	//loop removes whitespace and seperates elements into a vector
		if (expression[i] != ' ') {
			temp += expression[i];
		}
		else {
			expressionElements.push_back(temp);
			temp = "";
		}
	}
	expressionElements.push_back(temp);

	//determines appropriate operation for each element in vector, adds element to stack and applies operation
	for (int i = 0; i < expressionElements.size(); i++) {
		if (expressionElements.at(i) == "+") {
			double val1 = expressionStack.top();
			expressionStack.pop();

			double val2 = expressionStack.top();
			expressionStack.pop();

			expressionStack.push(val2 + val1);
		}
		else if (expressionElements.at(i) == "-") {
			double val1 = expressionStack.top();
			expressionStack.pop();

			double val2 = expressionStack.top();
			expressionStack.pop();

			expressionStack.push(val2 - val1);
		}
		else if (expressionElements.at(i) == "*") {
			double val1 = expressionStack.top();
			expressionStack.pop();

			double val2 = expressionStack.top();
			expressionStack.pop();

			expressionStack.push(val2 * val1);
		}
		else if (expressionElements.at(i) == "/") {
			double val1 = expressionStack.top();
			expressionStack.pop();

			double val2 = expressionStack.top();
			expressionStack.pop();

			expressionStack.push(val2 / val1);
		}
		else {
			expressionStack.push(stoi(expressionElements.at(i)));
		}
	}

	return expressionStack.top();
}

void middleStack() {
	int size, temp, middle;
	stack<int> firstStack;
	stack<int> finalStack;

	cout << "Enter size of stack: "; //reads in size of stack
	cin >> size;

	for (int i = 0; i < size; i++) {	//reads in elements of stack
		cout << "Please enter element " << i + 1 << ": ";
		cin >> temp;

		firstStack.push(temp);
	}

	cout << "Enter element to insert in middle: ";		//asks for element to insert
	cin >> middle;


	for (int i = 0; i < size; i++) {		//inserts element into new stack
		if (i == (size / 2)) {
			finalStack.push(middle);
		}
		finalStack.push(firstStack.top());
		firstStack.pop();
	}

	cout << endl << endl << "New Stack: ";

	for (int i = 0; i < size; i++) {	//outputs new stack
		cout << finalStack.top() << ", ";
		finalStack.pop();
	}
	cout << finalStack.top();
	finalStack.pop();
}

int main() {
	cout << decToBinary() << endl << endl;
	cout << postfix() << endl << endl;
	middleStack();
}