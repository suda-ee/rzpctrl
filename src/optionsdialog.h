////////////////////////////////////////////////////////////////////////
// Copyright 2009 Hertz Laboratory.
// Copyright 2009 Hollywell Corporation.
// $Id: optionsdialog.h 153 2009-12-13 05:14:19Z cai $
// $URL: svn://land.rf/projects/TerrainMast/trunk/src/TerrainMast/optionsdialog.h $
// Purpose: 
////////////////////////////////////////////////////////////////////////

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include "ui_optionsdialog.h"

class OptionsDialog : public QDialog
{
	Q_OBJECT

public:
	OptionsDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OptionsDialog();

public slots:
	void changeStyle(const QString & styleName);
	//void accept();

private:
	Ui::OptionsDialog ui;
};

#endif // OPTIONSDIALOG_H
