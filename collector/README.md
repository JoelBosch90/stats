# Collector

This is a C++ program that will check Nginx access log periodically, is able to
read default log entries and stores these entries in a Sqlite3 database.

This service makes sure that the API service has easy and efficient access to
the website statistics.

This services also takes care of hashing some of the personally identifiable
data that can be in the access records. It hashes both IP addresses and the
authentication parts of the URL with a salt that rotates daily. This means that
it is possible to use this information to accurately calculate unique website
visitors per day, but not across longer periods of time.

## Volumes

This service requires two mounted volumes:

### /data

The collector uses the `/data` volume to store the Sqlite3 database, so it will
need read and write access to this volume.

### /logs

The collector uses the `/logs` volume to search for the Nginx access log, so it
will only need read access to this volume.

## Environment variables

This services can be configured with the following environment variables:

### DATABASE_NAME

By setting `DATABASE_NAME`, you can rename the name of the Sqlite3 database that
the collector will create in the `/data` volume. By default, it is called
`stats.db`.

### LOGFILE_NAME

By setting `LOGFILE_NAME`, you can rename the name of the Nginx access log file
that the collector will read from in the `/logs` volume. By default, it will
try to read from `access.log`.

### UPDATE_INTERVAL

By setting `UPDATE_INTERVAL`, you can configure the interval at which the
collector will update the Sqlite3 database with the latest log entries from the
Nginx access log.
