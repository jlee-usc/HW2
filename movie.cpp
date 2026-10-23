#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty,
             const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
    // Name words are split at punctuation; genre is used verbatim
    set<string> keys = parseStringToWords(convToLower(name_));
    keys.insert(convToLower(genre_));
    return keys;
}

std::string Movie::displayString() const
{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}
