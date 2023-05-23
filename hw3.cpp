#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Employee{
    public:
        int employee_id;
        int action;
        int date;
        int hour;
        int min;
        string data;
};

bool compare(Employee e1 , Employee e2){
    if(e1.employee_id != e2.employee_id){
        return e1.employee_id < e2.employee_id;
    }
    else if(e1.date != e2.date){
        return e1.date < e2.date;
    }
    else if(e1.hour != e2.hour){
        return e1.hour < e2.hour;
    }
    else{
        return e1.min < e2.min;
    }
}

int main(int argc,char** argv){
    Employee employee[10100];
    ifstream file;

    file.open(argv[1]);

    int num = 0;
    while( !file.eof() ){

        file >> employee[num++].data;
    

        if(employee[num-1].data.length() == 0){
            num--;
        }

        for (int i=0 ; i<num ; i++){
            string data_temp = employee[i].data;
            int first = data_temp.find(',');
            employee[i].employee_id = stoi( data_temp.substr(0,first) );
            data_temp.erase(0,first+1);

            first = data_temp.find(',');
            string act = data_temp.substr(0,first);
            if(act == "sign-in"){
                employee[i].action = 0;
            }
            else{
                employee[i].action = 1;
            }
            data_temp.erase(0,first+1);

            employee[i].date = stoi( data_temp.substr(0,8) );
            data_temp.erase(0,8);
            employee[i].hour = stoi( data_temp.substr(0,2) );
            data_temp.erase(0,2);
            employee[i].min = stoi( data_temp.substr(0,2) );
        }

        sort(employee,employee+num,compare);

        int now_id = 0;
        int employee_num = 0;
        int ans[num+1][3];
        for(int i=0 ; i<num ; i++){
            if(ans[employee_num][0] != employee[i].employee_id){
                employee_num++;
                ans[employee_num][0] = 0;
                ans[employee_num][1] = 0;
                ans[employee_num][2] = 0;
                ans[employee_num][0] = employee[i].employee_id;
            }

            if( (employee[i].employee_id == employee[i+1].employee_id) && (employee[i].action == 0) && (employee[i+1].action == 1) && (employee[i+1].date == employee[i].date) ){
                if( ( (employee[i+1].hour - employee[i].hour)*60 + employee[i+1].min - employee[i].min ) > 480 ){
                    ans[employee_num][1]++;
                }
                i++;
            }
            else{
                ans[employee_num][2]++;
            }
            
        }

        

    }
    
    for(int i=1 ; i<=employee_num ; i++){
        cout << ans[i][0] << ","<< ans[i][1] << "," << ans[i][2] <<endl;;
     }

    return 0;
}