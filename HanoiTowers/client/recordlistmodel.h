#ifndef RECORDLISTMODEL_H
#define RECORDLISTMODEL_H
#include <QAbstractTableModel>
#include <QMap>
#include <qqml.h>

struct userPreview {
    QString UserName;
    int record;
    bool online;
};

class RecordListModel: public QAbstractTableModel
{
    Q_OBJECT

public:

    enum RecordListModelRoles {
        OnlineRole = Qt::UserRole,
        RemoveRole

    };

    RecordListModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void setSource(const QMap<QString, userPreview> &data);
    void updateSourceInte(const userPreview& data);
    void removeSourceItem(const QString& name);

private:
    QMap<QString, userPreview>  _data;

    // QAbstractItemModel interface
public:
    QHash<int, QByteArray> roleNames() const override;
};

#endif // RECORDLISTMODEL_H
