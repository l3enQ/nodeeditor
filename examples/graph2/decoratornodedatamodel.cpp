#include "decoratornodedatamodel.h"

DecoratorNodeDataModel::
DecoratorNodeDataModel()
{

}

QJsonObject
DecoratorNodeDataModel::
save() const
{
  QJsonObject modelJson = NodeDelegateModel::save();

  return modelJson;
}


void
DecoratorNodeDataModel::
restore(QJsonObject const& p)
{
}


unsigned int
DecoratorNodeDataModel::
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
