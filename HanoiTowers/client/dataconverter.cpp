#include "dataconverter.h"
#include <lvmainmodel.h>
#include <QSharedPointer>

DataConverter::DataConverter()
{

}

UserPreview DataConverter::toUserPreview(const LocalUser &input) const {
    UserPreview result;

    result.id = input.userId();
    result.record = input.record();
    result.userName = input.name();

    return result;
}

UserPreview DataConverter::toUserPreview(const QSharedPointer<LocalUser> &input) const {
    UserPreview result;

    result.id = input->userId();
    result.record = input->record();
    result.userName = input->name();

    return result;
}

UserPreview DataConverter::toUserPreview(const LoginView::UserData &input) const {
    UserPreview result;

    result.id = input.nickname();
    result.record = 0;
    result.userName = input.nickname();

    return result;
}
