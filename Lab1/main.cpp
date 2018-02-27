#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstdio>
#include<cmath>
#include<cstdlib>
using namespace std;
/*
Implementation of Counting Sort.

Given an array A of integers, and an integer k that
denotes the largest integer in the input array,
this function sorts integers in A using counting sort.

@param: vector of integers A passed by reference with n integers
whose values range from 0 to k.
A is passed by reference, so the sorted integers will be inside A
at the end of the execution.
Make sure A is not empty and each integer greater or equal to 0
AND is less than or equal to k
@param: constant integer k, the largest integer in A
Make sure k is within range from 0 to 1000.
@return: boolean true if A and k are in the right format;
returns false otherwise.
*/
bool counting(vector<int> &A, const int k);

/*
Implements Radix Sort.

Given an array of integers A, in which each integer has
the same number of digits, and given an integer d, 
the total number of digits in an integer, this function
sorts integers in A using Radix Sort.

@param: vector of integers A, and each integer has d digits,
where d is the second parameter.
A is passed by reference, the sorted result will be in A.
Make sure A is not empty, and each integer has d digits.
@param: integer d, the total number of digits in an integer in A.
Make sure d is in this range [1, 10] (between 1 and 9 inclusively).
@return: returns boolean true if sorted successfuly and false otherwise.
*/

bool radix(vector<int> &A, const int d);

/*
Merges the two sorted integer arrasy into a single sorted integer array.

Given two arrays A of size A_size and B of size B_size, each with
sorted in increasing order integers. This function creates 
a new array C in the heap of size = A_size + B_size,
merges the integers from A and B into this array so that 
C holds integers sorted in increasing order.

@param: an integer pointer A to an array of sorted integers of size A_size.
Make sure that integers in A are in non-decreasing order:
as you scan integers in A from left to right, an integer at position i
is less than or equal to the integer at position (i+1).
If the integers are not in this order, print out exact message:
"ERROR: integers are not sorted appropriately."
and return NULL.
@param: A_size is an integer that is the size of the array pointed by A
@param: an integer pointer B to an array of sorted integers of size B_size.
Make sure that integers in B are in non-decreasing order:
as you scan integers in B from left to right, an integer at position i
is less than or equal to the integer at position (i+1).
If the integers are not in this order, print out exact message:
"ERROR: integers are not sorted appropriately."
and return NULL.
@param: B_size is an integer, the size of the array pointed by B.
@return: an integer pointer C that points to the array created in the heap
with all integers from A and B sorted in non-decreasing order.
*/

int* merge(int *A, int A_size, int *B, int B_size);

/*
Finds intersection, difference and union of two given sets.

Given two sets A and B of integers, and integer k (the largest integer in A and B),
and string called type that defines what set is to be returned, this function
finds either the intersection of A and B (if type = "intersection"),
or the difference A - B (if type = "difference"),
or the unionn of A and B (if type = "union"). The resulting set is returned.

@param: vector of integers A that cannot be modified (passed by constant reference); 
since A represents a set, all integers in A must be distinct (no need to check this).
All integers in A are less than or equal to k (the third parameter) - no need
to check this.
@param: vector of integers B passed by constant reference;
since B represents a set, all integers in B must be distinct (no need to check this).
All integers in B are less than or equal to k (the third parameter) - no need
to check this.
@param: integer k, the largest integer in A and B.
@param: string called type. No need to check this parameter: it will be equal to one
of the three strings: "intersection", "difference" or "union".
@return: vector of integers with the results sorted in increasing order.
*/

vector<int> stat(const vector<int> &A, const vector<int> &B, int k, string type);



/* Prints integers from vector v */
void print(const vector<int> &v){
	for(int i = 0; i < (int)v.size(); i++)
		cout << v[i] << endl;
}
/* Prints integers from the array 
@param: integer pointer C that points to the array of integers in the heap
@param: constant integer size, the size of the array
*/
void print(int* ptrArray, const int size){
	for(int i = 0; i < size; i++)
		cout << ptrArray[i] << endl;
}

int main(){
	string command;
	while(cin >> command){
		if(command == "counting"){
			int size, k;
			cin >> size >> k;
			vector<int> A;
			for(int i = 0; i < size; i++)
			{	int x;
				cin >> x;
				A.push_back(x);
			}//for
			bool success = counting(A, k);
			if(success)
				print(A);
		}//counting
		else if(command == "radix"){
			int size, d;
			cin >> size >> d;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			bool success = radix(A, d);
			if(success)
				print(A);
		}//if radix
		else if(command == "merge"){
			int sizeA, sizeB;
			cin >> sizeA >> sizeB;
			int *A = new int[sizeA];
			int *B = new int[sizeB];
			for(int i = 0; i < sizeA; i++){
				int x;
				cin >> x;
				A[i] = x;
			}
			for(int i = 0; i < sizeB; i++){
				int x;
				cin >> x;
				B[i] = x;
			}
			int *C = merge(A, sizeA, B, sizeB);
			if(C != NULL){
				print(C, (sizeA + sizeB));
			}
			delete [] A;
			delete [] B;
			delete [] C;
		}//if merge
		else if(command == "stat"){
			int sizeA, sizeB, k;
			string type;
			cin >> sizeA >> sizeB >> k >> type;
			vector<int> A;
			vector<int> B;
			for(int i = 0; i < sizeA; i++){
				int x ;
				cin >> x;
				A.push_back(x);
			}
			for(int i = 0; i < sizeB; i++){
				int x ;
				cin >> x;
				B.push_back(x);
			}
			vector<int> C = stat(A, B, k, type);
			print(C);
		}//if stat
		else{
			cerr << "ERROR: the command " << command << " is not valid." << endl;
			exit(0);
		}
	}//while

}//main()


