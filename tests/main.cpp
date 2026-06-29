/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "../src/github.h"

// Qt include.
#include <QCommandLineParser>
#include <QCoreApplication>

int main(int argc,
         char **argv)
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Check GitHub for updates"));
    parser.addHelpOption();
    QCommandLineOption user(QStringList()
                                << "u"
                                << "user",
                            QStringLiteral("User on GitHub."),
                            QStringLiteral("User name"));
    QCommandLineOption project(QStringList()
                                   << "p"
                                   << "project",
                               QStringLiteral("Project on GitHub."),
                               QStringLiteral("Project name"));
    QCommandLineOption version(QStringList()
                                   << "v"
                                   << "current-version",
                               QStringLiteral("Current version."),
                               QStringLiteral("Version"));
    parser.addOption(user);
    parser.addOption(project);
    parser.addOption(version);

    parser.process(app);

    if (!parser.isSet(user)) {
        qDebug() << "GitHub user is not defined.";

        return -1;
    }

    if (!parser.isSet(project)) {
        qDebug() << "GitHub project is not defined.";

        return -1;
    }

    if (!parser.isSet(version)) {
        qDebug() << "Current version is not defined.";

        return -1;
    }

    QString newVersionUrl;

    if (GHRelease::isUpdateAvailable(
            parser.value(user),
            parser.value(project),
            parser.value(version),
            GHRelease::majorMinorPatchCompare,
            newVersionUrl)) {
        qDebug() << "New version available at:" << newVersionUrl;
    } else {
        qDebug() << "There is no update. Latest release available at:" << newVersionUrl;
    }

    return 0;
}
