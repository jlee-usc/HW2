#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <iostream>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore{
  public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    bool addToCart(const std::string& username, Product* p);
    bool viewCart(const std::string& username, std::ostream& os);
    bool buyCart(const std::string& username);

  private:
    User* findUser(const std::string& username);

    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_;
    std::map<std::string, std::deque<Product*>> carts_;
};
#endif