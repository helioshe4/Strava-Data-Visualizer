#include "credentialsdialog.h"

#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>

CredentialsDialog::CredentialsDialog(QWidget *parent)
    : QDialog(parent),
      clientIdEdit(new QLineEdit(this)),
      clientSecretEdit(new QLineEdit(this)),
      refreshTokenEdit(new QLineEdit(this)),
      infoLabel(new QLabel("Enter your Strava API credentials.", this))

{
    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(infoLabel);
    layout->addRow("Client ID:", clientIdEdit);
    layout->addRow("Client Secret:", clientSecretEdit);
    layout->addRow("Refresh Token:", refreshTokenEdit);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttons);
}

QString CredentialsDialog::getClientId() const
{
    return clientIdEdit->text();
}

QString CredentialsDialog::getClientSecret() const
{
    return clientSecretEdit->text();
}

QString CredentialsDialog::getRefreshToken() const
{
    return refreshTokenEdit->text();
}


