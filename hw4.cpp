#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Employee{
    public:
        int employee_id;
        int time = 0;
        int max_index = 0;
        vector<int> date;
};

int cal_date(int y , int m , int d){
    int ans;
    int feb = 0;
    int febyear = (y+3)/4 - 503;

    if(y%4==0){
        feb=1;
    }
    switch(m){
        case 1:
            ans = 0;
            break;
        case 2:
            ans = 31;
            break;
        case 3:
            ans = 59+feb;
            break;
        case 4:
            ans = 90+feb;
            break;
        case 5:
            ans = 120+feb;
            break;
        case 6:
            ans = 151+feb;
            break;
        case 7:
            ans = 181+feb;
            break;
        case 8:
            ans = 212+feb;
            break;
        case 9:
            ans = 243+feb;
            break;
        case 10:
            ans = 273+feb;
            break;
        case 11:
            ans = 304+feb;
            break;
        case 12:
            ans = 334+feb;
            break;
    }

    ans = ans + (y-2012)*365 + febyear + d;
    return ans;
}

int cal_year(int y){
    if (y <= 1*1+365*1){
      return 2012;
    }
    else if (y <= 1*1+365*2){
      return 2013;
    }
    else if (y <= 1*1+365*3){
      return 2014;
    }
    else if (y <= 1*1+365*4){
      return 2015;
    }
    else if (y <= 1*2+365*5){
      return 2016;
    }
    else if (y <= 1*2+365*6){
      return 2017;
    }
    else if (y <= 1*2+365*7){
      return 2018;
    }
    else if (y <= 1*2+365*8){
      return 2019;
    }
    else if (y <= 1*3+365*9){
      return 2020;
    }
    else if (y <= 1*3+365*10){
      return 2021;
    }
    else if (y <= 1*3+365*11){
      return 2022;
    }
    else if (y <= 1*3+365*12){
      return 2023;
    }
    else{
        return 2024;
    }
}

int cal_month(int m,int y){
    int count;
    int feb = y/4 - 502;
    if (y == 2012) count=1*0+365*0;
    else if (y == 2013) count=1*1+365*1;
    else if (y == 2014) count=1*1+365*2;
    else if (y == 2015) count=1*1+365*3;
    else if (y == 2016) count=1*1+365*4;
    else if (y == 2017) count=1*2+365*5;
    else if (y == 2018) count=1*2+365*6;
    else if (y == 2019) count=1*2+365*7;
    else if (y == 2020) count=1*2+365*8;
    else if (y == 2021) count=1*3+365*9;
    else if (y == 2022) count=1*3+365*10;
    else if (y == 2023) count=1*3+365*11;

    if(m-count<=31) return 1;
    if(m-count<=59+feb) return 2;
    if(m-count<=90+feb) return 3;
    if(m-count<=120+feb) return 4;
    if(m-count<=151+feb) return 5;
    if(m-count<=181+feb) return 6;
    if(m-count<=212+feb) return 7;
    if(m-count<=243+feb) return 8;
    if(m-count<=273+feb) return 9;
    if(m-count<=304+feb) return 10;
    if(m-count<=334+feb) return 11;
    else return 12;
}

int cal_day(int d,int y,int m){
    int count=0;
    int feb=0;
    if(y%4==0){
      feb=1;
    }
    if (y == 2012) count=1*0+365*0;
    else if (y == 2013) count=1*1+365*1;
    else if (y == 2014) count=1*1+365*2;
    else if (y == 2015) count=1*1+365*3;
    else if (y == 2016) count=1*1+365*4;
    else if (y == 2017) count=1*2+365*5;
    else if (y == 2018) count=1*2+365*6;
    else if (y == 2019) count=1*2+365*7;
    else if (y == 2020) count=1*2+365*8;
    else if (y == 2021) count=1*3+365*9;
    else if (y == 2022) count=1*3+365*10;
    else if (y == 2023) count=1*3+365*11;

    if (m == 2) count+=31;
    else if (m == 3) count+=59+feb;
    else if (m == 4) count+=90+feb;
    else if (m == 5) count+=120+feb;
    else if (m == 6) count+=151+feb;
    else if (m == 7) count+=181+feb;
    else if (m == 8) count+=212+feb;
    else if (m == 9) count+=243+feb;
    else if (m == 10) count+=273+feb;
    else if (m == 11) count+=304+feb;
    else if (m == 12) count+=334+feb;
    
    return d-count;
}

