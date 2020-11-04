#ifndef USERPREVIEW_H
#define USERPREVIEW_H

#include <QByteArray>
#include <QString>

struct UserPreview {
    QByteArray id;
    QString userName;
    int record;
};
#endif // USERPREVIEW_H
