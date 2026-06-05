-- -- DROP SCHEMA IF EXISTS links_urls CASCADE;

-- -- CREATE SCHEMA IF NOT EXISTS links_urls;

-- -- CREATE TABLE IF NOT EXISTS links_urls.urls (
-- --     uuid TEXT PRIMARY KEY,
-- --     author TEXT NOT NULL,
-- --     ip_source TEXT NOT NULL,
-- --     text TEXT NOT NULL,
-- --     created_at TIMESTAMPTZ NOT NULL
-- -- );



-- CREATE ROLE test_user PASSWORD 'password' LOGIN CREATEDB;

-- SET ROLE test_user;

-- CREATE DATABASE mydb;

-- \c postgresql://test_user:password@service-postgres:5432/mydb

-- CREATE TABLE IF NOT EXISTS urls (
--     id VARCHAR(10) PRIMARY KEY,
--     url VARCHAR(20)
-- );

-- -- DROP SCHEMA IF EXISTS links_urls CASCADE;

-- -- CREATE SCHEMA IF NOT EXISTS links_urls;

-- -- CREATE TABLE IF NOT EXISTS links_urls.urls (
-- --     id VARCHAR(10) PRIMARY KEY,
-- --     url VARCHAR(20)
-- -- );




DROP SCHEMA IF EXISTS mydb CASCADE;

CREATE SCHEMA IF NOT EXISTS mydb;

CREATE TABLE IF NOT EXISTS mydb.urls (
    id VARCHAR(10) PRIMARY KEY,
    url VARCHAR(20)
);
