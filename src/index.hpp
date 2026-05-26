#ifndef INDEX_H
#define INDEX_H

#include<unordered_map>
#include<string>
#include<memory>

namespace shortener {
    namespace models {
        
        struct Index final {
            using IndexById = std::unordered_map<std::string /* id */, std::string /* link */>;

            explicit Index(IndexById links = {});
            Index(IndexById&& links);

            IndexById all_links;
        };

        using IndexPtr = std::shared_ptr<const Index>;
    };
};

#endif // INDEX_H