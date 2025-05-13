#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);

class Member
{
private:
    string name;
    string memID;
    string password;

public:
    Member(string n, string m, string p)
        : name(n), memID(m), password(p) {}

    void mem_details()
    {
        cout << "\Member Details\n";
        cout << this->name << endl;
        cout << this->memID << endl;
    }
    void setmem_details(string n, string id, string p)
    {
        this->name = n;
        this->memID = id;
        this->password = p;
    }
};
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
        cout << this->title << endl;
        cout << this->author << endl;
        cout << this->publisher << endl;
        cout << this->edition << endl;
    }
    void setbook_details(string t, string auth, string pub, int e, bool av)
    {

        this->title = t;
        this->author = auth;
        this->publisher = pub;
        this->edition = e;
        this->avail = av;
    }
};
class Library
{

private:
    vector<Book> books;
    vector<Member> members;
};
int main()
{
    fastio;

    return 0;
}