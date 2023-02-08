# Dependencies

```
sudo apt install sqlite3
sudo apt-get install libsqlite3-dev
```

# Compile command

```
g++ -Wall -Werror -I. -o read_logs.out read_logs.cpp read_logs/open_database.cpp read_logs/read_lines_from_stream_from_end.cpp read_logs/string_to_access_record.cpp -l sqlite3
```
