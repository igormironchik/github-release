This is a small static C++/Qt library for checking new releases of the application
on GitHub.

In the code of your application you just do something like

```cpp
struct Update {
    QString m_url;
    QString m_tag;
    bool m_available = false;
}; // struct Update

void checkForUpdates(QPromise<Update> &promise,
                     const QString &currentVersion)
{
    Update info;
    info.m_available = GHRelease::isUpdateAvailable(QStringLiteral("igormironchik"),
                                                    QStringLiteral("markdown-tools"),
                                                    currentVersion,
                                                    GHRelease::majorMinorPatchCompare,
                                                    info.m_url,
                                                    info.m_tag);

    promise.addResult(info);
}

void MainWindow::onCheckForUpdates()
{
    if (QDateTime::currentDateTime() - m_d->m_lastCheckForUpdates
            > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::hours(1))
        && !GHRelease::majorMinorPatchCompare(MdShared::c_versionNumbers, m_d->m_updatesAbailable)) {
        auto future = QtConcurrent::run(checkForUpdates, MdShared::c_versionNumbers);
        m_d->m_updateWatcher->setFuture(future);
    } else {
        onAddUpdatesButton();
    }
}

void MainWindow::onCheckForUpdatesFinished()
{
    const auto update = m_d->m_updateWatcher->result();
    m_d->m_lastCheckForUpdates = QDateTime::currentDateTime();

    if (update.m_available) {
        m_d->m_updatesAbailable = update.m_tag;
        m_d->m_updatesUrl = update.m_url;
    } else {
        m_d->m_updatesAbailable.clear();
        m_d->m_updatesUrl.clear();
    }

    saveCfg();

    onAddUpdatesButton();
}

void MainWindow::onAddUpdatesButton()
{
    if (!m_d->m_updatesAbailable.isEmpty()
        && !m_d->m_updatesUrl.isEmpty()
        && GHRelease::majorMinorPatchCompare(MdShared::c_versionNumbers, m_d->m_updatesAbailable)) {
        auto btn = new GHRelease::NewVersionAvailableButton(m_d->m_updatesUrl,
            GHRelease::NewVersionAvailableButton::OpenUrlOnClick,
            statusBar());
        btn->setMinimumHeight(m_d->m_workingDirectoryWidget->labelHeight());
        btn->setMaximumHeight(m_d->m_workingDirectoryWidget->labelHeight());
        statusBar()->addPermanentWidget(m_d->makeSeparator());
        statusBar()->addPermanentWidget(btn);
    }
}
```

`onCheckForUpdates()` invokes ones on the application startup after reading the configuration.
And when new update will be available user will see a small button in the status bar.
Clicking that button will open GitHub page with the latest release.
