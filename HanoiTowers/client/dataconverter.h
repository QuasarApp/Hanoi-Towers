#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <localuser.h>
#include <userpreview.h>
#include <userdata.h>

namespace LoginView {
   class UserData;
}

/**
 * @brief The DataConverter class convert users data.
 */
class DataConverter
{
public:
    DataConverter();

    static UserPreview toUserPreview(const LocalUser& input);
    static UserPreview toUserPreview(const QSharedPointer<LocalUser>& input);
    static UserPreview toUserPreview(const LoginView::UserData& input);

    static UserData toUserData(const QSharedPointer<LocalUser>& input);
    static UserData toUserData(const LocalUser& input);
    static QSharedPointer<UserData> toUserDataPtr(const QSharedPointer<LocalUser>& input);
    static QSharedPointer<UserData> toUserDataPtr(const LocalUser& input);

};

#endif // DATACONVERTER_H
