#include <bits/stdc++.h>

using namespace std;

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
        cout << "Name: " << this->name << endl;
        cout << "Member ID: " << this->memID << endl;
    }
    void mem_full_details()
    {
        cout << "\nFull Details\n";
        cout << "Name: " << this->name << endl;
        cout << "Member ID: " << this->memID << endl;
        cout << "Password: " << this->password << endl;
    }
    void setmem_details(string n, string id, string p)
    {
        this->name = n;
        this->memID = id;
        this->password = p;
    }

    string borrow_book()
    {
        cout << "Borrowing book..\n";
        cout << "Enter book name: ";
        string title;
        getline(cin >> ws, title);

        return title;
    }
    void borrow_book_logic(Book name)
    {

        if (borrowed.size() > 5)
        {
            cout << "Sorry Already 5 books borrowed..";
            return;
        }

        borrowed.push_back(name);
        cout << "Book borrowed successfully!!";
        return;
    }
    string get_name() { return name; }
    string get_memID() { return memID; }
    string get_password() { return password; }
    int get_borrowed() { return borrowed.size(); }
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
        cout << "Admin name: " << this->name << endl;
    }
    void admin_full_details()
    {
        cout << "\nAdmin Details\n";
        cout << "Admin name: " << this->name << endl;
        cout << "Admin Password: " << this->password << endl;
    }
    void setadmin_details(string n, string p)
    {
        this->name = n;

        this->password = p;
    }
    string get_name() { return name; }
    string get_password() { return password; }

    void get_Member_full_details(Member &a)
    {

        a.mem_full_details();
    }
};

class Library
{

private:
    vector<Book> books;
    vector<Member> members;
    vector<Admin> admins;

    Book get_the_book(string title)
    {
        for (auto it : books)
        {
            if (it.get_title() == title)
            {
                return it;
            }
        }
    }
    Member *get_the_member(string name)
    {
        for (auto &it : members)
        {
            if (it.get_name() == name)
            {
                return &it;
            }
        }
        return nullptr;
    }

    bool check_member(Member m)
    {
        for (auto it : members)
        {
            if (it.get_name() == m.get_name())
            {
                return true;
            }
        }
        return false;
    }
    bool check_book(string name)
    {
        for (auto it : books)
        {
            if (it.get_title() == name)
            {
                return true;
            }
        }
        return false;
    }

    void giving_book(Member &m)
    {

        if (check_member(m))
        {
            string book_name = m.borrow_book();
            if (check_book(book_name))
            {
                if (m.get_borrowed() <= 5)
                {
                    Book bb = get_the_book(book_name);
                    m.borrow_book_logic(bb);
                }
            }
            else
            {
                cout << "\n Book not available\n";
            }
        }
        else
        {
            cout << "\n Not a member!!!\n";
        }
    }

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
    void addAdmin(string n = "", string pass = "")
    {
        Admin m(n, pass);
        admins.push_back(m);
    }
    void book_list()
    {
        if (books.size() == 0)
        {
            cout << "No book available..\n";
            return;
        }

        int i = 1;
        cout << "List of Books\n";
        for (auto it : books)
        {
            cout << i++ << "." << it.get_title() << "\n";
        }
    }

    void member_list()
    {
        if (members.size() == 0)
        {
            cout << "No members available..\n";
            return;
        }

        int i = 1;
        cout << "List of members\n";
        for (auto it : members)
        {
            cout << i++ << "." << it.get_name() << "\n";
        }
    }

    void admin_list()
    {
        if (admins.size() == 0)
        {
            cout << "No admins available..\n";
            return;
        }

        int i = 1;
        cout << "List of admins\n";
        for (auto it : admins)
        {
            cout << i++ << "." << it.get_name() << "\n";
        }
    }

    bool verify_Member_logic(string n, string p)
    {
        for (auto it : members)
        {
            if (it.get_name() == n and it.get_password() == p)
            {

                return true;
            }
        }

        return false;
    }

public:
    Library()
    {
        Admin a("admin", "shika noko");
        admins.push_back(a);
    }

    void giving_books()
    {

        cout << "Enter your name and password to borrow book\n";
        cout << "Enter name: ";
        string name, password;
        getline(cin >> ws, name);
        cout << "Enter password: ";
        getline(cin, password);

        if (verify_Member_logic(name, password))
        {
            Member *m = get_the_member(name);

            giving_book(*m);
            return;
        }
        cout << "You are not a member!!";
        return;
    }
    void verify_Member(string n, string p)
    {

        if (verify_Member_logic(n, p))
        {
            Member *m = get_the_member(n);

            cout << "Welcome " << m->get_name() << endl;
        }

        else
        {
            cout << "Wrong name or password..\n";
        }

        return;
    }
    void verify_Admin(string n, string p)
    {
        for (auto it : admins)
        {
            if (it.get_name() == n and it.get_password() == p)
            {
                cout << "Welcome " << it.get_name() << " ! \n";
                return;
            }
        }

        cout << "No such admin found... Wrong name or passoword \n";
        return;
    }
    void add_book()
    {

        string title, author, pub;
        int e;
        cout << "Adding new book....\n";
        cout << "Set title: ";
        getline(cin >> ws, title);
        cout << "\nSet Author: ";
        getline(cin, author);
        cout << "\nSet Publisher: ";
        getline(cin, pub);
        cout << "\nSet Editon: ";
        cin >> e;

        addBook(title, author, pub, e, true);
    }
    void add_member()
    {
        string name, memid, password;
        cout << "Adding new member....\n";
        cout << "Set Name: ";
        getline(cin >> ws, name);
        cout << "\nSet memID: ";
        getline(cin, memid);
        cout << "\nSet Password: ";
        getline(cin, password);

        addMember(name, memid, password);
    }
    void add_admin()
    {
        string name, password;
        cout << "Adding new admin....\n";
        cout << "Set Name: ";
        getline(cin >> ws, name);
        cout << "\nSet Password: ";
        getline(cin, password);

        addAdmin(name, password);
    }
    void show_book_list()
    {
        book_list();
    }
    void show_admin_list()
    {
        admin_list();
    }
    void show_member_list()
    {
        member_list();
    }
    void inquiry_books()
    {

        book_list();
        cout << "Choose book to inquire: ";
        int i;
        cin >> i;
        books[i - 1].book_details();
    }
    void inquiry_members()
    {

        member_list();
        cout << "Choose member to inquire: ";
        int i;
        cin >> i;
        members[i - 1].mem_details();
    }
};
int main()
{
    system("clear");
    Library lib;
    lib.add_book();
    system("clear");
    lib.add_member();
    system("clear");
    lib.giving_books();
    cout << "\n";

    return 0;
}