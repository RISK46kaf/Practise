#ifndef CUTTER_H
#define CUTTER_H
#include <QImage>
#include <vector>
#include <QDebug>

using namespace std;

class Cutter
{
public:
    Cutter();
    void cut(QString image_path);
    QSize image_size;
    uint scales_amount;
    QSize tile_size;
    vector<QSize> tile_amount;

};

#endif // CUTTER_H
