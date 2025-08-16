#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Utility function to trim whitespace from both ends of a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos) return "";
    return str.substr(first, last - first + 1);
}

// Utility function to convert string to lowercase for case-insensitive comparison
string to_lower(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

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
    virtual ~User() = default;
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

    Book(string title) : title(title), quantity(0), edition(0) {}

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

    string get_title() const { return title; }
    string get_author() const { return author; }
    string get_publisher() const { return publisher; }
    int get_edition() const { return edition; }
    int get_quantity() const { return quantity; }

    void decrease_quantity()
    {
        if (quantity > 0)
            quantity--;
    }
    void increase_quantity() { quantity++; }
    bool is_available() const { return quantity > 0; }
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

    void mem_full_details() const
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
        for (size_t i = 0; i < borrowed.size(); i++)
        {
            cout << i + 1 << ". " << borrowed[i].get_title() << endl;
        }

        cout << "Enter the number of the book to return: ";
        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(borrowed.size()))
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
        return trim(title);
    }

    void borrow_book_logic(const Book &name)
    {
        for (const auto &b : borrowed)
        {
            if (b.get_title() == name.get_title())
            {
                cout << "You already borrowed this book.\n";
                return;
            }
        }
        if (borrowed.size() >= 5)
        {
            cout << "Sorry, already 5 books borrowed.\n";
            return;
        }
        borrowed.push_back(name);
        cout << "Book borrowed successfully!\n";
    }

    void showBorrowedBooks() const
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

    const vector<Book> &get_borrowed_books() const { return borrowed; }
    string get_name() const { return name; }
    string get_memID() const { return memID; }
    string get_password() const { return password; }
    int get_borrowed() const { return static_cast<int>(borrowed.size()); }
};

class Admin : public User
{
private:
    string name, password;

    void admin_full_details() const
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

    string get_name() const { return name; }
    string get_password() const { return password; }

    void get_Member_full_details(const Member &a) const
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

    Book &get_the_book(const string &title)
    {
        for (auto &it : books)
        {
            if (to_lower(it.get_title()) == to_lower(title))
            {
                return it;
            }
        }
        throw runtime_error("Book not found");
    }

    bool check_member(const Member &m) const
    {
        for (const auto &it : members)
        {
            if (to_lower(it.get_name()) == to_lower(m.get_name()))
            {
                return true;
            }
        }
        return false;
    }

    bool check_book(const string &name) const
    {
        for (const auto &it : books)
        {
            if (to_lower(it.get_title()) == to_lower(name) && it.is_available())
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
                    cout << "Sorry, already 5 books borrowed.\n";
                }
            }
            else
            {
                cout << "\nBook not available\n";
            }
        }
        else
        {
            cout << "\nNot a member!!!\n";
        }
    }

    void addBook(const string &title, const string &author, const string &pub, int e, int aval)
    {
        Book b(title, author, pub, e, aval);
        books.push_back(b);
    }

    void addMember(const string &n, const string &id, const string &pass)
    {
        Member m(n, id, pass);
        members.push_back(m);
    }

    void addAdmin(const string &n, const string &pass)
    {
        Admin m(n, pass);
        admins.push_back(m);
    }

    void book_list() const
    {
        if (books.empty())
        {
            cout << "No books available.\n";
            return;
        }
        cout << "List of Books\n";
        int i = 1;
        for (const auto &it : books)
        {
            cout << i++ << ". " << it.get_title() << "\n";
        }
    }

    void member_list() const
    {
        if (members.empty())
        {
            cout << "No members available.\n";
            return;
        }
        cout << "List of members\n";
        int i = 1;
        for (const auto &it : members)
        {
            cout << i++ << ". " << it.get_name() << "\n";
        }
    }

    void admin_list() const
    {
        if (admins.empty())
        {
            cout << "No admins available.\n";
            return;
        }
        cout << "List of admins\n";
        int i = 1;
        for (const auto &it : admins)
        {
            cout << i++ << ". " << it.get_name() << "\n";
        }
    }

    bool verify_Member_logic(const string &n, const string &p) const
    {
        for (const auto &it : members)
        {
            if (to_lower(trim(it.get_name())) == to_lower(trim(n)) && trim(it.get_password()) == trim(p))
            {
                return true;
            }
        }
        return false;
    }

    bool verify_Admin_logic(const string &n, const string &p) const
    {
        for (const auto &it : admins)
        {
            if (to_lower(trim(it.get_name())) == to_lower(trim(n)) && trim(it.get_password()) == trim(p))
            {
                return true;
            }
        }
        return false;
    }

