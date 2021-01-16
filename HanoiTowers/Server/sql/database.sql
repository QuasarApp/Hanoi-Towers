CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) NOT NULL,
    userName VARCHAR(64) default NULL,

--Profile data
    gameState BLOB default NULL,
    points INTEGER default NULL,

    updateTime INTEGER default 0,
    userAvatar INTEGER default 0,

    FOREIGN KEY(id) REFERENCES NetworkMembers(userName)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Avatars (
    id INTEGER PRIMARY KEY NOT NULL,
    user_id VARCHAR(64) NOT NULL,
    data BLOB default NULL,

    FOREIGN KEY(user_id) REFERENCES NetworkMembers(id)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);
