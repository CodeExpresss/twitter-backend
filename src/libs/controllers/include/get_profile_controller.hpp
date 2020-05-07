#include <controller_header.hpp>

template<typename Serialize>
class GetProfileController: public AbstractController {
public:
    GetProfileController(std::shared_ptr<UnitOfWork> _worker): AbstractController(_worker), _profile() {};
    ~GetProfileController() = default;

    boost::property_tree::ptree get_queryset() override;
private:
    Profile _profile;
    Serialize _serialize;
};
