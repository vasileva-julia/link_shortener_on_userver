#include <userver/components/minimal_server_component_list.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/clients/dns/component.hpp>

#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/clients/http/component_core.hpp>
#include <userver/clients/http/middlewares/pipeline_component.hpp>

#include "src/links_cache.hpp"
#include "src/link_maker_handler.hpp"
#include "src/redirect_handler.hpp"

int main(int argc, char* argv[]) {
    auto component_list = userver::components::MinimalServerComponentList()
        .Append<userver::components::Postgres>("postgres-db-1")
        .Append<userver::clients::dns::Component>()
        .Append<shortener::components::LinksCache>()
        .Append<LinkMakerHandler>()
        .Append<RedirectHandler>()
        .Append<userver::components::TestsuiteSupport>()
        .Append<userver::server::handlers::TestsControl>()
        .Append<userver::components::HttpClient>()
        .Append<userver::components::HttpClientCore>()
        .Append<userver::clients::http::MiddlewarePipelineComponent>();
    return userver::utils::DaemonMain(argc, argv, component_list);
}