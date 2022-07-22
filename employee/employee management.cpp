#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>

using namespace std;

const char* filename="employee.txt";
class  Employee{
    private:
    int EmpId ;
    char EmpName[40],Post[30], Department[20];
    float Salary;
    public:
    void ReadData(){
        cout<<"\n"<<"Enter Employee ID\n";
        cin>>EmpId;
        cout<<"\n"<<"Enter Employee Name\n" ;
        cin>>EmpName;
        cout<<"\n"<<"Enter Employee Post\n";
        cin>>Post;
        cout<<"\n"<<"Enter Department\n";
        cin>>Department;
        cout<<"\n"<<"Enter Salary\n";
        cin>>Salary;
        };
    int GetID(){
        return EmpId;
    }
    void DispRec(){
        cout<<endl<<"---------------------";
        cout<<setw(5)<<EmpId<<setw(5) << EmpName<<setw(5)<<Post<< setw(5)<<Department<< setw(5)<< Salary;
        
    }
    char* GetDept(){
        return Department;
    }
    
};
int main(){
    Employee emp,e;
    int recno=0;
    char option,ch,Dept[20];
    int Id,isFound;
    fstream empfile(filename,ios::in | ios::out |ios::ate |ios::binary);
    if(!empfile){
        return 1;
    }
    // Selection Menu
    do{
    cout<<"*******Menu********";
    cout<<endl<<"Enter your option";
    cout<<endl<<"1 => Add a new record";
    cout<<endl<<"2 => Search record from employee id";
    cout<<endl<<"3 => List Employee of particular department";
    cout<<endl<<"4 => Display all employee";
    cout<<endl<<"5 => Update record of an employee";
    cout<<endl<<"6 => Delete record of particular employee";
    cout<<endl<<"7 => Exit from the program"<<endl;
    cout<<"********************"<<endl;
    cin>>option;
    //processing the input
    switch(option){
        case '1':
        emp.ReadData();
        empfile.seekg(0,ios::beg);
        isFound=0;
        empfile.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
           if(e.GetID()==emp.GetID()){    
                cout<<"this ID already exists.. Try for another ID";
                isFound=1;
                break;
           } 
           empfile.read((char*)&e,sizeof(e));
        }
        if(isFound==1)
        break;
        empfile.clear();
        empfile.seekp(0,ios::end);
        empfile.write((char*)&emp, sizeof(emp));
        cout<<endl<<"NEw record has been added successfully";
        break;
        
//------------------------------------------------------------------------
        case '2':
        isFound==0;
        cout<<endl<<"Enter Employee Id too be Searched";
        cin>>Id;
        empfile.seekg(0,ios::beg);
        empfile.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
            if(e.GetID()==Id){
                cout<<endl<<"The Record was Found";
                cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary" ;
                e.DispRec();
                isFound=1;
                break;
            }
        empfile.read((char*)&e,sizeof(e));
        }
        empfile.clear();
        if(isFound=0)
            cout<<endl<<"The Id was not Found";
        break;
        

//------------------------------------------------------------------------
        case '3':
        
        isFound=0;
        cout<<endl<<"Enter the name of the department to search";
        cin>>Dept;
        empfile.seekg(0,ios::beg);
        empfile.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
            if(strcmp(e.GetDept(),Dept)==0){
                cout<<endl<<"Record was found in this Department";
                cout<<endl<<setw(5)<<"Id"<< setw(15)<<"Name"<<setw(15) <<"Post"<<setw(15) <<"Department"<<setw(8) <<"Salary";
            e.DispRec();
            isFound=1;
            break;
            }
            empfile.read((char*)&e,sizeof(e));
        }
        empfile.clear();
        if(isFound==0)
            cout<<endl<<"Data not found";
        break;
//------------------------------------------------------------------------
        case '4':{
        cout<<endl<<"record of Employee";
        empfile.clear();
        empfile.seekg(0,ios::beg);
        int counter=0;
        empfile.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
            counter++;
            if(counter==1){
            cout<<endl<<setw(5)<<"ID"<<setw(15)<<"Name"<<setw(15)<<"Post"<<setw(15)<<"Department"<<setw(8)<<"Salary";
            }
            e.DispRec();
            empfile.read((char*)&e,sizeof(e));
        }
        cout<<endl<<counter<<"Records Found";
        empfile.clear();
        break;
        }
//------------------------------------------------------------------------    
        case '5':{
        int recno=0;
        cout<<endl<<"Modification Initialized";
        cout<<endl<<"Enter the Employee ID to edit";
        cin>>Id;
        isFound=0;
        empfile.seekg(0,ios::beg);
        empfile.read((char*)&e,sizeof(e));
        while(empfile.eof()){
            recno++;
            if(e.GetID()==Id){
                cout<<"The Old record of Employee having ID"<<Id<<"is:";
                e.DispRec();
                isFound=1;
                break;
            }
            empfile.read((char*)&e,sizeof(e));
            }
        if(isFound==0){
            cout<<"Data not found for given Employee Id"<<Id;
            break;
        }    
        empfile.clear();
        int location=(recno-1)*sizeof(e);
        empfile.seekg(location,ios::beg);
        cout<<endl<<"Enter new record for employee having ID"<<Id;
        e.ReadData();
        empfile.write((char*)&e,sizeof(e));
        break;
        }
//------------------------------------------------------------------------
        case '6':{
        recno=0;
        cout<<endl<<"enter employee Id to be deleted";
        cin>>Id;
        isFound=0;
        empfile.seekg(0,ios::beg);
        empfile.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
            recno++;
            if(e.GetID()==0){
                cout<<endl<<"Employee Having Id"<<Id<<"is:";
                e.DispRec();
                isFound=1;
                break;
            }
            empfile.read((char*)&e,sizeof(e));
            }      
            char tempfile[]="tempfile.txt";
            fstream temp(tempfile, ios::out | ios ::ate |ios::binary) ;

        if(isFound==0){
            cout<<"the Employee with Id"<<Id<<"was not found:"; 
            break;
        }  
        else {
            empfile.clear();
            empfile.seekg(0,ios::beg);
            empfile.read((char*)&e,sizeof(e));
            while(!empfile.eof()){
                if(e.GetID()!=Id)
                temp.write((char*)&e,sizeof(e));
                empfile.read((char*)&e,sizeof(e));
                
            }
        empfile.close();
        temp.close();
        temp.open(tempfile,ios::in | ios::binary);
        empfile.open(filename,ios::out | ios::binary);
        temp.read((char*)&e,sizeof(e));
        while(!empfile.eof()){
            empfile.write((char*)&e,sizeof(e));
            temp.read((char*)&e,sizeof(e));
            }
        }
        temp.close();
        empfile.close();
        remove(tempfile);
        empfile.open(filename , ios::ate | ios::in | ios::out | ios::binary);
        break;
        }
//------------------------------------------------------------------------
        case '7':{
        exit(0);
        break;
        }
//------------------------------------------------------------------------
        default:
        cout<<"invalid option selected ";
        }     
    cout<<"\ndo you really want to continue? ......y/n ";
    cin>>ch;
    }while(ch!='n');
empfile.close();
}

