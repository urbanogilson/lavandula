# Lavandula with SQL

This file assumes you have a linux-based environment.



## Setting up SqlLite3

First, create a new Lavandula project.

Run the following command to install SqlLite3.

```bash
sudo apt install libsqlite3-dev sqlite3
```

or

```bash
brew install sqlite3
```


Include this header file in your project.

```c
#include <sqlite3.h>
```

Ensure to run your application with this flag:

```bash
-lsqlite3
```