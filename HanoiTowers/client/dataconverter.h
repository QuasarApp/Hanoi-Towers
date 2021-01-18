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

    UserPreview toUserPreview(const LocalUser& input) const;
    UserPreview toUserPreview(const QSharedPointer<LocalUser>& input) const;
    UserPreview toUserPreview(const LoginView::UserData& input) const;

};

#endif // DATACONVERTER_H
