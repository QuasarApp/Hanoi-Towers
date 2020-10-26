CREATE TABLE IF NOT EXISTS Users (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    passwordHash BLOB default NULL,
    token BLOB default NULL,
    onlineUser BOOLEAN default false
);

CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    name VARCHAR(64) UNIQUE NOT NULL,
    points INTEGER default 0
    userdata BLOB default NULL,
);
