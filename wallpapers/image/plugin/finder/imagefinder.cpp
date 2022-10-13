/*
    SPDX-FileCopyrightText: 2007 Paolo Capriotti <p.capriotti@gmail.com>
    SPDX-FileCopyrightText: 2022 Fushan Wen <qydwhotmail@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "imagefinder.h"

#include <QDir>
#include <QImageReader>

#include "findsymlinktarget.h"
#include "suffixcheck.h"

ImageFinder::ImageFinder(const QStringList &paths, QObject *parent)
    : QObject(parent)
    , m_paths(paths)
{
}

void ImageFinder::run()
{
    QStringList images;

    QDir dir;
    dir.setFilter(QDir::AllDirs | QDir::Files | QDir::Readable);
    dir.setNameFilters(suffixes());

    const auto filterCondition = [](const QFileInfo &info) {
        const QString path = info.absoluteFilePath();

        return info.baseName() != QLatin1String("screenshot") && !path.contains(QLatin1String("contents/images/"))
            && !path.contains(QLatin1String("contents/images_dark/"));
    };
    int i;

    for (i = 0; i < m_paths.size(); ++i) {
        const QString &path = m_paths.at(i);
        const QString target = findSymlinkTarget(QFileInfo(path));
        const QFileInfo info(target);

        if (!info.exists() || !filterCondition(info)) {
            // is in a package
            continue;
        }

        if (info.isFile()) {
            if (isAcceptableSuffix(info.suffix()) && !info.isSymLink()) {
                images.append(target);
            }

            continue;
        }

        dir.setPath(target);
        const QFileInfoList files = dir.entryInfoList();

        for (const QFileInfo &wp : files) {
            const QFileInfo realwp(findSymlinkTarget(wp));

            if (realwp.isFile()) {
                if (filterCondition(realwp) && !realwp.isSymLink()) {
                    images.append(realwp.filePath());
                }
            } else if (realwp.isDir()) {
                if (realwp.fileName().startsWith(QLatin1Char('.'))) {
                    continue;
                }

                // add this to the directories we should be looking at
                m_paths.append(realwp.filePath());
            }
        }
    }

    images.removeAll(QString());
    images.removeDuplicates();

    Q_EMIT imageFound(images);
}
