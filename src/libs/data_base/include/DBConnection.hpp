#ifndef DBCONNECTION_HPP
#define DBCONNECTION_HPP

#include <memory>
#include <string>
#include <postgresql/libpq-fe.h>

using namespace std;

class DBConnection
{
public:
    DBConnection(string host, string dbname, string user, string password, int port);
    shared_ptr<PGconn> get_connection() const;

private:
    shared_ptr<PGconn> connection;
};

#endif