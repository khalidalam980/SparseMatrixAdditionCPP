#include <iostream>
using namespace std;

// Structure to store non-zero elements of the sparse matrix
class Elements
{
public:
	int i; // Row index
	int j; // Column index
	int x; // Value
};

// Class to represent the sparse matrix
class Sparse
{
private:
	int m; // Number of rows
	int n; // Number of columns
	int num; // Number of non-zero elements
	Elements* e; // Array to store non-zero elements

public:
	// Constructor
	Sparse(int m, int n, int num)
	{
		this->m = m;
		this->n = n;
		this->num = num;
		e = new Elements[num];
	}

	// Destructor
	~Sparse()
	{
		delete[] e;
	}

	// Overloaded operator+ for sparse matrix addition
	Sparse operator+(Sparse& s);

	// Friend function to overload the >> operator for input
	friend istream& operator>>(istream& is, Sparse& s);

	// Friend function to overload the << operator for output
	friend ostream& operator<<(ostream& os, Sparse& s);
};

// Overloading the >> operator to input sparse matrix
istream& operator>>(istream& is, Sparse& s)
{
	cout << "Enter all non-zero elements. In the order of row, column and element:" << endl;
	for (int i = 1; i <= s.num; i++)
	{
		cin >> s.e[i-1].i >> s.e[i-1].j >> s.e[i-1].x;
	}
	cout << endl;

	return is;
}

// Overloading the << operator to output sparse matrix
ostream& operator<<(ostream& os, Sparse& s)
{
	int k = 0;
	for (int i = 1; i <= s.m; i++)
	{
		for (int j = 1; j <= s.n; j++)
		{
			if (i == s.e[k].i && j == s.e[k].j)
				cout << s.e[k++].x << " ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;

	return os;
}

// Overloading the + operator to perform sparse matrix addition
Sparse Sparse::operator+(Sparse& s)
{
	int i, j, k;
	i = j = k = 0;

	// Create a new sparse matrix for the sum
	Sparse* sum = new Sparse(m, n, num + s.num);
	if (m != s.m || n != s.n)
		return Sparse(0, 0, 0);

	// Merge the non-zero elements from both matrices while adding
	while (i < num && j < s.num)
	{
		if (e[i].i < s.e[j].i)
			sum->e[k++] = e[i++];
		else if (e[i].i > s.e[j].i)
			sum->e[k++] = s.e[j++];
		else
		{
			if (e[i].j < s.e[j].j)
				sum->e[k++] = e[i++];
			else if (e[i].j > s.e[j].j)
				sum->e[k++] = s.e[j++];
			else
			{
				sum->e[k] = e[i];
				sum->e[k++].x = e[i++].x + s.e[j++].x;
			}
		}
	}

	// Copy the remaining elements from the first matrix, if any
	for (; i < num; i++)
		sum->e[k++] = e[i];

	// Copy the remaining elements from the second matrix, if any
	for (; j < s.num; j++)
		sum->e[k++] = s.e[j];
	sum->num = k;

	return *sum;
}

int main()
{
	Sparse s1(5, 5, 5); // Create a Sparse object s1 with dimensions 5x5 and 5 non-zero elements
	Sparse s2(5, 5, 5); // Create a Sparse object s2 with dimensions 5x5 and 5 non-zero elements

	cin >> s1; // Input non-zero elements for s1
	cin >> s2; // Input non-zero elements for s2

	Sparse sum = s1 + s2; // Add s1 and s2 to obtain the sum matrix

	cout << "First Matrix" << endl << s1; // Print the first matrix (s1)
	cout << "Second Matrix" << endl << s2; // Print the second matrix (s2)
	cout << "Sum Matrix" << endl << sum; // Print the sum matrix

	return 0;
}