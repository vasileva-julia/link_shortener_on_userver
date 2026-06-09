from http import HTTPStatus


async def test_create_no_longlink_param(service_client):
    response = await service_client.post('/v1/create', params = {'shortlink' : 'wiki'})
    assert response.status == HTTPStatus.BAD_REQUEST


async def test_create_no_shortlink_param(service_client):
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/'})
    assert response.status == HTTPStatus.BAD_REQUEST


async def test_create_extra_params(service_client, pgsql):
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
                                                                'shortlink' : 'wiki'})
    assert response.status == HTTPStatus.CREATED
    cursor = pgsql['db_1'].cursor()
    cursor.execute('SELECT * FROM mydb.urls WHERE id = \'wiki\'')
    assert list(cursor) == [('wiki', 'http://www.wikipedia.org/')]


async def test_create_new_link(service_client, pgsql):
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
                                                                'shortlink' : 'wiki'})
    assert response.status == HTTPStatus.CREATED
    cursor = pgsql['db_1'].cursor()
    cursor.execute('SELECT * FROM mydb.urls WHERE id = \'wiki\'')
    assert list(cursor) == [('wiki', 'http://www.wikipedia.org/')]


async def test_create_existing_link(service_client, pgsql):
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
                                                                'shortlink' : 'wiki3'})
    assert response.status == HTTPStatus.CREATED
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
                                                                'shortlink' : 'wiki3'})
    assert response.status == HTTPStatus.CONFLICT
    response = await service_client.post('/v1/create', params = {'longlink': 'http://www.wikipedia.org/',
                                                                'shortlink' : 'wiki0'})
    assert response.status == HTTPStatus.CREATED