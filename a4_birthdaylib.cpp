

#include "a4_birthdaylib.hpp"

#include <iostream>//needed for printing


Birthday* create_Birthday(short year, short month, short day, string name, string knownFor){
    
    //use new to allocate memory for the struct pointer
    Birthday* Birthday_ptr= new Birthday; 
    
    /*dereference the pointer to access each member variable
    and assign it the corresponding value that is passed to the function*/ 
    Birthday_ptr->year= year; 
    Birthday_ptr->month = month; 
    Birthday_ptr->day= day; 
    Birthday_ptr->name.append(name);
    Birthday_ptr->knownFor.append(knownFor); 

    return Birthday_ptr; //return pointer to the brithday struct 
}

//helper function for comparing birthdays by month and day
//-ve means p1 is "smaller" than p2, +ve means the other way
//0 means they are "the same"
int compareBirthdaysByMD( const Birthday* p1, const Birthday* p2){

    if (p1->month > p2->month){
        return 1;
    }else if (p1->month < p2->month){
        return -1;
    }else {//same month 
        if (p1->day >p2->day){
            return 1;
        }else if (p1->day < p2->day){
            return -1;
        }else{//same date 
            return 0;
        }
    }
}

void print_Birthday(Birthday* person, ostream& os){
    os<<person->year<<"-"<<person->month<<"-"<<person->day<<endl; 
    os<<person->name<<endl<<person->knownFor<<endl;
    os<<"===================================================="<<endl; 
}

//delete birthday function
void delete_Birthday(Birthday* person){
    delete person;
}

