#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Employee{
    public:
        int employee_id;
        int age;
        int gender;
        int salary;
        string data;
};

bool compare(Employee e1 , Employee e2){
    if(e1.salary != e2.salary){
        return e1.salary < e2.salary;
    }
    else if(e1.age != e2.age){
        return e1.age < e2.age;
    }
    else if(e1.gender != e2.gender){
        return e1.gender < e2.gender;
    }
    else{
        return e1.employee_id < e2.employee_id;
    }
}

int main(int argc,char** argv){
    Employee employee[10100];
    ifstream file;

    file.open(argv[1]);

    int num = 0;
    while( !file.eof() ){
        file >> employee[num++].data;
    }
    
    if(employee[num-1].data.length() == 0){
    	num--;
    }

    for (int i=0 ; i<num ; i++){
        string data_temp = employee[i].data;
        int first = data_temp.find_first_not_of("1234567890");
        employee[i].employee_id = stoi( data_temp.substr(0,first) );
        data_temp.erase(0,first+1);

        first = data_temp.find_first_not_of("1234567890");
        employee[i].age = stoi( data_temp.substr(0,first) );
        data_temp.erase(0,first+1);

        first = data_temp.find_first_not_of("1234567890fm");
        string gend = data_temp.substr(0,first);
        if(gend == "f"){
            employee[i].gender = 0;
        }
        else{
            employee[i].gender = 1;
        }
        data_temp.erase(0,first+1);
	
	first = data_temp.find_first_not_of("1234567890");
        employee[i].salary = stoi( data_temp.substr(0,first) );
    }

    sort(employee,employee+num,compare);

    int now_salary = 0;
    for(int i=0 ; i<num ; i++){
        if( now_salary != employee[i].salary ){
            if(i != 0){
                cout << endl;
            }
            now_salary = employee[i].salary;
            cout << now_salary ;
        }
        cout << "," << employee[i].employee_id; 
    }

    cout<<endl;

    return 0;
}