#include "evidencesmanager.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>

using namespace Core;

EvidencesManager::EvidencesManager(QTreeWidget *holder) : _tree(holder)
{
    _current_color = 0xFFFFFFFF;
}

QTreeWidgetItem *EvidencesManager::addRoot(const QString &name)
{
    _tree->blockSignals(true);

    QTreeWidgetItem* itm = new QTreeWidgetItem(_tree);
    itm->setText(0,name);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    QPixmap ico(16,16);
    QColor w(0xFFFFFFFF);
    ico.fill(w);
    itm->setIcon(0,QIcon(ico));
    _tree->addTopLevelItem(itm);
    itm->setExpanded(true);
    _current_color = w.rgba();
    Evidence val;
    val._color = w;
    val._name = itm->text(0);
    val._parent = itm->parent();
    _evidences.insert(itm,val);

    _tree->blockSignals(false);
    return itm;
}

QTreeWidgetItem *EvidencesManager::addChild(QTreeWidgetItem *parent, const QString &name)
{
    QTreeWidgetItem* itm = new QTreeWidgetItem(parent);
    itm->setText(0,name);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    itm->setIcon(0,parent->icon(0));
    parent->addChild(itm);
    itm->setExpanded(true);
    Evidence val;
    _current_color = _evidences.value(parent)._color.rgba();
    val._color = _evidences.value(parent)._color;
    val._name = itm->text(0);
    val._parent = itm->parent();
    _evidences.insert(itm,val);
    return itm;
}

bool EvidencesManager::addChild(const QString &name)
{
    _tree->blockSignals(true);

    QTreeWidgetItem* cur = _tree->currentItem();
    bool retVal = checkItem(cur,QObject::tr("предок"));

    _tree->blockSignals(false);

    return retVal == true ? addChild(cur,name) != 0 : false;
}

inline bool EvidencesManager::checkItem(QTreeWidgetItem *item, const QString& goal) const
{
    bool retVal = true;
    if(!item)
    {
        QMessageBox::warning(0,QObject::tr("Ошибка"),
                                     QObject::tr("Снача мышью выберите(кликните на) признак %1").arg(goal));
        retVal = false;
    }
    return retVal;
}

void EvidencesManager::removeItem(QTreeWidgetItem *item)
{
    if(!item) return;

    removeItem(item->child(0));
    Evidence rem = _evidences.take(item);
    qDebug() << "remove" << rem._name;
    delete item;
}

void EvidencesManager::removeItem()
{
    qDebug("remmy");
    QTreeWidgetItem* cur = _tree->currentItem();
    if(checkItem(cur,QObject::tr("для удаления")))
        removeItem(cur);
}

void EvidencesManager::setItemColor(QTreeWidgetItem *item)
{
    _tree->blockSignals(true);


    Evidence val = _evidences.value(item);

    QColor color = QColorDialog::getColor(val._color,_tree);
    if( _evidences.value(item)._color == color)
    {
        _tree->blockSignals(false);
        return;
    }
    QPixmap ico(16,16);
    ico.fill(color);
    item->setIcon(0,QIcon(ico));
    _current_color = color.rgba();
    val._color = color;
    val._name = item->text(0);
    val._parent = item->parent();
    _evidences.insert(item,val);

    _tree->blockSignals(false);
}

void EvidencesManager::setItemColor()
{
    QTreeWidgetItem* cur = _tree->currentItem();
    if(checkItem(cur,QObject::tr("для смены его цвета")))
        setItemColor(_tree->currentItem());
}

void EvidencesManager::itemChanged(QTreeWidgetItem *item, int col)
{
    if(col)
        qDebug("Mistique");
    Evidence val = _evidences.value(item);
    val._name = item->text(0);
    val._parent = item->parent();
    _evidences.insert(item,val);
    qDebug() << "chafae"<< item->text(0);
}

QColor EvidencesManager::itemColor(QTreeWidgetItem *item)
{
    _tree->blockSignals(true);
    QColor retVal = _evidences.value(item)._color;
    _current_color = retVal.rgba();
    _tree->blockSignals(false);
    return retVal;
}

QColor EvidencesManager::itemColor()
{
    QTreeWidgetItem* cur = _tree->currentItem();
    QColor retVal;
    if(checkItem(cur,QObject::tr("для выбора его цвета")))
    {
        retVal = itemColor(_tree->currentItem());
        _current_color = retVal.rgba();
    }
    return retVal;
}

uint *EvidencesManager::currentColor()
{
    return &_current_color;
}

Evidence EvidencesManager::evudence(QTreeWidgetItem *item)
{
    return _evidences.value(item);
}

