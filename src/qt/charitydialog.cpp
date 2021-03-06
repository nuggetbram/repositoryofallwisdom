#include "charitydialog.h"
#include "ui_charitydialog.h"

#include "walletmodel.h"
#include "base58.h"
#include "addressbookpage.h"
#include "init.h"

#include <QMessageBox>
#include <QLineEdit>

StakeForCharityDialog::StakeForCharityDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StakeForCharityDialog),
	 model(0)
{
    ui->setupUi(this);
}

StakeForCharityDialog::~StakeForCharityDialog()
{
    delete ui;
}

void StakeForCharityDialog::setModel(WalletModel *model)
{
	this->model = model;
	
	CBitcoinAddress strAddress;
	CBitcoinAddress strChangeAddress;
	int nPer;
	int64 nMin;
	int64 nMax;
	
	//model->getStakeForCharity(nPer, strAddress, strChangeAddress, nMin, nMax);
	/*
	if (strAddress.IsValid() && nPer > 0 )
	{
		ui->charityAddressEdit->setText(strAddress.ToString().c_str());
		ui->charityPercentEdit->setText(QString::number(nPer));
		if (strChangeAddress.IsValid())
			ui->charityChangeAddressEdit->setText(strChangeAddress.ToString().c_str());
		if (nMin > 0  && nMin != MIN_TX_FEE)
			ui->charityMinEdit->setText(QString::number(nMin/COIN));
		if (nMax > 0 && nMax != MAX_MONEY)
		ui->charityMaxEdit->setText(QString::number(nMax/COIN));	
        ui->message->setProperty("status", "ok");
        ui->message->style()->polish(ui->message);
		ui->message->setText(tr("You are now giving to\n") + strAddress.ToString().c_str() + tr("."));
	}*/
}

void StakeForCharityDialog::setAddress(const QString &address)
{
	setAddress(address, ui->charityAddressEdit);
}

void StakeForCharityDialog::setAddress(const QString &address, QLineEdit *addrEdit)
{
	addrEdit->setText(address);
	addrEdit->setFocus();
}

void StakeForCharityDialog::on_addressBookButton_clicked()
{
    if (model && model->getAddressTableModel())
    {
        AddressBookPage dlg(AddressBookPage::ForSending, AddressBookPage::SendingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec())
			setAddress(dlg.getReturnValue(), ui->charityAddressEdit);
    }
}

void StakeForCharityDialog::on_changeAddressBookButton_clicked()
{
	if (model && model->getAddressTableModel())
	{
		AddressBookPage dlg(AddressBookPage::ForSending, AddressBookPage::ReceivingTab, this);
		dlg.setModel(model->getAddressTableModel());
		//if (dlg.exec())
			//setAddress(dlg.getReturnValue(), ui->charityChangeAddressEdit);
	}
}

void StakeForCharityDialog::on_enableButton_clicked()
{
  /*  if(model->getEncryptionStatus() == WalletModel::Locked)
    {
        ui->message->setProperty("status", "");
        ui->message->style()->polish(ui->message);
        ui->message->setText(tr("Please unlock wallet before starting stake for charity."));
        return;
    }

    bool fValidConversion = false;
    int64 nMinAmount = MIN_TXOUT_AMOUNT;
    int64 nMaxAmount = MAX_MONEY;
	CBitcoinAddress changeAddress = "";

    CBitcoinAddress address = ui->charityAddressEdit->text().toStdString();
    if (!address.IsValid())
    {
        ui->message->setProperty("status", "error");
        ui->message->style()->polish(ui->message);
        ui->message->setText(tr("The entered address:\n") + ui->charityAddressEdit->text() + tr(" is invalid.\nPlease check the address and try again."));
        ui->charityAddressEdit->setFocus();
        return;
    }

    int nCharityPercent = ui->charityPercentEdit->text().toInt(&fValidConversion, 10);
    if (!fValidConversion || nCharityPercent > 50 || nCharityPercent <= 0)
    {
        ui->message->setProperty("status", "error");
        ui->message->style()->polish(ui->message);
        ui->message->setText(tr("Please Enter 1 - 50 for percent."));
        ui->charityPercentEdit->setFocus();
        return;
    }

    if (!ui->charityMinEdit->text().isEmpty())
    {
        nMinAmount = ui->charityMinEdit->text().toDouble(&fValidConversion) * COIN;
        if(!fValidConversion || nMinAmount <= MIN_TXOUT_AMOUNT || nMinAmount >= MAX_MONEY  )
        {
            ui->message->setProperty("status", "error");
            ui->message->style()->polish(ui->message);
            ui->message->setText(tr("Min Amount out of Range, please re-enter."));
            ui->charityMinEdit->setFocus();
            return;
        }
    }

    if (!ui->charityMaxEdit->text().isEmpty())
    {
        nMaxAmount = ui->charityMaxEdit->text().toDouble(&fValidConversion) * COIN;
        if(!fValidConversion || nMaxAmount <= MIN_TXOUT_AMOUNT || nMaxAmount >= MAX_MONEY  )
        {
            ui->message->setProperty("status", "error");
            ui->message->style()->polish(ui->message);
            ui->message->setText(tr("Max Amount out of Range, please re-enter."));
            ui->charityMaxEdit->setFocus();
            return;
        }
    }

        if (nMinAmount >= nMaxAmount)
    {
        ui->message->setProperty("status", "error");
            ui->message->style()->polish(ui->message);
        ui->message->setText(tr("Min Amount > Max Amount, please re-enter."));
        ui->charityMinEdit->setFocus();
        return;
    }

    if (!ui->charityChangeAddressEdit->text().isEmpty())
    {
        changeAddress = ui->charityChangeAddressEdit->text().toStdString();
        if (!changeAddress.IsValid())
        {
            ui->message->setProperty("status", "error");
            ui->message->style()->polish(ui->message);
            ui->message->setText(tr("The entered change address:\n") + ui->charityChangeAddressEdit->text() + tr(" is invalid.\nPlease check the address and try again."));
            ui->charityChangeAddressEdit->setFocus();
            return;
        }
        else if (!model->isMine(changeAddress))
        {
           ui->message->setProperty("status", "error");
            ui->message->style()->polish(ui->message);
           ui->message->setText(tr("The entered change address:\n") + ui->charityChangeAddressEdit->text() + tr(" is not owned.\nPlease check the address and try again."));
           ui->charityChangeAddressEdit->setFocus();
           return;
        }
    }

    model->setStakeForCharity(true, nCharityPercent, address, changeAddress, nMinAmount, nMaxAmount);
    ui->message->setProperty("status", "ok");
    ui->message->style()->polish(ui->message);
    ui->message->setText(tr("You are now sending to\n") + QString(address.ToString().c_str()) + tr("."));
    return;*/
}

void StakeForCharityDialog::on_disableButton_clicked()
{
 /*   int nCharityPercent = 0;
    CBitcoinAddress address = "";
	CBitcoinAddress changeAddress = "";
    int64 nMinAmount = MIN_TXOUT_AMOUNT;
    int64 nMaxAmount = MAX_MONEY;

    model->setStakeForCharity(false, nCharityPercent, address, changeAddress, nMinAmount, nMaxAmount);
    ui->charityAddressEdit->clear();
	ui->charityChangeAddressEdit->clear();
    ui->charityMaxEdit->clear();
    ui->charityMinEdit->clear();
    ui->charityPercentEdit->clear();
    ui->message->setProperty("status", "");
    ui->message->style()->polish(ui->message);
    ui->message->setText(tr("Stake For Charity is now off"));
    return;*/
}
