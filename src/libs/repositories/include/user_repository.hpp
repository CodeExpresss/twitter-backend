#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "user.hpp"

class UserRepository {
public:
    UserRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~UserRepository() = default;

    std::vector<User> get_where() {}
    User get_by_id(int id) {}
    void create(User item) {}
    void update(User item) {}
    void erase(int id) {}

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // USER_REPOSITORY_HPP
