/***************************************************************************
 *   Copyright (C) 2009 by the Quassel Project                             *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "coreconnectionstatuswidget.h"

#include "client.h"
#include "coreconnection.h"
#include "iconloader.h"

CoreConnectionStatusWidget::CoreConnectionStatusWidget(CoreConnection *connection, QWidget *parent)
  : QWidget(parent),
  _coreConnection(connection)
{
  ui.setupUi(this);
  update();

  connect(coreConnection(), SIGNAL(progressTextChanged(QString)), ui.messageLabel, SLOT(setText(QString)));
  connect(coreConnection(), SIGNAL(progressValueChanged(int)), ui.progressBar, SLOT(setValue(int)));
  connect(coreConnection(), SIGNAL(progressRangeChanged(int, int)), ui.progressBar, SLOT(setRange(int, int)));
  connect(coreConnection(), SIGNAL(progressRangeChanged(int, int)), this, SLOT(progressRangeChanged(int, int)));

  connect(coreConnection(), SIGNAL(connectionError(QString)), ui.messageLabel, SLOT(setText(QString)));
}

void CoreConnectionStatusWidget::update() {
  CoreConnection *conn = coreConnection();
  if(conn->progressMaximum() >= 0) {
    ui.progressBar->setMinimum(conn->progressMinimum());
    ui.progressBar->setMaximum(conn->progressMaximum());
    ui.progressBar->setValue(conn->progressValue());
    ui.progressBar->show();
  } else
    ui.progressBar->hide();

  ui.messageLabel->setText(conn->progressText());

}

void CoreConnectionStatusWidget::progressRangeChanged(int min, int max) {
  Q_UNUSED(min)
  ui.progressBar->setVisible(max >= 0);
}