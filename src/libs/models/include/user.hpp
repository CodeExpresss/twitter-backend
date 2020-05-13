#ifndef USER_HPP
#define USER_HPP

#include <utility>

#include "models_header.hpp"

class User {
public:
    User(int id, std::string _email, std::string _password): user_id(id), password(std::move(_password)), email(std::move(_email)) {};
    User() = default;
    ~User() = default;

    bool login();
    bool logout();
    bool sign_up();
    bool change_user_data();

    int get_user_id() {return user_id;}
    std::string& get_password() {return password;}
    std::string& get_email() {return email;}
    bool get_is_active() {return is_active;}
    std::string& get_session() {return session;}

    void set_user_id(int id) {user_id = id;}
    void set_password(std::string& _password) {password = _password;}
    void set_email(std::string& _email) {email = _email;}
    void set_is_active(bool status) {is_active = status;}
    void set_session(std::string& _session) {session = _session;}

private:
    int user_id;
    std::string password;
    std::string email;
    bool is_active;
    std::string session;

    bool change_password();
    bool change_email();
    //bool set_username();
};

#endif
