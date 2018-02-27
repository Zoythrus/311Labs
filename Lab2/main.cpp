#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;

void collect (string s, vector<string> &text, int i, vector<string> &Z);

template <typename T> vector<string> insert(T &Z){
        for (int i=1; i < (int)Z.size(); i++){
                int j=i;
                string key=Z[j];
                while ((j>=0) && (Z[j-1] > Z[j])){
                  swap(Z[j-1],Z[j]);
                  j--;
                }

        }
        return Z;
}


int main(){

        string s, text;
        vector<string> A, C;

        cin >> s;
        while (cin >> text){

                A.push_back(text);
        }

        collect(s, A, 0, C);


        for (unsigned int i=0; i<C.size(); i++)
            cout << C[i] << ' ';
        cout << endl << endl;

        insert(C);

        for (unsigned int i=0; i<C.size(); i++)
            cout << C[i] << ' ';
        cout << endl;

        return 0;
}

void collect(string s, vector<string> &text, int i, vector<string> &Z) {

        if (i>=(int)text.size())
                return;

        if (text[i].length() >= s.length()) {
                for (unsigned int j=0; j<text[i].length()-s.length(); j++){
                        if (text[i].substr(j, (s.length())) == s){
                                if (j==0){
                                        Z.push_back(text[i].substr(s.length(),text[i].length()));
                                }
                                else if ((j+s.length())==text[i].length()){
                                        Z.push_back(text[i].substr(0,j));
                                }
                                else{
                                        Z.push_back(text[i].substr(0,j)+text[i].substr(j+s.length(),text[i].length()-(j+s.length())));
                                }
                        }
                }
        }

        collect(s, text, ++i, Z);
}
