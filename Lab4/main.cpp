#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;

void readFromFile(string &S, string filename);
char convertToLower(char ch);
bool lessThan(const string &S, int f, int l);
int partition(const string &S, vector<int> &indices, int low, int high, int pivotIndex);
void insertion(const string &S, vector<int> &indices, int low, int high);
int select(const string &S, vector<int> &v, int start, int fin, int k);

int main(int argc, char* argv[]){

  string s;
  vector<int> index;

//This is the readFromFile function

    readFromFile(s,argv[1]);

    if (argc == 4){
      for(int i=0; i<(int)s.length();i++){
          index.push_back(i);}

      insertion(s, index, atoi(argv[2]), atoi(argv[3]));

      for(int i=0; i<(int)s.length();i++){
          cout << index[i] << " ";}

        cout << endl;
    }

    else if (argc == 3){
      for(int i=0; i<(int)s.length();i++){;
        index.push_back(i);}

      int temp = select(s, index, 0, s.length()-1, atoi(argv[2]));
      cout << temp << endl;
    }


}//main

//------------------------------------------------------
//readFromFile opens the file, then loops through the text,
//and throws the output into a string
//@param the string used to store the text and the text itself
void readFromFile(string &S, string fileName){

  ifstream in;
  in.open(fileName.c_str(), ios::in);

  if (!in){
    cerr << "Could not open " << fileName << endl;
    return;
  }

  string aline;
  getline(in, aline);


  while (!in.eof()){
    S+=aline;
    getline(in,aline);
  }

  in.close();
  in.clear();
}

void insertion(const string &S, vector<int> &indices, int low, int high){

  for (int i=low; i < high; i++){
          int j=i;
          while ( (j>=0) && (lessThan(S, indices[j+1],indices[j]))){
            swap(indices[j],indices[j+1]);
            if (j-1>=low)
              j--;
          }
  }

}
//------------------------------------------------------
//convertToLower simply reads through the string and
//converts everything to lowercase
//@param the character being converted
char convertToLower(char ch){
  if (ch >='A' && ch <= 'Z'){return (char)(ch-'A'+'a');}
  else return ch;
}
//------------------------------------------------------
//lessThan compares two characters in a string, then loops
//through the string one character at a time. It returns False
//if the first character is greater than the second character or
//if it hits the end.
//@param the string being used, the index of the first
//character, and the index of the second character
bool lessThan(const string &S, int first, int second){

    unsigned int j = 0;

    while(true){
//if we hit the end without first+j>second+j, return true


//if the first+j is greater than the second+j, and if we haven't hit the end, return false
	   if (((unsigned int)convertToLower(S[first+j]) > (unsigned int)convertToLower(S[second+j]))){
        ////cout << "false" << endl;
        return false;
        }

  //if first is less than second, return true
        else if (((unsigned int)convertToLower(S[first+j]) < (unsigned int)convertToLower(S[second+j]))){
        //cout << "true " << endl;
  		  return true;
  	  }

      else if (((second+j)>=S.length()-1) || ((first+j)>=S.length()-1)) {

        //cout << "We hit the end." << endl;
   		  if ((first+j)>=S.length()-1){
   			return true;}
         //if second hits the end before first, return false
 			else if ((second+j)>=S.length()-1){
 				return false;}
 	  }

  	//if second+j<=first+j, move to the next set of characters and loop
        else if (((unsigned int)convertToLower(S[first+j]) == (unsigned int)convertToLower(S[second+j]))){
          //cout << "continuing " << j << endl;
          j++;
        }
      //if no other options fire, this happens
      else return false;
    }
    //cout << endl << endl << endl;
}



//------------------------------------------------------
//This function is supposed to rearrange the numbers in indices to match up a properly
//partitioned string (S).
//Most of this Partition code was generously provided by Dr. Elena Harris as an example
//I couldn't get it to work with swap, so I'm leaving it
int partition(const string &S, vector<int> &A, int low, int high, int index){

  //cout << "partition: " << low << " " << high << " " << endl;

  int pivot = A[high];
  int i = low, j = high - 1;
  //cout << i << " " << pivot << " " << j << endl;

  while(i <= j){
    while(i<high && lessThan(S,A[i],pivot))
      i++;
    while(j >= low && lessThan(S,pivot,A[j]))
      j--;
    if(i < j){//swap A[i] and A[j]
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
      i++;
      j--;
    }//if
  }//while
  //swap A[i] and pivot
    A[high] = A[i];
    A[i] = pivot;
  return i;
}

int select(const string &S, vector<int> &v, int start, int fin, int k){

    //cout << "First" << endl<< "Start: "<<start << endl << "Finish: " << fin << endl;

    int vsize = fin - start + 1;

    if(start == fin){
        return v[start];}
    else if(start > fin){
        return -1;}

  	if(vsize <= 5){
  		insertion(S, v, start, fin);
  		return v[k];
  	}

	   int msize = ceil((double)vsize/5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for(int i = start; i <= fin; i = i + 5){
        vector<int> temp(5, 0);
        int j = 0;
        for(; j < 5 && (i + j)<= fin; j++){
            temp[j] = v[i+j];
        }//for j
        if(j < 5)
            temp.resize(j);
        insertion(S, temp, 0, temp.size()-1);
        if(j == 5)
            medians[med_ind++] = temp[2];
        else{
            int jmid = j >> 1;//divide by 2
            if(j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];

            }
    }//for i

    //so far we selected the medians of n/5 groups, each group of 5 elements
    int mid = msize >> 1; //divide by 2
    if((msize % 2) == 0)
        mid--;

	//find the median of the medians
    int x = select(S, medians, 0, msize - 1, mid);
	if(x == -1)
	{
		cerr << "ERROR: returned value of median of medians is -1." << endl;
		exit(0);
	}

    //partition elements of v around x
    //find the index of x in v
  int ind_of_x = -1;

	for(int i = start; i <= fin; i++){
    //cout << "Start: "<<start << endl << "Finish: " << fin << endl << "I is:"  << i << endl;
		if(v[i] == x){
			//cout << "Found it!" << endl;
			ind_of_x = i;
			break;
		}//if
	}//for

    //cout << "Start: "<<start << endl << "Finish: " << fin << endl << "Index of X: " << ind_of_x << endl << "X: " << x << endl;
    int pivotIndex = partition(S, v, start, fin, ind_of_x);
    //cout <<pivotIndex<<endl;
    if(k == pivotIndex){
		//cout << endl << "Returning" << endl;
		  return v[k];}
    else if(pivotIndex < k){
		//cout << endl << "pivot is less than k" << endl;
		  return select(S, v, pivotIndex + 1, fin, k);}
    else{
		//cout << endl << "pivot is greater than k" << endl;
		  return select(S, v, start, pivotIndex - 1, k);}
}//select
