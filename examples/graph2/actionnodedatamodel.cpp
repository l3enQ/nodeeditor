#include "actionnodedatamodel.h"

ActionNodeDataModel::
ActionNodeDataModel()
{

}

QJsonObject
ActionNodeDataModel::
save() const
{
  QJsonObject modelJson = NodeDelegateModel::save();

  return modelJson;
}


void
ActionNodeDataModel::
restore(QJsonObject const& p)
{
}


unsigned int
ActionNodeDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}

