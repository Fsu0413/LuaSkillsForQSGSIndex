#include <git2.h>
#include "git.h"

#include <QDir>
#include <QMessageBox>

void e(int error) {
    if (error < 0)
        throw error;
}

bool GitManager::clone() {
    // @#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()

    QDir dir("git");
    if (dir.exists()) {
        if (!dir.removeRecursively()) {
            QMessageBox::critical(NULL, QObject::tr("Error!"), QObject::tr("The folder \"git\" is not avaliable, please check again for the permissions."));
            return false;
        }
    }

    git_repository *repo = NULL;
    try {
        e(git_clone(&repo, "https://gitcafe.com/Fsu0413/LuaSkillsForQSGSIndexTest", "git", NULL));
        git_repository_free(repo);
    }
    catch (int error) {
        const git_error *err = giterr_last();
        if (err != NULL)
            QMessageBox::critical(NULL, QObject::tr("libgit Error!"), QObject::tr("Error code:") + QString::number(error) + "\n" +
            QString::number(err->klass) + "\t" + QString(err->message));
        else
            QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Unknown Error"));

        giterr_clear();
        git_repository_free(repo);
        return false;
    }
    return true;
}

bool GitManager::pull() {
    // @#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()

    QDir dir("git/.git");
    if (!dir.exists()) {
        QMessageBox::critical(NULL, QObject::tr("Error!"), QObject::tr("The folder \"git\" is not a git folder, please check again for the permissions."));
        return false;
    }
    
    git_repository *repo = NULL;
    git_remote *remote = NULL;
    git_merge_head *merge_head = NULL;
    try {
        e(git_repository_open(&repo, "git"));
        e(git_remote_load(&remote, repo, "origin"));
        e(git_remote_connect(remote, GIT_DIRECTION_FETCH));
        int connected = git_remote_connected(remote);
        if (connected)
            e(git_remote_fetch(remote, NULL, NULL));

        git_checkout_options checkout_opt = GIT_CHECKOUT_OPTIONS_INIT;
        checkout_opt.checkout_strategy = GIT_CHECKOUT_FORCE;
        checkout_opt.file_mode = 0644;

        git_merge_options merge_opt = GIT_MERGE_OPTIONS_INIT;
        merge_opt.file_favor = GIT_MERGE_FILE_FAVOR_THEIRS;

        
        const git_remote_head **head = NULL;
        size_t size = 0;
        e(git_remote_ls(&head, &size, remote));
        if (size <= 0)
            e(-1);

        git_oid oid = head[0]->oid;

        e(git_merge_head_from_fetchhead(&merge_head, repo, "master", git_remote_url(remote), &oid));
        e(git_merge(repo, (const git_merge_head **)(&merge_head), 1, &merge_opt, &checkout_opt));

        git_merge_head_free(merge_head);
        git_remote_free(remote);
        git_repository_free(repo);
    }
    catch (int error) {
        const git_error *err = giterr_last();
        if (err != NULL)
            QMessageBox::critical(NULL, QObject::tr("libgit Error!"), QObject::tr("Error code:") + QString::number(error) + "\n" +
            QString::number(err->klass) + "\t" + QString(err->message));
        else
            QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Unknown Error"));

        giterr_clear();
        git_merge_head_free(merge_head);
        git_remote_free(remote);
        git_repository_free(repo);
        return false;
    }
    return true;
}
/*
bool GitManager::checkoutHead() {
    // @#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()@#$%^&*()

    QDir dir("git/.git");
    if (!dir.exists()) {
        QMessageBox::critical(NULL, QObject::tr("Error!"), QObject::tr("The folder \"git\" is not a git folder, please check again for the permissions."));
        return false;
    }

    git_repository *repo = NULL;


    try {
        e(git_repository_open(&repo, "git"));
        int branch = git_checkout_head(repo, &opt);
        if (branch != GIT_EUNBORNBRANCH)
            e(branch);

        git_repository_free(repo);
    }
    catch (int error) {
        const git_error *err = giterr_last();
        if (err != NULL)
            QMessageBox::critical(NULL, QObject::tr("libgit Error!"), QObject::tr("Error code:") + QString::number(error) + "\n" +
            QString::number(err->klass) + "\t" + QString(err->message));
        else
            QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Unknown Error"));

        giterr_clear();
        git_repository_free(repo);
        return false;
    }
    return true;
}
*/