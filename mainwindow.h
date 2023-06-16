#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QFileDialog>
#include <QMessageBox>
#include <QFrame>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QProcess>
#include <QIODevice>
#include <QDataStream>
#include <QFont>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_yenile_clicked();

    void on_pushButton_baslat_clicked();

    void on_pushButton_dosya_ac_clicked();

    void on_pushButton_klasor_ac_clicked();

    void on_pushButton_kapat_clicked();

private:
    Ui::MainWindow *ui;
    QString dosya_yolu;         // Bu veriye her yerden ulaşabilmek için bu işlemi gerçekleştirdik.
    QString yol;
};

#endif // MAINWINDOW_H
