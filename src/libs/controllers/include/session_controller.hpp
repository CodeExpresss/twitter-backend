#ifndef APP_SESSION_CONTROLLER_HPP
#define APP_SESSION_CONTROLLER_HPP

#include "controller_header.hpp"

class SessionController {
public:
    explicit SessionController(std::shared_ptr<UnitOfWork> _worker)
            : worker(_worker) {};
    ~SessionController() = default;

    int get_profile_id(std::string session);
    std::string create_session();
    void delete_session();

private:
    std::shared_ptr<UnitOfWork> worker;
};

#endif
