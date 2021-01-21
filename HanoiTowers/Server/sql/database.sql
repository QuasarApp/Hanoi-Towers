CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) NOT NULL,
    userName VARCHAR(64) default NULL,

--Profile data
    gameState BLOB default NULL,
    points INTEGER default NULL,

    updateTime INTEGER default 0,
    userAvatar BLOB default NULL

    FOREIGN KEY(id) REFERENCES NetworkMembers(userName)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);
