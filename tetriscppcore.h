#ifndef TETRISCPPCORE_H
#define TETRISCPPCORE_H

#include <QObject>
#include <QString>

class TetrisCppCore : public QObject {
    Q_OBJECT
public:
    explicit TetrisCppCore(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TETRISCPPCORE_H
