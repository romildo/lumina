//===========================================
//  Lumina-DE source code
//  Copyright (c) 2016, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#ifndef _LUMINA_ARCHIVER_MAIN_UI_H
#define _LUMINA_ARCHIVER_MAIN_UI_H

#include <QMainWindow>
#include <QString>
#include <QTreeWidgetItem>

#include "TarBackend.h"

namespace Ui{
	class MainUI;
};

class MainUI : public QMainWindow{
	Q_OBJECT
public:
	MainUI();
	~MainUI();

	void LoadArguments(QStringList);
	void loadIcons();

private:
	Ui::MainUI *ui;
	Backend *BACKEND;

	QTreeWidgetItem* findItem(QString path, QTreeWidgetItem *start = 0);
	bool cleanItems(QStringList list, QTreeWidgetItem *start = 0); //returns true if anything gets cleaned

	//Functions for setting the valid file extensions ("tar" limitations)
	QString CreateFileTypes();
        QString OpenFileTypes();

private slots:
	void NewArchive();
	void OpenArchive();
	void addFiles();
	void addDirs();
	void remFiles();
	void extractFiles();
	void ViewFile(QTreeWidgetItem *it);
	void UpdateTree();

	
	//Backend Handling
	void ProcStarting();
	void ProcFinished();
	void ProcUpdate(int percent, QString txt);

};

#endif
