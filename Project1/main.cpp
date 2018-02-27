#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

void readFromFile(string &S, string filename);
char convertToLower(char ch);
int select(const string &S, vector<int> &v, int start, int fin, int k);
void init(vector<string> &v, string fileName);
int partition(const string &S,vector<int> &A, int low, int high, int index);
bool lessThan(const string &S, int first, int second);
void insertion(const string &S, vector<int> &indices, int low, int high);
void quicksort(string &S, vector<int> &A, int low, int high);

int main(int argc, char* argv[]){

  string s;
  vector<int> A, B;
  vector<string> text2;

//This is the readFromFile function

    readFromFile(s,argv[1]);
    for(int i=0; i<(int)s.length();i++){
      //cout << s[i];
      A.push_back(i);
      B.push_back(i);
    }

    //cout << endl;

    if (argc==2){

      cerr << "Length of S: " << s.length() << endl;
      clock_t clock1 = clock();
      quicksort(s, A, 0, A.size()-1);
      clock_t clock2 = clock();
      double elapsed = double(clock2-clock1)/CLOCKS_PER_SEC;
      cerr << "Time for Quicksort: " << elapsed << endl;

      clock_t clock3 = clock();
      insertion(s, B, 0, B.size()-1);
      clock_t clock4 = clock();
      double elapsed2 = double(clock4-clock3)/CLOCKS_PER_SEC;
      cerr << "Time for Insertion: " << elapsed2 << endl;

    }

    else if (argc==3){

      cerr << "Length of S: " << s.length() << endl;
      clock_t clock1 = clock();
      quicksort(s, A, 0, A.size()-1);
      clock_t clock2 = clock();
      double elapsed = double(clock2-clock1)/CLOCKS_PER_SEC;
      cerr << "Time for Quicksort: " << elapsed << endl;

      clock_t clock3 = clock();
      select(s, B, 0, B.size()-1, atoi(argv[2]));
      clock_t clock4 = clock();
      double elapsed2 = double(clock4-clock3)/CLOCKS_PER_SEC;
      cerr << "Time for Selection: " << elapsed2 << endl;

    }

    else if (argc==4){

      cerr << "Length of S: " << s.length() << endl;
      clock_t clock1 = clock();
      select(s, B, 0, B.size()-1, atoi(argv[2]));
      clock_t clock2 = clock();
      double elapsed = double(clock2-clock1)/CLOCKS_PER_SEC;
      cerr << "Time for Selection: " << elapsed << endl;

      clock_t clock3 = clock();
      insertion(s, B, 0, B.size()-1);
      clock_t clock4 = clock();
      double elapsed2 = double(clock4-clock3)/CLOCKS_PER_SEC;
      cerr << "Time for Insertion: " << elapsed2 << endl;

    }
/*
    init(text2, argv[2]);

    for (int i=0; i<index.size()-1;i++)
    select(s, index, 0, index.size()-1, 0);

    for(int i=0; i<(int)s.length();i++){
      cout << text2[index[i]] << " ";
    }
    cout << endl;
*/
}//main

//------------------------------------------------------
//readFromFile opens the file, then loops through the text,
//and throws the output into a stringvoid insertion(const string &S, vector<int> &indices, int low, int high)
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

void quicksort(string &S, vector<int> &A, int low, int high){
  //cout << low << " " << high << " " << endl;

  if(low < high){
    int pivotIndex = partition(S, A, low, high,0);
    //cout << "pivot is: " <<  pivotIndex<<endl;
    quicksort(S, A, low, pivotIndex - 1);
    quicksort(S, A, pivotIndex + 1, high);
  }
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
