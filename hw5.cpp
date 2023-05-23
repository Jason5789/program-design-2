#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc,char** argv){
    vector<string> corpus_num;
    vector<string> corpus;
    vector<string> keyword;
    ifstream file1;
    file1.open(argv[1]);
    int count=0;

    while(!file1.eof()){
        int count_exp=0;
        string input;
        getline(file1,input);
        char c;
        int num_end = input.find(',');
        corpus_num.push_back(input.substr(0,num_end));
        for(int i=0 ; i<input.length() ; i++){
            c=input[i];
            input[i] = tolower(c);
            if(input[i]==' '){
                input[i]='@';
            }
            else if(input[i]>='a' && input[i]<='z'){
            }
            else if(input[i]>='A' && input[i]<='Z'){
            }
            else{
                for(int j=i ; j<input.length()-1 ; j++){
                    input[j] = input[j+1];
                }
                count_exp++;
                input[input.length()-count_exp]=' ';
                i--;
            }
        }
        input = "@" + input + "@";
        corpus.push_back(input);
        count++;
    }

    ifstream file2;
    file2.open(argv[2]);
    count=0;

    while(!file2.eof()){
        vector<int> ans;
        string input;
        getline(file2,input);
        if(input.length() == 0){
                break;
        }
        char c;
        int search_num=1;
        int front=0;
        int back=1;
        for(int i=0 ; i<input.length() ; i++){
            c=input[i];
            if(c!=' '){
               input[i] = tolower(c); 
            }
            else{
                search_num++;
            }
        }
        keyword.push_back(input);
        string index[search_num];
        for(int i=0 ; i<search_num ; i++){
            int first = input.find(' ');
            string temp = input.substr(0,first);
            temp = "@" + temp + "@";
            index[i] = temp;
            input.erase(0,first+1);
        }
        size_t found[search_num];
        int no;
        int access=0;
        for(int i=0 ; i<corpus.size() ; i++){
            no=0;
            for(int j=0 ; j<search_num ; j++){
                found[j] = corpus[i].find(index[j]);
                if(found[j]==string::npos){
                    no=1;
                    break;
                }
            }
            if(no==0){
                ans.push_back(stoi(corpus_num[i]));
                access = 1;
            }
        }
        if(access==0){
            cout<< "-1";
        }
        else{
            sort(ans.begin(),ans.end());
            cout << ans[0];
            for(int i=1 ; i<ans.size() ; i++){
                cout << " " <<ans[i];
            }
        }
        cout<<endl;
        

        count++;
    }
    
    return 0;
}