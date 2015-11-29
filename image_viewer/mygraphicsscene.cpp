#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene()
{

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    qDebug()<<mouseEvent->scenePos().toPoint();
    emit mousePressPos(mouseEvent->scenePos().toPoint());
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    emit mouseReleasePos(mouseEvent->scenePos().toPoint());
}
