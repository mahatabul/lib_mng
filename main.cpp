#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class Member;
class Admin;

class Book
{
protected:
    string title;
    bool avail;
    string author;
    string publisher;
    int edition;

public:
    Book(string t, string auth, string pub, int e, bool av)
        : title(t), author(auth), publisher(pub), edition(e), avail(av) {}

    void book_details()
    {
        cout << "\nBook Details\n";
        cout << "Title: " << this->title << endl;
        cout << "Author: " << this->author << endl;
        cout << "Publisher: " << this->publisher << endl;
        cout << "Edition: " << this->edition << endl;
        cout << "Available: " << (this->avail ? "Yes" : "No") << endl;
    }
    void setbook_details(string t, string auth, string pub, int e, bool av)
    {

        this->title = t;
        this->author = auth;
        this->publisher = pub;
        this->edition = e;
        this->avail = av;
    }
    string get_title() { return title; }
    string get_author() { return author; }
    string get_publisher() { return publisher; }
    int get_edition() { return edition; }
};





class Member
{
    friend class Admin;

private:
    string name;
    string memID;
    string password;
    vector<Book> borrowed;

public:
    Member(string n, string m, string p)
        : name(n), memID(m), password(p) {}

    void mem_details()
    {
        cout << "\nMember Details\n";
        cout <<"Name: "<< this->name << endl;
        cout <<"Member ID: "<<this->memID << endl;
        
    }
    void mem_full_details()
    {
        cout << "\nFull Details\n";
        cout <<"Name: "<< this->name << endl;
        cout <<"Member ID: "<<this->memID << endl;
        cout<<"Password: "<<this->password<<endl;
    }
    void setmem_details(string n, string id, string p)
    {
        this->name = n;
        this->memID = id;
        this->password = p;
    }
    string get_name() { return name; }
    string get_memID() { return memID; }
};

class Admin
{
private:
    string name, password;

public:
    Admin(string n, string p)
        : name(n), password(p) {}

    void admin_details()
    {
        cout << "\nAdmin Details\n";
        cout << this->name << endl;
    }
    void setadmin_details(string n, string p)
    {
        this->name = n;

        this->password = p;
    }
    string get_name() { return name; }

    void get_Member_full_details(Member& a){

        a.mem_full_details();
        

    }
};

class Library
{

private:
    vector<Book> books;
    vector<Member> members;

    void addBook(string title = "", string author = "", string pub = "", int e = 0, bool aval = true)
    {
        Book b(title, author, pub, e, aval);
        books.push_back(b);
    }
    void addMember(string n = "", string id = "", string pass = "")
    {
        Member m(n, id, pass);
        members.push_back(m);
    }
    void book_list()
    {
        int i = 1;
        cout << "List of Books\n";
        for (auto it : books)
        {
            cout << i++ << "." << it.get_title() << "\n";
        }
    }

public:
    void add_book()
    {

        string title, author, pub;
        int e;
        cout << "Adding new book....\n";
        cout << "Set title: ";
        cin >> title;
        cout << "\nSet Author: ";
        cin >> author;
        cout << "\nSet Publisher: ";
        cin >> pub;
        cout << "\nSet Editon: ";
        cin >> e;

        addBook(title, author, pub, e, true);
    }
    void add_member()
    {
        string name, memid, password;
        cout << "Adding new member....\n";
        cout << "Set Name: ";
        cin >> name;
        cout << "\nSet memID: ";
        cin >> memid;
        cout << "\nSet Password: ";
        cin >> password;

        addMember(name, memid, password);
    }
    void show_book_list()
    {
        book_list();
    }
    void inquiry()
    {

        book_list();
        cout << "Choose book to inquire: ";
        int i;
        cin >> i;
        books[i - 1].book_details();
    }
};
int main()
{

    

    return 0;
}