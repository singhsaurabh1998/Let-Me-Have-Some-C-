#include<bits/stdc++.h>
using namespace std;
const int available_seats = 5;
struct user_ticket
{
    string name;
    string Phone;
    int userId;
    int seat;
    string date;
    string show_time;

};
vector<int>seats;
vector<user_ticket>Candidate; ///record of users who booked movie ticket
map<int,pair<string,string>>movId;
map<int,pair<string,string>>show_time_details;
void SomeMovies()
{
    movId.insert({1,{"Simmba","Action"}});
    movId.insert({2,{"Kabir Singh","Thrill"}});
    movId.insert({3,{"Saaho","Romantic"}});
    movId.insert({4,{"Junglee","Social"}});
    movId.insert({5,{"Mission Mangal","Patriotic"}});
    movId.insert({6,{"Mirzapur","Action"}});

    ///filling show details(id,date,show timing)
    show_time_details.insert({1,{"10-3-2019","4:30 PM"}});
    show_time_details.insert({2,{"11-3-2019","8:30 PM"}});
    show_time_details.insert({3,{"12-3-2019","8:30 PM"}});
    show_time_details.insert({4,{"13-3-2019","9:00 PM"}});
    show_time_details.insert({5,{"14-3-2019","5:00 PM"}});
    show_time_details.insert({6,{"15-3-2019","4:35 PM"}});

}
void ShowMovies()
{
    static int c = 0;
    if(c==0)
    SomeMovies();///only for one time appearance
    c=1;

    cout<<"Id - Movie Name - Genre \n";
    for(auto x:movId)
        cout<<x.first<<" : "<<(x.second).first<<" -->  "<<(x.second).second<<"\n";
}
void BookTicket()
{
    int id;
    static int c = 0;
    if(seats.empty())
    {
        cout<<"*** Sorry ! Hall Is Full ***\n";
        return;
    }

    if(c==0)
     cout<<"***Welcome To Ticket Booking system ****\n";

    cout<<"Enter the Selected Movie Id : ";cin>>id;

    if(movId[id].first=="")
       {
           c++;
           cout<<"**Wrong ID**\n";
           BookTicket();

       }
    else
    {
        cin.ignore();
        user_ticket u; ///creating the candidate's ticket
        ///putting inializing user part in the constructor
        string name,ph;
        cout<<"Enter Your Name : ";getline(cin,name);
        cout<<"Enter Your Phone Number : ";cin>>ph;


        u.name = name;
        u.Phone = ph;
        u.userId = id;
        u.date = show_time_details[id].first;
        u.seat = seats.front();
        u.show_time = show_time_details[id].second;
        Candidate.push_back(u);

        seats.erase(seats.begin()); ///that seat is occupied
        cout<<"*** Booked Successfully ***\n";
    }

    /**sql part - Insert the data into the customers table*/
}
void ShowMyTicket()
{
    int id;
    string name;
    cout<<"Enter Your Movie Id : ";
    cin>>id;
    cout<<"Enter Your Name : ";cin>>name;
    int flag = 1;


        for(auto x:Candidate)
        {
            if(x.userId==id && x.name == name) ///getting the id belongs to that user
            {
                flag = 0;
                cout<<"\n### Your Movie Information ###\n\n";
                cout<<"Name : "<<x.name<<endl;
                cout<<"Phone Number : "<<x.Phone<<endl;
                cout<<"Movie Name : "<<movId[id].first<<endl;
                cout<<"Genre : "<<movId[id].second<<endl;
                cout<<"Date Of Show : "<<x.date<<endl;
                cout<<"Time Of Show : "<<x.show_time<<endl;
                cout<<"Seat Number : "<<x.seat<<endl;

                break;
            }
        }

     if(flag == 1) ///not in candidate vector
    {
        cout<<"## No Records Found ! ##\n";
        cout<<"Want to Re-Enter The Id...?? Press Y(if Yes) OtherWise N \n";
        char ch ;
        cin>>ch;
        if(ch=='Y' || ch == 'y')
            ShowMyTicket();
        else
            return;

    }

}
///system admin will do this
void AddNewMovie()
{
    string movie_name,genre;
    int n;
    string date,time;
    cout<<"Enter The Number Of Movies :";cin>>n;
    cout<<"***Enter The Movie Details : \n";

    while(n--)
    {
        cin.ignore();

     cout<<"Movie Name : ";getline(cin,movie_name);
     cout<<"Genre : ";cin>>genre;
     cout<<"Date Of Show : ";cin>>date;
     cout<<"Show Time : ";cin>>time;
     movId.insert({movId.size()+1,{movie_name,genre}});
     show_time_details.insert({movId.size(),{date,time}});
     cout<<"Success-fully Added !!\n";
    }
}

///system admin will do this
void DeleteMovie()
{
    int id,n;
    cout<<"Enter The Number Of Movies  To Be Deleted : ";cin>>n;
    while(n--)
    {
        if(movId.size()==0)
        {
            cout<<"** Empty Collection !! **\n";
            return;
        }
        cout<<"Enter The Movie Id : ";cin>>id;
        auto it = movId.find(id);
        if(it==movId.end())
        {
            cout<<"Not Found/Already Deleted\n";
            n++;
            continue;
        }
        string name = (it->second).first;
        movId.erase(it);
        cout<<name<<" Success-fully Deleted !!\n";
    }
}
void EditMovie()
{
    if(movId.size()==0)
    {
        cout<<"Empty Collection !!\n";
        return;
    }
    int id;
    string name,genre;
    cout<<"Enter The Movie Id To Be Edited : ";cin>>id;
    cin.ignore(); ///flushing the input buffer
    cout<<"Enter The Name Of The Movie : ";getline(cin,name);
    cout<<"Enter Genre : ";cin>>genre;
    movId[id] ={ name,genre};
    cout<<"\n*** Edited ***\n";
}
int main()
{
     system("color a0");
     for(int i = 1;i<=available_seats;i++)
        seats.push_back(i);
    int choice;
    while(1)
    {
        //system("clean");
        cout<<"\n1.Show Current Movies \n";
        cout<<"2.Book My Ticket \n";
        cout<<"3.Show My Ticket \n";
        cout<<"4.Add New Movie \n";
        cout<<"5.Delete Movie \n";
        cout<<"6.Edit Movie \n";
        cout<<"7.Exit \n";
        cout<<"Enter Choice : ";cin>>choice;
        cout<<"\n";
        switch(choice)
        {
            case 1:ShowMovies();break;
            case 2:BookTicket();break;
            case 3:ShowMyTicket();break;
            case 4:AddNewMovie();break;
            case 5:DeleteMovie();break;
            case 6:EditMovie();break;
            case 7:cout<<"*** Bye Bye ! ***";
                exit(0);
        }
    }
}
