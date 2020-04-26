#include <controller_header.hpp>

class LoginController {
public:
    explicit LoginController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~LoginController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};