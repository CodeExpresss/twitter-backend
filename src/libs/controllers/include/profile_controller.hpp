#include <controller_header.hpp>

class ProfileController {
public:
    explicit ProfileController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~ProfileController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};