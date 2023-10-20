//Simran Mann
//301542808
//sma308@sfu.ca

#include "a4_birthdayBST.hpp"
#include "a4_birthdaylib.hpp"

#include <fstream> //needed to work with files 

int main(){
    cout<<"===================================================="<<endl; 
    cout<<"===========Famous Birthdays Lookup System==========="<<endl;
    cout<<"=====================Simran Mann===================="<<endl;
    cout<<"===================================================="<<endl; 

    int input=0; //initialize a vairable to keep track of the users option 
    int file_counter=0; //to keep track of how many files are opened 

    BirthdayBST bdaytree; //automatically calls its constructor 

     while (input != 6) { //6 terminates the program 
        cout<<"Press numbers 1-6 for the following options and then enter:"<<endl; 
        cout<<"1) to load a birthday file."<<endl; 
        cout<<"2) to list birthdays sorted by month day."<<endl;
        cout<<"3) to lookup a birthday."<<endl;
        cout<<"4) to add a birthday."<<endl;
        cout<<"5) to save a birthday file."<<endl;
        cout<<"6) to terminate the program."<<endl;

        string filename; //define the filename to be scanned 
        cin>>input; 

        if (input==1){
            cout<<"Enter the full name of the birthday file (with extension):"<<endl; 
            cin>>filename;
            ifstream file(filename); 
            if(!file.is_open()){
                cout<<"Unable to open file."<<endl; 
            }else{
                
                if (file_counter>0){//if 2 or more files are opened, clear the array 
                    bdaytree.reset();//function to free memory in current BST
                }
               //read the information from each line 
                string date; 
                while (getline(file, date)) {//load entries and add create the BST 
                        string name;  //initalize char for name and knownFor 
                        string knownFor;

                        short year; //initialize int values for the date 
                        short month; 
                        short day;
                        
                        string year1;
                        string day1; 
                        string month1; 
                        year1=date.substr(0,4);
                        year =stoi(year1); 

                        month1=date.substr(5, 2);
                        month=stoi(month1); 

                        if (month<10){
                            day1=date.substr(7, 2);
                        }else{
                            day1=date.substr(8,2);
                        }
                        day=stoi(day1);

                        getline(file,name); 
                        getline(file, knownFor);

                        string extra;
                        getline(file, extra); //===== line 

                        //create a pointer to the birthday struct of that person 
                        Birthday* person= create_Birthday(year, month, day, name, knownFor); 

                        bdaytree.insertNode(person);
                }
             
            /*// file_counter increments each time so we know to reset
            the BST nexttime option 1 is called */
            file_counter++; 
            cout<<bdaytree.getSize()<<" entries loaded"<<endl;
            file.close();
            }
            cout<<"===================================================="<<endl;
        }else if (input ==2){//inorder traversal of BST 
            if (bdaytree.getSize() ==0){ //if BST is empty there is no file loaded 
                cout<<"No file loaded. Load one first"<<endl;
            }else{
                bdaytree.inOrderPrint(cout); 
            }
        }else if (input ==3){//search for a matching bday 
            if (bdaytree.getSize() ==0){
                cout<<"No file loaded. Load one first"<<endl;
            }else{
                int month; 
                int day; 
                cout<<"What is the month?"<<endl; 
                cin>>month; 
                cout<<"What is the day?"<<endl; 
                cin>>day; 

                //if findNodeByMD returns a bday struct pointer, it found a matching bday 
                if(bdaytree.findNodeByMD(month, day)!=NULL){
                    //call the function to find and print all matches 
                    bdaytree.printAllNodeWithMatchingMD(month, day, cout); 
                }else{
                    cout<<"No such birthday on record"<<endl;
                }
            }
            
        }else if (input ==4){//add a birthday to current file 
            if (bdaytree.getSize() ==0){
                cout<<"No file loaded. Load one first"<<endl;
            }else{
                int year;
                int month;
                int day;
                string name, knownFor; 
                cout<<"What is the year?"<<endl;
                cin>>year; 
                cout<<"What is the month?"<<endl;
                cin>>month; 
                cout<<"What is the day?"<<endl;
                cin>>day; 
                cout<<"What is the name? ";
                getline(cin>>ws, name);//use getline to read whitespaces 
                cout<<"What are they known for? ";
                getline(cin>>ws, knownFor);//use getline to read whitespaces 

                /*if findNodeByYMDN returns a valid bday struct pointer, 
                it has the same name, year, month and day so we dont add it to the BST*/

                Birthday* match=bdaytree.findNodeByYMDN (year, month, day, name);

                if (match==NULL){//if there is no same entry, add the info 
                    Birthday* new_bday=create_Birthday(year, month, day, name, knownFor);
                    bdaytree.insertNode(new_bday);
                    cout<<"Birthday added. There are now "<<bdaytree.getSize()<<" entries"<<endl;
                }else{//there is an entry with the same info 
                    cout<<"There is an entry with the same birthday and name. Nothing added."<<endl;
                }
                cout<<"===================================================="<<endl; 
            }
        }else if (input ==5){//save bday entries to a new file
            if (bdaytree.getSize() ==0){
                cout<<"No file loaded. Load one first"<<endl;
            }else{
                string newFilename;

                cout<<"Enter the full name of the newfile (with extension):"<<endl; 
                cin>>newFilename; 

                ofstream fout(newFilename); //new file to write to
                bdaytree.inOrderPrint(fout);//function to write inorder traversal to the file
                //report number of entries 
                cout<<bdaytree.getSize()<<" entries saved."<<endl;
                cout<<"===================================================="<<endl; 
            }
        }
    }
    return 0;
}
