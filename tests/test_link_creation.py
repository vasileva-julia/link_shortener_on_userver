async def test_create_no_longlink_param(service_client):
    response = await service_client.get('/v1/create', params = {'shortlink' : 'wiki`'})
    assert response.status == 400


async def test_create_no_shortlink_param(service_client):
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/'})
    assert response.status == 400


async def test_create_extra_params(service_client):
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/',
                                                                'shortlink' : 'wiki`'})
    assert response.status == 200


async def test_create_new_link(service_client, pgsql):
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/',
                                                                'shortlink' : 'wiki'})
    assert response.status == 200
    cursor = pgsql['db_1'].cursor()
    cursor.execute('SELECT * FROM mydb.urls WHERE id = \'wiki\'')
    assert list(cursor) == [('wiki', 'www.wikipedia.org/')]


async def test_create_existing_link(service_client, pgsql):
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/',
                                                                'shortlink' : 'wiki3'})
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/',
                                                                'shortlink' : 'wiki3'})
    assert response.status == 200
    response = await service_client.get('/v1/create', params = {'longlink': 'www.wikipedia.org/',
                                                                'shortlink' : 'wiki0'})
    assert response.status == 200
    # cursor = pgsql['db_1'].cursor()