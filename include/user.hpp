#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
    User();
    ~User();

    bool login();
    bool logout();
    bool sign_up();
    bool check_user();
    bool is_active();
private:
    int user_id;
    std::string password;
    std::string email;

    bool set_password();
    bool set_email();
    bool set_username();
};

#endif
