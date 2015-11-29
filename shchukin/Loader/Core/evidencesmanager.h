#ifndef EVIDENCESMANAGER_H
#define EVIDENCESMANAGER_H

#include <QTreeWidget>
#include <QHash>


namespace Core {

struct Evidence {
    QString _name;
    QColor _color;
    QTreeWidgetItem* _parent;
};

class EvidencesManager
{
public:
    EvidencesManager(QTreeWidget* holder);

    QTreeWidgetItem* addRoot(const QString& name);
    QTreeWidgetItem* addChild(QTreeWidgetItem* parent, const QString& name);
    bool addChild(const QString& name);
    bool checkItem(QTreeWidgetItem* item, const QString &goal) const;
    void removeItem(QTreeWidgetItem* item);
    void removeItem();
    void setItemColor(QTreeWidgetItem* item);
    void setItemColor();
    void itemChanged(QTreeWidgetItem*item, int col);
    QColor itemColor(QTreeWidgetItem* item);
    QColor itemColor();
    uint* currentColor();
    Evidence evudence(QTreeWidgetItem* item);


private:
    QTreeWidget* _tree;
    QHash<QTreeWidgetItem*,Evidence> _evidences;
    uint _current_color;
signals:

public slots:
};

}
#endif // EVIDENCESMANAGER_H
