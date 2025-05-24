#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>

using namespace std;

void printAsciiArt()
{
    std::cout << u8R"(
  /$$$$$$  /$$$$$$$   /$$$$$$        /$$       /$$ /$$                                             
 /$$__  $$| $$__  $$ /$$__  $$      | $$      |__/| $$                                             
| $$  \ $$| $$  \ $$| $$  \__/      | $$       /$$| $$$$$$$   /$$$$$$  /$$$$$$   /$$$$$$  /$$   /$$
| $$$$$$$$| $$$$$$$ | $$            | $$      | $$| $$__  $$ /$$__  $$|____  $$ /$$__  $$| $$  | $$
| $$__  $$| $$__  $$| $$            | $$      | $$| $$  \ $$| $$  \__/ /$$$$$$$| $$  \__/| $$  | $$
| $$  | $$| $$  \ $$| $$    $$      | $$      | $$| $$  | $$| $$      /$$__  $$| $$      | $$  | $$
| $$  | $$| $$$$$$$/|  $$$$$$/      | $$$$$$$$| $$| $$$$$$$/| $$     |  $$$$$$$| $$      |  $$$$$$$
|__/  |__/|_______/  \______/       |________/|__/|_______/ |__/      \_______/|__/       \____  $$
                                                                                          /$$  | $$
                                                                                         |  $$$$$$/
                                                                                          \______/ 
)" << std::endl;
}
class Member;
class Admin;

class User
{
public:
    virtual void show_details() = 0;
};

class Book : public User
{
protected:
    string title;
    int quantity;
    string author;
    string publisher;
    int edition;

public:
    Book(string t, string auth, string pub, int e, int av)
        : title(t), author(auth), publisher(pub), edition(e), quantity(av) {}

    Book(string title) : title(title) {}

    void show_details() override
    {
        cout << "\nBook Details\n";
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Edition: " << edition << endl;
        cout << "Available: " << (quantity > 0 ? "Yes" : "No") << endl;
        cout << "Copies Available: " << quantity << endl;
    }

    void set_book_details(string t, string auth, string pub, int e, int av)
    {
        title = t;
        author = auth;
        publisher = pub;
        edition = e;
        quantity = av;
    }

    string get_title() { return title; }
    string get_author() { return author; }
    string get_publisher() { return publisher; }
    int get_edition() { return edition; }
    int get_quantity() { return quantity; }

    void decrease_quantity()
    {
        if (quantity > 0)
            quantity--;
    }
    void increase_quantity() { quantity++; }
    bool is_available() { return quantity > 0; }
};

class Member : public User
{
    friend class Admin;
    friend class Library;

private:
    string name;
    string memID;
    string password;
    vector<Book> borrowed;

public:
    Member(string n, string m, string p)
        : name(n), memID(m), password(p) {}

    void show_details() override
    {
        cout << "\nMember Details\n";
        cout << "Name: " << name << endl;
        cout << "Member ID: " << memID << endl;
        cout << "Number of borrowed Books: " << borrowed.size() << endl;
    }

    void mem_full_details()
    {
        cout << "\nFull Profile\n";
        cout << "Name: " << name << endl;
        cout << "Member ID: " << memID << endl;
        cout << "Password: " << password << endl;
        cout << "Number of borrowed Books: " << borrowed.size() << endl;
    }

    void setmem_details(string n, string id, string p)
    {
        name = n;
        memID = id;
        password = p;
    }

