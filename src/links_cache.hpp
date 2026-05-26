#ifndef LINKSCACHE_H
#define LINKSCACHE_H

#include <userver/components/component.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/dynamic_config/storage/component.hpp>
#include <userver/dynamic_config/source.hpp>
#include <userver/cache/caching_component_base.hpp>
#include <userver/cache/cache_statistics.hpp>
#include <userver/cache/update_type.hpp>

#include <string_view>
#include <chrono>

#include "index.hpp"

namespace shortener {
    namespace components {

        class LinksCache : public userver::components::CachingComponentBase<shortener::models::Index> {
        public:
            constexpr static const std::string_view kName = "recent-links-cache";
            LinksCache(const userver::components::ComponentConfig& config,
                       const userver::components::ComponentContext& context);
        private:
            void Update(userver::cache::UpdateType type, // full or incremental
                        const std::chrono::system_clock::time_point& last_update,
                        const std::chrono::system_clock::time_point& now,
                        userver::cache::UpdateStatisticsScope& stats_scope) override;

            userver::dynamic_config::Source dynamic_conf_;
            userver::storages::postgres::ClusterPtr pg_cluster_;
        };
    };
};

#endif // LINKSCACHE_H