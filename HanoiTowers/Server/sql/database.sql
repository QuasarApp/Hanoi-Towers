CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) NOT NULL UNIQUE,

--General user name, it is not userID of local user. for get userId see NetworkMembers.userName of the UserDB.sql
    userName VARCHAR(64) default NULL,

--Profile data
    gameState BLOB default NULL,
    points INTEGER default NULL,

    updateTime INTEGER default 0,
    userAvatar BLOB default NULL,

    FOREIGN KEY(id) REFERENCES NetworkMembers(id)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);