    string return_book()
    {
        if (borrowed.empty())
        {
            cout << "You have no borrowed books to return.\n";
            return "";
        }

        cout << "\nYour Borrowed Books:\n";
        for (int i = 0; i < borrowed.size(); i++)
        {
            cout << i + 1 << ". " << borrowed[i].get_title() << endl;
        }

        cout << "Enter the number of the book to return: ";
        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= borrowed.size())
        {
            string title = borrowed[choice - 1].get_title();
            borrowed.erase(borrowed.begin() + (choice - 1));
            cout << "Book returned successfully.\n";
            return title;
        }
        else
        {
            cout << "Invalid choice.\n";
            return "";
        }
    }

    void set_borrowed_books(const vector<Book> &b)
    {
        borrowed = b;
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
        for (auto &b : borrowed)
        {
            if (b.get_title() == name.get_title())
            {
                cout << "You already borrowed this book.\n";
                return;
            }
        }
        if (borrowed.size() >= 5)
        {
            cout << "Sorry Already 5 books borrowed..";
            return;
        }
        borrowed.push_back(name);
        cout << "Book borrowed successfully!!";
    }

    void showBorrowedBooks()
    {
        cout << "\n--- Borrowed Books List ---\n";
        if (borrowed.empty())
        {
            cout << "No books have been borrowed yet.\n";
        }
        else
        {
            for (size_t i = 0; i < borrowed.size(); ++i)
            {
                cout << i + 1 << ". " << borrowed[i].get_title() << "\n";
            }
        }
        cout << endl;
    }

    string get_name() { return name; }
    string get_memID() { return memID; }
    string get_password() { return password; }
    int get_borrowed() { return borrowed.size(); }
};

class Admin : public User
{
private:
    string name, password;

    void admin_full_details()
    {
        cout << "\nAdmin Details\n";
        cout << "Admin name: " << name << endl;
        cout << "Admin Password: " << password << endl;
    }

public:
    Admin(string n, string p)
        : name(n), password(p) {}

    void show_details() override
    {
        cout << "\nAdmin Details\n";
        cout << "Admin name: " << name << endl;
    }

