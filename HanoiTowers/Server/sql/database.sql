CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) PRIMARY KEY NOT NULL,
    visibleName VARCHAR default NULL,
    points INTEGER default 0,
    userdata BLOB default NULL,
    updateTime INTEGER default 0
);
