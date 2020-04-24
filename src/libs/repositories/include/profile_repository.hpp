#ifndef PROFILE_REPOSITORY_HPP
#define PROFILE_REPOSITORY_HPP

//#include "abstract_repository.hpp"
#include "types.hpp"
#include "profile.hpp"

/*class ProfileRepository : public AbstractRepository<Profile> {*/
//public:
    //ProfileRepository() = default;
    //~ProfileRepository() = default;


    //std::vector<Profile> get_all() override;
    //Profile get_by_id(int id) override;
    //void create(Profile item) override;
    //void update(Profile item) override;
    //void erase(int id) override;

//private:
    //Profile a;
/*}*/;

class ProfileRepository {
public:
    ProfileRepository() = default;
    ~ProfileRepository() = default;


    std::vector<Profile> get_all();
    Profile get_by_id(int id);
    void create(Profile item);
    void update(Profile item);
    void erase(int id);

private:
};

#endif // PROFILE_REPOSITORY_HPP
