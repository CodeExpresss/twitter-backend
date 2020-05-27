#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include "repositories_header.hpp"
#include "user.hpp"

class UserRepository {
public:
    UserRepository(std::weak_ptr<DBController<DBConnection>> controller) : db_controller(controller) {};
    ~UserRepository() = default;

    bool check_user_email(User& item, err_code& rc);
    std::vector<User> get_where() {}
    User get_by_id(int id, err_code &rc);
    User get_by_email(std::string enail, err_code &rc);
    void create(User &item, err_code &rc);
    void update(User &item, err_code &rc);
    void erase(int id, err_code &rc);

private:
    std::weak_ptr<DBController<DBConnection>> db_controller;
};

#endif // USER_REPOSITORY_HPP
