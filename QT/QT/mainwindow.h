#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_COPY_BUTTON_clicked();

    void on_CLOSE_COPY_LABEL_clicked();

    void on_BROWSE_BUTTON_clicked();

    void on_BACK_BROWSE_BUTTON_clicked();



    void on_OK_COPY_BUTTON_clicked();

    void on_Most_follower_button_clicked();

    void on_most_active_clicked();

    void on_mutual_followers_clicked();

    void on_suggestions_clicked();

    void on_dropdown_currentTextChanged(const QString &arg1);

    void on_back_button_clicked();

    void on_back_button_2_clicked();

    void on_most_follower_clicked();

    void on_Search_Back_clicked();

    void on_SearchByTopic_clicked();

    void on_SearchBack_clicked();

    void on_SearchByWord_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
