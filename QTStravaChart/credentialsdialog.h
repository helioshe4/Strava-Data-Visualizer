#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class CredentialsDialog : public QDialog
{
    Q_OBJECT

public:
    CredentialsDialog(QWidget *parent = nullptr);

    QString getClientId() const;
    QString getClientSecret() const;
    QString getRefreshToken() const;

private:
    QLineEdit *clientIdEdit;
    QLineEdit *clientSecretEdit;
    QLineEdit *refreshTokenEdit;
    QLabel *infoLabel;
};

#endif // CREDENTIALSDIALOG_H
