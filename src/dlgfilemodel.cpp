#include "dlgfilemodel.h"

DlgFileModel::DlgFileModel(const QDir &dir) : AbstractTableModelTrackBy(1), _dir(dir) {
    _watcher.addPath(dir.absolutePath());
    QObject::connect(&_watcher, &QFileSystemWatcher::directoryChanged, this, &DlgFileModel::update);
    update();
}

void DlgFileModel::update() {
    QFileInfoList list;
    if (_displayHidden) {
        _dir.setFilter(QDir::AllEntries | QDir::Hidden);
    } else {
        _dir.setFilter(QDir::AllEntries);
    }
    _dir.setSorting(QDir::DirsFirst | QDir::Name);
    list = _dir.entryInfoList();

    QVector<Row> newData;

    if(_dir.path() != "/") {
        Row row;
        row.key = "";
        QMap<int, QVariant> column;
        column[Qt::DisplayRole] = "../";
        row.columns.append(std::move(column));
        newData.append(row);
    }

    for (int i = 0; i < list.size(); ++i) {
        const QFileInfo &fileInfo = list.at(i);

        Row row;
        row.key = fileInfo.absoluteFilePath();
        QMap<int, QVariant> column;

        if(fileInfo.fileName() != "." && fileInfo.fileName() != "..") {
            if( fileInfo.isDir()) {
                column[Qt::DisplayRole] = fileInfo.fileName()+"/";
            } else {
                column[Qt::DisplayRole] = fileInfo.fileName();
            }
            row.columns.append(std::move(column));
            newData.append(row);
        }
    }
    setData(newData);
}

void DlgFileModel::setDisplayHidden(bool displayHidden) {
    if (_displayHidden == displayHidden) {
        return;
    }
    _displayHidden = displayHidden;
    update();
}

void DlgFileModel::setDirectory(const QDir &dir) {
    if (_dir == dir) {
        return;
    }
    _dir = dir;
    update();
}