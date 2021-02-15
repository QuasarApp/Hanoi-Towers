CREATE TABLE IF NOT EXISTS Users (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    passwordHash BLOB default NULL,
    token BLOB default NULL,

--Profile data
    gameState BLOB default NULL,
    userName VARCHAR(64) default NULL,
    points INTEGER default NULL,
    fOnline BOOLEAN default false,

    updateTime INTEGER default 0,
    userAvatar BLOB default NULL

);

