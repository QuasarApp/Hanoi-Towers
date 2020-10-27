CREATE TABLE IF NOT EXISTS Users (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    passwordHash BLOB default NULL,
    token BLOB default NULL,
    onlineUser BOOLEAN default false,
    userdata BLOB default NULL,
);
