#include "user.hpp"

User::User(int id, std::string& password,
    std::string& email, std::string& session,
    bool is_active)
    : user_id(id), password(std::move(password)),
    email(std::move(email)), session(std::move(session)),
    is_active(is_active) {
}
User::User(int id, std::string email, std::string password)
    : user_id(id), password(std::move(password)),
    email(std::move(email)) {
}

bool User::login() {}
bool User::logout() {}
bool User::sign_up() {}
bool User::change_user_data() {}

int User::get_user_id() {
    return user_id;
}

std::string& User::get_password() {
    return password;
}

std::string& User::get_email() {
    return email;
}

bool User::get_is_active() {
    return is_active;
}

std::string& User::get_session() {
    return session;
}

void User::set_user_id(int id) {
    user_id = id;
}

void User::set_password(std::string& _password) {
    password = _password;
}

void User::set_email(std::string& _email) {
    email = _email;
}

void User::set_is_active(bool status) {
    is_active = status;
}

void User::set_session(std::string& _session) {
    session = _session;
}
