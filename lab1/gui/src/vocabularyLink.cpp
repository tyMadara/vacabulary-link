#include "vocabularyLink.h"
#include "readFile.h"
#include "getresult.h"

vocabularyLink::vocabularyLink(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	w = false;
	c = false;
	h = -1;
	t = -1;
	n = -1;

	ui.verticalLayout->setSpacing(0);
	IniSignalSlots();
	InitButton();
	ui.textEditOut->setFocusPolicy(Qt::NoFocus);
}

vocabularyLink::~vocabularyLink() {
	for (int i = 0; i < 27; i++) {
		delete Act_T[i];
		delete Act_H[i];
	}
	delete Act_Unlimited;
	delete Act_setNum;
	delete menu_N;
}

void vocabularyLink::IniSignalSlots(){
	connect(ui.btn_OpFile, SIGNAL(triggered()), this, SLOT(onchkActionOp()));
	connect(ui.Act_output, SIGNAL(triggered()), this, SLOT(onchkActionOut()));
	connect(ui.toolButton_W, SIGNAL(clicked()), this, SLOT(onchkButtonW()));
	connect(ui.toolButton_C, SIGNAL(clicked()), this, SLOT(onchkButtonC()));
	connect(ui.Btn_out, SIGNAL(clicked()), this, SLOT(onclkoutput()));
	
	//connect(ui.Btn_setFontIn, SIGNAL(clicked()), this, SLOT(onchkButtonSetFontIn()));
	//connect(ui.Btn_setFontOut, SIGNAL(clicked()), this, SLOT(onchkButtonSetFontOut()));

	connect(ui.actionInput, SIGNAL(triggered()), this, SLOT(onchkButtonSetFontIn()));
	connect(ui.actionOutput, SIGNAL(triggered()), this, SLOT(onchkButtonSetFontOut()));
	connect(ui.Act_help, SIGNAL(triggered()), this, SLOT(ontriggeredhelp()));
}

void vocabularyLink::InitButton(){
	ui.toolButton_W->setCheckable(true);
	ui.toolButton_C->setCheckable(true);
	ui.toolButton_T->setCheckable(true);
	ui.toolButton_H->setCheckable(true);
	ui.toolButton_N->setCheckable(true);
	InitButton_H(ui.toolButton_H);
	InitButton_T(ui.toolButton_T);
	InitButton_N(ui.toolButton_N);
}

void vocabularyLink::InitButton_H(QToolButton * btn){
	QMenu *MyMenu = new QMenu();

	Act_H[0] = new QAction(tr("������"));
	MyMenu->addAction(Act_H[0]);
	connect(Act_H[0], SIGNAL(triggered()), this, SLOT(onchooseUnlimited_H()));
	for (i = 1; i <= 26; i++) {
		char c[1];
		c[0] = (char)('A' + i - 1);
		Act_H[i] = new QAction(tr(c));
		//Act_H[i]->setObjectName(tr(c));
		MyMenu->addAction(Act_H[i]);
		connect(Act_H[i], SIGNAL(triggered()), this, SLOT(onchooseAct_H()));
	}
	btn->setMenu(MyMenu);
	btn->setPopupMode(QToolButton::InstantPopup);
}

void vocabularyLink::InitButton_T(QToolButton * btn) {
	QMenu *MyMenu = new QMenu();

	Act_T[0] = new QAction(tr("������"));
	MyMenu->addAction(Act_T[0]);
	connect(Act_T[0], SIGNAL(triggered()), this, SLOT(onchooseUnlimited_T()));
	for (i = 1; i <= 26; i++) {
		char c[1];
		c[0] = (char)('A' + i - 1);
		Act_T[i] = new QAction(tr(c));
		//Act_T[i]->setObjectName(c);
		MyMenu->addAction(Act_T[i]);
		connect(Act_T[i], SIGNAL(triggered()), this, SLOT(onchooseAct_T()));
	}
	btn->setMenu(MyMenu);
	btn->setPopupMode(QToolButton::InstantPopup);
}

void vocabularyLink::InitButton_N(QToolButton * btn){
	menu_N = new QMenu();
	Act_Unlimited = new QAction(tr("������"));
	Act_setNum = new QAction(tr("����num"));
	menu_N->addAction(Act_Unlimited);
	menu_N->addAction(Act_setNum);
	btn->setMenu(menu_N);
	btn->setPopupMode(QToolButton::InstantPopup);
	connect(Act_Unlimited, SIGNAL(triggered()), this, SLOT(onchooseAct_Unlimited()));
	connect(Act_setNum, SIGNAL(triggered()), this, SLOT(onchooseAct_setNum()));
}

void vocabularyLink::onchkButtonW(){
	if (ui.toolButton_W->isChecked()) {
		if (c == true) {
			ui.toolButton_W->setChecked(true);
			w = true;
			/*QString dlgTitle = "warning";
			QString strInfo = "����������ĸ���Ʋ���ͬʱ��ѡ�У�";
			QMessageBox::warning(this, dlgTitle, strInfo);*/
			ui.toolButton_C->setChecked(false);
			c = false;
		}
		/*else if (n != -1) {
			ui.toolButton_W->setChecked(false);
			QString dlgTitle = "warning";
			QString strInfo = "����ָ��������Ŀ��Ѱ�����������";
			QMessageBox::warning(this, dlgTitle, strInfo);
		}*/
		else w = true;
	}
	else w = false;
}

