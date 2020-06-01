#ifndef USER_HPP
#define USER_HPP

#include <utility>

#include "models_header.hpp"

class User {
public:
    User(int id, std::string& password, std::string& email, std::string& session, bool is_active = 1);
    User(int id, std::string email, std::string password);
    User() = default;
    ~User() = default;

    bool login();
    bool logout();
    bool sign_up();
    bool change_user_data();

    int get_user_id();
    std::string& get_password();
    std::string& get_email();
    bool get_is_active();
    std::string& get_session();

    void set_user_id(int id);
    void set_password(std::string& _password);
    void set_email(std::string& _email);
    void set_is_active(bool status);
    void set_session(std::string& _session);

private:
    int user_id;
    std::string password;
    std::string email;
    std::string session;
    bool is_active;

    bool change_password();
    bool change_email();
    //bool set_username();
};

#endif
