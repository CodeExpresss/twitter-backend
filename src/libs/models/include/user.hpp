#ifndef USER_HPP
#define USER_HPP

#include <utility>

#include "models_header.hpp"

class User {
public:
    User(int id, std::string password, std::string& email, std::string& session, bool is_active = 1)
        : user_id(id), password(std::move(password)), email(std::move(email)), session(std::move(session)), is_active(is_active) {};
    User(int id, std::string email, std::string password): user_id(id), password(std::move(password)), email(std::move(email)) {};
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
    std::string session;
    bool is_active;

    bool change_password();
    bool change_email();
    //bool set_username();
};

#endif