/*
This is the Counting function that sorts the values inside vector A by ascending order.

Step 1: This function first checks to make sure that vector A is not empty and that the constant k is within 0 and 1000.
Step 2: The function then creates array C of size k and zeroes it out.
Step 3: The function crawls through A, checking to make sure the values at the appropriate index are both positive and less than k.
Step 4: The value at the index of C increments by 1 for every time it passes by the appropriate value at the index number in A.
Step 5: C then repopulates A with the values properly sorted.

*/
bool counting(vector<int> &A, const int k){	
	
	//check to see if A exists and k is in the range of 0 and 1000
	if (A.size() != 0 && k >= 0 && k <= 1000){
		int C[k];
		int size = A.size();
		int y=0;
		int x=0;

		//for loop that zeroes out C
		for(int h=0; h<k+1; h++){
			C[h]=0;
		}	
		//for loop that crawls through A, making sure that A's value is the right size
		for (int i=0; i<size; i++){
			if (A[i] >= 0 && A[i] <= k){
				//x holds the value at the index of A, then uses that to 
				//increment the value at that index of C
				x = A[i];
				C[x]++;
			}
			else return false;
			
		}
		//for loop that uses the values in C to repopulate A in the proper order
		for (int j=0; j<k+1; j++){
			while (C[j] >0){
				A[y]=j;
				y++;
				C[j]--;
			}
			
		}	
		return true;
	}
	else return false;
}

bool radix(vector<int> &A, const int d){
	if (A.size() !=0 && d>=1 && d<10){
		vector< vector <int> > bins(10);
		int digit, x=0, z=0;
		int bins_size = bins.size();
		int A_size = A.size();

		for (int i=0; i<d; i++){
			for (int j=0; j<A_size; j++){
				x = (A[j]/pow(10,i));
				digit = x % 10;
				
				cout << "x is: " << x << " and digit is: " << digit << endl;
				bins[digit].push_back(A[j]);
			}
		
			for (int k=0; k<bins_size; k++){

				int y=0;
				for (int l=0; l<bins[k].size(); l++){
					if (bins[k][l] !=0){
						A[y] = bins[k][l];
						bins[k][l] = 0;
						cout << "bins[k][l] is: " << bins[k][l] << endl;
						y++;
					}
				}
			}
		}

		cout << endl << endl;
		return true;
	}
	else return false;
}

/*
This function merges two arrays that have been pre-sorted in numerical order into a single array, 
then returns that array.

Step 1: Verifies that array A is sorted properly.
Step 2: Verifies that array B is sorted properly.
Step 3: Compares the values between both arrays, then places the compared values into C.
*/
int* merge(int *A, int A_size, int *B, int B_size){
	
	int y=0;
	int z=0;
	
	int C_size = (A_size+B_size);
	int *C = new int[C_size];
	
	//for loop that verifies that A is sorted properly.
	for (int i=0; i<A_size; i++){
		if (A[i] > A[i]+1){
			cerr << "ERROR: integers are not sorted appropriately.";
			return NULL;		
		}
	}
	//for loop that verifies that B is sorted properly.
	for (int j=0; j<B_size; j++){
		if (B[j] > B[j]+1){
			cerr << "ERROR: integers are not sorted appropriately.";
			return NULL;		
		}
	}
	//for loop that compares the values in the indecies of A and B then places them into C
	for (int k; k<C_size; k++){

		//A's value is less than B's value AND A hasn't run out of values, OR B hasn't run out of values,
		//add A's value to C and increase the iterator by 1.
		if ((A[y] <= B[z] && y!=A_size) || z==B_size){
			C[k] = A[y];
			y++;
		}
		//If the above conditions are not met at any time, add B's value to C and increase it iterator by 1.
		else {
			C[k] = B[z];
			z++;
		}

	}
	
	return C;
}

/*

This function finds the intersection, union, and difference between two sets. 

*/
vector<int> stat(const vector<int> &A, const vector<int> &B, int k, string type){
	
	vector<int> C;
	
	vector<int> A_temp = A;
	vector<int> B_temp = B;
	
	bool setSuccess;

	int A_size = A.size();
	int B_size = B.size();

	counting(A_temp,k);
	counting(B_temp,k);

// if "intersection is chosen, two for loops compare all the items in A with every item in B. If they're equal, it pushes the value to C.
	if (type == "intersection"){


		int x=0;


		for(int i=0; i<A_size;i++){
			x = A[i];
			for (int j=0; j<B_size;j++){
				if (x == B[j]){
					C.push_back(x);
				} 
			}
		}

	}
	else if (type == "difference"){
		
		int x=0;


		for(int i=0; i<A_size;i++){
			x = A[i];
			for (int j=0; j<B_size;j++){
				if (x == B[j]){
					continue;
				} 

					C.push_back(x);
				
			}
		}


	}
	
	//union puts one instance of each item in both A and B into C
	else {
		
		int y=0;
		int z=0;

		while(true){
			if ((A_temp[y] < B_temp[z]) || z==B_size){
				C.push_back(A_temp[y]);
				y++;
			}
			else if ((B_temp[z] < A_temp[y]) || y == A_size){
				C.push_back(B_temp[z]);
				z++;
			}
			else{
				C.push_back(B_temp[z]);
				y++;
				z++;
			}
			if ((y == A_size) && (z == B_size)){
				break;
			}
			
		}


	}

	setSuccess = counting(C,k);

	if (setSuccess){
		return C;
	}


}