    void setadmin_details(string n, string p)
    {
        name = n;
        password = p;
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

    Book &get_the_book(string title)
    {
        for (auto &it : books)
        {
            if (it.get_title() == title)
            {
                return it;
            }
        }
        throw runtime_error("Book not found");
    }

    bool check_member(Member m)
    {
        for (auto &it : members)
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
        for (auto &it : books)
        {
            if (it.get_title() == name and it.is_available())
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
                if (m.get_borrowed() < 5)
                {
                    Book &bb = get_the_book(book_name);
                    m.borrow_book_logic(bb);
                    bb.decrease_quantity();
                }
                else
                {
                    cout << "Sorry Already 5 books borrowed..";
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

    void addBook(string title = "", string author = "", string pub = "", int e = 0, int aval = 0)
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
        save_admin_to_csv(m);
        admins.push_back(m);
    }

    void book_list()
    {
        if (books.empty())
        {
            cout << "No book available..\n";
            return;
        }
        cout << "List of Books\n";
        int i = 1;
        for (auto &it : books)
        {
            cout << i++ << "." << it.get_title() << "\n";
        }
    }

    void member_list()
    {
        if (members.empty())
        {
            cout << "No members available..\n";
            return;
        }
        cout << "List of members\n";
        int i = 1;
        for (auto &it : members)
        {
            cout << i++ << "." << it.get_name() << "\n";
        }
    }

    void admin_list()
    {
        if (admins.empty())
        {
            cout << "No admins available..\n";
            return;
        }
        cout << "List of admins\n";
        int i = 1;
        for (auto &it : admins)
        {
            cout << i++ << "." << it.get_name() << "\n";
        }
    }

    bool verify_Member_logic(string n, string p)
    {
        for (auto &it : members)
        {
            if (it.get_name() == n && it.get_password() == p)
            {
                return true;
            }
        }
        return false;
    }
    bool verify_Admin_logic(string n, string p)
    {
        for (auto &it : admins)
        {
            if (it.get_name() == n && it.get_password() == p)
            {
                return true;
            }
        }
        return false;
    }

public:
    void load_member_from_csv(const string &filename);
    void load_books_from_csv(const string &filename);
    void load_admins_from_csv(const string &filename);

    void unload_member_to_csv(const string &filename);
    void unload_books_to_csv(const string &filename);
    void unload_admins_to_csv(const string &filename);

    void save_admin_to_csv(Admin m)
    {
        ofstream file("admins.csv", ios::app);

        if (!file.is_open())
        {
            cerr << "File not opened\n";
            return;
        }

        file << m.get_name() << "," << m.get_password();

        file.close();

        return;
    }
    void save_member_to_csv(Member m)
    {
        ofstream file("members.csv", ios::app);

        if (!file.is_open())
        {
            cerr << "File not opened\n";
            return;
        }

        file << m.get_name() << "," << m.get_memID() << "," << m.get_password();

        file.close();

        return;
    }

    void set_books(const vector<Book> &b)
    {
        books = b;
    }
    void set_admins(const vector<Admin> &b)
    {
        admins = b;
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
        }
        else
        {
            cout << "You are not a member!!";
        }
    }

    void return_book_by_member()
    {
        cout << "Enter your name and password to return a book\n";
        cout << "Enter name: ";
        string name, password;
        getline(cin >> ws, name);
        cout << "Enter password: ";
        getline(cin, password);

        if (verify_Member_logic(name, password))
        {
            Member *m = get_the_member(name);
            string returned_title = m->return_book();
            if (!returned_title.empty())
            {
                Book &b = get_the_book(returned_title);
                b.increase_quantity();
            }
        }
        else
        {
            cout << "Invalid credentials. You are not a member.\n";
        }
    }

    void verify_Member(string n, string p)
    {
        if (verify_Member_logic(n, p))
        {

            cout << "Welcome " << n << endl;
        }
        else
        {
            cout << "Wrong name or password..\n";
        }
    }

    bool verify_Member_bool(string n, string p)
    {
        return verify_Member_logic(n, p);
    }

    void verify_Admin(string n, string p)
    {
        if (verify_Admin_logic(n, p))
        {
            cout << "Welcome " << n << endl;
            return;
        }

        cout << "No such admin found... Wrong name or password \n";
        return;
    }

    bool verify_Admin_bool(string n, string p)
    {
        return verify_Admin_logic(n, p);
    }

    void add_book()
    {
        string title, author, pub;
        int e, quantity;
        cout << "Adding new book....\n";
        cout << "Set title: ";
        getline(cin >> ws, title);
        cout << "\nSet Author: ";
        getline(cin, author);
        cout << "\nSet Publisher: ";
        getline(cin, pub);
        cout << "\nSet Edition: ";
        cin >> e;
        cout << "\nSet Quantity: ";
        cin >> quantity;
        addBook(title, author, pub, e, quantity);
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

    void remove_book()
    {
        if (books.empty())
        {
            cout << "No books available to remove.\n";
            return;
        }
        book_list();
        cout << "Enter the number of the book to remove: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= books.size())
        {
            books.erase(books.begin() + (choice - 1));
            cout << "Book removed successfully.\n";
        }
        else
        {
            cout << "Invalid book number.\n";
        }
    }
    void remove_member()
    {
        if (members.empty())
        {
            cout << "No members available to remove.\n";
            return;
        }
        member_list();
        cout << "Enter the number of the member to remove: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= members.size())
        {
            members.erase(members.begin() + (choice - 1));
            cout << "Member removed successfully.\n";
        }
        else
        {
            cout << "Invalid member number.\n";
        }
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

    void show_book_list() { book_list(); }
    void show_admin_list() { admin_list(); }
    void show_member_list() { member_list(); }

    void inquiry_books()
    {
        book_list();
        if (books.size())
        {
            cout << "Choose book to inquire: ";
            int i;
            cin >> i;
            books[i - 1].show_details();
        }
        return;
    }

    void inquiry_members()
    {
        member_list();
        if (members.size())
        {
            cout << "Choose member to inquire: ";
            int i;
            cin >> i;
            members[i - 1].show_details();
        }
        return;
    }
};

void Library::load_member_from_csv(const string &filename)
{

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Members csv file not opened\n";
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        string name, memId, pass, borrowed_book_list;

        getline(ss, name, ',');
        getline(ss, memId, ',');
        getline(ss, pass, ',');
        getline(ss, borrowed_book_list);

        Member m(name, memId, pass);

        stringstream bb(borrowed_book_list);

        string bookTitle;
        vector<Book> blist;

        while (getline(bb, bookTitle, ';'))
        {
            if (!bookTitle.empty())
            {
                Book b(bookTitle);
                blist.push_back(b);
            }
        }

        m.set_borrowed_books(blist);

        members.push_back(m);
    }
    file.close();
    return;
}
void Library::load_books_from_csv(const string &filename)
{

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Books csv file not opened\n";
        return;
    }

    string line;
    getline(file, line);
    vector<Book> blist;

    while (getline(file, line))
    {
        stringstream ss(line);

        string title, author, pub, editionStr, quantityStr;
        int edition;
        int quantity;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pub, ',');
        getline(ss, editionStr, ',');
        getline(ss, quantityStr);

        edition = stoi(editionStr);
        quantity = stoi(quantityStr);

        Book b(title, author, pub, edition, quantity);

        blist.push_back(b);

        set_books(blist);
    }
    file.close();
    return;
}

void Library::load_admins_from_csv(const string &filename)
{

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Admins csv file not opened\n";
        return;
    }

