
#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <stdio.h>

using namespace std;


/**************************************************************************************
*	this function will merge left sub arry and right sub arr into array (arr)
*	parameter: arr -->  final arr in which all element are sorted which will returned
*			  left -->  left sub array contains all elements from 0 to mid
*			  right -->  right sub array contains all elements from mid + 1 to size
*			  l_size --> size of left sub arr
*			  r_size --> size of right sub arr
*	return: none
***************************************************************************************/
void merge(int* arr, int left[], int right[], int l_size, int r_size)
{
	int i = 0, j = 0, k = 0; // i index for left sub arr, j for right sub arr and k for origanl array --> arr
	while (i < l_size && j < r_size)
	{
		// comparing the smallest element and storing it into arr
		if (left[i] <= right[j])
			arr[k++] = left[i++];
		else
			arr[k++] = right[j++];
	}
	// storing remaing elements of left sub array into arr
	while (i < l_size)
		arr[k++] = left[i++];

	// storing remaing elements of right sub array into arr
	while (j < r_size)
		arr[k++] = right[j++];
}

/******************************************************************************************************************
*	this function will sort the elements of array first divided them the merge them in sorted order
*	parameter: arr -->  elements to be sorted and are stored into arr after sorted
*			  n -->  size of array
*	return: none
******************************************************************************************************************/
void mergeSort(int* arr, int n)
{
	// if their is only one element so array with one element is always sorted so return 
	if (n == 1)
		return;

	// calculating mid 
	int mid = n / 2;
	// allocating space for left sub array
	int* left = new int[mid];
	// allocating space for right sub array
	int* right = new int[n - mid];

	// copying first half elements of arr int left sub array
	for (int i = 0; i < mid; i++) {
		left[i] = arr[i];
	}

	// copying next half elements of arr int left sub array
	for (int i = mid; i < n; i++) {
		right[i - mid] = arr[i];
	}
	// calling mergeSort for left sub array so it will divided into single element
	mergeSort(left, mid);
	// calling mergeSort for right sub array so it will divided into single element
	mergeSort(right, n - mid);

	// merging both left and right sub array into the arr (original array to be sorted)
	merge(arr, left, right, mid, n - mid);
}


/**************************************************************************************
*	Node structure use to store data
*	it store the element and the crossponding index
*	this node is use in min heap to sort data and merge into files
***************************************************************************************/
struct Node {
	int ele;   // to store integer from file
	int index; // to store index of element of crossponding file
};


/**************************************************************************************
* this function will swap the Node's x and y of Min heap
***************************************************************************************/
void Swap(Node* x, Node* y);

class MinHeap
{

	Node* arr; //this will point towords the minimum element of the heap
	int _size;	// size of heap
public:

	/**************************************************************************************
	*	this function will create heap of array with given size
	*	parameters: arr of Nodes, size of array
	*	return: none
	***************************************************************************************/
	MinHeap(Node arr[], int _size);


	/**************************************************************************************
	*	this function will heapify the smallest elemet to the top of heap
	*	parameters: int --> index of array
	*	return: none
	***************************************************************************************/
	void Heapify(int);

	/**************************************************************************************
	*	this function will return the parent of heap
	*	parameters: int --> index of array
	*	return: int --> index
	***************************************************************************************/
	int parent(int i)
	{
		return (i - 1) / 2;
	}

	/**************************************************************************************
	*	this function will return the left child of heap
	*	parameters: int --> index of array
	*	return: int --> index
	***************************************************************************************/
	int left(int i)
	{
		return (2 * i + 1);
	}

	/**************************************************************************************
	*	this function will return the right child of heap
	*	parameters: int --> index of array
	*	return: int --> index
	***************************************************************************************/
	int right(int i)
	{
		return (2 * i + 2);
	}

	/**************************************************************************************
	*	this function will return the min element of heap
	*	parameters: none
	*	return: arr[0] --> smallest element of heap
	***************************************************************************************/
	Node getMin()
	{
		return arr[0];
	}

	/******************************************************************************************************************
	*	this function will replace the min element with Node x then heapify it from first element --> 0 index
	*	parameters: Node
	*	return: none
	***************************************************************************************************************/
	void replaceMin(Node x)
	{
		arr[0] = x;
		Heapify(0);
	}
};

MinHeap::MinHeap(Node arr[], int _size)
{
	this->_size = _size;
	this->arr = arr;
	int i = (this->_size - 1) / 2; // parent index
	while (i >= 0)
	{
		Heapify(i);
		i--;
	}
}

void MinHeap::Heapify(int i)
{
	int l = left(i); // left element from given index i
	int r = right(i); // right element from given index i
	int smallest = i; // i will be the smallest element of heap
	// compare left element with i th elemet then assign left index to smallest
	if (l < _size && (arr[l].ele < arr[i].ele))
		smallest = l;
	// compare right element with smallest elemet then assign right index to smallest
	if (r < _size && (arr[r].ele < arr[smallest].ele))
		smallest = r;
	// if i th index and smallest are not same then heapify and swap the smallest untill it reach to the top of heap
	if (smallest != i)
	{
		Swap(&arr[i], &arr[smallest]);
		Heapify(smallest);
	}
}

