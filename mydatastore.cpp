#include <iomanip>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){
  for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }
  for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete it->second;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);

  set<string> keys = p->keywords();
  for (set<string>::iterator it = keys.begin(); it != keys.end(); ++it){
    keywordMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  string key = convToLower(u->getName());
  users_[key] = u;
  carts_[key];
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  set<Product*> result;
  bool first = true;

  for (size_t i = 0; i < terms.size(); ++i){
    set<Product*> matches;
    map<string, set<Product*>>::iterator it = keywordMap_.find(convToLower(terms[i]));
    if (it !=keywordMap_.end()){
      matches = it->second;
    }
    if (first){
      result = matches;
      first = false;
    }
    else if (type == 0){
      result = setIntersection(result, matches);
    }
    else{
      result = setUnion(result, matches);
    }
  }
  return vector<Product*>(result.begin(), result.end());
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << endl;
  for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    it->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}

User* MyDataStore::findUser(const std::string& username){
  map<string, User*>::iterator it = users_.find(convToLower(username));
  if (it == users_.end()){
    return NULL;
  }
  return it->second;
}

bool MyDataStore::addToCart(const std::string& username, Product* p){
  if (findUser(username) == NULL || p == NULL){
    return false;
  }

  carts_[convToLower(username)].push_back(p);
  return true;
}

bool MyDataStore::viewCart(const std::string& username, std::ostream& os){
  if (findUser(username) == NULL){
    return false;
  }

  deque<Product*>& cart = carts_[convToLower(username)];
  int itemNo = 1;
  for (deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it){
    os << "Item " << setw(3) << itemNo << endl;
    os << (*it)->displayString() << endl;
    os << endl;
    itemNo++;
  }
  return true;
}

bool MyDataStore::buyCart(const std::string& username){
  User* u = findUser(username);
  if (u == NULL){
    return false;
  }
  deque<Product*>& cart = carts_[convToLower(username)];
  deque<Product*> remaining;
  for (deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it){
    Product* p = *it;
    if (p->getQty() > 0 && u->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      u->deductAmount(p->getPrice());
    }
    else{
      remaining.push_back(p);
    }
  }
  cart = remaining;
  return true;
}