    string line;
    getline(file, line);
    vector<Admin> adminlist;

    while (getline(file, line))
    {
        stringstream ss(line);

        string name, pass;

        getline(ss, name, ',');

        getline(ss, pass);

        Admin a(name, pass);

        adminlist.push_back(a);

        set_admins(adminlist);
    }
    file.close();
    return;
}

void Library::unload_member_to_csv(const string &filename)
{

    ofstream file(filename, ios::out);

    if (!file.is_open())
    {
        cerr << "Members csv file not opened\n";
        return;
    }

    file << "Name,MemberID,Password,BorrowedBooks\n";

    vector<Member> memlist = members;

    for (auto i = 0; i < memlist.size(); i++)
    {
        vector<Book> booklist = memlist[i].borrowed;

        file << memlist[i].get_name() << "," << memlist[i].get_memID() << "," << memlist[i].get_password() << ",";
        
        for (int j = 0; j < booklist.size(); j++)
        {
            file << booklist[j].get_title();
            if (j < booklist.size() - 1)
            {
                file << ";";
            }
        }
        file << "\n";
    }

    file.close();
    return;
}

void Library::unload_books_to_csv(const string &filename)
{

    ofstream file(filename, ios::out);

    if (!file.is_open())
    {
        cerr << "Books csv file not opened\n";
        return;
    }

    file << "Title,Author,Publisher,Edition,Quantity\n";
    vector<Book> blist = books;

    for (auto i = 0; i < blist.size(); i++)
    {
        file << blist[i].get_title() << "," << blist[i].get_author() << "," << blist[i].get_publisher() << "," << blist[i].get_edition() << "," << blist[i].get_quantity() << "\n";
    }
    file.close();
    return;
}

