/*
  TasksWindow.cpp

  This file is part of Charm, a task-based time tracking application.

  Copyright (C) 2014-2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

  Author: Frank Osterfeld <frank.osterfeld@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TasksWindow.h"
#include "ApplicationCore.h"
#include "TasksView.h"

#include <QMenuBar>

TasksWindow::TasksWindow( QWidget* parent )
    : CharmWindow( tr( "Tasks Editor" ), parent )
    , m_tasksView( new TasksView( toolBar(), this ) )
{
    setWindowNumber( 1 );
    setWindowIdentifier( QLatin1String( "window_tasks" ) );
    setCentralWidget( m_tasksView );
    setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    connect( m_tasksView, SIGNAL(emitCommand(CharmCommand*)),
             SIGNAL(emitCommand(CharmCommand*)) );
    connect( m_tasksView, SIGNAL(emitCommandRollback(CharmCommand*)),
             SIGNAL(emitCommandRollback(CharmCommand*)) );
    connect( m_tasksView, SIGNAL(saveConfiguration()),
             SIGNAL(saveConfiguration()) );
}

TasksWindow::~TasksWindow()
{
}

void TasksWindow::stateChanged( State previous )
{
    CharmWindow::stateChanged( previous );
    m_tasksView->stateChanged( previous );

    if ( ApplicationCore::instance().state() == Connecting ) {
        m_tasksView->setModel( & ApplicationCore::instance().model() );
    }
}

void TasksWindow::restore()
{
    show();
}

void TasksWindow::configurationChanged()
{
    CharmWindow::configurationChanged();
    m_tasksView->configurationChanged();
}

void TasksWindow::insertEditMenu()
{
    QMenu* editMenu = menuBar()->addMenu( tr( "Edit" ) );
    m_tasksView->populateEditMenu( editMenu);
}

void TasksWindow::sendCommand( CharmCommand* )
{
    Q_ASSERT( false ); // should not be called
}

void TasksWindow::sendCommandRollback( CharmCommand* )
{
    Q_ASSERT( false ); // should not be called
}

void TasksWindow::commitCommand( CharmCommand* )
{
}

#include "moc_TasksWindow.cpp"
