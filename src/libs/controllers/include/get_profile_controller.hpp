#include <controller_header.hpp>

class GetProfileController {
public:
    explicit GetProfileController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~GetProfileController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};