void Swap(Node* x, Node* y)
{
	Node temp = *x;
	*x = *y;
	*y = temp;
}

void deleteFiles(string name)
{
	if (remove(&name[0]) != 0) return;
}


// this will copy source file to destination file
void copyFiles(string src, string dest)
{
	fstream s_file(src.c_str(), ios::in);
	fstream d_file(dest.c_str(), ios::out);
	d_file << s_file.rdbuf();
	s_file.close();
	d_file.close();
}


//this function will merges all files that are created using 2 way merge sort

int mergeFiles(int num_of_files, int pass)
{

	fstream* in_file = new fstream[2];
	// the files will be opend that are to be merged

	int j = 0;
	for (size_t i = 0; i < num_of_files; i += 2, j++)
	{
		fstream tempFile("temp.txt", ios::out);
		in_file[0].open(to_string(i) + ".txt", ios::in);
		in_file[1].open(to_string(i + 1) + ".txt", ios::in);
		Node* arr = new Node[2];
		int k;
		char ch;
		int heap_count = 0;
		for (int k = i; k < i + 2 ; k++)
		{
			if (in_file[k - i].eof() && !in_file[k - i])
				break;

			in_file[k - i] >> arr[k - i].ele; // reading data
			in_file[k - i] >> ch; // skipping character ,
			arr[k - i].index = k - i; // assigning index of file
			heap_count++;
		}

		// creating heap of that array
		MinHeap heap(arr, heap_count);

		int count = 0;
		/**************************************
		* do untill all data of file is in sorted way
		***************************************/
		while (count != heap_count)
		{
			Node root = heap.getMin(); // get the min elemment and store it into output file
			tempFile << root.ele << ",";
			
			in_file[root.index] >> root.ele; // reading data from file next element of that index
			in_file[root.index] >> ch; // skipping character ,			
			if (!in_file[root.index])
			{
				root.ele = INT_MAX; // if file is completed 
				count++;		// add that one of file is completed
			}
			heap.replaceMin(root); // it will replace the min element that is inserted into output file
		}

		in_file[0].close();
		in_file[1].close();
		tempFile.close();

		deleteFiles(to_string(i) + ".txt");
		deleteFiles(to_string(i + 1) + ".txt");

		copyFiles("temp.txt", to_string(j) + ".txt");
		
	}
	cout << "{ " << pass << ", " << 3 << ", " << j << " }" << endl;
	return j;
}


// this function will create all temporay file and the sort them
// rum_size --> no of file size
// num_ways --> no of files to be created
int createInitalRuns(string inputFile, int file_size)
{
	fstream in_file(inputFile.c_str(), ios::in);
	int temp_file_count = 0;

	if (in_file)
	{
		while (!in_file.eof())
		{
			string tempFile = to_string(temp_file_count) + ".txt";
			fstream out_file(tempFile.c_str(), ios::out);

			int size_elements = 0;
			char ch = ' ';
			int* arr = new int[file_size];
			string temp = "";
			int count = 0;
			while (in_file >> ch && !in_file.eof())
			{
				if (ch != ',')
					temp += ch;
				else
				{
					arr[size_elements] = atoi(&temp[0]);
					size_elements++;
					temp = "";
				}
				count++;
				if (count > file_size && ch == ',')
					break;
			}

			mergeSort(arr, size_elements);

			for (int i = 0; i < size_elements; i++)
				out_file << arr[i] << ",";
			temp_file_count++;
			out_file.close();
		}
	}

	return temp_file_count;
}



void externalMergeSort(string inputFile, string outputFile)
{
	cout << "Sorting external_sorting_age.txt ........" << endl;
	int pass = 0;
	int in_out_no_of_disk = 0; // I/O's disks 
	int file_size = 4092; // file size 
	int n = createInitalRuns(inputFile, file_size); // this will create sorted files of input buffers
	cout << "{ " << pass << ", " << 2 << ", " << n << " }" << endl;
	cout << "external_sorting_age is split and sorted into " << n << " files of 4096 bytes each ...... " << endl << endl;
	in_out_no_of_disk = n + 1;
	cout << "merging files ........ " << endl << endl;
	while (n != 1)
	{
		pass++;
		n = mergeFiles(n,pass); // this will merge all files into output file
		in_out_no_of_disk += n * 2;
	}
	copyFiles(to_string(0) + ".txt", outputFile); // this will copy output file into tempoary file 0.txt so it will use in next run 
	deleteFiles(to_string(0) + ".txt");
	deleteFiles("temp.txt");
	cout << endl << "Sorting is done." << endl;
	cout << "Sorted data save to: output_external_sorting_age.txt" << endl;
	cout << "Total no of disk file I/O's' " << in_out_no_of_disk << endl;
}


int main()
{
	string inputFile = "external_sorting_age.txt";
	string outputFile = "output_external_sorting_age.txt";

	externalMergeSort(inputFile, outputFile); // calling external merge sort with input and output file


	return 0;
}
