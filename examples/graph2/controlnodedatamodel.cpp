#include "controlnodedatamodel.h"

ControlNodeDataModel
::ControlNodeDataModel()
{

}

QJsonObject
ControlNodeDataModel::
save() const
{
  QJsonObject modelJson = NodeDelegateModel::save();

  return modelJson;
}


void
ControlNodeDataModel::
restore(QJsonObject const& p)
{
}


unsigned int
ControlNodeDataModel::
nPorts(PortType portType) const
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