public:
    void load_books_from_csv(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open books CSV file: " << filename << endl;
            return;
        }

        string line;
        if (!getline(file, line))
        {
            cerr << "Error: Empty or invalid books CSV file: " << filename << endl;
            file.close();
            return;
        }

        books.clear();
        while (getline(file, line))
        {
            stringstream ss(line);
            string title, author, pub, editionStr, quantityStr;

            if (!getline(ss, title, ',') ||
                !getline(ss, author, ',') ||
                !getline(ss, pub, ',') ||
                !getline(ss, editionStr, ',') ||
                !getline(ss, quantityStr))
            {
                cerr << "Warning: Skipping malformed line in books CSV: " << line << endl;
                continue;
            }

            // Remove quotes if present
            title = trim(title);
            if (!title.empty() && title.front() == '"' && title.back() == '"')
                title = title.substr(1, title.length() - 2);
            author = trim(author);
            if (!author.empty() && author.front() == '"' && author.back() == '"')
                author = author.substr(1, author.length() - 2);
            pub = trim(pub);
            if (!pub.empty() && pub.front() == '"' && pub.back() == '"')
                pub = pub.substr(1, pub.length() - 2);
            editionStr = trim(editionStr);
            quantityStr = trim(quantityStr);

            try
            {
                int edition = stoi(editionStr);
                int quantity = stoi(quantityStr);
                books.emplace_back(title, author, pub, edition, quantity);
            }
            catch (const exception &e)
            {
                cerr << "Warning: Invalid data in books CSV line: " << line << endl;
            }
        }

        file.close();
        cout << "Loaded " << books.size() << " books from " << filename << endl;
    }

    void save_books_to_csv(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open books CSV file for writing: " << filename << endl;
            return;
        }

        file << "Title,Author,Publisher,Edition,Quantity\n";
        for (const auto &book : books)
        {
            file << "\"" << book.get_title() << "\","
                 << "\"" << book.get_author() << "\","
                 << "\"" << book.get_publisher() << "\","
                 << book.get_edition() << ","
                 << book.get_quantity() << "\n";
        }

        file.close();
        cout << "Saved " << books.size() << " books to " << filename << endl;
    }

    void load_members_from_csv(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open members CSV file: " << filename << endl;
            return;
        }

        string line;
        if (!getline(file, line))
        {
            cerr << "Error: Empty or invalid members CSV file: " << filename << endl;
            file.close();
            return;
        }

        members.clear();
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, memId, pass, borrowed_book_list;

            if (!getline(ss, name, ',') ||
                !getline(ss, memId, ',') ||
                !getline(ss, pass, ',') ||
                !getline(ss, borrowed_book_list))
            {
                cerr << "Warning: Skipping malformed line in members CSV: " << line << endl;
                continue;
            }

            // Remove quotes and trim
            name = trim(name);
            if (!name.empty() && name.front() == '"' && name.back() == '"')
                name = name.substr(1, name.length() - 2);
            memId = trim(memId);
            if (!memId.empty() && memId.front() == '"' && memId.back() == '"')
                memId = memId.substr(1, memId.length() - 2);
            pass = trim(pass);
            if (!pass.empty() && pass.front() == '"' && pass.back() == '"')
                pass = pass.substr(1, pass.length() - 2);
            borrowed_book_list = trim(borrowed_book_list);
            if (!borrowed_book_list.empty() && borrowed_book_list.front() == '"' && borrowed_book_list.back() == '"')
                borrowed_book_list = borrowed_book_list.substr(1, borrowed_book_list.length() - 2);

            Member m(name, memId, pass);
            vector<Book> borrowed_books;

            if (!borrowed_book_list.empty())
            {
                stringstream bb(borrowed_book_list);
                string bookTitle;
                while (getline(bb, bookTitle, ';'))
                {
                    bookTitle = trim(bookTitle);
                    if (!bookTitle.empty())
                    {
                        for (const auto &book : books)
                        {
                            if (to_lower(book.get_title()) == to_lower(bookTitle))
                            {
                                borrowed_books.push_back(book);
                                break;
                            }
                        }
                    }
                }
            }

            m.set_borrowed_books(borrowed_books);
            members.push_back(m);
        }

        file.close();
        cout << "Loaded " << members.size() << " members from " << filename << endl;
        // Debug: Print loaded members
        cout << "Debug: Loaded members:\n";
        for (const auto &m : members)
        {
            cout << "Name: '" << m.get_name() << "', Password: '" << m.get_password() << "'\n";
        }
    }

    void save_members_to_csv(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open members CSV file for writing: " << filename << endl;
            return;
        }

        file << "Name,MemberID,Password,BorrowedBooks\n";
        for (const auto &member : members)
        {
            file << "\"" << member.get_name() << "\","
                 << "\"" << member.get_memID() << "\","
                 << "\"" << member.get_password() << "\",\"";

            const auto &borrowed_books = member.get_borrowed_books();
            for (size_t i = 0; i < borrowed_books.size(); ++i)
            {
                file << borrowed_books[i].get_title();
                if (i < borrowed_books.size() - 1)
                    file << ";";
            }
            file << "\"\n";
        }

        file.close();
        cout << "Saved " << members.size() << " members to " << filename << endl;
    }

    void load_admins_from_csv(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open admins CSV file: " << filename << endl;
            return;
        }

        string line;
        if (!getline(file, line))
        {
            cerr << "Error: Empty or invalid admins CSV file: " << filename << endl;
            file.close();
            return;
        }

        admins.clear();
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, pass;

            if (!getline(ss, name, ',') || !getline(ss, pass))
            {
                cerr << "Warning: Skipping malformed line in admins CSV: " << line << endl;
                continue;
            }

            // Remove quotes and trim
            name = trim(name);
            if (!name.empty() && name.front() == '"' && name.back() == '"')
                name = name.substr(1, name.length() - 2);
            pass = trim(pass);
            if (!pass.empty() && pass.front() == '"' && pass.back() == '"')
                pass = pass.substr(1, pass.length() - 2);

            admins.emplace_back(name, pass);
        }

        file.close();
        cout << "Loaded " << admins.size() << " admins from " << filename << endl;
        // Debug: Print loaded admins
        cout << "Debug: Loaded admins:\n";
        for (const auto &a : admins)
        {
            cout << "Name: '" << a.get_name() << "', Password: '" << a.get_password() << "'\n";
        }
    }

    void save_admins_to_csv(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open admins CSV file for writing: " << filename << endl;
            return;
        }

        file << "Name,Password\n";
        for (const auto &admin : admins)
        {
            file << "\"" << admin.get_name() << "\","
                 << "\"" << admin.get_password() << "\"\n";
        }

        file.close();
        cout << "Saved " << admins.size() << " admins to " << filename << endl;
    }

    void set_books(const vector<Book> &b)
    {
        books = b;
    }

    void set_admins(const vector<Admin> &b)
    {
        admins = b;
    }

    Member *get_the_member(const string &name)
    {
        for (auto &it : members)
        {
            if (to_lower(trim(it.get_name())) == to_lower(trim(name)))
            {
                return &it;
            }
        }
        return nullptr;
    }

    void giving_books(const string &name)
    {
        Member *m = get_the_member(name);
        if (m)
        {
            giving_book(*m);
            save_members_to_csv("members.csv");
            save_books_to_csv("books.csv");
        }
        else
        {
            cout << "You are not a member!!\n";
        }
    }

    void return_book_by_member(string name)
    {
        
        

        
            Member *m = get_the_member(name);
            string returned_title = m->return_book();
            if (!returned_title.empty())
            {
                try
                {
                    Book &b = get_the_book(returned_title);
                    b.increase_quantity();
                    save_members_to_csv("members.csv");
                    save_books_to_csv("books.csv");
                }
                catch (const runtime_error &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
            }
        
    }

    void verify_Member(const string &n, const string &p)
    {
        string trimmed_n = trim(n);
        string trimmed_p = trim(p);
        cout << "Debug: Verifying member - Name: '" << trimmed_n << "', Password: '" << trimmed_p << "'\n";
        if (verify_Member_logic(trimmed_n, trimmed_p))
        {
            cout << "Welcome " << trimmed_n << endl;
        }
        else
        {
            cout << "Wrong name or password.\n";
        }
    }

    bool verify_Member_bool(const string &n, const string &p) const
    {
        return verify_Member_logic(trim(n), trim(p));
    }

    void verify_Admin(const string &n, const string &p)
    {
        string trimmed_n = trim(n);
        string trimmed_p = trim(p);
        cout << "Debug: Verifying admin - Name: '" << trimmed_n << "', Password: '" << trimmed_p << "'\n";
        if (verify_Admin_logic(trimmed_n, trimmed_p))
        {
            cout << "Welcome " << trimmed_n << endl;
        }
        else
        {
            cout << "No such admin found... Wrong name or password\n";
        }
    }

    bool verify_Admin_bool(const string &n, const string &p) const
    {
        return verify_Admin_logic(trim(n), trim(p));
    }

    void add_book()
    {
        string title, author, pub;
        int e, quantity;
        cout << "Adding new book...\n";
        cout << "Set title: ";
        getline(cin >> ws, title);
        cout << "Set Author: ";
        getline(cin, author);
        cout << "Set Publisher: ";
        getline(cin, pub);
        cout << "Set Edition: ";
        cin >> e;
        cout << "Set Quantity: ";
        cin >> quantity;
        addBook(trim(title), trim(author), trim(pub), e, quantity);
        save_books_to_csv("books.csv");
    }

    void add_member()
    {
        string name, memid, password;
        cout << "Adding new member...\n";
        cout << "Set Name: ";
        getline(cin >> ws, name);
        cout << "Set memID: ";
        getline(cin, memid);
        cout << "Set Password: ";
        getline(cin, password);
        addMember(trim(name), trim(memid), trim(password));
        save_members_to_csv("members.csv");
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
        if (choice >= 1 && choice <= static_cast<int>(books.size()))
        {
            books.erase(books.begin() + (choice - 1));
            cout << "Book removed successfully.\n";
            save_books_to_csv("books.csv");
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
        if (choice >= 1 && choice <= static_cast<int>(members.size()))
        {
            members.erase(members.begin() + (choice - 1));
            cout << "Member removed successfully.\n";
            save_members_to_csv("members.csv");
        }
        else
        {
            cout << "Invalid member number.\n";
        }
    }

    void add_admin()
    {
        string name, password;
        cout << "Adding new admin...\n";
        cout << "Set Name: ";
        getline(cin >> ws, name);
        cout << "Set Password: ";
        getline(cin, password);
        addAdmin(trim(name), trim(password));
        save_admins_to_csv("admins.csv");
    }

    void show_book_list() { book_list(); }
    void show_admin_list() { admin_list(); }
    void show_member_list() { member_list(); }

    void inquiry_books()
{
    book_list();
    if (books.empty())
    {
        cout << "No books available to inquire.\n";
        return;
    }

    int i;
    bool valid_input = false;
    do
    {
        cout << "Choose book to inquire (1-" << books.size() << "): ";
        if (cin >> i)
        {
            if (i >= 1 && i <= static_cast<int>(books.size()))
            {
                valid_input = true;
                cout << "Debug: Selected book index " << i << endl;
                books[i - 1].show_details();
            }
            else
            {
                cout << "Invalid book number. Please enter a number between 1 and " << books.size() << ".\n";
            }
        }
        else
        {
            cout << "Invalid input. Please enter a numeric value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!valid_input);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after valid input
}

    void inquiry_members()
{
    member_list();
    if (members.empty())
    {
        cout << "No members available to inquire.\n";
        return;
    }

    int i;
    bool valid_input = false;
    do
    {
        cout << "Choose member to inquire (1-" << members.size() << "): ";
        if (cin >> i)
        {
            if (i >= 1 && i <= static_cast<int>(members.size()))
            {
                valid_input = true;
                cout << "Debug: Selected member index " << i << endl;
                members[i - 1].show_details();
            }
            else
            {
                cout << "Invalid member number. Please enter a number between 1 and " << members.size() << ".\n";
            }
        }
        else
        {
            cout << "Invalid input. Please enter a numeric value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!valid_input);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after valid input
}
};

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
    // Create empty CSV files if they don't exist
    ofstream booksFile("books.csv", ios::app);
    if (booksFile.tellp() == 0)
    {
        booksFile << "Title,Author,Publisher,Edition,Quantity\n";
    }
    booksFile.close();

    ofstream membersFile("members.csv", ios::app);
    if (membersFile.tellp() == 0)
    {
        membersFile << "Name,MemberID,Password,BorrowedBooks\n";
    }
    membersFile.close();

    ofstream adminsFile("admins.csv", ios::app);
    if (adminsFile.tellp() == 0)
    {
        adminsFile << "Name,Password\n";
    }
    adminsFile.close();

    Library library;
    int main_choice;

    library.load_books_from_csv("books.csv");
    library.load_members_from_csv("members.csv");
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        if (main_choice == 1)
        {
            string name, pass;
            clear_screen();
            printAsciiArt();
            cout << "Admin Login\n";
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Password: ";
            getline(cin, pass);

            library.verify_Admin(name, pass);

            bool is_admin = library.verify_Admin_bool(name, pass);

            if (is_admin)
            {
                int admin_choice;
                while (true)
                {
                    clear_screen();
                    printAsciiArt();

                    cout << "\n==== Hello " << trim(name) << " ====\n";
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                    cin.get();
                }
            }
            else
            {
                cout << "Invalid admin credentials.\n";
                cout << "\nPress Enter to continue...";
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
            getline(cin, name);
            cout << "Enter Password: ";
            getline(cin, pass);

            library.verify_Member(name, pass);

            bool is_member = library.verify_Member_bool(name, pass);

            if (is_member)
            {
                Member *m = library.get_the_member(name);

                int mem_choice;
                while (true)
                {
                    clear_screen();
                    printAsciiArt();
                    cout << "\n==== Hello " << trim(name) << " ====\n";
                    cout << "1. Borrow Book\n";
                    cout << "2. Return Book\n";
                    cout << "3. List Borrowed Books\n";
                    cout << "4. Full Profile\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> mem_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (mem_choice)
                    {
                    case 1:
                        clear_screen();
                        printAsciiArt();
                        library.show_book_list();
                        library.giving_books(name);
                        break;
                    case 2:
                        clear_screen();
                        printAsciiArt();
                        library.return_book_by_member(name);
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
                    cin.get();
                }
            }
            else
            {
                cout << "Invalid user credentials.\n";
                cout << "\nPress Enter to continue...";
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
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    main_menu:
        continue;
    }

    return 0;
}
