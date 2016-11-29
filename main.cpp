#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <windows.h>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <string>
#include <windows.h>
#include <queue>
#include <ctime>
#include <time.h>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

time_t then, now;  //GLOBAL VARIABLES
COORD coord={0,0}; //GLOBAL VARIABLE

void sleep(unsigned int ms){
clock_t goal = ms*1000*60 + clock();
while(goal>clock());
}

void add_website(string name){
ofstream log("C:/Windows/System32/drivers/etc/hosts", std::ios_base::app | std::ios_base::out);
log << ("127.0.0.1 "+name+'\n');
name = "www."+name;
log << ("127.0.0.1 "+ name+'\n');
log.close();
}

void remove_website(){
vector <string> example;
string str,x;
fstream log("C:/Windows/System32/drivers/etc/hosts");
while(getline(log,str)){
    if(str[0]=='#'){
        example.push_back(str);
    }
}
log.close();
remove("C:/Windows/System32/drivers/etc/hosts");
ofstream output_file("C:/Windows/System32/drivers/etc/hosts");
ostream_iterator<string> output_iterator(output_file, "\n");
copy(example.begin(), example.end(), output_iterator);
}



string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

void display_notif(string message){
message = "msg * "+message;
system(message.c_str());
}

void gotoXY (int x, int y){
coord.X = x; coord.Y = y; // X and Y coordinates
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char Menu(string title){
system("cls");
cout<<"Press ! --> exit; \n      '~' --> Menu;";
gotoXY(65,0);
system("date /t");
for(int w=0;w<160;++w) cout<<'_';
gotoXY(40-(title.length())/2,3); cout<<title; gotoXY(0,6);
gotoXY(29,5); cout<<"PRESS THE OPTION NUMBER\n\n\n";
cout<<"[1] Set the websites.\n\n\n[2] Set the applications. \n\n\n[3] View currently running applications.\n\n\n[4] Readme\n\n";
char w;
cout<<"> ";
cin>>w;
return w;
}

vector <string> listreader(){
    system("tasklist /nh > list.txt");
    string str,check;
    vector <string> APPS;
    int size_string;
    ifstream F("list.txt");
    while(F)
    {
        check="";
       F>>str;
       size_string = str.size();
       check+=str[size_string-3];
       check+=str[size_string-2];
       check+=str[size_string-1];
       if(check=="exe"){
        APPS.push_back(str);
       }
    }
    F.close();
return APPS;
}

void kill_app(string app){
system(("taskkill /f /im "+app).c_str());
cout<<"[*]Killed "<<app<<endl<<endl;
}

int main()
{
    vector <string> running_apps,Apps_list;
    vector <int> timer;
    queue<string> Apps;
    char choice;
    string app,website;
    int N_apps,x,timer_web;

    running_apps.clear();
    timer.clear();
//    Apps.clear();

start:
    choice = Menu("Self Control - Main Menu");
    if(choice=='~')
        goto start;
    else if(choice == '!')
            return 0;
    else if(choice =='3'){
        system("tasklist \nh");
        cout<<"\n\n";
        system("pause");
        goto start;
    }
    else if(choice == '1'){
    system("cls");
    cout<<"[*]Enter number of websites to handle\n";
    cout<<">"; cin>>N_apps;
    cout<<"[*]Enter time limit (mins)\n";
    cout<<">"; cin>>timer_web;

    for(int i=0;i<N_apps;i++){
        cout<<"Enter website > ";
        cin>>website;
        add_website(website);
    }
    cout<<endl<<endl;
    display_notif("Websites have been blocked for " + IntToString(timer_web*60) + " seconds");

    sleep(timer_web);
    remove_website();
    display_notif("Websites have been unblocked");
    cout<<"\nWebsites have been unblocked\n";

    }

else if(choice=='2'){
    system("cls");
    cout<<"[*]Enter number of applications to handle\n";
    cout<<">"; cin>>N_apps;

    for(int i=0;i<N_apps;i++){
        cout<<"Enter "<<i+1<<" Application name >";
        cin>>app;
        app.append(".exe");
        Apps.push(app);
        Apps_list.push_back(app);
        cout<<"Enter time limit >";
        cin>>x;
        timer.push_back(x);
    }


system("cls");
running_apps = listreader();
string name;
x=timer[0];//1
name = Apps.front();

display_notif(name+" will be killed in " + IntToString(x*60) + " seconds");
sleep(x);
kill_app(name);
Apps.pop();
for(int i=1;i<timer.size();i++){
name = Apps.front();
x=timer[i]-timer[i-1];
display_notif(name+" will be killed in " + IntToString(x*60) + " seconds");
sleep(x);
kill_app(name);
Apps.pop();
}
}

else if(choice=='4'){
    system("cls");
    fstream read("readme.txt");
    string line;
    while(getline(read,line))
        cout<<line<<endl;


    read.close();
system("pause");
goto start;
}

else
    goto start;

return 0;
}

