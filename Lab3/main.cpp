#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

void readFromFile(string &S, string filename);
char convertToLower(char ch);
bool lessThan(const string &S, int f, int l);
void partition(const string &S, vector<int> &indices, int low, int high, int pivotIndex);

int main(int argc, char* argv[] ){

  string s;
  vector<int> index;

//This is the readFromFile function
  if (argc==2){
    readFromFile(s,argv[1]);
    for(int i=0; i<(int)s.length();i++){
      cout << s[i];}

    cout << endl;
  }
//This is the lessThan function
  else if (argc==4){
    readFromFile(s,argv[1]);
    //First, this runs convertToLower on the string
    for(int i=0; i<(int)s.length();i++){
      s[i] = convertToLower(s[i]);
      cout << s[i];}
    //Second, we actually run lessThan
    if (lessThan(s, atoi(argv[2]), atoi(argv[3]))) {
      cout << "True" << endl;
    }
    else{
      cout << "False" << endl;}
    }
//This is the Partition function
    else if (argc==3){
      readFromFile(s,argv[1]);
//This runs convertToLower on the string
      for(int i=0; i<(int)s.length();i++){
        s[i] = convertToLower(s[i]);
        index.push_back(i);
      }
//And here is where we run Partition
      partition(s, index, 0, (s.length()-1), atoi(argv[2]));
    }
    else return 0;

}
//------------------------------------------------------
//readFromFile opens the file, then loops through the text,
//and throws the output into a string
//@param the string used to store the text and the text itself
void readFromFile(string &S, string fileName){

  ifstream in;
  in.open(fileName.c_str(), ios::in);

  if (!in){
    cerr << "Could not open." << fileName << endl;
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

    cout << "This is the first parameter: " << first << endl;
    cout << "This is the second parameter: " << second << endl;

    while(true){

//These are simply some tests to see output
      cout << "First Test: " << (unsigned int)S[first+j] << " "  << (unsigned int)S[second+j] << endl;
      cout << "Second Test:" << ((char)S[first+j]) << " and " << (char)S[second+j] << endl;
      cout << "Third Test: " << first+j << " " << second+j << " " << j << " " << S.length() << endl;

//if the first+j is greater than the second+j, and if we haven't hit the end, return false
      if (((unsigned int)S[first+j] > (unsigned int)S[second+j]) && (((second+j)<S.length()-1) || ((first+j)<S.length()-1))){
        cout << "false" << endl;
        return false;
        }

//if we hit the end without first+j>second+j, return true
      else if (((second+j)>=S.length()-1) || ((first+j)>=S.length()-1)) {
          cout << "true" << endl;
          return true;}

//if second+j<=first+j, move to the next set of characters and loop
      else if (((unsigned int)S[first+j] <= (unsigned int)S[second+j])){
        cout << "continuing " << first+j << endl;

        j++;
      }

      else return false;
    }
    cout << endl << endl << endl;
}
//------------------------------------------------------
//This function is supposed to rearrange the numbers in indices to match up a properly
//partitioned string (S).
void partition(const string &S, vector<int> &indices, int low, int high, int pivotIndex){
  clock_t clock1 = clock();

  int i=indices[low];
  int j=indices[high-1];


//First, the last index and the pivot index of indices get swapped
    cout << "swapping " << indices[pivotIndex] << " and " << indices[high]<< endl;
  swap(indices[pivotIndex], indices[high]);

//test outputs to see what's going on
  for(int i=0; i<(int)S.length();i++){
    cout << S[indices[i]];
  }

  cout << endl;

  for(int i=0; i<(int)S.length();i++){
    cout << indices[i];
  }

//while i is <= j
  while (i<=j){

//notice more testing
  cout << endl<< "i is " << i << " and j is " << j << " and pivot is " << pivotIndex << endl;
//while indices[i] is <= indices[h], i++
    while (lessThan(S,indices[i],indices[high]) && i<high){
        cout << "i is now: " <<  indices[i] << " " << S[i]<< endl;
        i++;
    }
        cout << "i is now: " <<  indices[i] << " " << S[i]<< endl;

//while indices[h] <= indices[j], j--
    while (lessThan(S,indices[high],indices[j]) && j>low){
         cout << "j is now: " << indices[j] << " " << S[j]<< endl;
          j--;
    }
         cout << "j is now: " << indices[j] << " " << S[j]<< endl;

//after the while loops stop, if i<j, swap i and j
    if(i<j){
      cout << "swapping " << indices[i] << " and " << indices[j]<< endl;
      swap(indices[i], indices[j]);
      i++;
      j--;
    }

      cin.get();
    }
    cout << "swapping " << indices[i] << " and " << indices[high]<< endl;
//the last thing to do is swap high and i
    swap(indices[high],indices[i]);


    for(int k=0; k<(int)S.length();k++){

      cout << indices[k] << " ";
    }

    cout << endl << endl << endl;
  //}

  for(int k=0; k<(int)S.length();k++){

    cout << S[indices[k]] ;
  }

      cout << endl << endl << endl;
      
//ignore the clock stuff
    clock_t clock2 = clock();
    double elapsed = double(clock2-clock1)/CLOCKS_PER_SEC;
    cerr << "Time to run partition is " << elapsed << " seconds." << endl;
    return;
}
