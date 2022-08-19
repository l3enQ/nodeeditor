#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::ConnectionPolicy;

class DecoratorNodeDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    DecoratorNodeDataModel();

    virtual
    ~DecoratorNodeDataModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Decorator"); }

  bool
  captionVisible() const override
  { return true; }

  QString
  name() const override
  { return QStringLiteral("Decorator"); }

public:

  QJsonObject
  save() const override;

  void
  restore(QJsonObject const& p) override;

public:

  unsigned int
  nPorts(PortType portType) const override;

  ConnectionPolicy
  portOutConnectionPolicy(PortIndex) const override
  {
    return ConnectionPolicy::One;
  }

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override
  {return {"",""};}

  std::shared_ptr<NodeData>
  outData(PortIndex port) override
  {return nullptr;}

  void
  setInData(std::shared_ptr<NodeData>, PortIndex) override
  {}

  QWidget*
  embeddedWidget() override { return nullptr; }

};
