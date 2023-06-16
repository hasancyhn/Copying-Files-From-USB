#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_yenile_clicked();                     // Flash belleklerin yenile butonuna basılmadan direkt olarak comboBox'da görünmesi için bu fonksiyon çalıştırılır.
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_yenile_clicked()
{
    QMessageBox::information(this,"BİLGİ","Sistem yükleniyor, lütfen bekleyiniz.", "TAMAM");
    ui->comboBox->clear();                              // ComboBox'daki verileri temizler.
    QString komut;                                      // QString sınıfından "command" adında bir değişken oluşturduk.
    komut = "ls /media/root";                           // Takılan flash bellekleri bu konumda arar.
    QProcess deviceName;                                // QProcess sınıfından deviceName adında bir değişken oluşturduk.
    deviceName.start(komut,QProcess::ReadOnly);         // Takılan cihazı okuma modunda başlatıyoruz.
    deviceName.waitForFinished();                       // komut yolunda bulunanları okuma modunda açılmasını sağlar.
    QString output(deviceName.readAllStandardOutput()); // readAllStandartdOutput sayesinde sistemin çıktısından elde edilen verileri QByteArray'e çevirir.
    QStringList deviceList;                             // QStringList sınıfından "deviceList" adında bir değişken oluşturuldu. (Dizelerin bir listesini sağlar.)
    deviceList=output.split("\n");                      // Takılan cihaz birden fazla ise "/n" sayesinde bir alt satıra geçerek cihaz isimlerinin karışıklığı önlenmiş olacak.
    ui->comboBox->addItems(deviceList);                 // comboBox'ın içine takılan cihazların isimleri ekleniyor.
    ui->statusbar->clearMessage();                      // Yenile butonuna basıldığında statusbar'da bulunan dosya veyahut klasör yolu temizlenecek.
    ui->label_dosya_yolu->clear();                      // label_dosya_yolu kısmında yer ala dosya veyhaut klasör yolu temizlenecek.
}


void MainWindow::on_pushButton_baslat_clicked()
{
    if(ui->comboBox->currentText().isEmpty()){                  // Anlık olarak comboBox'ın içinin boş olup olmadığını kontrol ediyor boşsa uyarı mesajı veriyor.
        QMessageBox::warning(this, "UYARI", "Flash Bellek Bulunamadı.", "TAMAM");
    }
    else{
        QString deviceNameSTRING = ui->comboBox->currentText(); // comboBox'daki USB'lerin ismini hafızada tutuyoruz.
        QProcess myProcess;
        QString path1 = ui->label_dosya_yolu->text();           // label_dosya_yolu'ndaki dosya yolunu hafızaya alıyoruz.
        QString path2 = " /media/root/"+ deviceNameSTRING;      // USB'lerin bulunduğu yer ile USB'lerin isimlerini birleştiriyoruz.
        QString path3 = "cp -r " + path1 + path2;               // Kopyalama komutuyla path1 ve path2'yi birleştiriyoruz sebebi ise aşağıdaki .start() argümanının kullanım şeklinin bu şekilde olması.
        myProcess.start(path3);                                 // Kopyalama işlemini gerçekleştiriyoruz.
        myProcess.waitForFinished();                            // Kopyalama işleminin bitmesini sağlar. İşlem tamamlandıysa "true" değer döndürür.
        if(!ui->label_dosya_yolu->text().isEmpty()){
            QMessageBox::information(this,"BİLGİ","İşlem başarılı.","TAMAM");
        }
        ui->label_dosya_yolu->clear();
    }
}

void MainWindow::on_pushButton_dosya_ac_clicked()
{
    QString yol = QFileDialog::getSaveFileName(this,"Dosya seç!");          // DOSYA seçimi yapıyoruz.
    ui->label_dosya_yolu->setText(yol);                 // Seçilen dosyanın yolu label_dosya_yolu'na aktarılıyor böylelikle başlat butonuna bastığımızda burdaki yolu çekiyor.
    if(ui->label_dosya_yolu->text().isEmpty()){         // Eğer dosya seçildiyse...
        QMessageBox::warning(this,"UYARI","Dosya seçilmedi!","TAMAM");
    }
}

void MainWindow::on_pushButton_klasor_ac_clicked()
{
    QString yol = QFileDialog::getExistingDirectory(this,"Klasör seç!");    // KLASÖR seçimi yapıyoruz.
    ui->label_dosya_yolu->setText(yol);                 // Seçilen klasörün yolu label_dosya_yolu'na aktarılıyor böylelikle başlat butonuna bastığımızda burdaki yolu çekiyor.
    if(ui->label_dosya_yolu->text().isEmpty()){         // Eğer dosya seçildiyse...
        QMessageBox::warning(this,"UYARI","Klasör seçilmedi!","TAMAM");
    }
}

void MainWindow::on_pushButton_kapat_clicked()
{
    close();
}
