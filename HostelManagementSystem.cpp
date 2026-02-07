#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class hostel
{
    int sid[100],taka[100],c;
    string ch[100];
public:

    hostel()
    {
        this->c=0;
    }

    void header();
    void welcome();
    int idposition(int sid);
    void program_close();

    void available_room();

    vector<int>rnumber;
    vector<int>rfloor;
    vector<int>rcategory;

    void get_roominfo();
    void add_room();
    void update_room();
    void display_room();
    void search_room();
    void delete_room();
    int room_position(int n);
    int greator_rnum();
    int cheikh_room(int roomid);
    int avi_room(int roomid);
    void room_close();

    vector<int> studentid;
    vector<string>studentname;
    vector<int>studentroom;

    int student_id_maker();
    void get_studentinfo();
    void display_student();
    void search_student();
    void update_student();
    void add_student();
    void delete_student();
    void student_clear();
    void student_insert();
};

void hostel::program_close()
{
    student_clear();
    student_insert();
    room_close();
}

void hostel::display_room()
{
    printf("\t\t\t\t\t\tDisplay All Room Information\n");
    printf("\t\t\t\t\t============================================");
    printf("\n\n");
    printf("\t\t   Room Number\t\t Floor Number \t\t Room Category \t\t Room Status\n");
    printf("\t\t  ============\t\t===============\t\t=============\t\t==============\n\n");
    for(int j=0; j<rnumber.size(); j++)
    {
        cout << right  << setw(25) <<  this->rnumber[j] << right << setw(22)
             << this->rfloor[j]  << setw(22) << rcategory[j]
             << setw(27) << "Avilabol"<< '\n';
    }
    cout << "\n";
}

void hostel::get_roominfo()
{
    int rnum,rfloor1,rcat;
    int c1=0;
    ifstream info;
    info.open("room.txt");
    while(!info.eof())
    {
        string name1[2],name2[2],name3[3];

        if(c1==0 || c1==1)
        {
            info >> name1[0] >> name2[0] >> name3[0];
        }
        else
        {
            info >> rnum >> rfloor1 >> rcat;
            rnumber.push_back(rnum);
            rfloor.push_back(rfloor1);
            rcategory.push_back(rcat);
        }
        c1++;
    }
    info.close();
}

void hostel::add_room()
{
    printf("\t\t\t\t\t\t\tAdded New Room\n");
    printf("\t\t\t\t\t============================================");

    printf("\n\n");
    int num,floor,category;
    num=greator_rnum();
    cout << "\t\t\t\t\t\tNew Room Number is: " << num << "\n";
    cout <<"\t\t\t\t\t\tEnter New Room Floor: ";
    cin >> floor;
    cout << "\t\t\t\t\t\tEnter New Room Category Number: ";
    cin >> category;
    rnumber.push_back(num);
    rfloor.push_back(floor);
    rcategory.push_back(category);
    cout << "\n\t\t\t\t\t\tSucessfully Added New Data\n\n";
}

void hostel::update_room()
{
    printf("\t\t\t\t\t\tUpdate Room Information\n");
    printf("\t\t\t\t\t=========================================");

    printf("\n\n");
    int num,floor,category;
    cout << "\t\t\t\t\t\tEnter Room Number: ";
    while(cin >> num)
    {
        if(num==-1)break;
        int position=room_position(num);

        if(position!=-1)
        {
            cout << "\t\t\t\t\t\tEnter Room Floor: ";
            cin >> floor;
            rfloor[position]=floor;
            cout << "\t\t\t\t\t\tEnter Room Category:";
            cin >> category;
            rcategory[position]=category;
            cout << "\n\t\t\t\t\tSucessfully Update Room Information Info\n\n";
            break;
        }
        else
        {
            cout << "\n\t\t\t\t\tSorry No user id found for name update\n\n";
            cout << "\t\t\t\t\tEnter Room Number or exit press (-1): ";
        }
    }
}

