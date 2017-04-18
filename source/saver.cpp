#include "saver.h"

Saver::Saver():
    QObject()
{

}
void Saver::save(const short &lvl) const{
    QFile f(SAVE);
    if(f.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        f.write((char*)(&lvl),sizeof(lvl));
        f.close();
    }
}
short Saver::read()const{
    short temp=1;
    QFile f(SAVE);
    if(f.open(QIODevice::ReadOnly)){
        f.read((char*)&temp,sizeof(temp));
        f.close();
    }
    return temp;
}
