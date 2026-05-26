#include <index.hpp>

using namespace shortener::models;

Index::Index(IndexById links) : all_links(links) {
}

Index::Index(IndexById&& links) : all_links(links) {
}