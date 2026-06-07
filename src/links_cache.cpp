#include "links_cache.hpp"

#include <string>

#include "shortener/sql_queries.hpp"

using namespace shortener::components;

LinksCache::LinksCache(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : CachingComponentBase<shortener::models::Index>{config, context},
      dynamic_conf_{context.FindComponent<userver::components::DynamicConfig>().GetSource()},
      pg_cluster_{context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster()}
{}

struct IdAndUrl
{
    std::string id;
    std::string url;
};

void LinksCache::Update(
    userver::cache::UpdateType /* type */,
    [[maybe_unused]] const std::chrono::system_clock::time_point& last_update,
    [[maybe_unused]] const std::chrono::system_clock::time_point& now,
    userver::cache::UpdateStatisticsScope& stats_scope)
{
    auto result = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave,
                                       sql::kSelectAllLinksPairs);
    auto converted_result = result.AsContainer<std::vector<IdAndUrl>>(userver::storages::postgres::kRowTag);
    shortener::models::Index new_index;
    const auto size = converted_result.size();
    stats_scope.IncreaseDocumentsReadCount(size);

    for (const auto& item : converted_result)
        new_index.all_links[item.id] = item.url;

    Emplace(new_index);
    stats_scope.Finish(size);
}