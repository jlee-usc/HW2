#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
           const std::string isbn, const std::string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
    // Name and author words are split at punctuation; ISBN is used verbatim.
    // Everything is stored lowercase so search is case-insensitive.
    set<string> nameWords = parseStringToWords(convToLower(name_));
    set<string> authorWords = parseStringToWords(convToLower(author_));
    set<string> keys = setUnion(nameWords, authorWords);
    keys.insert(convToLower(isbn_));
    return keys;
}

std::string Book::displayString() const
{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}
