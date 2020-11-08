CREATE TABLE IF NOT EXISTS Users (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    passwordHash BLOB default NULL,
    token BLOB default NULL,
    userdata BLOB default NULL,
    updateTime INTEGER default 0
    userAvatar INTEGER default 0,

);

CREATE TABLE IF NOT EXISTS Avatars (
    id INTEGER PRIMARY KEY NOT NULL
    user_id VARCHAR(64) NOT NULL,
    data BLOB default NULL,

    FOREIGN KEY(user_id) REFERENCES Users(id)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);
