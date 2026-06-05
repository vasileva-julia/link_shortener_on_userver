import pytest
from testsuite.databases.pgsql import discover, control

pytest_plugins = ['pytest_userver.plugins.core', 'pytest_userver.plugins.postgresql']

# USERVER_CONFIG_HOOKS

SERVICE_BASEURL = 'http://localhost:8083/'


@pytest.fixture(scope='session')
def pgsql_local(service_source_dir, pgsql_local_create):
    databases = discover.find_schemas(
        'mydb',
        [service_source_dir.joinpath('postgresql/schemas')],
    )
    return pgsql_local_create(list(databases.values()))


@pytest.fixture
async def server_client(
        ensure_daemon_started,
        create_service_client,
        mockserver,
        service_daemon,
):
    await ensure_daemon_started(service_daemon)
    return create_service_client(SERVICE_BASEURL)