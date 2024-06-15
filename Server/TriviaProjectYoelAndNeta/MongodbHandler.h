#pragma once

#include <iostream>

//#include "cmake-build/mongo-cxx-driver/src/bsoncxx/include/bsoncxx/v_noabi/bsoncxx/builder/stream/document-fwd.hpp"
#include "cmake-build/mongo-cxx-driver/src/bsoncxx/include/bsoncxx/v_noabi/bsoncxx/builder/stream/document.hpp"
#include "cmake-build/mongo-cxx-driver/src/bsoncxx/include/bsoncxx/v_noabi/bsoncxx/json.hpp"
#include "cmake-build/mongo-cxx-driver/src/bsoncxx/include/bsoncxx/v_noabi/bsoncxx/oid.hpp"
#include "cmake-build/mongo-cxx-driver/src/mongocxx/include/mongocxx/v_noabi/mongocxx/client.hpp"
#include "cmake-build/mongo-cxx-driver/src/mongocxx/include/mongocxx/v_noabi/mongocxx/database.hpp"
#include "cmake-build/mongo-cxx-driver/src/mongocxx/include/mongocxx/v_noabi/mongocxx/uri.hpp"


class MongodbHandler
{
public:
    bool addCharToDB(const std::string& char_name, const std::string& size, const int16_t& wins);
private:
    mongocxx::v_noabi::database _database;
    mongocxx::v_noabi::uri _uri;
    mongocxx::v_noabi::client _client;
    
    /*mongocxx::v_noabi::database _database;
    mongocxx::v_noabi::database ds;*/
    
};
