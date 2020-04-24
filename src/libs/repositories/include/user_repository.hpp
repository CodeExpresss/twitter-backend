#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include "types.hpp"
#include "user.hpp"

class UserRepository {
public:
    UserRepository() = default;
    ~UserRepository() = default;


    std::vector<User> get_all();
    User get_by_id(int id);
    void create(User item);
    void update(User item);
    void erase(int id);

private:
};

#endif // REPOSITORY_HPP
