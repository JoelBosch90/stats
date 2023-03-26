# Stats

This is a lightweight setup to provide insight into website statistics that can
be run entirely server-side. It works by reading It uses three different
services:

## Collector

This service periodically reads Nginx access logs, and stores them in an Sqlite3
database.

## API

This service provides a REST API to access the data in the Sqlite3 database.

## Client

this service provides a web interface to view the data provided by the REST API.
