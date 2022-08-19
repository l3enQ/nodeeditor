#pragma once

#include <QtCore/QPointF>
#include <QtCore/QSize>

#include <QtNodes/StyleCollection>

#include "NodeDelegateModelRegistry.hpp"
#include "AbstractGraphModel.hpp"
#include "StyleCollection.hpp"
#include "ConnectionIdUtils.hpp"


using ConnectionId     = QtNodes::ConnectionId;
using ConnectionPolicy = QtNodes::ConnectionPolicy;
using NodeFlag        = QtNodes::NodeFlag;
using NodeId          = QtNodes::NodeId;
using NodeRole        = QtNodes::NodeRole;
using PortIndex       = QtNodes::PortIndex;
using PortRole        = QtNodes::PortRole;
using PortType        = QtNodes::PortType;
using StyleCollection = QtNodes::StyleCollection;
using QtNodes::InvalidNodeId;

namespace QtNodes
{


class NODE_EDITOR_PUBLIC BehaviorTreeGraphModel : public AbstractGraphModel
{
  Q_OBJECT
public:

  struct NodeGeometryData
  {
    QSize size;
    QPointF pos;
  };


public:

  BehaviorTreeGraphModel(std::shared_ptr<NodeDelegateModelRegistry> registry);

  ~BehaviorTreeGraphModel() override;


  std::unordered_set<NodeId>
  allNodeIds() const override;

  std::unordered_set<ConnectionId>
  allConnectionIds(NodeId const nodeId) const override;

  std::unordered_set<std::pair<NodeId, PortIndex>>
  connectedNodes(NodeId    nodeId,
                 PortType  portType,
                 PortIndex portIndex) const override;

  bool
  connectionExists(ConnectionId const connectionId) const override;

  NodeId
  addNode(QString const nodeType = QString()) override;

  /**
   * Connection is possible when graph contains no connectivity data
   * in both directions `Out -> In` and `In -> Out`.
   */
  bool
  connectionPossible(ConnectionId const connectionId) const override;

  void
  addConnection(ConnectionId const connectionId) override;

  bool
  nodeExists(NodeId const nodeId) const override;

  QVariant
  nodeData(NodeId nodeId, NodeRole role) const override;

  NodeFlags
  nodeFlags(NodeId nodeId) const override;

  bool
  setNodeData(NodeId   nodeId,
              NodeRole role,
              QVariant value) override;

  QVariant
  portData(NodeId    nodeId,
           PortType  portType,
           PortIndex portIndex,
           PortRole  role) const override;

  bool
  setPortData(NodeId    nodeId,
              PortType  portType,
              PortIndex portIndex,
              PortRole  role) const override;

  bool
  deleteConnection(ConnectionId const connectionId) override;

  bool
  deleteNode(NodeId const nodeId) override;

private:
  std::shared_ptr<NodeDelegateModelRegistry> _registry;

  std::unordered_set<NodeId> _nodeIds; // remove

  std::unordered_map<std::tuple<NodeId, PortType, PortIndex>,
                     std::unordered_set<std::pair<NodeId, PortIndex>>>
  _connectivity;

  mutable std::unordered_map<NodeId,
                             NodeGeometryData>
  _nodeGeometryData;


  unsigned int _lastNodeId;

  std::unordered_map<NodeId,
                     std::unique_ptr<NodeDelegateModel>>
  _models;

};


}
