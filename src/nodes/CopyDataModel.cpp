#include <QtGui/QDoubleValidator>
#include <iostream>
#include "CopyDataModel.hpp"

CopyDataModel::CopyDataModel()
  :
    m_v(nullptr),
    m_cp(new QLineEdit)
{
  int margin = 12;
  int y = 0, x = 0;
  int w = m_cp->sizeHint().width()/2;
  int h = m_cp->sizeHint().height();

  auto d = new QDoubleValidator;
  d->setLocale(QLocale("en_GB"));
  m_cp->setValidator(d);
  m_cp->setMaximumSize(m_cp->sizeHint());
  m_cp->setGeometry(x, y, w, h);
  connect(m_cp, &QLineEdit::textChanged, this, &CopyDataModel::valueEdit);

  m_cp->setText("0.0");


}

CopyDataModel::~CopyDataModel()
{

}

void CopyDataModel::save(Properties &p) const
{
}

void CopyDataModel::valueEdit(QString string)
{
  m_v = std::make_shared<ScalarData>(m_cp->text().toStdString());
  emit dataUpdated(0);

}

unsigned int CopyDataModel::nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

NodeDataType CopyDataModel::dataType(PortType portType, PortIndex portIndex) const
{
  switch (portType)
  {
    case PortType::In:
      return DistanceFieldInput().type();
    break;
    case PortType::Out:
      return ScalarData().type();
    break;

    default:
      break;
  }
  return ScalarData().type();
}

std::shared_ptr<NodeData> CopyDataModel::outData(PortIndex port)
{
  if(m_v)
    return m_v;
  else
    return nullptr;

}

void CopyDataModel::setInData(std::shared_ptr<NodeData> _data, PortIndex portIndex)
{
  auto data = std::dynamic_pointer_cast<ScalarData>(_data);
  if(data) {
    m_cp->setVisible(false);
    m_cp->setText(data->value().c_str());
  } else {
    m_cp->setVisible(true);
    m_cp->setText("0.0");
  }
}

std::vector<QWidget *> CopyDataModel::embeddedWidget()
{
  return std::vector<QWidget *>{m_cp};
}

std::string CopyDataModel::getShaderCode() {
 return "";
}
