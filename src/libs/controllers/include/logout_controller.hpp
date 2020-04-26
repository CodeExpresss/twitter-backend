#include <controller_header.hpp>

class LogoutController {
public:
    explicit LogoutController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~LogoutController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};