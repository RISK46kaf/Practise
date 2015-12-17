#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene()
{

}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    qDebug()<<mouseEvent->scenePos().toPoint();
    emit mousePressPos(mouseEvent->scenePos().toPoint());
    update();
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    if(mouseEvent->buttons() & Qt::LeftButton)
    {
        emit mouseReleasePos(mouseEvent->scenePos().toPoint());
        update();
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    emit mouseReleasePos(mouseEvent->scenePos().toPoint());
    update();
}
