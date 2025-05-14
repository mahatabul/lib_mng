#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);

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
        cout << this->name << endl;
        cout << this->memID << endl;
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