#include <controller_header.hpp>

class UserController {
public:
    explicit UserController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~UserController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};