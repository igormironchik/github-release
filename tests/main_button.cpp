/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "../src/github.h"

// Qt include.
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc,
         char **argv)
{
    QApplication app(argc, argv);

    QWidget w;
    w.resize(100, 100);
    auto l = new QVBoxLayout(&w);
    GHRelease::NewVersionAvailableButton btn(QStringLiteral("www.google.com"),
                                             GHRelease::NewVersionAvailableButton::OpenUrlOnClick,
                                             &w);
    l->addWidget(&btn);
    w.show();

    return QApplication::exec();
}
