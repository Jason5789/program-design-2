#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main(int argc,char** argv){
    vector<int> corpus_num;
    vector<string> corpus;
    vector<string> keyword;
    ifstream file1;
    file1.open(argv[1]);
    int count=0;

    while(!file1.eof()){
        int count_exp=0;
        string input;
        getline(file1,input);
        if(input.length()==0){
            break;
        }
        char c;
        int num_end = input.find(',');
        corpus_num.push_back( stoi(input.substr(0,num_end)) );
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
    int count2=0;

    while(!file2.eof()){
        string input;
        getline(file2,input);
        if(input.length() == 0){
                break;
        }
        char c;
        int search_num=1;
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
            index[i] = "@" + input.substr(0,first) + "@";
            input.erase(0,first+1);
        }
        size_t found[1];
        float idf[search_num];

        {
            float found_num[search_num];
            for(int i=0 ; i<search_num ; i++){
                found_num[i] = 0;
            }
            
            int in1=-1;
            int in2=-1;
            int in3=-1;

            for(int i=0 ; i<search_num ; i++){
                for(int j=0 ; j<corpus.size() ; j++){
                    found[0] = corpus[j].find(index[i]);
                    if(found[0]!=string::npos){
                        found_num[i]++;
                    }
                }
                double d=corpus.size() / found_num[i];
                idf[i] = log10( d );
            }
        }

        
        float idf_sum[corpus.size()];
        int max_index1=0;
        int max_index2=0;
        int max_index3=0;
        float max_value=0;
        int find_num=0;

        for(int i=0 ; i<corpus.size() ; i++){
          idf_sum[i]=0.0;
          int yes=0;
            for(int j=0 ; j<search_num ; j++){
              found[0] = corpus[i].find(index[j]);
                if(found[0]!=string::npos){
                    idf_sum[i] += idf[j];
                    yes=1;
                }
            }
            if(yes==1 && idf_sum[i]==0){
                idf_sum[i]=-1;
            }
            if(idf_sum[i]>0){
                find_num++;
            }
        }

        int k_range=stoi(argv[3]);

        if(k_range==1){
            if(find_num==0){
                cout << "-1"<<endl;
            }
            else{
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i]){
                        max_value=idf_sum[i];
                        max_index1=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index1>corpus_num[i]){
                        max_index1=corpus_num[i];
                    }
                }

                cout << max_index1 <<endl;
            }
        }
        else if(k_range==2){
            if(find_num==0){
                cout << "-1 -1"<<endl;
            }
            else if(find_num==1){
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i]){
                        max_value=idf_sum[i];
                        max_index1=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index1>corpus_num[i]){
                        max_index1=corpus_num[i];
                    }
                }

                cout << max_index1 << " -1" <<endl;
            }
            else{
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i]){
                        max_value=idf_sum[i];
                        max_index1=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index1>corpus_num[i]){
                        max_index1=corpus_num[i];
                    }
                }
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i] && max_index1!=corpus_num[i]){
                        max_value=idf_sum[i];
                        max_index2=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index2>corpus_num[i] && max_index1!=corpus_num[i]){
                        max_index2=corpus_num[i];
                    }
                }
                cout << max_index1 << " " << max_index2 <<endl;
            }
        }
        else if(k_range==3){
            if(find_num==0){
                cout << "-1 -1 -1"<<endl;
            }
            else if(find_num == 2){
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i]){
                        max_value=idf_sum[i];
                        max_index1=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index1>corpus_num[i]){
                        max_index1=corpus_num[i];
                    }
                }
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i] && max_index1!=corpus_num[i]){
                        max_value=idf_sum[i];
                        max_index2=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index2>corpus_num[i] && max_index1!=corpus_num[i]){
                        max_index2=corpus_num[i];
                    }
                }

                cout << max_index1 << " " << max_index2 << " -1" <<endl;
            }
            else{
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i]){
                        max_value=idf_sum[i];
                        max_index1=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index1>corpus_num[i]){
                        max_index1=corpus_num[i];
                    }
                }
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i] && max_index1!=corpus_num[i]){
                        max_value=idf_sum[i];
                        max_index2=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index2>corpus_num[i] && max_index1!=corpus_num[i]){
                        max_index2=corpus_num[i];
                    }
                }
                max_value=0.0;
                for(int i=0 ; i<corpus.size() ; i++){
                    if(max_value<idf_sum[i] && max_index1!=corpus_num[i] && max_index2!=corpus_num[i]){
                        max_value=idf_sum[i];
                        max_index3=corpus_num[i];
                    }
                    else if(max_value==idf_sum[i] && max_index3>corpus_num[i] &&  max_index1!=corpus_num[i] && max_index2!=corpus_num[i]){
                        max_index3=corpus_num[i];
                    }
                }
                if(max_index2!=0){
                    cout << max_index1 << " " << max_index2 << " " << max_index3 <<endl;
                }
                else{
                    cout << max_index1 << " -1 -1" <<endl;
                }
            }
        }

        
        count2++;
    }
    
    return 0;
}