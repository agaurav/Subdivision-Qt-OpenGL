#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"
#include "ui_mainwindow.h"
class GLWidget;
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
    void on_actionLoad_Obj_triggered();

    void on_SubDivLvl_valueChanged(int arg1);

    void on_Reset_btn_clicked();

    void on_Wirefarme_chk_clicked();

    void on_Scale_mesh_valueChanged(int value);

    void on_chkShowVetices_toggled(bool checked);

    void on_chkShowEdges_toggled(bool checked);

    void on_horizontalSlider_valueChanged(int value);

    void on_chkShowVetices_2_toggled(bool checked);

    void on_spinBox_2_valueChanged(int arg1);

    void on_chkreverseNormal_clicked(bool checked);

    void on_vertexID_spinBox_valueChanged(int arg1);

    void on_free_Button_toggled(bool checked);

    void on_loose_btton_toggled(bool checked);

    void on_fixed_button_toggled(bool checked);

    void on_xRotate_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
GLWidget *currentGlWidget;
void loadFile(const QString &fileName);
};

#endif // MAINWINDOW_H