void Library::unload_admins_to_csv(const string &filename)
{

    ofstream file(filename, ios::out);

    if (!file.is_open())
    {
        cerr << "Admins csv file not opened\n";
        return;
    }

    file << "Name" << "," << "Password\n";
    vector<Admin> adminlist = admins;

    for (auto i = 0; i < adminlist.size(); i++)
    {
        file << adminlist[i].get_name() << "," << adminlist[i].get_password() << "\n";
    }
    file.close();
    return;
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{

    Library library;
    int main_choice;

    library.load_member_from_csv("members.csv");
    library.load_books_from_csv("books.csv");
    library.load_admins_from_csv("admins.csv");

    while (true)
    {
        clear_screen();
        printAsciiArt();
        cout << "\n==== Library Management System ====\n";
        cout << "1. Admin Panel\n";
        cout << "2. Member Panel\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> main_choice;

        if (main_choice == 1)
        {
            string name, pass;
            clear_screen();
            printAsciiArt();
            cout << "Admin Login\n";
            cout << "Enter Name: ";
            getline(cin >> ws, name);
            cout << "Enter Password: ";
            getline(cin, pass);

            bool is_admin = library.verify_Admin_bool(name, pass);

            if (is_admin)
            {
                int admin_choice;
                while (true)
                {
                    clear_screen();
                    printAsciiArt();

                    cout << "\n==== Hello " << name << " ====\n";
                    cout << "1. Add Book\n";
                    cout << "2. Remove Book\n";
                    cout << "3. Add Member\n";
                    cout << "4. Remove Member\n";
                    cout << "5. Add Admin\n";
                    cout << "6. View Book List\n";
                    cout << "7. View Member List\n";
                    cout << "8. View Admin List\n";
                    cout << "9. Inquire Book Details\n";
                    cout << "10. Inquire Member Details\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> admin_choice;

                    switch (admin_choice)
                    {
                    case 1:
                        clear_screen();
                        printAsciiArt();
                        library.add_book();
                        break;
                    case 2:
                        clear_screen();
                        printAsciiArt();
                        library.remove_book();
                        break;
                    case 3:
                        clear_screen();
                        printAsciiArt();
                        library.add_member();
                        break;
                    case 4:
                        clear_screen();
                        printAsciiArt();
                        library.remove_member();
                        break;
                    case 5:
                        clear_screen();
                        printAsciiArt();
                        library.add_admin();
                        break;
                    case 6:
                        clear_screen();
                        printAsciiArt();
                        library.show_book_list();
                        break;
                    case 7:
                        clear_screen();
                        printAsciiArt();
                        library.show_member_list();
                        break;
                    case 8:
                        clear_screen();
                        printAsciiArt();
                        library.show_admin_list();
                        break;
                    case 9:
                        clear_screen();
                        printAsciiArt();
                        library.inquiry_books();
                        break;
                    case 10:
                        clear_screen();
                        printAsciiArt();
                        library.inquiry_members();
                        break;
                    case 0:
                        goto main_menu;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
            }
            else
            {
                cout << "Invalid admin credentials.\n";
                cin.ignore();
                cin.get();
            }
        }
        else if (main_choice == 2)
        {
            string name, pass;
            clear_screen();
            printAsciiArt();
            cout << "Member Login\n";
            cout << "Enter Name: ";
            getline(cin >> ws, name);
            cout << "Enter Password: ";
            getline(cin, pass);

            bool is_member = library.verify_Member_bool(name, pass);

            if (is_member)
            {
                Member *m = library.get_the_member(name);

                int mem_choice;
                while (true)
                {
                    clear_screen();
                    printAsciiArt();
                    cout << "\n==== Hello " << name << " ====\n";
                    cout << "1. Borrow Book\n";
                    cout << "2. Return Book\n";
                    cout << "3. List Borrowed Books\n";
                    cout << "4. Full Profile\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> mem_choice;

                    switch (mem_choice)
                    {
                    case 1:
                        clear_screen();
                        printAsciiArt();
                        library.giving_books();
                        break;
                    case 2:
                        clear_screen();
                        printAsciiArt();
                        library.return_book_by_member();
                        break;
                    case 3:
                        clear_screen();
                        printAsciiArt();
                        m->showBorrowedBooks();
                        break;
                    case 4:
                        clear_screen();
                        printAsciiArt();
                        m->mem_full_details();
                        break;
                    case 0:
                        goto main_menu;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                    }
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
            }

            else
            {
                cout << "Invalid user credentials.\n";
                cin.ignore();
                cin.get();
            }
        }
        else if (main_choice == 3)
        {
            cout << "Exiting Library System. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
            cin.ignore();
            cin.get();
        }

    main_menu:
        continue;
    }

    library.unload_admins_to_csv("admins.csv");
    library.unload_books_to_csv("books.csv");
    library.unload_member_to_csv("members.csv");

    return 0;
}
