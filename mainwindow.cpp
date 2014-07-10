#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    currentGlWidget = new GLWidget(0, 0);
    QColor clearColor;
    clearColor.setHsv( 255,255, 163);
    //currentGlWidget->setClearColor(Qt::white);
 //   currentGlWidget->rotateBy(+42 * 16, +42 * 16, -21 * 16);

//currentGlWidget->setParent(ui->widget);



    ui->setupUi(this);
    currentGlWidget->setParent(ui->glWidget_win);
    ui->vertexID_spinBox->setRange(0,currentGlWidget->vCount-1);
    ui->vCount_label->setText(QString::number(currentGlWidget->vCount));
    ui->tCount_label->setText(QString::number(currentGlWidget->fCount));
on_vertexID_spinBox_valueChanged(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Obj_triggered()
{
    QString selfilter = tr("Obj (*.obj)");
    QString fileName = QFileDialog::getOpenFileName(
            this
            ,tr("Open model obj file"),QDir::currentPath()
            ,
            tr("Obj files (*.obj)" ),
            &selfilter
    );
    //QString fileName = QFileDialog::getOpenFileName(this,);
    if (!fileName.isEmpty())
        currentGlWidget->loadNewMesh(fileName.toStdString().c_str(),4);
    ui->vertexID_spinBox->setRange(0,currentGlWidget->vCount-1);
}

void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
}

void MainWindow::on_SubDivLvl_valueChanged(int arg1)
{
    currentGlWidget->setSubDivLvl(arg1);
    ui->vertexID_spinBox->setRange(0,currentGlWidget->vCount-1);
    ui->vCount_label->setText(QString::number(currentGlWidget->vCount));
    ui->tCount_label->setText(QString::number(currentGlWidget->fCount));
}

void MainWindow::on_Reset_btn_clicked()
{

}

void MainWindow::on_Wirefarme_chk_clicked()
{
    currentGlWidget->toggleWireFrame();

}

void MainWindow::on_Scale_mesh_valueChanged(int value)
{
    if(value > 10 )
    {currentGlWidget->setMeshScale((float)(value - 9));}
     else if(value < 10)   {currentGlWidget->setMeshScale(((float)value)/10);}
         else {
             currentGlWidget->setMeshScale(1.0);
         }

}

void MainWindow::on_chkShowVetices_toggled(bool checked)
{
    currentGlWidget->toggleShowVertices();
}


void MainWindow::on_chkShowEdges_toggled(bool checked)
{
    currentGlWidget->toggleShowEdges();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
currentGlWidget->setLineWidth(value);
}

void MainWindow::on_chkShowVetices_2_toggled(bool checked)
{


}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{

}

void MainWindow::on_chkreverseNormal_clicked(bool checked)
{
    currentGlWidget->setReverseNormal(checked);
}


void MainWindow::on_vertexID_spinBox_valueChanged(int arg1)
{
    switch (currentGlWidget->getVertexState(arg1)) {
    case FREE:
ui->free_Button->setChecked(true);
ui->loose_btton->setChecked(false);
ui->fixed_button->setChecked(false);
        break;
    case LOOSE:
        ui->free_Button->setChecked(false);
        ui->loose_btton->setChecked(true);
        ui->fixed_button->setChecked(false);
        break;
    case FIXED:
        ui->free_Button->setChecked(false);
        ui->loose_btton->setChecked(false);
        ui->fixed_button->setChecked(true);
break;
    default:
        break;
    }
}


void MainWindow::on_free_Button_toggled(bool checked)
{
    if(checked)
    currentGlWidget->setVertexState(ui->vertexID_spinBox->value(),FREE);
}

void MainWindow::on_loose_btton_toggled(bool checked)
{
    if(checked)
    currentGlWidget->setVertexState(ui->vertexID_spinBox->value(),LOOSE);
}

void MainWindow::on_fixed_button_toggled(bool checked)
{
    if(checked)
    currentGlWidget->setVertexState(ui->vertexID_spinBox->value(),FIXED);
}

void MainWindow::on_xRotate_valueChanged(int value)
{
    currentGlWidget->setRotate(PI*((float)value),currentGlWidget->rotate.y,currentGlWidget->rotate.z);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    currentGlWidget->setRotate(currentGlWidget->rotate.x,PI*((float)value),currentGlWidget->rotate.z);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    currentGlWidget->setRotate(currentGlWidget->rotate.x,currentGlWidget->rotate.y,PI*((float)value));
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
currentGlWidget->setTranslate((float)arg1,currentGlWidget->translate.y,currentGlWidget->translate.z);
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    currentGlWidget->setTranslate(currentGlWidget->translate.x,(float)arg1,currentGlWidget->translate.z);
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
currentGlWidget->setTranslate(currentGlWidget->translate.x,currentGlWidget->translate.y,(float)arg1);
}