void vocabularyLink::onchkButtonC() {
	if (ui.toolButton_C->isChecked()) {
		if (w == true) { 
			ui.toolButton_C->setChecked(true); 
			c = true;
			/*QString dlgTitle = "warning";
			QString strInfo = "����������ĸ���Ʋ���ͬʱ��ѡ�У�";
			QMessageBox::warning(this, dlgTitle, strInfo);*/
			ui.toolButton_W->setChecked(false);
			w = false;
		}
		/*else if (n != -1) {
			ui.toolButton_C->setChecked(false);
			QString dlgTitle = "warning";
			QString strInfo = "����ָ��������Ŀ��Ѱ�����������";
			QMessageBox::warning(this, dlgTitle, strInfo);
		}*/
		else c = true;
	}
	else c = false;
}

void vocabularyLink::onchkButtonSetFontIn(){
	QFont iniFont = ui.textEditIn->font(); //��ȡ�ı��������
	bool   ok = false;
	QFont font = QFontDialog::getFont(&ok, iniFont); //ѡ������
	if (ok) //ѡ����Ч
		ui.textEditIn->setFont(font);
}

void vocabularyLink::onchkButtonSetFontOut(){
	QFont iniFont = ui.textEditOut->font(); //��ȡ�ı��������
	bool   ok = false;
	QFont font = QFontDialog::getFont(&ok, iniFont); //ѡ������
	if (ok) //ѡ����Ч
		ui.textEditOut->setFont(font);
}

void vocabularyLink::ontriggeredhelp() {
	QString dlgTitle = "ʹ��˵��";
	QString strInfo = "W��ťѡ��Ϊ���Ұ�����൥�ʵĵ�����\n"
		"C��ťѡ��Ϊ���Ұ��������ĸ�ĵ�����\n"
		"Hѡ���Ƿ�Ե������Ŀ�ͷ��ĸ������\n"
		"Tѡ���Ƿ�Ե������Ľ�β��ĸ������\n"
		"Nѡ���Ƿ�Ե������ĵ��ʸ���������\n"
				;
	QMessageBox::information(this, dlgTitle, strInfo,
		QMessageBox::Ok, QMessageBox::NoButton);
}

void vocabularyLink::onclkoutput(){
	if (!w && !c) {
		QString dlgTitle = "����";
		QString strInfo = QString("�����ڵ������������ĸ���ѡȡһ����");
		QMessageBox::critical(this, dlgTitle, strInfo);
		ui.toolButton_W->setChecked(true);
		w = true;
		ui.toolButton_W->setFocus();
		return;
	}

	QString str = ui.textEditIn->toPlainText();

	//�ж������ʽ�Ƿ����ȷ
	QByteArray ba = str.toLatin1();
	int i = 0;
	int offset = 0;
	bool setflag = false;
	QTextCursor & tmpCursor = ui.textEditIn->textCursor();
	
	for (i = 0; i < ba.size(); i++) {
		if (!((ba.at(i) <= 90 && ba.at(i) >= 65) || (ba.at(i) <= 122 && ba.at(i) >= 97) || ba.at(i) == '\n' || ba.at(i) == ';' || ba.at(i) == ',')) {
			if(!setflag){
				QString dlgTitle = "����";
				QString strInfo = QString("���뵥�ʸ�ʽ���󣬵���ֻ���ɴ�Сд��ĸ���ɣ���ֻ���Ի��з����ֺż���Ƕ��ŷָ���");
				QMessageBox::critical(this, dlgTitle, strInfo);
			}
			setflag = true; offset++;
			continue;
		}
		else if (setflag) break;
	}
	if (setflag) { 
		tmpCursor.setPosition(i-offset, QTextCursor::MoveAnchor);
		tmpCursor.setPosition(i, QTextCursor::KeepAnchor);
		ui.textEditIn->setTextCursor(tmpCursor); 
		ui.textEditIn->setFocus();
		return; 
	}

	if (n == -1 && h != -1 && t != -1) {
		QString dlgTitle = "����";
		QString strInfo = QString("����ָ�����ʳ���n������ͬʱָ��������ͷ�͵�����β��");
		QMessageBox::critical(this, dlgTitle, strInfo);
		return;
	}

	QList <QString> lst = str.split(QRegExp("[,;\n^]"), QString::SkipEmptyParts);
	std::vector <std::string> words;
	for (const QString i : lst) {
		words.push_back(i.toStdString());
		//qDebug() << i;
	}
	
	QString strresult = QString::fromStdString(getresult(words, w, c ,h ,t ,n));
	if (strresult == "1") {
		QString dlgTitle = "����";
		QString strInfo = QString("Two much input file��");
		QMessageBox::critical(this, dlgTitle, strInfo);
		return;
	}else if (strresult == "2") {
		QString dlgTitle = "����";
		QString strInfo = QString("Not a valid character��");
		QMessageBox::critical(this, dlgTitle, strInfo);
		return;
	}else if (strresult == "3") {
		QString dlgTitle = "����";
		QString strInfo = QString("Word number should be a positive integer��");
		QMessageBox::critical(this, dlgTitle, strInfo);
		return;
	}else if (strresult == "4") {
		QString dlgTitle = "����";
		QString strInfo = QString("No input file��");
		QMessageBox::critical(this, dlgTitle, strInfo);
		return;
	}
	qDebug() << strresult;
	ui.textEditOut->setText(strresult);
	qDebug() << "W = " << w;
	qDebug() << "C = " << c;
	qDebug() << "H = " << (int)h;
	qDebug() << "T = " << (int)t;
	qDebug() << "N = " << n;
}


