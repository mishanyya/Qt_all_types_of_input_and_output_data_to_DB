#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QSqlDatabase" //для работы с базами данных, не забыть про QT += sql в файле .pro!
#include "QFileDialog"//для работы с диалоговыми окнами для выбора файлов на компьютере

#include "QSqlTableModel" //класс для работы с редактируемой одиночной таблицей из БД
#include "QSqlRelationalTableModel" //класс для работы с редактируемой таблицей из БД с поддержкой внешних ключей
#include "QSqlQueryModel" //класс для работы с таблицей только для чтения из БД для вывода SQL запросов

#include "QSqlQuery"//для работы с SQL запросами

#include "QTableView"//для работы с графическим выводом информации в виде таблиц

//#include "QDebug"

//

/*
#include "QtGui"





*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(connectDB())); //для выбора и подключения к базе данных
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(outputfromDB())); //для получения данных из базы данных
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(inputtoDB())); //для ввода данных в базу данных
}

MainWindow::~MainWindow()
{
    delete ui;
}

//глобальные переменные
static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//подключение драйвера для базы данных SQLite
static QString file;//адрес подключаемой базы данных
static QString filename;//имя подключаемой базы данных






//для выбора и подключения к базе данных
void MainWindow::connectDB(){
//в переменную file после выбора файла автоматически поместится его адрес
file = QFileDialog::getOpenFileName(
this,
"Выбрать файл базы данных",//заголовок открывающегося стандартного окна
"/home");//каталог, который открывается при запуске
//если прописать QDir :: currentPath (); то откроется каталог созданного приложения Qt с исполняемыми файлами программы
}

//для получения данных из БД
void MainWindow::outputfromDB(){
    //подключить БД по ее адресу на компьютере
    db.setDatabaseName(file);
    //открывает базу данных по адресу file
    db.open();



    //Код для QSqlTableModel и QSqlRelationalTableModel - таблиц с редактируемыми ячейками

    QSqlTableModel *model = new QSqlTableModel; //создается глобальный объект модели таблицы с редактируемыми ячейками
  //QSqlRelationalTableModel работает также как QSqlTableModel, но позволяет настройку внешних ключей с другими таблицами
    model->setTable("basetable");//выбирается имя существующей таблицы из БД
    //Возможны значения для редактирования записей:
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//настраивается редактирование таблицы
    //model->setEditStrategy(QSqlTableModel::OnFieldChange);//данные сохранятся в БД сразу при переходе на другую ячейку
    //model->setEditStrategy(QSqlTableModel::OnRowChange);//данные сохранятся в БД сразу при переходе на другую строку
    model->select();//заполняет модель данными из таблицы, без этого кода выйдет пустая таблица
    ui->tableView->setModel(model);//выводит в виде таблицы все элементы в окне приложения

    //Код для QSqlQueryModel - таблиц только для чтения информации через запросы SQL

    QSqlQueryModel *model1 = new QSqlQueryModel; //создается объект модели с таблицей только для чтения
   model1->setQuery("SELECT * FROM basetable");//в модель помещается результат SQL запроса к существующим в БД, таблице и полям
   ui->tableView_2->setModel(model1);//выводит в виде таблицы все элементы в окне приложения, не работает в функции main()



   ui->listView->setModel(model);//выводит в виде одного столбца значения первой колонки таблицы БД
   ui->treeView->setModel(model);//выводит в виде таблицы все значения таблицы БД
   ui->columnView->setModel(model);//выводит в виде одного столбца значения первой колонки таблицы БД, но ширину содержимого можно изменять
   ui->undoView->setModel(model);//выводит в виде одного столбца значения первой колонки таблицы БД


   //Код для для вывода в textEdit

   //создает объект для запросов SQL
   QSqlQuery query( db );

   query.exec("SELECT * FROM basetable");

   //Вывод всех значений из БД
   while (query.next())
   {
   QString value_0 = query.value(0).toString();//value(0)-элемент 0 массива вывода
   QString value_1 = query.value(1).toString();//value(1)-элемент 1 массива вывода
   QString value_2 = query.value(2).toString();//value(2)-элемент 2 массива вывода
   QString value_3 = query.value(3).toString();//value(3)-элемент 3 массива вывода
   QString value_4 = query.value(4).toString();//value(4)-элемент 4 массива вывода

   ui->textEdit->insertPlainText(value_0+" "+value_1+" "+value_2+" "+value_3+" "+value_4+"\n");//Вывод всех строк из таблицы БД
   ui->textEdit_2->append(value_0+" "+value_1+" "+value_2+" "+value_3+" "+value_4+"\n");// Выводит все строки из таблицы БД с небольшим интервалом между ними
   ui->textEdit_3->setText(value_0+" "+value_1+" "+value_2+" "+value_3+" "+value_4+"\n");// Выводит только последнюю строку из таблицы БД
   }


    //закрывает базу данных по адресу file
    db.close();
}


//для ввода данных в базу данных
void MainWindow::inputtoDB(){
    //подключить БД по ее адресу на компьютере
    db.setDatabaseName(file);
    //открывает базу данных по адресу file
    db.open();

    QString name=ui->lineEdit->text();//имя
    QString fone=ui->lineEdit_2->text();//номер телефона
    QString automodel=ui->lineEdit_3->text();//модель авто
    QString price=ui->lineEdit_4->text();//стоимость

    //создает объект для запросов SQL
    QSqlQuery query( db );

    query.prepare("INSERT INTO basetable (number,name,fone,automodel,price) VALUES (NULL,:name,:fone,:automodel,:price)");

    query.bindValue(":name", name);
    query.bindValue(":fone", fone);
    query.bindValue(":automodel", automodel);
    query.bindValue(":price", price);
    query.exec();

    //закрыть БД
    db.close();
}