void hostel::delete_room()
{
    printf("\t\t\t\t\t\t\tDelete Room Information\n");
    printf("\t\t\t\t\t============================================");

    printf("\n\n");

    int rid,position;
    vector<int>rnumber1,rfloor1,rcategory1;
    cout << "\t\t\t\t\t\tEnter Room Number: ";
    while(cin >> rid)
    {
        if(rid==-1)break;
        position=room_position(rid);
        if(position!=-1)
        {
            for(int i=0; i<position; i++)
            {
                rnumber1.push_back(rnumber[i]);
                rfloor1.push_back(rfloor[i]);
                rcategory1.push_back(rcategory[i]);
            }
            for(int i=position; i<rnumber.size()-1; i++)
            {
                rnumber1.push_back(rnumber[i+1]);
                rfloor1.push_back(rfloor[i+1]);
                rcategory1.push_back(rcategory[i+1]);
            }
            rnumber=rnumber1;
            rfloor=rfloor1;
            rcategory=rcategory1;
            cout << "\t\t\t\t\tSucesully Delete This Room\n\n";
            break;
        }
        else
        {
            cout << "\t\t\t\t\t\tRoom Number Is Not Found\n";
            cout << "\t\t\t\t\t\tEnter Room Id or exit pres (-1): ";
        }
    }
}

int hostel::avi_room(int num)
{
    for(int i=0; i<studentroom.size(); i++)
    {
        if(num==studentroom[i])
            return 1;
    }
    return 0;
}

void hostel::available_room()
{
    printf("\t\t\t\t\t\tAll Available Room Information\n");
    printf("\t\t\t\t\t============================================");
    printf("\n\n");

    printf("\t\t   Room Number\t\t Floor Number \t\t Room Category \t\t Room Status\n");
    printf("\t\t  ============\t\t===============\t\t=============\t\t==============\n\n");
    for(int i=0; i<rnumber.size(); i++)
    {
        if(avi_room(rnumber[i])==0)
        {
            cout << right  << setw(25) << rnumber[i] << setw(22)
                 << rfloor[i] << setw(22) << rcategory[i]
                 << setw(28) << "Avilabol"<< '\n';
        }
    }
}

int hostel::room_position(int num)
{
    for(int i=0; i<rnumber.size(); i++)
    {
        if(rnumber[i]==num)
            return i;
    }
    return -1;
}

int hostel::greator_rnum()
{
    sort(rnumber.begin(), rnumber.end(),greater<int>());
    return rnumber[0]+1;
}

void hostel::student_clear()
{
    ofstream sclear ("information.txt", ios::out | ios::trunc);
    sclear.close();
}

void hostel::student_insert()
{
    ofstream sinsert("information.txt", ios::app);
    sinsert << "Id StudentName Room\n";
    sinsert << "-- ------------ -----";
    for(int i=0;i<studentid.size();i++)
        sinsert << "\n" << studentid[i] << " " << studentname[i] << " " << studentroom[i];
    sinsert.close();
}

int hostel::idposition(int sid)
{
    for(int i=0;i<studentid.size();i++)
        if(studentid[i]==sid)
            return i;
    return -1;
}

int hostel::student_id_maker()
{
    if(studentid.empty()) return 1;
    return *max_element(studentid.begin(), studentid.end())+1;
}

void hostel::welcome()
{
    cout << "\n\n\t\t\t***************************************************\n";
    cout << "\t\t\t*\tWELCOME\t\t\t\t\t*\n";
    cout << "\t\t\t*\tHostel Management System\t*\n";
    cout << "\t\t\t***************************************************\n";
    system("pause");
    system("cls");
}

int main()
{
    int n;
    hostel ob1;

    ob1.get_roominfo();
    ob1.get_studentinfo();

    ob1.welcome();
    ob1.header();

    while(cin>>n)
    {
        if(n==0)
        {
            ob1.program_close();
            break;
        }
    }
    return 0;
}
