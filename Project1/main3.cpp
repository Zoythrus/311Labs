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
void quicksort(string &S, vector<int> &A, int low, int high);
void init(vector<string> &v, string fileName);
int partition(string &S,vector<int> &A, int low, int high);
bool lessThan(const string &S, int first, int second);

int main(int argc, char* argv[]){

  string s;
  vector<int> index;
  vector<string> text2;

//This is the readFromFile function

    readFromFile(s,argv[1]);
    for(int i=0; i<(int)s.length();i++){
      //cout << s[i];
      index.push_back(i);
    }
    //cout << endl;
    for(int i=0; i<(int)s.length();i++){
      //cout << index[i] << " ";
    }

    //cout << endl;
    init(text2, argv[2]);
    for(int i=0; i<(int)s.length();i++){
      //cout << text2[i] << " ";
    }
    //cout << endl << endl;

    quicksort(s, index, 0, index.size()-1);

    for(int i=0; i<(int)s.length();i++){
      //cout << s[index[i]];
    }

    //cout << endl;

    for(int i=0; i<(int)s.length();i++){
      cout << text2[index[i]] << " ";
    }
    cout << endl;

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

char convertToLower(char ch){
  if (ch >='A' && ch <= 'Z'){return (char)(ch-'A'+'a');}
  else return ch;
}

void quicksort(string &S, vector<int> &A, int low, int high){
  //cout << low << " " << high << " " << endl;

  if(low < high){
    int pivotIndex = partition(S, A, low, high);
    //cout << "pivot is: " <<  pivotIndex<<endl;
    quicksort(S, A, low, pivotIndex - 1);
    quicksort(S, A, pivotIndex + 1, high);
  }
}

void init(vector<string> &v, string fileName){

    ifstream in;
    in.open(fileName.c_str(), ios::in);

    if (!in){
      cerr << "Could not open " << fileName << endl;
      return;
    }

    string x;
    getline(in,x);

    while(!in.eof()){
        v.push_back(x);
        getline(in,x);
    }

    in.close();
    in.clear();

}

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

int partition(string &S, vector<int> &A, int low, int high){

  //cout << "partition: " << low << " " << high << " " << endl;

  for(int i=0; i<(int)S.length();i++){
    //cout << S[A[i]];
  }
  //cout <<endl;
  for(int i=0; i<(int)S.length();i++){
    //cout << A[i] << " ";
  }
  //cout << endl;

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
