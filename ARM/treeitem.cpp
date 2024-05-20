#include "treeitem.h"
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QFile>

QMap<QString, int> orderList;

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent) {
    parentItem = parent;
    itemData = data;
}

TreeItem::~TreeItem() {
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int number) {
    return childItems.value(number);
}

int TreeItem::childCount() const {
    return childItems.count();
}

int TreeItem::childNumber() const {
    if (!parentItem) {
        return 0;
    }
    return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
}

int TreeItem::columnCount() const {
    return itemData.count();
}

QVariant TreeItem::data(int column) const {
    return itemData.value(column);
}

bool TreeItem::insertChildren(int position, int count, int columns){
    if (position < 0 || position > childItems.size()) {
        return false;
    }
    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }
    return true;
}

bool TreeItem::insertColumns(int position, int columns) {
    if (position < 0 || position > itemData.size()) {
        return false;
    }
    for (int column = 0; column < columns; ++column) {
        itemData.insert(position, QVariant());
    }
    foreach (TreeItem *child, childItems) {
        child->insertColumns(position, columns);
    }
    return true;
}

TreeItem *TreeItem::parent() {
    return parentItem;
}

bool TreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > childItems.size()) {
        return false;
    }
    for (int row = 0; row < count; ++row) {
        delete childItems.takeAt(position);
    }
    return true;
}

bool TreeItem::removeColumns(int position, int columns) {
    if (position < 0 || position + columns > itemData.size()) {
        return false;
    }
    for (int column = 0; column < columns; ++column) {
        itemData.remove(position);
    }
    foreach (TreeItem *child, childItems) {
        child->removeColumns(position, columns);
    }
    return true;
}

void writeOrderFile(const QString name, int delta, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qWarning() << "Could not open file" << filename;
        return;
    }

    QTextStream out(&file);
    out << name << " - " << delta << "\n";

    file.close();
}

void parse(const QVariant &value) {
    QString str = value.toString();
    QString name;
    QString currentCount;
    QString maxCount;
    int idx = 0;
    int delta;
    while(idx < str.length() - 1) {
        name = "";
        currentCount = "";
        maxCount = "";
        while (str[idx] != '[' and idx < str.length()) {
            idx++;
        }
        while (str[++idx] != ';' and idx < str.length()) {
            name += str[idx];
        }
        while (str[++idx] != '/' and idx < str.length()) {
            currentCount += str[idx];
        }
        while (str[++idx] != ']' and idx < str.length()) {
            maxCount += str[idx];
        }
        delta = maxCount.toInt() - currentCount.toInt();
        if (delta > 0) {
            writeOrderFile(name, delta, "Order.txt");
        }
        orderList.insert(name, delta);
    }
}

bool TreeItem::setData(int column, const QVariant &value) {
    if (column < 0 || column >= itemData.size()) {
        return false;
    }
    itemData[column] = value;
    parse(value);
    return true;
}

