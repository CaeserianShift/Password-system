//Author CaeserianShift
//Time BST 13:40
//Language c++
//compiler: repl.it


#include <iostream>
#include <fstream>
#include <string>
#include "sha256.h"
using namespace std;

//my variables
string pass, user, login, gmail, signup, answer, line, sha256userpass, saltpass, saltuser, saltgmail, salt;
int main(int argc, char *argv[]){
  //salts for the hashes
  //change and do not give this out. This would allow for decreased time for bruteforce if salt is known.
  saltpass = "Abr$2JCQWW1adbRR31!$";
  saltuser = "Dd2r!$f££f3h!fwfeg£f";
  saltgmail = "ADqw2d131?234222q132";
  salt = "£fAdsqwdBEtg32$££wf#24fwfe";
  //input to see if user wants to login or signup
  cout << "do you want to signup or login?[s,l]: ";
  cin >> answer;
  if (answer == "s"){
    //the user input for the signup
    cout << "pass: ";
    cin >> pass;
    cout <<"\nusername: ";
    cin >> user;
    cout <<"\ngmail: ";
    cin >> gmail;
    //hashing the users data with the salt at the start
    string sha256pass = sha256(saltpass + pass);
    string sha256user = sha256(saltuser + user);
    string sha256gmail = sha256(saltgmail + gmail);
    //opens a file called password.txt
    ofstream myfile;
    myfile.open ("password.txt",ios::out | ios::app);
    //adds the whole hashed pass username gmail and adds to one salt hashed variable
    sha256userpass = sha256(salt + sha256pass + sha256user + sha256gmail);
    //writes to the file and closes
    myfile << sha256userpass << endl;
    myfile.close();
  }
  else if (answer == "l"){
    //the user input for the login
    cout << "pass: ";
    cin >> pass;
    cout <<"\nusername: ";
    cin >> user;
    cout <<"\ngmail: ";
    cin >> gmail;
    //hashes inputs with using the salts
    string sha256pass = sha256(saltpass + pass);
    string sha256user = sha256(saltuser + user);
    string sha256gmail = sha256(saltgmail + gmail);
    //adds the whole hashed pass username gmail and adds to one salt hashed variable
    sha256userpass = sha256(salt + sha256pass + sha256user + sha256gmail);
    //opens the file password.txt
    ifstream  stream1("password.txt");
    //uses the line variable as the line with the same as the vriable
    string line ;
    //sets a bool value to found
    bool found = false;
    //getline with the line and stream1 aka the file password.txt
    while( std::getline( stream1, line ) && !found)
      {
        if(line.find(sha256userpass) != string::npos){ // looks for the variable in the text file
            cout << "you have logged on.\n";
            found = true;
            break;
        }
        else{
          //was not found meaning it was wrong
          found = false;
          cout << "Sorry password or username is wrong.\nTry again later.\n";
          break;
        }
      }      
  }
  else{
    // the format of s,l was not used so it was ignored.
    cout << "Use [s,l].\nTry again later.\n";
  }
  return 0;
}
