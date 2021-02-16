#include "dataconverter.h"
#include <lvmainmodel.h>
#include <QSharedPointer>

DataConverter::DataConverter()
{

}

UserPreview DataConverter::toUserPreview(const LocalUser &input) {
    UserPreview result;

    result.id = input.userId();
    result.record = input.record();
    result.userName = input.name();

    return result;
}

UserPreview DataConverter::toUserPreview(const QSharedPointer<LocalUser> &input) {
    return toUserPreview(*input.data());
}

UserPreview DataConverter::toUserPreview(const LoginView::UserData &input) {
    UserPreview result;

    result.id = input.nickname();
    result.record = 0;
    result.userName = input.nickname();

    return result;
}

UserData DataConverter::toUserData(const QSharedPointer<LocalUser> &input) {
    return toUserData(*input.data());
}

UserData DataConverter::toUserData(const LocalUser &input) {
    UserData result;
    result.setUpdateTime(input.updateTime());
    result.setId(input.getId());
    result.setUserData(*input.userData());

    return result;
}

QSharedPointer<UserData> DataConverter::toUserDataPtr(
        const QSharedPointer<LocalUser> &input) {
    return toUserDataPtr(*input.data());
}

QSharedPointer<UserData> DataConverter::toUserDataPtr(const LocalUser &input) {
    auto result = QSharedPointer<UserData>::create(toUserData(input));
    return result;
}

QH::PKG::UserMember DataConverter::toUserMember(const QSharedPointer<LocalUser> &input) {
    return toUserMember(*input.data());
}

QH::PKG::UserMember DataConverter::toUserMember(const LocalUser &input) {
    QH::PKG::UserMember result;
    result.setName(input.getId().toString());
    result.setToken(input.token());
    result.setAuthenticationData(input.hashPassword());

    return result;
}

