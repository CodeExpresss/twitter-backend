#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "container_user.hpp"

class User {
public:
    User();
    ~User();

    bool login();
    bool logout();
    bool sign_up();
    bool change_user_data();
    bool is_active();
private:
    int user_id;
    std::string password;
    std::string email;
    std::string session;

    bool change_password();
    bool change_email();
    //bool set_username();
    static ContainerUser &Objects;
};

#endif