bool compare2(int e1 , int e2){
    if(e1 != e2){
        return e1 < e2;
    }
    else{
        return e1 == e2;
    }
}

bool compare3(Employee e1 , Employee e2){
    if(e1.time != e2.time){
        return e1.time > e2.time;
    }
    else{
      return e1.employee_id < e2.employee_id;
    }
}

int main(int argc,char** argv){
    vector<Employee> emp_vec;
    ifstream file;

    file.open(argv[1]);

    int num = 0;
    int circle=0;
    
    while( !file.eof() ){
            Employee employee;
            string input;
            file >> input;

            if(input.length() != 0){
                circle++;
            }
            else{
                break;
            }
        
            int first = input.find(',');
            int id = stoi( input.substr(0,first) );
            input.erase(0,first+1);
            first = input.find(',');
            input.erase(0,first+1);
            int date_now = stoi( input.substr(0,8) );

            int year = date_now/10000;
            int month = (date_now%10000)/100;
            int day = date_now%100;

            date_now = cal_date(year,month,day);

            int in=0;

            for (int i = 0 ; i < num ; i++){
                if(emp_vec[i].employee_id == id){
                    for(int j=0 ; j<emp_vec[i].time ; j++){
                        if(emp_vec[i].date[j] == date_now){
                            in=2;
                            break;
                        }
                    }
                    if(in != 2){
                        emp_vec[i].date.push_back(date_now);
                        emp_vec[i].time += 1;
                        in=1;
                    }
                    break;
                }
            }
            if(in == 0){
                employee.employee_id = id;
                employee.date.push_back(date_now);
                employee.time += 1;
                emp_vec.push_back(employee);
                num++;
            }
    }

    for(int i = 0 ; i < num ; i++){
        if(emp_vec[i].date.size()>1){
            sort(emp_vec[i].date.begin(),emp_vec[i].date.end(),compare2);
        }
    }

    for(int i =0 ; i < num ; i++){
        int max=0;
        for(int j = 0 ; j<emp_vec[i].time ; j++){
            int index = emp_vec[i].date[j];
                for(int k = j ; k<emp_vec[i].time ; k++){
                    if(index+k-j == emp_vec[i].date[k] ){
                        if(k-j+1 >= max){
                            max = k-j+1;
                            emp_vec[i].max_index = j;
                        }
                    }
                    else{
                        break;
                    }
                }
            
            
        }
        emp_vec[i].time = max;
    }

    sort(emp_vec.begin(),emp_vec.end(),compare3);

    for(int i = 0 ; i < 3 ; i++){
        cout << emp_vec[i].employee_id << "," << emp_vec[i].time;

        int start = emp_vec[i].date[emp_vec[i].max_index];
        int year1 = cal_year(start);
        int month1 = cal_month(start,year1);
        int day1 = cal_day(start,year1,month1);
        cout << "," << year1;
        if(month1 < 10 ) cout<<"0";
        cout << month1;
        if(day1 < 10 ) cout<<"0";
        cout << day1;

        int end=start+emp_vec[i].time-1;
        int year2 = cal_year(end);
        int month2 = cal_month(end,year2);
        int day2 = cal_day(end,year2,month2);
        cout << "," << year2;
        if(month2 < 10 ) cout<<"0";
        cout << month2;
        if(day2 < 10 ) cout<<"0";
        cout << day2 <<endl;
    }

    return 0;
}