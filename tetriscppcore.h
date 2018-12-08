#ifndef TETRISCPPCORE_H
#define TETRISCPPCORE_H

#include <QObject>
#include <QString>

class TetrisCppCore : public QObject {
    Q_OBJECT
public:
    explicit TetrisCppCore(QObject *parent = nullptr);

signals:
    void setText(QString text);

public slots:
    void onTextChange(QString text) {emit setText(text);}
};

#endif // TETRISCPPCORE_H
