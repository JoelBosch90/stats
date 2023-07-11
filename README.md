**Note that this is currently an incomplete product and in active development.**

# Stats

This is a lightweight setup to provide insight into website statistics that can
be run entirely server-side. It works by reading the Nginx access logs. It uses
four different services:

## Proxy

This service reroutes incoming traffic to the correct services.

## Collector

This service periodically reads Nginx access logs, interprets those logs, and
stores them in an Sqlite3 database.

## Api

This service provides a REST API to access the data in the Sqlite3 database.

## Web

This service provides a web interface to login and visualize the data in the
Sqlite3 database.
