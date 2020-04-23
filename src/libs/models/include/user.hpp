#ifndef USER_HPP
#define USER_HPP

#include "types.h"

//#include "container_user.hpp"

class ContainerUser {
public:
    //ContainerUser() = default;
    //~ContainerUser() = default;
    void create();
    std::vector<User>& all();
    bool check_user();

private:

};

template <class ContainerUser>
class User {
public:
    User();
    ~User();

    bool login() {
        return User::objects.check_user();
    }
    bool logout();
    bool sign_up();
    bool change_user_data();
    bool is_active();

    static ContainerUser objects; // interface !
private:
    int user_id;
    std::string password;
    std::string email;
    std::string session;

    bool change_password();
    bool change_email();
    //bool set_username();
};

#endif
