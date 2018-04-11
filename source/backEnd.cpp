#include "backEnd.h"
#include <cmath>

BackEnd::BackEnd():
    QObject()
{

}

unsigned short BackEnd::getMinSteps(const unsigned short lvl) const{
    return pow(2, lvl) - 1;
}

void BackEnd::save(const short &lvl) const{
    QFile f(SAVE);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        f.write((char*)(&lvl),sizeof(lvl));
        f.close();
    }
}

short BackEnd::read()const{
    short temp=1;
    QFile f(SAVE);
    if(f.open(QIODevice::ReadOnly)){
        f.read((char*)&temp,sizeof(temp));
        f.close();
    }
    return temp;
}
