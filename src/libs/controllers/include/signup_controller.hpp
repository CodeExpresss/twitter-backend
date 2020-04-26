#include <controller_header.hpp>

class SignUpController {
public:
    explicit SignUpController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~SignUpController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};