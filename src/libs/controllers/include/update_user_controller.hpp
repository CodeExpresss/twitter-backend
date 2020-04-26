#include <controller_header.hpp>

class UpdateUserController {
public:
    explicit UpdateUserController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~UpdateUserController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};