void vocabularyLink::onchkActionOp() {
	QString curPath = QDir::currentPath();
	QString dlgTitle = "ѡ��һ���ļ�"; 
	QString filter = "�ı��ļ�(*.txt)"; 
	QString FileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
	//qDebug() << FileName << endl;
	if (FileName == "") return;
	std::vector <std::string> words;
	bool ok = false;
	readFile(words, FileName.toStdString(), ok);
	qDebug() << ok;
	if (!ok) {
		QString dlgTitle = "����";
		QString strInfo = QString("�ļ� ") + FileName + " ��ʧ��";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	else if(words.size() == 0) {
		QString dlgTitle = "����";
		QString strInfo = QString("�ļ� ") + FileName + " ��������Ϊ0";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}else{
		QString str = "";
		for (int i = 0; i < words.size(); i++) {
			str += QString(words[i].c_str());
			str += QString("\n");
		}
		ui.textEditIn->setText(str);
	}
}

bool vocabularyLink::saveTextByIODevice(const QString &aFileName)
{ //��IODevice��ʽ�����ı��ļ�
	QFile aFile(aFileName);
	//aFile.setFileName(aFileName);
	if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;
	QString str = ui.textEditOut->toPlainText();//����������Ϊ�ַ���
	QByteArray  strBytes = str.toUtf8();//ת��Ϊ�ֽ�����
	//QByteArray  strBytes=str.toLocal8Bit();
	aFile.write(strBytes, strBytes.length());  //д���ļ�
	aFile.close();
	//ui.->setCurrentIndex(0);
	return true;
}

void vocabularyLink::onchkActionOut() {
	QString curPath = QDir::currentPath();//��ȡϵͳ��ǰĿ¼
	QString dlgTitle = "���Ϊһ���ļ�"; //�Ի������
	QString filter = "�ı��ļ�(*.txt);;�����ļ�(*.*)"; //�ļ�������
	QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
	if (aFileName.isEmpty())
		return;
	saveTextByIODevice(aFileName);
}

void vocabularyLink::onchooseAct_T() {
	QAction *act = qobject_cast<QAction*>(sender());
	for (int i = 0; i < 27; i++) {
		if (Act_T[i] == act) t = 'A' + i - 1;
	}
	ui.toolButton_T->setText(QString("T:") + QString(t));
	ui.toolButton_T->setChecked(true);
}

void vocabularyLink::onchooseAct_H() {
	QAction *act = qobject_cast<QAction*>(sender());
	for (int i = 0; i < 27; i++) {
		if (Act_H[i] == act) h = 'A' + i - 1;
	}
	ui.toolButton_H->setText(QString("H:") + QString(h));
	ui.toolButton_H->setChecked(true);
}

void vocabularyLink::onchooseUnlimited_T() {
	t = -1;
	ui.toolButton_T->setText(QString("T"));
	ui.toolButton_T->setChecked(false);
}

void vocabularyLink::onchooseAct_Unlimited(){
	n = -1;
	ui.toolButton_N->setText("N");
	ui.toolButton_N->setChecked(false);
}

void vocabularyLink::onchooseAct_setNum(){
	if (w == false || c == false) {
		QString dlgTitle = "��������";
		QString txtLabel = "���������������";
		int defaultValue = -1;
		int minValue = 1, maxValue = 50, stepValue = 1;
		bool ok = false;
		int inputValue = QInputDialog::getInt(this, dlgTitle, txtLabel,
			defaultValue, minValue, maxValue, stepValue, &ok);
		n = inputValue;
		if (ok) {
			QString value = QString::number(inputValue);
			ui.toolButton_N->setText(value);
			ui.toolButton_N->setChecked(true);
		}
	}
	else {
		ui.toolButton_N->setChecked(false);
		QString dlgTitle = "warning";
		QString strInfo = "����������ĸ���Ʋ���ͬʱ��ѡ�У�";
		QMessageBox::warning(this, dlgTitle, strInfo);
	}
}

void vocabularyLink::onchooseUnlimited_H() {
	h = -1;
	ui.toolButton_H->setText(QString("H"));
	ui.toolButton_H->setChecked(false);
}