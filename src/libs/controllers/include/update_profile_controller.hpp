#include <controller_header.hpp>

class UpdateProfileController {
public:
    explicit UpdateProfileController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~UpdateProfileController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};